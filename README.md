# HWFlashTool

Hardware programmer for SST39VF1601, SST39VF1602, SST39VF3201, SST39VF3202. With some new support files in `/src/cmdset`, it could be used to program other flash chips.

HWFlashTool is recognised by your computer as a mass storage device, which means you don't need to install any driver to read data from the flash.

## Writing to the flash

Before writing to the flash, you need to erase the block you will be writing to. This can't be done automatically at write because the flash's sector size is different to unicore-mx's sector size.

However, this can be done before flashing using a SCSI command that will erase the whole flash. To issue this command, you can use [sg_format](https://linux.die.net/man/8/sg_format) utility (available in `sg3_utils` on Fedora) :

```
$ sudo sg_format --six --format /dev/sdb
    SST       SST39VF3201       1.0    peripheral_type: disk [0x0]
Mode Sense (block descriptor) data, prior to changes:
  Number of blocks=0 [0x0]
  Block size=0 [0x0]

A FORMAT will commence in 15 seconds
    ALL data on /dev/sdb will be DESTROYED
        Press control-C to abort

A FORMAT will commence in 10 seconds
    ALL data on /dev/sdb will be DESTROYED
        Press control-C to abort

A FORMAT will commence in 5 seconds
    ALL data on /dev/sdb will be DESTROYED
        Press control-C to abort
format unit: transport: Host_status=0x03 [DID_TIME_OUT]
Driver_status=0x00 [DRIVER_OK, SUGGEST_OK]

Format command: Sense category: -1, try '-v' option for more information
FORMAT failed
    try '-v' for more information
```

Do not worry if it fails : it is normal. You can then use dd to upload to the flash like any other storage device :

```
$ sudo dd if=myfile.bin of=/dev/sdb
```

## Hardware

You need a handfull components to build your own HWFlashTool :

 * STM32F103C8T6 development board ("Blue pill", "Black pill", etc.) with the correct resistor values for USB pull-up (otherwise it won't work properly)
 * ST-Link programmer
 * 3x 74HC595 8-bit shift register
 * A few decoupling capacitors

Schematics are available as a [PDF file](docs/KiCAD/HWFlashTool.pdf).

## Firmware

Run the following commands to fetch the firmware's dependencies and compile ; you will need beforehand an ARM toolchain.

```
git clone https://github.com/jeanthom/HWFlashTool hwflashtool
cd hwflashtool
git submodule init
git submodule update
make
```

Firmware is compiled as `src/hwflashtool.bin`.

## Performance

Quite terrible : a "whopping" 18,7 kB/s, measured on a full dump (4 MB) of an SST39VF3201 flash. Write speeds are worse : 3,2 kB/s.

## Why is PC13 LED blinking ?

This means that the flash chip hasn't been recognised by the HWFlashTool firmware.

 1. Check connections
 2. Ensure your flash chip has a supported command set (see `src/cmdset/` folder)
