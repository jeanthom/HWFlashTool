EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:sst39vf3201
LIBS:bluepill
LIBS:HWFlashTool-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "HWFlashTool"
Date ""
Rev ""
Comp "Jean THOMAS <git0@pub.jeanthomas.me>"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74HC595 U1
U 1 1 5A0416A9
P 5000 4150
F 0 "U1" H 5150 4750 50  0000 C CNN
F 1 "74HC595" H 5000 3550 50  0000 C CNN
F 2 "" H 5000 4150 50  0001 C CNN
F 3 "" H 5000 4150 50  0001 C CNN
	1    5000 4150
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U2
U 1 1 5A041728
P 5000 5950
F 0 "U2" H 5150 6550 50  0000 C CNN
F 1 "74HC595" H 5000 5350 50  0000 C CNN
F 2 "" H 5000 5950 50  0001 C CNN
F 3 "" H 5000 5950 50  0001 C CNN
	1    5000 5950
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U3
U 1 1 5A041767
P 5000 7750
F 0 "U3" H 5150 8350 50  0000 C CNN
F 1 "74HC595" H 5000 7150 50  0000 C CNN
F 2 "" H 5000 7750 50  0001 C CNN
F 3 "" H 5000 7750 50  0001 C CNN
	1    5000 7750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR4
U 1 1 5A041D24
P 4700 3500
F 0 "#PWR4" H 4700 3350 50  0001 C CNN
F 1 "+3.3V" H 4700 3640 50  0000 C CNN
F 2 "" H 4700 3500 50  0001 C CNN
F 3 "" H 4700 3500 50  0001 C CNN
	1    4700 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 5A041E28
P 4700 4800
F 0 "#PWR5" H 4700 4550 50  0001 C CNN
F 1 "GND" H 4700 4650 50  0000 C CNN
F 2 "" H 4700 4800 50  0001 C CNN
F 3 "" H 4700 4800 50  0001 C CNN
	1    4700 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR6
U 1 1 5A04211C
P 4700 5300
F 0 "#PWR6" H 4700 5150 50  0001 C CNN
F 1 "+3.3V" H 4700 5440 50  0000 C CNN
F 2 "" H 4700 5300 50  0001 C CNN
F 3 "" H 4700 5300 50  0001 C CNN
	1    4700 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 5A042478
P 4700 6600
F 0 "#PWR7" H 4700 6350 50  0001 C CNN
F 1 "GND" H 4700 6450 50  0000 C CNN
F 2 "" H 4700 6600 50  0001 C CNN
F 3 "" H 4700 6600 50  0001 C CNN
	1    4700 6600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR8
U 1 1 5A0426DC
P 4700 7100
F 0 "#PWR8" H 4700 6950 50  0001 C CNN
F 1 "+3.3V" H 4700 7240 50  0000 C CNN
F 2 "" H 4700 7100 50  0001 C CNN
F 3 "" H 4700 7100 50  0001 C CNN
	1    4700 7100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 5A042A52
P 4700 8400
F 0 "#PWR9" H 4700 8150 50  0001 C CNN
F 1 "GND" H 4700 8250 50  0000 C CNN
F 2 "" H 4700 8400 50  0001 C CNN
F 3 "" H 4700 8400 50  0001 C CNN
	1    4700 8400
	1    0    0    -1  
$EndComp
Text GLabel 3600 3700 0    49   Input ~ 0
SR_SER
$Comp
L SST39VF3201 U4
U 1 1 5A0589E5
P 7450 6000
F 0 "U4" H 8700 8400 60  0000 C CNN
F 1 "SST39VF3201" H 8100 7250 60  0000 C CNN
F 2 "" H 7450 6000 60  0001 C CNN
F 3 "" H 7450 6000 60  0001 C CNN
	1    7450 6000
	1    0    0    -1  
$EndComp
Entry Wire Line
	5900 4200 6000 4300
Entry Wire Line
	5900 4300 6000 4400
Entry Wire Line
	5900 4400 6000 4500
Wire Wire Line
	5700 4600 5800 4600
Wire Wire Line
	5800 4600 5800 5050
