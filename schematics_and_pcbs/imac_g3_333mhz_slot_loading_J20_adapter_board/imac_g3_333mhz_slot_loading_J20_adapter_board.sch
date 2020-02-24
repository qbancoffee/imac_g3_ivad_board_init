EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "iMac G3 333 Mhz Slot Loading Power and Video Board"
Date "2020-02-03"
Rev "1"
Comp ""
Comment1 "and control other functions."
Comment2 "used to send the i2c IVAD inititialization sequence and the EDID info to the computer"
Comment3 "Powers atmega328p fromJ20 and powers an atmega328p from VGA cable"
Comment4 "Rocky Hill"
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega328-PU U1
U 1 1 5E393326
P 1350 2650
F 0 "U1" H 1100 4250 50  0000 R CNN
F 1 "ATmega328-PU" H 2250 4350 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 1350 2650 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 1350 2650 50  0001 C CNN
	1    1350 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1150 1350 850 
Wire Wire Line
	1450 1150 1450 850 
NoConn ~ 750  1450
$Comp
L power:GND #PWR07
U 1 1 5E39A336
P 1350 4450
F 0 "#PWR07" H 1350 4200 50  0001 C CNN
F 1 "GND" H 1355 4277 50  0000 C CNN
F 2 "" H 1350 4450 50  0001 C CNN
F 3 "" H 1350 4450 50  0001 C CNN
	1    1350 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 4150 1350 4450
$Comp
L Device:Crystal Y1
U 1 1 5E39C3FD
P 3400 2100
F 0 "Y1" V 3354 2231 50  0000 L CNN
F 1 "Crystal" V 3445 2231 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 3400 2100 50  0001 C CNN
F 3 "http://www.txccrystal.com/images/pdf/9b.pdf" H 3400 2100 50  0001 C CNN
F 4 "digikey" V 3400 2100 50  0001 C CNN "Vendor"
F 5 "887-2015-ND" V 3400 2100 50  0001 C CNN "Part#"
	1    3400 2100
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5E39D342
P 3400 1400
F 0 "C1" H 3515 1446 50  0000 L CNN
F 1 "22pF" H 3515 1355 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D9.0mm_W5.0mm_P10.00mm" H 3438 1250 50  0001 C CNN
F 3 "http://www.vishay.com/docs/28537/vy1series.pdf" H 3400 1400 50  0001 C CNN
F 4 "digikey" H 3400 1400 50  0001 C CNN "Vendor"
F 5 "BC2364-ND" H 3400 1400 50  0001 C CNN "Part#"
	1    3400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1550 3400 1750
Wire Wire Line
	3400 2650 3400 2450
Wire Wire Line
	2650 2050 2650 1750
Wire Wire Line
	2650 1750 3400 1750
Connection ~ 3400 1750
Wire Wire Line
	3400 1750 3400 1950
Wire Wire Line
	1950 2150 2650 2150
Wire Wire Line
	2650 2150 2650 2450
Wire Wire Line
	2650 2450 3400 2450
Connection ~ 3400 2450
Wire Wire Line
	3400 2450 3400 2250
Wire Wire Line
	1950 2050 2650 2050
$Comp
L power:GND #PWR04
U 1 1 5E3A7604
P 3400 2950
F 0 "#PWR04" H 3400 2700 50  0001 C CNN
F 1 "GND" H 3405 2777 50  0000 C CNN
F 2 "" H 3400 2950 50  0001 C CNN
F 3 "" H 3400 2950 50  0001 C CNN
	1    3400 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5E3A84E9
P 7650 1300
F 0 "#PWR02" H 7650 1050 50  0001 C CNN
F 1 "GND" H 7655 1127 50  0000 C CNN
F 2 "" H 7650 1300 50  0001 C CNN
F 3 "" H 7650 1300 50  0001 C CNN
	1    7650 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1250 3400 900 
Wire Wire Line
	3400 900  2950 900 
Wire Wire Line
	2950 900  2950 1050
Text Label 2200 2750 0    50   ~ 0
IVAD_SDA
Text Label 2200 2850 0    50   ~ 0
IVAD_SCL
Wire Wire Line
	1950 2750 2200 2750
Wire Wire Line
	1950 2850 2200 2850
Text Label 8300 1100 2    50   ~ 0
IVAD_SDA
Text Label 9600 1100 0    50   ~ 0
IVAD_SCL
Wire Wire Line
	8300 1100 8700 1100
