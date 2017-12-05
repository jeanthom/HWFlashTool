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

#include <unicore-mx/stm32/rcc.h>
#include <unicore-mx/stm32/gpio.h>

#include "shiftreg.h"
#include "flash.h"
#include "usb.h"

int main(void) {
  const flash_driver_t *flash_driver;
  flash_infos_t flash_infos;
  int i;
  
  /* Clock generation */
  rcc_clock_setup_in_hsi_out_48mhz();

  /* Enable peripherals */
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOC);
  rcc_periph_clock_enable(RCC_AFIO);

  /* Disable JTAG but let SWD in a working state */
  AFIO_MAPR |= AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON;

  /* Init various functionnalities */
  flash_init();

  flash_driver = flash_get_driver(&flash_infos);

  if (flash_driver) {
    usb_init(&flash_infos, flash_driver);
    
    while (1) {
      usb_poll();
    }
  } else {
    /* Toggle PC13 LED to notify the user about an error occuring
       during flash chip detection */
    gpio_set_mode(GPIOC, GPIO_CNF_OUTPUT_PUSHPULL,
		  GPIO_MODE_OUTPUT_2_MHZ, GPIO13);
    
    while (1) {
      gpio_toggle(GPIOC, GPIO13);
      for (i = 0; i < 800000; i++) {
	__asm__("nop");
      }
    }
  }
  
  return 0;
}
