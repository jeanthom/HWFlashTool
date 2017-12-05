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

enum flash_mode {
  READ,
  WRITE
};
typedef enum flash_mode flash_mode_t;

struct flash_infos {
  const char* manufacturer_name;
  const char* device_name;
  uint32_t blocks;
};
typedef struct flash_infos flash_infos_t;

struct flash_driver {
  int (*detect)(flash_infos_t *infos);
  void (*read)(uint32_t address, uint16_t *buf, uint32_t len);
  void (*write)(uint32_t address, uint16_t *buf, uint32_t len);
  void (*format)(void);
};
typedef struct flash_driver flash_driver_t;

void flash_init(void);
const flash_driver_t* flash_get_driver(flash_infos_t *flash_infos);
void flash_set_data(uint32_t address, uint16_t data);
uint16_t flash_get_data(uint32_t address);