Text Label 9600 1500 0    50   ~ 0
PFW
Wire Wire Line
	9600 1500 9200 1500
$Comp
L power:GND #PWR01
U 1 1 5E3B5B7F
P 2950 1050
F 0 "#PWR01" H 2950 800 50  0001 C CNN
F 1 "GND" H 2955 877 50  0000 C CNN
F 2 "" H 2950 1050 50  0001 C CNN
F 3 "" H 2950 1050 50  0001 C CNN
	1    2950 1050
	1    0    0    -1  
$EndComp
$Comp
L Connector:DB15_Female_HighDensity J1
U 1 1 5E3B898B
P 8950 3400
F 0 "J1" H 8950 4267 50  0000 C CNN
F 1 "DB15_Female_HighDensity" H 8950 4176 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-15-HD_Female_Horizontal_P2.29x1.98mm_EdgePinOffset8.35mm_Housed_MountingHolesOffset10.89mm" H 8000 3800 50  0001 C CNN
F 3 "https://cdn.amphenol-icc.com/media/wysiwyg/files/drawing/l77hdxxxsd1ch4f.pdf" H 8000 3800 50  0001 C CNN
F 4 "digikey" H 8950 3400 50  0001 C CNN "Vendor"
F 5 "L77HDE15SD1CH4F-ND" H 8950 3400 50  0001 C CNN "Part#"
	1    8950 3400
	1    0    0    -1  
$EndComp
Text Label 8400 3000 2    50   ~ 0
RED
Text Label 8400 2900 2    50   ~ 0
GND_RED
Text Label 8400 3100 2    50   ~ 0
GND_GREEN
Text Label 9500 3800 0    50   ~ 0
COMPUTER_SCL
Text Label 8400 3200 2    50   ~ 0
GREEN
Text Label 8400 3300 2    50   ~ 0
GND_BLUE
Text Label 8400 3400 2    50   ~ 0
BLUE
Text Label 8400 3500 2    50   ~ 0
COMPUTER_5V
NoConn ~ 8650 3600
$Comp
L power:GND #PWR05
U 1 1 5E3D17A3
P 8400 3800
F 0 "#PWR05" H 8400 3550 50  0001 C CNN
F 1 "GND" H 8405 3627 50  0000 C CNN
F 2 "" H 8400 3800 50  0001 C CNN
F 3 "" H 8400 3800 50  0001 C CNN
	1    8400 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 3700 8400 3700
Wire Wire Line
	8400 3700 8400 3800
Wire Wire Line
	8650 3800 8400 3800
Connection ~ 8400 3800
Wire Wire Line
	8400 2900 8650 2900
Wire Wire Line
	8400 3000 8650 3000
Wire Wire Line
	8400 3100 8650 3100
Wire Wire Line
	8400 3200 8650 3200
Wire Wire Line
	8400 3300 8650 3300
Wire Wire Line
	8400 3400 8650 3400
Wire Wire Line
	8400 3500 8650 3500
NoConn ~ 9250 3000
Text Label 9500 3200 0    50   ~ 0
COMPUTER_SDA
Text Label 9500 3400 0    50   ~ 0
H_SYNC
Text Label 9500 3600 0    50   ~ 0
V_SYNC
Wire Wire Line
	9250 3200 9500 3200
Wire Wire Line
	9250 3400 9500 3400
Wire Wire Line
	9250 3600 9500 3600
Wire Wire Line
	9250 3800 9500 3800
Text Label 8300 1500 2    50   ~ 0
H_SYNC
Wire Wire Line
	7650 1200 7650 1300
Wire Wire Line
	7650 1200 8700 1200
Wire Wire Line
	8300 1500 8700 1500
Text Label 8300 1600 2    50   ~ 0
V_SYNC
Text Label 8300 1700 2    50   ~ 0
BLUE
Text Label 9600 1700 0    50   ~ 0
GND_BLUE
Text Label 8300 1800 2    50   ~ 0
GREEN
Text Label 9600 1800 0    50   ~ 0
GND_GREEN
Text Label 8300 1900 2    50   ~ 0
RED
Text Label 9600 1900 0    50   ~ 0
GND_RED
Wire Wire Line
	8300 1600 8700 1600
Wire Wire Line
	8700 1700 8300 1700
