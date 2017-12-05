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

#include <stdint.h>

#include "../delay.h"
#include "../helpers.h"
#include "../flash.h"
#include "sst.h"

#define UNLOCK_ADDR1 0x5555
#define UNLOCK_ADDR2 0x2AAA

static const char* const sst_man_str = "SST";
static const char* const sst_39vf1601_str = "SST39VF1601";
static const char* const sst_39vf1602_str = "SST39VF1602";
static const char* const sst_39vf3201_str = "SST39VF3201";
static const char* const sst_39vf3202_str = "SST39VF3202";

static void sst_software_id_entry(void) {
  flash_set_data(UNLOCK_ADDR1, 0xAA);
  flash_set_data(UNLOCK_ADDR2, 0x55);
  flash_set_data(UNLOCK_ADDR1, 0x90);
}

static void sst_cfi_query_enter(void) {
  flash_set_data(UNLOCK_ADDR1, 0xAA);
  flash_set_data(UNLOCK_ADDR2, 0x55);
  flash_set_data(UNLOCK_ADDR1, 0x98);
}

/* Can also be used to exit Software ID mode */
static void sst_cfi_query_exit(void) {
  flash_set_data(UNLOCK_ADDR1, 0xAA);
  flash_set_data(UNLOCK_ADDR2, 0x55);
  flash_set_data(UNLOCK_ADDR1, 0xF0);
}

static int sst_detect(flash_infos_t *infos) {
  uint16_t buffer, manufacturer_id, device_id;

  sst_cfi_query_enter();

  /* Check for "QRY" string */
  buffer = flash_get_data(0x10);
  if (buffer != 'Q') {
    return 0;
  }
  buffer = flash_get_data(0x11);
  if (buffer != 'R') {
    return 0;
  }
  buffer = flash_get_data(0x12);
  if (buffer != 'Y') {
    return 0;
  }

  /* Ensure primary OEM command set is correct */
  if (flash_get_data(0x13) != 1 || flash_get_data(0x14) != 7) {
    return 0;
  }

  /* Read flash size */
  if (infos) {
    buffer = flash_get_data(0x27);
    infos->blocks = pow_int(2, buffer-9);
  }

  sst_cfi_query_exit();

  sst_software_id_entry();

  manufacturer_id = flash_get_data(0x0);
  if (manufacturer_id != 0xBF) {
    return 0;
  }
  if (infos) {
    infos->manufacturer_name = sst_man_str;
  }
  
  device_id = flash_get_data(0x1);
  switch (device_id) {
  case 0x234B:
    if (infos) {
      infos->device_name = sst_39vf1601_str;
    }
    break;
  case 0x234A:
    if (infos) {
      infos->device_name = sst_39vf1602_str;
    }
    break;
  case 0x235B:
    if (infos) {
      infos->device_name = sst_39vf3201_str;
    }
    break;
  case 0x235A:
    if (infos) {
      infos->device_name = sst_39vf3202_str;
    }
    break;
  default:
    return 0;
  }

  sst_cfi_query_exit();

  return 1;
}

static void sst_read(uint32_t address, uint16_t *buf, uint32_t len) {
  uint32_t i;

  for (i = 0; i < len/2; i++) {
    buf[i] = flash_get_data(address+i);
  }
}

static void sst_write(uint32_t address, uint16_t *buf, uint32_t len) {
  uint32_t i;

  for (i = 0; i < len/2; i++) {
    flash_set_data(0x5555, 0xAA);
    flash_set_data(0x2AAA, 0x55);
    flash_set_data(0x5555, 0xA0);
    flash_set_data(address+i, buf[i]);

    /* Wait TBP (10µs) */
    delay_10us();
  }
}

static void sst_format(void) {
  unsigned int i;
  
  flash_set_data(0x5555, 0xAA);
  flash_set_data(0x2AAA, 0x55);
  flash_set_data(0x5555, 0x80);
  flash_set_data(0x5555, 0xAA);
  flash_set_data(0x2AAA, 0x55);
  flash_set_data(0x5555, 0x10);

  /* Waiting Tsce (50ms) */
  for (i = 0; i < 5000; i++) {
    delay_10us();
  }
}

const flash_driver_t sst_driver = {
  .detect = sst_detect,
  .read = sst_read,
  .write = sst_write,
  .format = sst_format
};
