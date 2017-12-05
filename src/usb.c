/*
  Copyright (c) 2017 Jean THOMAS.
  
  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software
  is furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <unicore-mx/usbd/usbd.h>
#include <unicore-mx/usbd/class/msc.h>

#include "flash.h"
#include "usb.h"

#define MSC_IN_EP 0x01
#define MSC_OUT_EP 0x82
#define MSC_EP_SIZE 64
#define SECTOR_SIZE 512

static usbd_device *g_usbd_device;
static usbd_msc *g_usbd_msc;
static const flash_driver_t *g_flash_driver = NULL;

static int usb_write_callback(const usbd_msc_backend *backend, uint32_t lba,
			      const void *buffer);
static int usb_read_callback(const usbd_msc_backend *backend, uint32_t lba,
			     void *buffer);
static int usb_format_callback(const usbd_msc_backend *backend);

static const struct usb_string_descriptor string_lang_list = {
  .bLength = USB_DT_STRING_SIZE(1),
  .bDescriptorType = USB_DT_STRING,
  .wData = {
    USB_LANGID_ENGLISH_UNITED_STATES
  }
};

static const struct usb_string_descriptor string_0 = {
  .bLength = USB_DT_STRING_SIZE(16),
  .bDescriptorType = USB_DT_STRING,
  /* Mad Resistor LLP */
  .wData = {
    0x004d, 0x0061, 0x0064, 0x0020, 0x0052, 0x0065, 0x0073, 0x0069,
    0x0073, 0x0074, 0x006f, 0x0072, 0x0020, 0x004c, 0x004c, 0x0050
  }
};

static const struct usb_string_descriptor string_1 = {
  .bLength = USB_DT_STRING_SIZE(8),
  .bDescriptorType = USB_DT_STRING,
  /* MSC Demo */
  .wData = {
    0x004d, 0x0053, 0x0043, 0x0020, 0x0044, 0x0065, 0x006d, 0x006f
  }
};

static const struct usb_string_descriptor string_2 = {
  .bLength = USB_DT_STRING_SIZE(4),
  .bDescriptorType = USB_DT_STRING,
  /* DEMO */
  .wData = {
    0x0044, 0x0045, 0x004d, 0x004f
  }
};

static const struct usb_string_descriptor **string_data[1] = {
  (const struct usb_string_descriptor *[]){&string_0, &string_1, &string_2},
};

static const struct usbd_info_string string = {
  .lang_list = &string_lang_list,
  .count = 3,
  .data = string_data
};

static const struct __attribute__((packed)) {
  struct usb_config_descriptor desc;
  struct usb_interface_descriptor msc_iface;
  struct usb_endpoint_descriptor msc_endp[2];
} config_descr = {
  .desc = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = sizeof(config_descr),
    .bNumInterfaces = 1,
    .bConfigurationValue = 1,
    .iConfiguration = 0,
    .bmAttributes = 0x80,
    .bMaxPower = 0x32
  },
  
  .msc_iface = {
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 0,
    .bAlternateSetting = 0,
    .bNumEndpoints = 2,
    .bInterfaceClass = USB_CLASS_MSC,
    .bInterfaceSubClass = USB_MSC_SUBCLASS_SCSI,
    .bInterfaceProtocol = USB_MSC_PROTOCOL_BBB,
    .iInterface = 0
  },
  
  .msc_endp = {{
      .bLength = USB_DT_ENDPOINT_SIZE,
      .bDescriptorType = USB_DT_ENDPOINT,
      .bEndpointAddress = 0x01,
      .bmAttributes = USB_ENDPOINT_ATTR_BULK,
      .wMaxPacketSize = 64,
      .bInterval = 0,
    }, {
      .bLength = USB_DT_ENDPOINT_SIZE,
      .bDescriptorType = USB_DT_ENDPOINT,
      .bEndpointAddress = 0x82,
      .bmAttributes = USB_ENDPOINT_ATTR_BULK,
      .wMaxPacketSize = 64,
      .bInterval = 0,
    }}
};