Wire Wire Line
	8300 1800 8700 1800
Wire Wire Line
	8700 1900 8300 1900
Wire Wire Line
	9200 1700 9600 1700
Wire Wire Line
	9600 1800 9200 1800
Wire Wire Line
	9200 1900 9600 1900
Text Label 9600 1300 0    50   ~ 0
5V_TRICKLE
Wire Wire Line
	9200 1300 9600 1300
$Comp
L MCU_Microchip_ATmega:ATmega328-PU U2
U 1 1 5E42FE47
P 4250 5750
F 0 "U2" H 4000 7350 50  0000 R CNN
F 1 "ATmega328-PU" H 5150 7450 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4250 5750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 4250 5750 50  0001 C CNN
	1    4250 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4250 4250 3950
Wire Wire Line
	4350 4250 4350 3950
NoConn ~ 3650 4550
$Comp
L power:GND #PWR09
U 1 1 5E42FE61
P 4250 7550
F 0 "#PWR09" H 4250 7300 50  0001 C CNN
F 1 "GND" H 4255 7377 50  0000 C CNN
F 2 "" H 4250 7550 50  0001 C CNN
F 3 "" H 4250 7550 50  0001 C CNN
	1    4250 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 7250 4250 7550
Wire Wire Line
	6300 4650 6300 4850
Wire Wire Line
	6300 5750 6300 5550
Wire Wire Line
	5550 5150 5550 4850
Wire Wire Line
	5550 4850 6300 4850
Connection ~ 6300 4850
Wire Wire Line
	6300 4850 6300 5050
Wire Wire Line
	4850 5250 5550 5250
Wire Wire Line
	5550 5250 5550 5550
Wire Wire Line
	5550 5550 6300 5550
Connection ~ 6300 5550
Wire Wire Line
	6300 5550 6300 5350
Wire Wire Line
	4850 5150 5550 5150
$Comp
L power:GND #PWR08
U 1 1 5E42FE96
P 6300 6050
F 0 "#PWR08" H 6300 5800 50  0001 C CNN
F 1 "GND" H 6305 5877 50  0000 C CNN
F 2 "" H 6300 6050 50  0001 C CNN
F 3 "" H 6300 6050 50  0001 C CNN
	1    6300 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4350 6300 4000
Wire Wire Line
	6300 4000 5850 4000
Wire Wire Line
	5850 4000 5850 4150
Text Label 5100 5850 0    50   ~ 0
COMPUTER_SDA
Text Label 5100 5950 0    50   ~ 0
COMPUTER_SCL
Wire Wire Line
	4850 5850 5100 5850
Wire Wire Line
	4850 5950 5100 5950
$Comp
L power:GND #PWR06
U 1 1 5E42FEA7
P 5850 4150
F 0 "#PWR06" H 5850 3900 50  0001 C CNN
F 1 "GND" H 5855 3977 50  0000 C CNN
F 2 "" H 5850 4150 50  0001 C CNN
F 3 "" H 5850 4150 50  0001 C CNN
	1    5850 4150
	1    0    0    -1  
$EndComp
Text Label 8300 1400 2    50   ~ 0
PROT
Text Label 9600 1400 0    50   ~ 0
-10V
Text Label 9600 1600 0    50   ~ 0
LPIACT:L1_LP
Wire Wire Line
	8700 1300 8300 1300
Wire Wire Line
	9200 1100 9600 1100
Wire Wire Line
	9200 1400 9600 1400
Wire Wire Line
	8700 1400 8300 1400
Wire Wire Line
	9600 1600 9200 1600
$Comp
L power:GND #PWR03
U 1 1 5E4745C4
P 10300 2100
F 0 "#PWR03" H 10300 1850 50  0001 C CNN
F 1 "GND" H 10305 1927 50  0000 C CNN
F 2 "" H 10300 2100 50  0001 C CNN
F 3 "" H 10300 2100 50  0001 C CNN
	1    10300 2100
	1    0    0    -1  
$EndComp
Text Label 8300 1300 2    50   ~ 0
DCO
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J20
U 1 1 5E3F686C
P 8900 1500
F 0 "J20" H 8950 2117 50  0000 C CNN
F 1 "Conn_02x10_Odd_Even" H 8950 2026 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 8900 1500 50  0001 C CNN
F 3 "https://cdn.amphenol-icc.com/media/wysiwyg/files/drawing/69168.pdf" H 8900 1500 50  0001 C CNN
F 4 "digikey" H 8900 1500 50  0001 C CNN "Vendor"
F 5 "609-2430-ND" H 8900 1500 50  0001 C CNN "Part#"
	1    8900 1500
	1    0    0    -1  