Wire Wire Line
	4700 4700 4700 4800
Wire Wire Line
	4700 5300 4700 5400
Wire Wire Line
	5800 5050 4250 5050
Wire Wire Line
	4250 5050 4250 5500
Wire Wire Line
	4250 5500 4300 5500
Wire Wire Line
	4700 3500 4700 3600
Wire Wire Line
	4700 7100 4700 7200
Wire Wire Line
	4700 6500 4700 6600
Wire Wire Line
	5700 6400 5800 6400
Wire Wire Line
	5800 6400 5800 6850
Wire Wire Line
	5800 6850 4200 6850
Wire Wire Line
	4200 6850 4200 7300
Wire Wire Line
	4200 7300 4300 7300
Wire Wire Line
	4700 8300 4700 8400
Wire Wire Line
	3600 3700 4300 3700
Wire Wire Line
	3600 3900 4300 3900
Wire Wire Line
	4100 3900 4100 7500
Wire Wire Line
	4100 5700 4300 5700
Wire Wire Line
	4100 7500 4300 7500
Connection ~ 4100 5700
Wire Wire Line
	4300 4000 4000 4000
Wire Wire Line
	4000 4000 4000 7600
Wire Wire Line
	4000 5800 4300 5800
Wire Wire Line
	4000 7600 4300 7600
Connection ~ 4000 5800
Wire Wire Line
	4300 4200 3900 4200
Wire Wire Line
	3900 4200 3900 7800
Wire Wire Line
	3900 6000 4300 6000
Wire Wire Line
	3900 7800 4300 7800
Connection ~ 3900 6000
Wire Wire Line
	5700 4200 5900 4200
Wire Wire Line
	5700 4300 5900 4300
Wire Wire Line
	5700 4400 5900 4400
Wire Wire Line
	7250 3800 7050 3800
Wire Wire Line
	7250 3900 7050 3900
Wire Wire Line
	7250 4000 7050 4000
Wire Wire Line
	7250 4100 7050 4100
Wire Wire Line
	7050 4200 7250 4200
Wire Wire Line
	7250 4300 7050 4300
Wire Wire Line
	7050 4400 7250 4400
Wire Wire Line
	7250 4500 7050 4500
Wire Wire Line
	7050 4600 7250 4600
Wire Wire Line
	7250 4700 7050 4700
Wire Wire Line
	7250 4800 7050 4800
Wire Wire Line
	7250 4900 7050 4900
Wire Wire Line
	7250 5000 7050 5000
Wire Wire Line
	7250 5100 7050 5100
Wire Wire Line
	7250 5200 7050 5200
Wire Wire Line
	7250 5300 7050 5300
Wire Wire Line
	7250 5400 7050 5400
Wire Wire Line
	7250 5500 7050 5500
Wire Wire Line
	7250 5600 7050 5600
Wire Wire Line
	7050 5700 7250 5700
Wire Wire Line
	7250 5800 7050 5800
Wire Wire Line
	5700 5500 5900 5500
Wire Wire Line
	5700 5600 5900 5600
Wire Wire Line
	5700 5700 5900 5700
Wire Wire Line
	5700 5800 5900 5800
Wire Wire Line
	5700 5900 5900 5900
Wire Wire Line
	5700 6000 5900 6000
Wire Wire Line
	5700 6100 5900 6100
Wire Wire Line
	5700 6200 5900 6200
$Comp
L +3.3V #PWR11
U 1 1 5A059833
P 8100 3400
F 0 "#PWR11" H 8100 3250 50  0001 C CNN
F 1 "+3.3V" H 8100 3540 50  0000 C CNN
F 2 "" H 8100 3400 50  0001 C CNN
F 3 "" H 8100 3400 50  0001 C CNN
	1    8100 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 5A05984A
P 8050 6400
F 0 "#PWR10" H 8050 6150 50  0001 C CNN
F 1 "GND" H 8050 6250 50  0000 C CNN
F 2 "" H 8050 6400 50  0001 C CNN
F 3 "" H 8050 6400 50  0001 C CNN
	1    8050 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 6200 8050 6400
