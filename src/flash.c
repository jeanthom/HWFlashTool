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

#include <stdlib.h>
#include <unicore-mx/stm32/gpio.h>

#include "delay.h"
#include "shiftreg.h"
#include "flash.h"

#include "cmdset/sst.h"

#define FLASH_CTL_PORT GPIOA
#define FLASH_CTL_WE GPIO5
#define FLASH_CTL_RST GPIO4
#define FLASH_CTL_WP GPIO6
#define FLASH_CTL_OE GPIO7
#define FLASH_CTL_CE GPIO15

#define FLASH_DATA_PORT GPIOB
#define FLASH_DATA_MASK 0xFFFF ^ GPIO2

static void flash_reset(void);
static void flash_prepare_read(void);
static void flash_prepare_write(void);

static const flash_driver_t *drivers[] = {
  &sst_driver,
  NULL
};

static flash_mode_t flash_mode;

void flash_init(void) {
  /* Set pin mode for flash control pins */
  gpio_set_mode(FLASH_CTL_PORT,
		GPIO_MODE_OUTPUT_10_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
		FLASH_CTL_WE | FLASH_CTL_RST | FLASH_CTL_WP | FLASH_CTL_OE | FLASH_CTL_CE);

  /* Various initial pin configuration */
  gpio_clear(FLASH_CTL_PORT, FLASH_CTL_WP|FLASH_CTL_CE);
  gpio_set(FLASH_CTL_PORT, FLASH_CTL_RST|FLASH_CTL_WE);

  /* Init shift register for address input */
  shiftreg_init();

  /* Prepare flash in read mode */
  flash_prepare_read();
  flash_mode = READ;
}

const flash_driver_t* flash_get_driver(flash_infos_t *flash_infos) {
  int i, ret;

  for (i = 0; drivers[i]; i++) {
    flash_reset();
    ret = drivers[i]->detect(flash_infos);
    if (ret) {
      return drivers[i];
    }
  }

  return NULL;
}

static void flash_reset(void) {
  /* Toggle RST# back and forth */
  gpio_clear(FLASH_CTL_PORT, FLASH_CTL_RST);
  gpio_set(FLASH_CTL_PORT, FLASH_CTL_RST);
}

static void flash_prepare_read(void) {
  /* Disable write operations */
  gpio_clear(FLASH_CTL_PORT, FLASH_CTL_WP);

  /* Enable output */
  gpio_clear(FLASH_CTL_PORT, FLASH_CTL_OE);

  /* Set all data pins to inputs */
  gpio_set_mode(FLASH_DATA_PORT,
		GPIO_MODE_INPUT,
		GPIO_CNF_INPUT_PULL_UPDOWN,
		GPIO_ALL & (~GPIO2));
  gpio_set_mode(FLASH_CTL_PORT,
		GPIO_MODE_INPUT,
		GPIO_CNF_INPUT_PULL_UPDOWN,
		GPIO8);

  flash_mode = READ;
}

static void flash_prepare_write(void) {
  /* Disable write protect */
  gpio_set(FLASH_CTL_PORT, FLASH_CTL_WP);
  
  /* Disable output */
  gpio_set(FLASH_CTL_PORT, FLASH_CTL_OE);
  
  /* Set all data pins to inputs */
  gpio_set_mode(FLASH_DATA_PORT,
		GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
		GPIO_ALL & (~GPIO2));
  gpio_set_mode(FLASH_CTL_PORT,
		GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
		GPIO8);

  flash_mode = WRITE;
}

static void flash_set_port_data(uint32_t port, uint16_t mask,
				uint16_t data) {
  GPIO_BSRR(port) = ((~data & mask) << 16) | (data & mask);
}

void flash_set_data(uint32_t address, uint16_t data) {
  /* Set control signals if needed */
  if (flash_mode != WRITE) {
    flash_prepare_write();
  }

  shiftreg_send(address);

  /* To set the data, we use direct access to the HW registers */
  flash_set_port_data(FLASH_DATA_PORT, FLASH_DATA_MASK, data);
  if (data & GPIO2) {
    gpio_set(FLASH_CTL_PORT, GPIO8);
  } else {
    gpio_clear(FLASH_CTL_PORT, GPIO8);
  }

  /* Toggle write enable */
  gpio_clear(FLASH_CTL_PORT, FLASH_CTL_WE);
  delay_100ns();
  gpio_set(FLASH_CTL_PORT, FLASH_CTL_WE);
  delay_100ns();
}

uint16_t flash_get_data(uint32_t address) {
  uint16_t read_data;

  /* Set control signals if needed */
  if (flash_mode != READ) {
    flash_prepare_read();
  }

  /* Set the address */
  shiftreg_send(address);

  /* It takes 70ns for the data lines to have the correct value */
  delay_100ns();
  
  /* Read data */
  read_data = (gpio_port_read(FLASH_DATA_PORT) & (~GPIO2));
  read_data |= ((gpio_port_read(FLASH_CTL_PORT) & GPIO8) >> 6);

  return read_data;
}