$EndComp
Text Label 8300 2000 2    50   ~ 0
LINE_SENSE
Wire Wire Line
	10300 1200 10300 2000
Wire Wire Line
	9200 1200 10300 1200
Wire Wire Line
	9200 2000 10300 2000
Connection ~ 10300 2000
Wire Wire Line
	10300 2000 10300 2100
Wire Wire Line
	8700 2000 8300 2000
Wire Wire Line
	1350 850  1400 850 
Text Label 1400 700  0    50   ~ 0
5V_TRICKLE
Wire Wire Line
	1400 700  1400 850 
Connection ~ 1400 850 
Wire Wire Line
	1400 850  1450 850 
Wire Wire Line
	4250 3950 4300 3950
Text Label 4300 3750 0    50   ~ 0
COMPUTER_5V
Wire Wire Line
	4300 3750 4300 3950
Connection ~ 4300 3950
Wire Wire Line
	4300 3950 4350 3950
Text Notes 900  4800 0    50   ~ 0
Sends initialization sequence to the IVAD board
Text Notes 2100 6550 0    50   ~ 0
Sends EDID data to computer via DE15\nconnector
$Comp
L Device:C C2
U 1 1 5E552ABD
P 3400 2800
F 0 "C2" H 3515 2846 50  0000 L CNN
F 1 "22pF" H 3515 2755 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D9.0mm_W5.0mm_P10.00mm" H 3438 2650 50  0001 C CNN
F 3 "http://www.vishay.com/docs/28537/vy1series.pdf" H 3400 2800 50  0001 C CNN
F 4 "digikey" H 3400 2800 50  0001 C CNN "Vendor"
F 5 "BC2364-ND" H 3400 2800 50  0001 C CNN "Part#"
	1    3400 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5E552F81
P 6300 4500
F 0 "C3" H 6415 4546 50  0000 L CNN
F 1 "22pF" H 6415 4455 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D9.0mm_W5.0mm_P10.00mm" H 6338 4350 50  0001 C CNN
F 3 "http://www.vishay.com/docs/28537/vy1series.pdf" H 6300 4500 50  0001 C CNN
F 4 "digikey" H 6300 4500 50  0001 C CNN "Vendor"
F 5 "BC2364-ND" H 6300 4500 50  0001 C CNN "Part#"
	1    6300 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5E554B25
P 6300 5900
F 0 "C4" H 6415 5946 50  0000 L CNN
F 1 "22pF" H 6415 5855 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D9.0mm_W5.0mm_P10.00mm" H 6338 5750 50  0001 C CNN
F 3 "http://www.vishay.com/docs/28537/vy1series.pdf" H 6300 5900 50  0001 C CNN
F 4 "digikey" H 6300 5900 50  0001 C CNN "Vendor"
F 5 "BC2364-ND" H 6300 5900 50  0001 C CNN "Part#"
	1    6300 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y2
U 1 1 5E555ABD
P 6300 5200
F 0 "Y2" V 6254 5331 50  0000 L CNN
F 1 "Crystal" V 6345 5331 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 6300 5200 50  0001 C CNN
F 3 "http://www.txccrystal.com/images/pdf/9b.pdf" H 6300 5200 50  0001 C CNN
F 4 "digikey" V 6300 5200 50  0001 C CNN "Vendor"
F 5 "887-2015-ND" V 6300 5200 50  0001 C CNN "Part#"
	1    6300 5200
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5E55AF97
P 5100 1400
F 0 "H1" H 5200 1446 50  0000 L CNN
F 1 "MountingHole" H 5200 1355 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad" H 5100 1400 50  0001 C CNN
F 3 "~" H 5100 1400 50  0001 C CNN
	1    5100 1400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5E55BA96
P 5250 2200
F 0 "H2" H 5350 2246 50  0000 L CNN
F 1 "MountingHole" H 5350 2155 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad" H 5250 2200 50  0001 C CNN
F 3 "~" H 5250 2200 50  0001 C CNN
	1    5250 2200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