Wire Wire Line
	8050 6300 8150 6300
Wire Wire Line
	8150 6300 8150 6200
Connection ~ 8050 6300
Wire Wire Line
	8100 3400 8100 3500
Entry Wire Line
	5900 5500 6000 5600
Entry Wire Line
	5900 5600 6000 5700
Entry Wire Line
	5900 5700 6000 5800
Entry Wire Line
	5900 5800 6000 5900
Entry Wire Line
	5900 5900 6000 6000
Entry Wire Line
	5900 6000 6000 6100
Entry Wire Line
	5900 6100 6000 6200
Entry Wire Line
	5900 6200 6000 6300
Wire Wire Line
	5700 7300 5900 7300
Wire Wire Line
	5700 7400 5900 7400
Wire Wire Line
	5700 7500 5900 7500
Wire Wire Line
	5900 7600 5700 7600
Wire Wire Line
	5700 7700 5900 7700
Entry Wire Line
	5900 7300 6000 7400
Entry Wire Line
	5900 7400 6000 7500
Entry Wire Line
	5900 7500 6000 7600
Entry Wire Line
	5900 7600 6000 7700
Entry Wire Line
	5900 7700 6000 7800
Wire Wire Line
	5700 4100 5900 4100
Wire Wire Line
	5700 4000 5900 4000
Entry Wire Line
	5900 4000 6000 4100
Entry Wire Line
	5900 4100 6000 4200
Wire Wire Line
	5700 3900 5900 3900
Entry Wire Line
	5900 3900 6000 4000
Entry Wire Line
	5900 3800 6000 3900
Entry Wire Line
	5900 3700 6000 3800
Wire Wire Line
	5700 3800 5900 3800
Wire Wire Line
	5900 3700 5700 3700
Text Label 5700 3700 0    60   ~ 0
A0
Text Label 5700 3800 0    60   ~ 0
A1
Text Label 5700 3900 0    60   ~ 0
A2
Text Label 5700 4000 0    60   ~ 0
A3
Text Label 5700 4100 0    60   ~ 0
A4
Text Label 5700 4200 0    60   ~ 0
A5
Text Label 5700 4300 0    60   ~ 0
A6
Text Label 5700 4400 0    60   ~ 0
A7
Text Label 5700 5500 0    60   ~ 0
A8
Text Label 5700 5600 0    60   ~ 0
A9
Text Label 5700 5700 0    60   ~ 0
A10
Text Label 5700 5800 0    60   ~ 0
A11
Text Label 5700 5900 0    60   ~ 0
A12
Text Label 5700 6000 0    60   ~ 0
A13
Text Label 5700 6100 0    60   ~ 0
A14
Text Label 5700 6200 0    60   ~ 0
A15
Text Label 5700 7300 0    60   ~ 0
A16
Text Label 5700 7400 0    60   ~ 0
A17
Text Label 5700 7500 0    60   ~ 0
A18
Text Label 5700 7600 0    60   ~ 0
A19
Text Label 5700 7700 0    60   ~ 0
A20
Entry Wire Line
	6950 3700 7050 3800
Entry Wire Line
	6950 3800 7050 3900
Entry Wire Line
	6950 3900 7050 4000
Entry Wire Line
	6950 4000 7050 4100
Entry Wire Line
	6950 4100 7050 4200
Entry Wire Line
	6950 4200 7050 4300
Entry Wire Line
	6950 4300 7050 4400
Entry Wire Line
	6950 4400 7050 4500
Entry Wire Line
	6950 4500 7050 4600
Entry Wire Line
	6950 4600 7050 4700
Entry Wire Line
	6950 4700 7050 4800
Entry Wire Line
	6950 4800 7050 4900
Entry Wire Line
	6950 4900 7050 5000
Entry Wire Line
	6950 5000 7050 5100
Entry Wire Line
	6950 5100 7050 5200
Entry Wire Line
	6950 5200 7050 5300
Entry Wire Line
	6950 5300 7050 5400
Entry Wire Line
	6950 5400 7050 5500
Entry Wire Line
	6950 5500 7050 5600
Entry Wire Line
	6950 5600 7050 5700
