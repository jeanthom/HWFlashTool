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

#include <unicore-mx/stm32/gpio.h>

#include "delay.h"
#include "shiftreg.h"

#define SHIFTREG_PORT GPIOA
#define SHIFTREG_SER GPIO0
#define SHIFTREG_SRCLK GPIO3
#define SHIFTREG_SRCLR GPIO2
#define SHIFTREG_RCLK GPIO1

static void shiftreg_clear(void);
static void shiftreg_clock(void);
static void shiftreg_latch(void);

void shiftreg_init(void) {
  /* Set all shift register pins as output, no pull-up/pull-down */
  gpio_set_mode(SHIFTREG_PORT,
		GPIO_MODE_OUTPUT_10_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
		SHIFTREG_SER | SHIFTREG_RCLK | SHIFTREG_SRCLK | SHIFTREG_SRCLR);

  /* Reset the shift register data */
  shiftreg_clear();
}

static void shiftreg_clear(void) {
  /* Pulling SRCLR# low */
  gpio_clear(SHIFTREG_PORT, SHIFTREG_SRCLR);

  delay_100ns();

  /* Pulling SRCLR# back to high */
  gpio_set(SHIFTREG_PORT, SHIFTREG_SRCLR);
}

static void shiftreg_clock(void) {
  /* Pull clock pin high */
  gpio_set(SHIFTREG_PORT, SHIFTREG_SRCLK);

  delay_100ns();

  /* Pull clock pin low */
  gpio_clear(SHIFTREG_PORT, SHIFTREG_SRCLK);

  delay_100ns();
}

static void shiftreg_latch(void) {
  /* Pull latch pin high */
  gpio_set(SHIFTREG_PORT, SHIFTREG_RCLK);

  delay_100ns();

  /* Pull latch pin low */
  gpio_clear(SHIFTREG_PORT, SHIFTREG_RCLK);
}

void shiftreg_send(uint32_t value) {
  int8_t i;
  uint8_t bit_to_send;

  /* Clear the current shift register value */
  shiftreg_clear();

  /* Looping through all the bits */
  for (i = 31; i >= 0; i--) {
    /* Extracting the exact bit we want to send */
    bit_to_send = (value >> i) & 1;

    /* Setting SER pin to the correct state */
    if (bit_to_send) {
      gpio_set(SHIFTREG_PORT, SHIFTREG_SER);
    } else {
      gpio_clear(SHIFTREG_PORT, SHIFTREG_SER);
    }

    /* Delay before clocking */
    delay_100ns();

    /* Clock the shift register */
    shiftreg_clock();
  }

  /* Latch to update shift register outputs */
  shiftreg_latch();
}