static const struct usb_device_descriptor dev_descr = {
  .bLength = USB_DT_DEVICE_SIZE,
  .bDescriptorType = USB_DT_DEVICE,
  .bcdUSB = 0x0110,
  .bDeviceClass = 0,
  .bDeviceSubClass = 0,
  .bDeviceProtocol = 0,
  .bMaxPacketSize0 = 64,
  .idVendor = 0x0483,
  .idProduct = 0x5741,
  .bcdDevice = 0x0200,
  .iManufacturer = 1,
  .iProduct = 2,
  .iSerialNumber = 3,
  .bNumConfigurations = 1
};

static const struct usbd_info info = {
  .device = {
    .desc = &dev_descr,
    .string = &string
  },
  
  .config = {{
      .desc = (const struct usb_config_descriptor *)&config_descr,
      .string = &string
    }}
};

usbd_msc_backend msc_backend = {
  .vendor_id = "",
  .product_id = "",
  .product_rev = "1.0",
  .block_count = 0,
  .write_block = usb_write_callback,
  .read_block = usb_read_callback,
  .format_unit = usb_format_callback,
};

static void set_config_callback(usbd_device *dev,
				const struct usb_config_descriptor *cfg) {
  (void)cfg;
  
  usbd_ep_prepare(dev, MSC_IN_EP, USBD_EP_BULK, MSC_EP_SIZE, USBD_INTERVAL_NA,
		  USBD_EP_DOUBLE_BUFFER);
  usbd_ep_prepare(dev, MSC_OUT_EP, USBD_EP_BULK, MSC_EP_SIZE, USBD_INTERVAL_NA,
		  USBD_EP_DOUBLE_BUFFER);
  usbd_msc_start(g_usbd_msc);
}

static void setup_callback(usbd_device *dev, uint8_t ep_addr,
			   const struct usb_setup_data *setup_data) {
  (void) ep_addr; /* assuming ep_addr == 0 */

  if (!usbd_msc_setup_ep0(g_usbd_msc, setup_data)) {
    usbd_ep0_setup(dev, setup_data);
  }
}

static int usb_write_callback(const usbd_msc_backend *backend, uint32_t lba,
			      const void *buffer) {
  (void)backend;
  
  g_flash_driver->write(lba*SECTOR_SIZE, (uint16_t*)buffer, SECTOR_SIZE);

  return 0;
}

static int usb_read_callback(const usbd_msc_backend *backend, uint32_t lba,
			     void *buffer) {
  (void)backend;

  if (!g_flash_driver) {
    return 0;
  }

  g_flash_driver->read(lba*SECTOR_SIZE, (uint16_t*)buffer, SECTOR_SIZE);

  return 0;
}

static int usb_format_callback(const usbd_msc_backend *backend) {
  (void)backend;

  if (!g_flash_driver) {
    return 0;
  }

  if (g_flash_driver->format) {
    g_flash_driver->format();
  }

  return 0;
}

void usb_init(flash_infos_t *flash_infos, const flash_driver_t *flash_driver) {
  g_usbd_device = usbd_init(USBD_STM32_FSDEV, NULL, &info);
  
  msc_backend.vendor_id = flash_infos->manufacturer_name;
  msc_backend.product_id = flash_infos->device_name;
  msc_backend.block_count = flash_infos->blocks;

  g_usbd_msc = usbd_msc_init(g_usbd_device,
			     MSC_OUT_EP, MSC_EP_SIZE,
			     MSC_IN_EP, MSC_EP_SIZE,
			     (const usbd_msc_backend*)&msc_backend);

  usbd_register_set_config_callback(g_usbd_device, set_config_callback);
  usbd_register_setup_callback(g_usbd_device, setup_callback);

  g_flash_driver = flash_driver;
}

void usb_poll() {
  usbd_poll(g_usbd_device,0);
}