Entry Wire Line
	6950 5700 7050 5800
Wire Bus Line
	6000 7850 6000 3600
Wire Bus Line
	6000 3600 6950 3600
Wire Bus Line
	6950 3600 6950 5950
Text Label 7050 5800 0    60   ~ 0
A0
Text Label 7050 5700 0    60   ~ 0
A1
Text Label 7050 5600 0    60   ~ 0
A2
Text Label 7050 5500 0    60   ~ 0
A3
Text Label 7050 5400 0    60   ~ 0
A4
Text Label 7050 5300 0    60   ~ 0
A5
Text Label 7050 5200 0    60   ~ 0
A6
Text Label 7050 5100 0    60   ~ 0
A7
Text Label 7050 5000 0    60   ~ 0
A8
Text Label 7050 4900 0    60   ~ 0
A9
Text Label 7050 4800 0    60   ~ 0
A10
Text Label 7050 4700 0    60   ~ 0
A11
Text Label 7050 4600 0    60   ~ 0
A12
Text Label 7050 4500 0    60   ~ 0
A13
Text Label 7050 4400 0    60   ~ 0
A14
Text Label 7050 4300 0    60   ~ 0
A15
Text Label 7050 4200 0    60   ~ 0
A16
Text Label 7050 4100 0    60   ~ 0
A17
Text Label 7050 4000 0    60   ~ 0
A18
Text Label 7050 3900 0    60   ~ 0
A19
Text Label 7050 3800 0    60   ~ 0
A20
Text GLabel 3600 3900 0    49   Input ~ 0
SR_SRCLK
Text GLabel 3600 4100 0    49   Input ~ 0
SR_SRCLR
Connection ~ 4100 3900
Wire Wire Line
	3600 4100 4000 4100
Connection ~ 4000 4100
$Comp
L GND #PWR1
U 1 1 5A064067
P 4250 4400
F 0 "#PWR1" H 4250 4150 50  0001 C CNN
F 1 "GND" H 4250 4250 50  0000 C CNN
F 2 "" H 4250 4400 50  0001 C CNN
F 3 "" H 4250 4400 50  0001 C CNN
	1    4250 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5A0640A3
P 4250 6200
F 0 "#PWR2" H 4250 5950 50  0001 C CNN
F 1 "GND" H 4250 6050 50  0000 C CNN
F 2 "" H 4250 6200 50  0001 C CNN
F 3 "" H 4250 6200 50  0001 C CNN
	1    4250 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5A06414F
P 4250 8000
F 0 "#PWR3" H 4250 7750 50  0001 C CNN
F 1 "GND" H 4250 7850 50  0000 C CNN
F 2 "" H 4250 8000 50  0001 C CNN
F 3 "" H 4250 8000 50  0001 C CNN
	1    4250 8000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 7900 4250 7900
Wire Wire Line
	4250 7900 4250 8000
Wire Wire Line
	4300 6100 4250 6100
Wire Wire Line
	4250 6100 4250 6200
Wire Wire Line
	4300 4300 4250 4300
Wire Wire Line
	4250 4300 4250 4400
Text GLabel 3600 4300 0    49   Input ~ 0
SR_RCLK
Wire Wire Line
	3600 4300 3900 4300
Connection ~ 3900 4300
$Comp
L BluePill U5
U 1 1 5A0843B7
P 11300 5950
F 0 "U5" H 12350 8200 60  0000 C CNN
F 1 "BluePill" H 11950 7250 60  0000 C CNN
F 2 "" H 11300 6000 60  0001 C CNN
F 3 "" H 11300 6000 60  0001 C CNN
	1    11300 5950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR12
U 1 1 5A0847CC
P 11050 5650
F 0 "#PWR12" H 11050 5500 50  0001 C CNN
F 1 "+3.3V" H 11050 5790 50  0000 C CNN
F 2 "" H 11050 5650 50  0001 C CNN
F 3 "" H 11050 5650 50  0001 C CNN
	1    11050 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	11300 5750 11050 5750
Wire Wire Line
	11050 5750 11050 5650
$Comp
L GND #PWR13
U 1 1 5A084A93
P 11050 5950
F 0 "#PWR13" H 11050 5700 50  0001 C CNN
F 1 "GND" H 11050 5800 50  0000 C CNN
F 2 "" H 11050 5950 50  0001 C CNN
F 3 "" H 11050 5950 50  0001 C CNN
	1    11050 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	11300 5850 11050 5850
Wire Wire Line
	11050 5850 11050 5950
Text GLabel 11100 3850 0    49   Output ~ 0
SR_SER
Wire Wire Line
	11300 3850 11100 3850
Text GLabel 11100 3950 0    49   Output ~ 0
SR_RCLK
Wire Wire Line
	11300 3950 11100 3950
Text GLabel 11100 4050 0    49   Output ~ 0
SR_SRCLR
Text GLabel 11100 4150 0    49   Output ~ 0
SR_SRCLK
Wire Wire Line
	11100 4050 11300 4050
Wire Wire Line
	11300 4150 11100 4150
Wire Wire Line
	12650 3850 12950 3850
Wire Wire Line
	12650 3950 12950 3950
Wire Wire Line
	12650 4150 12950 4150
Wire Wire Line
	12650 4250 12950 4250
Wire Wire Line
	12650 4350 12950 4350
Wire Wire Line
	12650 4450 12950 4450
Wire Wire Line
	12650 4550 12950 4550
Wire Wire Line
	12650 4650 12950 4650
Wire Wire Line
	12650 4750 12950 4750
Wire Wire Line
	12650 4850 12950 4850
Wire Wire Line
	12650 4950 12950 4950
Wire Wire Line
	12650 5050 12950 5050
Wire Wire Line
	12650 5150 12950 5150
Wire Wire Line
	12650 5250 12950 5250
Wire Wire Line
	12650 5350 12950 5350
Wire Wire Line
	8950 3800 9250 3800
Wire Wire Line
	9250 3900 8950 3900
Wire Wire Line
	8950 4000 9250 4000
Wire Wire Line
	9250 4100 8950 4100
Wire Wire Line
	8950 4200 9250 4200
Wire Wire Line
	9250 4300 8950 4300
Wire Wire Line
	8950 4400 9250 4400
Wire Wire Line
	9250 4500 8950 4500
Wire Wire Line
	8950 4600 9250 4600
Wire Wire Line
	8950 4700 9250 4700
Wire Wire Line
	9250 4800 8950 4800
Wire Wire Line
	8950 4900 9250 4900
Wire Wire Line
	9250 5000 8950 5000
Wire Wire Line
	8950 5100 9250 5100
Wire Wire Line
	9250 5200 8950 5200
Wire Wire Line
	8950 5300 9250 5300
Text Label 8950 3800 0    60   ~ 0
DQ15
Text Label 8950 3900 0    60   ~ 0
DQ14
Text Label 8950 4000 0    60   ~ 0
DQ13
Text Label 8950 4100 0    60   ~ 0
DQ12
Text Label 8950 4200 0    60   ~ 0
DQ11
Text Label 8950 4300 0    60   ~ 0
DQ10
Text Label 8950 4400 0    60   ~ 0
DQ9
Text Label 8950 4500 0    60   ~ 0
DQ8
Text Label 8950 4600 0    60   ~ 0
DQ7
Text Label 8950 4700 0    60   ~ 0
DQ6
Text Label 8950 4800 0    60   ~ 0
DQ5
Text Label 8950 4900 0    60   ~ 0
DQ4
Text Label 8950 5000 0    60   ~ 0
DQ3
Text Label 8950 5100 0    60   ~ 0
DQ2
Text Label 8950 5200 0    60   ~ 0
DQ1
Text Label 8950 5300 0    60   ~ 0
DQ0
Entry Wire Line
	9250 3800 9350 3900
Entry Wire Line
	9250 3900 9350 4000
Entry Wire Line
	9250 4000 9350 4100
Entry Wire Line
	9250 4100 9350 4200
Entry Wire Line
	9250 4200 9350 4300
Entry Wire Line
	9250 4300 9350 4400
Entry Wire Line
	9250 4400 9350 4500
Entry Wire Line
	9250 4500 9350 4600
Entry Wire Line
	9250 4600 9350 4700
Entry Wire Line
	9250 4700 9350 4800
Entry Wire Line
	9250 4800 9350 4900
Entry Wire Line
	9250 4900 9350 5000
Entry Wire Line
	9250 5000 9350 5100
Entry Wire Line
	9250 5100 9350 5200
Entry Wire Line
	9250 5200 9350 5300
Entry Wire Line
	9250 5300 9350 5400
Text Label 12650 3850 0    60   ~ 0
DQ0
Text Label 12650 3950 0    60   ~ 0
DQ1
Text Label 12650 4150 0    60   ~ 0
DQ3
Text Label 12650 4250 0    60   ~ 0
DQ4
Text Label 12650 4350 0    60   ~ 0
DQ5
Text Label 12650 4450 0    60   ~ 0
DQ6
Text Label 12650 4550 0    60   ~ 0
DQ7
Text Label 12650 4650 0    60   ~ 0
DQ8
Text Label 12650 4750 0    60   ~ 0
DQ9
Text Label 12650 4850 0    60   ~ 0
DQ10
Text Label 12650 4950 0    60   ~ 0
DQ11
Text Label 12650 5050 0    60   ~ 0
DQ12
Text Label 12650 5150 0    60   ~ 0
DQ13
Text Label 12650 5250 0    60   ~ 0
DQ14
Text Label 12650 5350 0    60   ~ 0
DQ15
Entry Wire Line
	12950 3850 13050 3950
Entry Wire Line
	12950 3950 13050 4050
Entry Wire Line
	12950 4150 13050 4250
Entry Wire Line
	12950 4250 13050 4350
Entry Wire Line
	12950 4350 13050 4450
Entry Wire Line
	12950 4450 13050 4550
Entry Wire Line
	12950 4550 13050 4650
Entry Wire Line
	12950 4650 13050 4750
Entry Wire Line
	12950 4750 13050 4850
Entry Wire Line
	12950 4850 13050 4950
Entry Wire Line
	12950 4950 13050 5050
Entry Wire Line
	12950 5050 13050 5150
Entry Wire Line
	12950 5150 13050 5250
Entry Wire Line
	12950 5250 13050 5350
Entry Wire Line
	12950 5350 13050 5450
Text GLabel 9100 5600 2    49   Input ~ 0
FL_RST
Text GLabel 9100 5500 2    49   Input ~ 0
FL_WE
Text GLabel 9100 5700 2    49   Input ~ 0
FL_WP
Text GLabel 9100 5800 2    49   Input ~ 0
FL_CE
Text GLabel 9100 5900 2    49   Input ~ 0
FL_OE
Wire Wire Line
	8950 5500 9100 5500
Wire Wire Line
	9100 5600 8950 5600
Wire Wire Line
	8950 5700 9100 5700
Wire Wire Line
	9100 5800 8950 5800
Wire Wire Line
	8950 5900 9100 5900
Text GLabel 11100 4250 0    49   Output ~ 0
FL_RST
Text GLabel 11100 4350 0    49   Output ~ 0
FL_WE
Wire Wire Line
	11100 4250 11300 4250
Wire Wire Line
	11300 4350 11100 4350
Text GLabel 11100 4450 0    49   Output ~ 0
FL_WP
Text GLabel 11100 4550 0    49   Output ~ 0
FL_OE
Wire Wire Line
	11100 4450 11300 4450
Wire Wire Line
	11300 4550 11100 4550
Text GLabel 11100 5350 0    49   Output ~ 0
FL_CE
Wire Wire Line
	11300 5350 11100 5350
Wire Bus Line
	9350 5400 9350 3550
Wire Bus Line
	9350 3550 13050 3550
Wire Bus Line
	13050 3550 13050 5450
Wire Wire Line
	11300 4650 10450 4650
Entry Wire Line
	10350 4550 10450 4650
Text Label 10450 4650 0    49   ~ 0
DQ2
Wire Bus Line
	10350 3550 10350 4650
$EndSCHEMATC