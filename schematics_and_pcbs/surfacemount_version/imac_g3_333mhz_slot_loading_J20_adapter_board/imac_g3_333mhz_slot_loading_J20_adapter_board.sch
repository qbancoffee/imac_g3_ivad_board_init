EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "iMac G3 333 Mhz Slot Loading Power and Video Board"
Date "2020-03-27"
Rev "3"
Comp ""
Comment1 "and control other functions."
Comment2 "used to send the i2c IVAD inititialization sequence and the EDID info to the computer"
Comment3 "Powers atmega328p fromJ20 and from the VGA cable"
Comment4 "Rocky Hill"
$EndDescr
NoConn ~ 3650 2600
$Comp
L power:GND #PWR09
U 1 1 5E39A336
P 4250 5600
F 0 "#PWR09" H 4250 5350 50  0001 C CNN
F 1 "GND" H 4255 5427 50  0000 C CNN
F 2 "" H 4250 5600 50  0001 C CNN
F 3 "" H 4250 5600 50  0001 C CNN
	1    4250 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E39D342
P 6300 2550
F 0 "C1" H 6415 2596 50  0000 L CNN
F 1 "22pF" H 6415 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6338 2400 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810271113_Samsung-Electro-Mechanics-CL21C220JBANNNC_C1804.pdf" H 6300 2550 50  0001 C CNN
F 4 "JLCPCB" H 6300 2550 50  0001 C CNN "Vendor"
F 5 "C1804" H 6300 2550 50  0001 C CNN "Vendor part#"
F 6 "CL21C220JBANNNC" H 6300 2550 50  0001 C CNN "Manufacturer part#"
	1    6300 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2700 6300 2900
Wire Wire Line
	6300 3800 6300 3600
Wire Wire Line
	5550 3200 5550 2900
Wire Wire Line
	5550 2900 6300 2900
Connection ~ 6300 2900
Wire Wire Line
	6300 2900 6300 3100
Wire Wire Line
	4850 3300 5550 3300
Wire Wire Line
	5550 3300 5550 3600
Wire Wire Line
	5550 3600 6300 3600
Connection ~ 6300 3600
Wire Wire Line
	6300 3600 6300 3400
Wire Wire Line
	4850 3200 5550 3200
$Comp
L power:GND #PWR07
U 1 1 5E3A7604
P 6300 4100
F 0 "#PWR07" H 6300 3850 50  0001 C CNN
F 1 "GND" H 6305 3927 50  0000 C CNN
F 2 "" H 6300 4100 50  0001 C CNN
F 3 "" H 6300 4100 50  0001 C CNN
	1    6300 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2400 6300 2050
Wire Wire Line
	6300 2050 5850 2050
Wire Wire Line
	5850 2050 5850 2200
Text Label 5100 4700 0    50   ~ 0
IVAD_SDA
Text Label 5100 4800 0    50   ~ 0
IVAD_SCL
Wire Wire Line
	4850 4700 5100 4700
Wire Wire Line
	4850 4800 5100 4800
$Comp
L power:GND #PWR04
U 1 1 5E3B5B7F
P 5850 2200
F 0 "#PWR04" H 5850 1950 50  0001 C CNN
F 1 "GND" H 5855 2027 50  0000 C CNN
F 2 "" H 5850 2200 50  0001 C CNN
F 3 "" H 5850 2200 50  0001 C CNN
	1    5850 2200
	1    0    0    -1  
$EndComp
Text Notes 3800 5950 0    50   ~ 0
Sends initialization sequence to the IVAD board
Wire Wire Line
	8700 2000 8300 2000
Wire Wire Line
	10300 2000 10300 2100
Connection ~ 10300 2000
Wire Wire Line
	9200 2000 10300 2000
Wire Wire Line
	9200 1200 10300 1200
Wire Wire Line
	10300 1200 10300 2000
Text Label 8300 2000 2    50   ~ 0
LINE_SENSE
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J2
U 1 1 5E3F686C
P 8900 1500
F 0 "J2" H 8950 2117 50  0000 C CNN
F 1 "Conn_02x10_Odd_Even" H 8950 2026 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 8900 1500 50  0001 C CNN
F 3 "http://suddendocs.samtec.com/prints/tsw-xxx-xx-x-x-xx-xxx-footprint.pdf" H 8900 1500 50  0001 C CNN
F 4 "digikey" H 8900 1500 50  0001 C CNN "Vendor"
F 5 "SAM1068-10-ND" H 8900 1500 50  0001 C CNN "Part#"
	1    8900 1500
	1    0    0    -1  
$EndComp
Text Label 8300 1300 2    50   ~ 0
DCO
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
Wire Wire Line
	9600 1600 9200 1600
Wire Wire Line
	8700 1400 8300 1400
Wire Wire Line
	9200 1400 9600 1400
Wire Wire Line
	9200 1100 9600 1100
Wire Wire Line
	8700 1300 8300 1300
Text Label 9600 1600 0    50   ~ 0
LPIACT:L1_LP
Text Label 9600 1400 0    50   ~ 0
-10V
Text Label 8300 1400 2    50   ~ 0
PROT
Wire Wire Line
	9200 1300 9600 1300
Text Label 9600 1300 0    50   ~ 0
5V_TRICKLE
Wire Wire Line
	9200 1900 9600 1900
Wire Wire Line
	9600 1800 9200 1800
Wire Wire Line
	9200 1700 9600 1700
Wire Wire Line
	8700 1900 8300 1900
Wire Wire Line
	8300 1800 8700 1800
Wire Wire Line
	8700 1700 8300 1700
Wire Wire Line
	8300 1600 8700 1600
Text Label 9600 1900 0    50   ~ 0
GND_RED
Text Label 8300 1900 2    50   ~ 0
RED
Text Label 9600 1800 0    50   ~ 0
GND_GREEN
Text Label 8300 1800 2    50   ~ 0
GREEN
Text Label 9600 1700 0    50   ~ 0
GND_BLUE
Text Label 8300 1700 2    50   ~ 0
BLUE
Text Label 8300 1600 2    50   ~ 0
V_SYNC
Wire Wire Line
	8300 1500 8700 1500
Wire Wire Line
	7650 1200 8700 1200
Wire Wire Line
	7650 1200 7650 1300
Text Label 8300 1500 2    50   ~ 0
H_SYNC
Wire Wire Line
	9250 3800 9500 3800
Wire Wire Line
	9250 3600 9500 3600
Wire Wire Line
	9250 3400 9500 3400
Wire Wire Line
	9250 3200 9500 3200
Text Label 9500 3600 0    50   ~ 0
V_SYNC
Text Label 9500 3400 0    50   ~ 0
H_SYNC
NoConn ~ 9250 3000
Wire Wire Line
	8400 3500 8650 3500
Wire Wire Line
	8400 3400 8650 3400
Wire Wire Line
	8400 3300 8650 3300
Wire Wire Line
	8400 3200 8650 3200
Wire Wire Line
	8400 3100 8650 3100
Wire Wire Line
	8400 3000 8650 3000
Wire Wire Line
	8400 2900 8650 2900
Connection ~ 8400 3800
Wire Wire Line
	8650 3800 8400 3800
Wire Wire Line
	8400 3700 8400 3800
Wire Wire Line
	8650 3700 8400 3700
$Comp
L power:GND #PWR06
U 1 1 5E3D17A3
P 8400 3800
F 0 "#PWR06" H 8400 3550 50  0001 C CNN
F 1 "GND" H 8405 3627 50  0000 C CNN
F 2 "" H 8400 3800 50  0001 C CNN
F 3 "" H 8400 3800 50  0001 C CNN
	1    8400 3800
	1    0    0    -1  
$EndComp
NoConn ~ 8650 3600
Text Label 8400 3500 2    50   ~ 0
COMPUTER_5V
Text Label 8400 3400 2    50   ~ 0
BLUE
Text Label 8400 3300 2    50   ~ 0
GND_BLUE
Text Label 8400 3200 2    50   ~ 0
GREEN
Text Label 8400 3100 2    50   ~ 0
GND_GREEN
Text Label 8400 2900 2    50   ~ 0
GND_RED
Text Label 8400 3000 2    50   ~ 0
RED
$Comp
L Connector:DB15_Female_HighDensity J4
U 1 1 5E3B898B
P 8950 3400
F 0 "J4" H 8950 4267 50  0000 C CNN
F 1 "DB15_Female_HighDensity" H 8950 4176 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-15-HD_Female_Horizontal_P2.29x1.98mm_EdgePinOffset8.35mm_Housed_MountingHolesOffset10.89mm" H 8000 3800 50  0001 C CNN
F 3 "https://jlcpcb.com/parts/componentSearch?isSecondLevel=true&firstName=CONNECTORS&name=D-SUB%2FDVI%2FHDMI%20CONNECTORS" H 8000 3800 50  0001 C CNN
F 4 "JLCPCB" H 8950 3400 50  0001 C CNN "Vendor"
F 5 "C235854" H 8950 3400 50  0001 C CNN "Vendor part#"
F 6 "Z-SUBHRBF707A000" H 8950 3400 50  0001 C CNN "Manufacturer part#"
	1    8950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 1500 9200 1500
Text Label 9600 1500 0    50   ~ 0
PFW
Wire Wire Line
	8300 1100 8700 1100
Text Label 9600 1100 0    50   ~ 0
IVAD_SCL
Text Label 8300 1100 2    50   ~ 0
IVAD_SDA
$Comp
L power:GND #PWR01
U 1 1 5E3A84E9
P 7650 1300
F 0 "#PWR01" H 7650 1050 50  0001 C CNN
F 1 "GND" H 7655 1127 50  0000 C CNN
F 2 "" H 7650 1300 50  0001 C CNN
F 3 "" H 7650 1300 50  0001 C CNN
	1    7650 1300
	1    0    0    -1  
$EndComp
Text Label 9900 3800 0    50   ~ 0
COMPUTER_SCL
Text Label 9900 3200 0    50   ~ 0
COMPUTER_SDA
Text Notes 3850 6250 0    50   ~ 0
Sends EDID data to computer via DE15\nconnector and monitors VSYNC to detect\nif computer is on or off.
Wire Wire Line
	4300 2000 4350 2000
Text Label 5500 1150 0    50   ~ 0
COMPUTER_5V
Connection ~ 4300 2000
Wire Wire Line
	4250 2000 4300 2000
Wire Wire Line
	4850 4000 5100 4000
Wire Wire Line
	4850 3900 5100 3900
Text Label 5100 4000 0    50   ~ 0
COMPUTER_SCL
Text Label 5100 3900 0    50   ~ 0
COMPUTER_SDA
Wire Wire Line
	4350 2300 4350 2000
Wire Wire Line
	4250 2300 4250 2000
Wire Wire Line
	6750 5100 7000 5100
Wire Wire Line
	7000 5100 7000 5200
Wire Wire Line
	7000 5300 6750 5300
Text Label 7300 4800 0    50   ~ 0
PFW
Text Label 7300 4650 0    50   ~ 0
LPIACT:L1_LP
Wire Wire Line
	7000 5200 7300 5200
Connection ~ 7000 5200
Wire Wire Line
	7000 5200 7000 5300
Wire Wire Line
	6750 4100 6750 4900
Text Label 6800 6150 0    50   ~ 0
5V_TRICKLE
Wire Wire Line
	6750 5500 6750 6150
Wire Wire Line
	6750 6150 6800 6150
$Comp
L Device:D_Schottky_ALT D1
U 1 1 5E621824
P 4650 1550
F 0 "D1" V 4696 1471 50  0000 R CNN
F 1 "D_Schottky_ALT" V 4605 1471 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 4650 1550 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1809140216_Changjiang-Electronics-Tech--CJ-B5819W-SL_C8598.pdf" H 4650 1550 50  0001 C CNN
F 4 "JLCPCB" H 4650 1550 50  0001 C CNN "Vendor"
F 5 "C8598" H 4650 1550 50  0001 C CNN "Vendor part#"
F 6 "B5819W SL" V 4650 1550 50  0001 C CNN "Manufacturer part#"
	1    4650 1550
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Schottky_ALT D2
U 1 1 5E621F90
P 5500 1550
F 0 "D2" V 5546 1471 50  0000 R CNN
F 1 "D_Schottky_ALT" V 5455 1471 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 5500 1550 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1809140216_Changjiang-Electronics-Tech--CJ-B5819W-SL_C8598.pdf" H 5500 1550 50  0001 C CNN
F 4 "JLCPCB" H 5500 1550 50  0001 C CNN "Vendor"
F 5 "C8598" H 5500 1550 50  0001 C CNN "Vendor part#"
F 6 "B5819W SL" V 5500 1550 50  0001 C CNN "Manufacturer part#"
	1    5500 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 1700 4650 1700
Wire Wire Line
	5500 1700 4650 1700
Connection ~ 4650 1700
Wire Wire Line
	5500 1150 5500 1400
Text Label 4650 1100 0    50   ~ 0
5V_TRICKLE
Wire Wire Line
	4650 1100 4650 1400
NoConn ~ 4850 3500
NoConn ~ 4850 3600
NoConn ~ 4850 3700
NoConn ~ 4850 3800
NoConn ~ 4850 4900
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5E68104D
P 3750 5550
F 0 "#FLG02" H 3750 5625 50  0001 C CNN
F 1 "PWR_FLAG" H 3750 5723 50  0000 C CNN
F 2 "" H 3750 5550 50  0001 C CNN
F 3 "~" H 3750 5550 50  0001 C CNN
	1    3750 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5550 4250 5550
Connection ~ 4250 5550
Wire Wire Line
	4250 5550 4250 5600
Wire Wire Line
	2500 1450 2150 1450
Wire Wire Line
	2150 1350 2500 1350
Wire Wire Line
	2150 1150 2500 1150
Text Label 2500 1450 0    50   ~ 0
LINE_SENSE
Text Label 2500 1350 0    50   ~ 0
-10V
Text Label 3200 1250 0    50   ~ 0
PROT
Text Label 2500 1150 0    50   ~ 0
DCO
Text Label 5600 4250 0    50   ~ 0
PWR_BTN
Text Label 2500 1550 0    50   ~ 0
PWR_BTN
Wire Wire Line
	2500 1550 2300 1550
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5E7116D4
P 4600 7300
F 0 "H2" H 4700 7349 50  0000 L CNN
F 1 "MountingHole_Pad" H 4700 7258 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad" H 4600 7300 50  0001 C CNN
F 3 "~" H 4600 7300 50  0001 C CNN
	1    4600 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5E712C50
P 4600 7550
F 0 "#PWR011" H 4600 7300 50  0001 C CNN
F 1 "GND" H 4605 7377 50  0000 C CNN
F 2 "" H 4600 7550 50  0001 C CNN
F 3 "" H 4600 7550 50  0001 C CNN
	1    4600 7550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R1
U 1 1 5E723C5A
P 1350 1500
F 0 "R1" H 1555 1500 50  0000 C CNN
F 1 "10k" H 1550 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 1350 1500 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810271610_UNI-ROYAL-Uniroyal-Elec-0805W8F1002T5E_C17414.pdf" H 1350 1500 50  0001 C CNN
F 4 "JLCPCB" H 1350 1500 50  0001 C CNN "Vendor"
F 5 "C17414" H 1350 1500 50  0001 C CNN "Vendor part#"
F 6 "0805W8F1002T5E" H 1350 1500 50  0001 C CNN "Manufacturer part#"
	1    1350 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	1350 1600 1350 1950
Wire Wire Line
	1350 1950 2300 1950
Wire Wire Line
	2300 1950 2300 1550
Connection ~ 2300 1550
Wire Wire Line
	2300 1550 2150 1550
Text Label 1350 1150 2    50   ~ 0
5V_TRICKLE
Wire Wire Line
	1350 1150 1350 1400
$Comp
L Connector:Screw_Terminal_01x06 J1
U 1 1 5E74116A
P 1950 1350
F 0 "J1" H 1868 825 50  0000 C CNN
F 1 "Screw_Terminal_01x06" H 1868 916 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_PT-1,5-6-5.0-H_1x06_P5.00mm_Horizontal" H 1950 1350 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Phoenix%20Contact%20PDFs/1935200.pdf" H 1950 1350 50  0001 C CNN
F 4 "digikey" H 1950 1350 50  0001 C CNN "Vendor"
F 5 "277-1581-ND" H 1950 1350 50  0001 C CNN "Part#"
	1    1950 1350
	-1   0    0    1   
$EndComp
Text Label 2500 1050 0    50   ~ 0
PWR_LED
Wire Wire Line
	2150 1050 2500 1050
Text Label 7300 4450 0    50   ~ 0
PWR_LED
Wire Wire Line
	7300 4450 7300 5200
Wire Wire Line
	4600 7400 4600 7500
Text Label 3350 7100 0    50   ~ 0
GND_BLUE
Text Label 3350 7200 0    50   ~ 0
GND_GREEN
Text Label 3350 7300 0    50   ~ 0
GND_RED
$Comp
L power:GND #PWR08
U 1 1 5E77D79F
P 3350 7450
F 0 "#PWR08" H 3350 7200 50  0001 C CNN
F 1 "GND" H 3355 7277 50  0000 C CNN
F 2 "" H 3350 7450 50  0001 C CNN
F 3 "" H 3350 7450 50  0001 C CNN
	1    3350 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 7100 3350 7450
$Comp
L Device:CP C3
U 1 1 5E5FB13C
P 1100 6050
F 0 "C3" H 1150 6150 50  0000 L CNN
F 1 "100uF 6.3V" H 1100 5750 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-21_Kemet-B_Pad1.50x2.35mm_HandSolder" H 1138 5900 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1811071223_AVX-TAJB107K006RNJ_C16133.pdf" H 1100 6050 50  0001 C CNN
F 4 "JLCPCB" H 1100 6050 50  0001 C CNN "Vendor"
F 5 "C16133" H 1100 6050 50  0001 C CNN "Vendor part#"
F 6 "TAJB107K006RNJ" H 1100 6050 50  0001 C CNN "Manufacturer part#"
	1    1100 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E5FD400
P 1900 6650
F 0 "#PWR010" H 1900 6400 50  0001 C CNN
F 1 "GND" H 1905 6477 50  0000 C CNN
F 2 "" H 1900 6650 50  0001 C CNN
F 3 "" H 1900 6650 50  0001 C CNN
	1    1900 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 6200 1100 6550
Text Label 1900 5350 2    50   ~ 0
5V_TRICKLE
Wire Wire Line
	1100 5600 1100 5900
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5E630257
P 9650 3200
F 0 "JP1" H 9650 3405 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9650 3314 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9650 3200 50  0001 C CNN
F 3 "~" H 9650 3200 50  0001 C CNN
	1    9650 3200
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5E6323A4
P 9650 3800
F 0 "JP2" H 9650 4005 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9650 3914 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9650 3800 50  0001 C CNN
F 3 "~" H 9650 3800 50  0001 C CNN
	1    9650 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 3200 9900 3200
Wire Wire Line
	9800 3800 9900 3800
Wire Wire Line
	4300 1700 4300 2000
Wire Wire Line
	3100 1700 3100 1250
Connection ~ 3100 1250
Wire Wire Line
	3100 1250 3200 1250
$Comp
L power:GND #PWR02
U 1 1 5E933CC7
P 3100 1900
F 0 "#PWR02" H 3100 1650 50  0001 C CNN
F 1 "GND" H 3105 1727 50  0000 C CNN
F 2 "" H 3100 1900 50  0001 C CNN
F 3 "" H 3100 1900 50  0001 C CNN
	1    3100 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 1250 3100 1250
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5E93EB52
P 4300 1250
F 0 "#FLG01" H 4300 1325 50  0001 C CNN
F 1 "PWR_FLAG" H 4300 1423 50  0000 C CNN
F 2 "" H 4300 1250 50  0001 C CNN
F 3 "~" H 4300 1250 50  0001 C CNN
	1    4300 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1250 4300 1700
Connection ~ 4300 1700
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J3
U 1 1 5E95321E
P 1750 3300
F 0 "J3" H 1800 3617 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 1800 3526 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 1750 3300 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Wurth%20Electronics%20PDFs/Box%20Header_IDC%20Conn%20WR-BHD.pdf" H 1750 3300 50  0001 C CNN
F 4 "digikey" H 1750 3300 50  0001 C CNN "Vendor"
F 5 "732-5394-ND" H 1750 3300 50  0001 C CNN "Part#"
	1    1750 3300
	1    0    0    -1  
$EndComp
Text Label 2400 2750 0    50   ~ 0
5V_TRICKLE
Wire Wire Line
	2400 3200 2400 2750
Wire Wire Line
	2050 3200 2400 3200
Text Label 2050 3300 0    50   ~ 0
MOSI
Text Label 1550 3200 2    50   ~ 0
MISO
Text Label 1550 3300 2    50   ~ 0
SCK
Text Label 1550 3400 2    50   ~ 0
~RESET
$Comp
L power:GND #PWR05
U 1 1 5E9606E5
P 2400 3500
F 0 "#PWR05" H 2400 3250 50  0001 C CNN
F 1 "GND" H 2405 3327 50  0000 C CNN
F 2 "" H 2400 3500 50  0001 C CNN
F 3 "" H 2400 3500 50  0001 C CNN
	1    2400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3400 2400 3400
Wire Wire Line
	2400 3400 2400 3500
Wire Wire Line
	1550 3400 1250 3400
Wire Wire Line
	1250 3400 1250 3600
Wire Wire Line
	1250 3800 1250 4100
Wire Wire Line
	1250 4100 2800 4100
Wire Wire Line
	2800 4100 2800 3200
Wire Wire Line
	2800 3200 2400 3200
Connection ~ 2400 3200
Text Label 5150 2900 0    50   ~ 0
MOSI
Text Label 5150 3000 0    50   ~ 0
MISO
Text Label 5150 3100 0    50   ~ 0
SCK
Text Label 5100 4100 0    50   ~ 0
~RESET
Wire Wire Line
	4850 4100 5100 4100
Wire Wire Line
	5150 2900 4850 2900
Wire Wire Line
	5150 3000 4850 3000
Wire Wire Line
	5150 3100 4850 3100
NoConn ~ 4850 4500
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5E9C8BC5
P 4250 7300
F 0 "H1" H 4350 7349 50  0000 L CNN
F 1 "MountingHole_Pad" H 4350 7258 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad" H 4250 7300 50  0001 C CNN
F 3 "~" H 4250 7300 50  0001 C CNN
	1    4250 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 7400 4250 7500
Wire Wire Line
	4250 7500 4600 7500
Connection ~ 4600 7500
Wire Wire Line
	4600 7500 4600 7550
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J5
U 1 1 5E9E28CC
P 1800 4850
F 0 "J5" H 1850 5167 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 1850 5076 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 1800 4850 50  0001 C CNN
F 3 "https://cdn.amphenol-icc.com/media/wysiwyg/files/drawing/67996.pdf" H 1800 4850 50  0001 C CNN
F 4 "digikey" H 1800 4850 50  0001 C CNN "Vendor"
F 5 "609-3234-ND" H 1800 4850 50  0001 C CNN "Part#"
	1    1800 4850
	1    0    0    -1  
$EndComp
Text Label 1600 4750 2    50   ~ 0
COMPUTER_SDA
Text Label 2100 4750 0    50   ~ 0
COMPUTER_SCL
$Comp
L Device:C C2
U 1 1 5EA0EC6A
P 6300 3950
F 0 "C2" H 6415 3996 50  0000 L CNN
F 1 "22pF" H 6415 3905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6338 3800 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810271113_Samsung-Electro-Mechanics-CL21C220JBANNNC_C1804.pdf" H 6300 3950 50  0001 C CNN
F 4 "JLCPCB" H 6300 3950 50  0001 C CNN "Vendor"
F 5 "C1804" H 6300 3950 50  0001 C CNN "Vendor part#"
F 6 "CL21C220JBANNNC" H 6300 3950 50  0001 C CNN "Manufacturer part#"
	1    6300 3950
	1    0    0    -1  
$EndComp
Text Label 4850 4300 0    50   ~ 0
SERIAL_RX
Text Label 4850 4400 0    50   ~ 0
SERIAL_TX
Wire Wire Line
	5600 4250 5600 4600
Wire Wire Line
	4850 4600 5600 4600
Text Label 1600 4850 2    50   ~ 0
SERIAL_RX
Text Label 1600 4950 2    50   ~ 0
SERIAL_TX
Text Label 4850 2600 0    50   ~ 0
PB0
Text Label 4850 2700 0    50   ~ 0
PB1
Text Label 2100 4850 0    50   ~ 0
PB0
Text Label 2100 4950 0    50   ~ 0
PB1
$Comp
L Device:R_Small_US R2
U 1 1 5E80ECB2
P 3100 1800
F 0 "R2" H 3305 1800 50  0000 C CNN
F 1 "10k" H 3300 1900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 3100 1800 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810271610_UNI-ROYAL-Uniroyal-Elec-0805W8F1002T5E_C17414.pdf" H 3100 1800 50  0001 C CNN
F 4 "JLCPCB" H 3100 1800 50  0001 C CNN "Vendor"
F 5 "C17414" H 3100 1800 50  0001 C CNN "Vendor part#"
F 6 "0805W8F1002T5E" H 3100 1800 50  0001 C CNN "Manufacturer part#"
	1    3100 1800
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R3
U 1 1 5E810630
P 1250 3700
F 0 "R3" H 1455 3700 50  0000 C CNN
F 1 "10k" H 1450 3800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 1250 3700 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810271610_UNI-ROYAL-Uniroyal-Elec-0805W8F1002T5E_C17414.pdf" H 1250 3700 50  0001 C CNN
F 4 "JLCPCB" H 1250 3700 50  0001 C CNN "Vendor"
F 5 "C17414" H 1250 3700 50  0001 C CNN "Vendor part#"
F 6 "0805W8F1002T5E" H 1250 3700 50  0001 C CNN "Manufacturer part#"
	1    1250 3700
	-1   0    0    1   
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP3
U 1 1 5E9A08C1
P 5500 2800
F 0 "JP3" H 5500 3050 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 5500 2950 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 5500 2800 50  0001 C CNN
F 3 "~" H 5500 2800 50  0001 C CNN
	1    5500 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2800 4850 2800
Text Label 5650 2800 0    50   ~ 0
V_SYNC
NoConn ~ 7200 5700
$Comp
L MCU_Microchip_ATmega:ATmega328P-AU U1
U 1 1 61ADE917
P 4250 3800
F 0 "U1" H 3950 5350 50  0000 C CNN
F 1 "ATmega328P-AU" H 3400 2600 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 4250 3800 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 4250 3800 50  0001 C CNN
F 4 "JLCPCB" H 4250 3800 50  0001 C CNN "Vendor"
F 5 "C14877" H 4250 3800 50  0001 C CNN "Vendor part#"
F 6 "ATMEGA328P-AU" H 4250 3800 50  0001 C CNN "Manufacturer part#"
	1    4250 3800
	1    0    0    -1  
$EndComp
$Comp
L Relay_SolidState:FOD4208 U3
U 1 1 61B68D06
P 6450 5400
F 0 "U3" H 6450 5050 50  0000 C CNN
F 1 "CPC1972GSTR" H 6450 5150 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm_SMDSocket_SmallPads" H 6250 5200 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/FOD4218-D.PDF" H 6450 5400 50  0001 L CNN
F 4 "JLCPCB" H 6450 5400 50  0001 C CNN "Vendor"
F 5 "C150430" H 6450 5400 50  0001 C CNN "Vendor part#"
F 6 "CPC1972GSTR" H 6450 5400 50  0001 C CNN "Manufacturer part#"
	1    6450 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 5300 4250 5550
Wire Wire Line
	4250 5550 4850 5550
Wire Wire Line
	5200 5550 5300 5550
Wire Wire Line
	5300 5550 5300 5500
Wire Wire Line
	4850 5000 5300 5000
$Comp
L Relay_SolidState:FOD4208 U2
U 1 1 61BAF2D0
P 6450 5000
F 0 "U2" H 6450 5325 50  0000 C CNN
F 1 "CPC1972GSTR" H 6450 5234 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm_SMDSocket_SmallPads" H 6250 4800 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/FOD4218-D.PDF" H 6450 5000 50  0001 L CNN
F 4 "JLCPCB" H 6450 5000 50  0001 C CNN "Vendor"
F 5 "C150430" H 6450 5000 50  0001 C CNN "Vendor part#"
F 6 "CPC1972GSTR" H 6450 5000 50  0001 C CNN "Manufacturer part#"
	1    6450 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5500 6150 5500
Wire Wire Line
	6150 5100 6000 5100
Wire Wire Line
	6000 5100 6000 5200
Wire Wire Line
	6000 5300 6150 5300
Wire Wire Line
	5300 5000 5300 5200
Wire Wire Line
	5300 5200 6000 5200
Connection ~ 6000 5200
Wire Wire Line
	6000 5200 6000 5300
Wire Wire Line
	6750 4100 6300 4100
Connection ~ 6300 4100
$Comp
L Device:R_Small_US R4
U 1 1 5E5FAFCC
P 5100 5550
F 0 "R4" V 5305 5550 50  0000 C CNN
F 1 "220" V 5214 5550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5100 5550 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810241809_UNI-ROYAL-Uniroyal-Elec-0805W8F2200T5E_C17557.pdf" H 5100 5550 50  0001 C CNN
F 4 "JLCPCB" V 5100 5550 50  0001 C CNN "Vendor"
F 5 "C17557" V 5100 5550 50  0001 C CNN "Vendor part#"
F 6 "0805W8F2200T5E" V 5100 5550 50  0001 C CNN "Manufacturer part#"
	1    5100 5550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R5
U 1 1 61BF961D
P 6000 4650
F 0 "R5" H 5900 4700 50  0000 C CNN
F 1 "220" H 5850 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 6000 4650 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810241809_UNI-ROYAL-Uniroyal-Elec-0805W8F2200T5E_C17557.pdf" H 6000 4650 50  0001 C CNN
F 4 "JLCPCB" V 6000 4650 50  0001 C CNN "Vendor"
F 5 "C17557" V 6000 4650 50  0001 C CNN "Vendor part#"
F 6 "0805W8F2200T5E" V 6000 4650 50  0001 C CNN "Manufacturer part#"
	1    6000 4650
	1    0    0    -1  
$EndComp
Text Label 6150 4450 0    50   ~ 0
5V_TRICKLE
Wire Wire Line
	6150 4450 6000 4450
Wire Wire Line
	6000 4450 6000 4550
Wire Wire Line
	6000 4750 6000 4900
Wire Wire Line
	6000 4900 6150 4900
$Comp
L Device:R_Small_US R6
U 1 1 61C22880
P 4850 5300
F 0 "R6" H 5055 5300 50  0000 C CNN
F 1 "10k" H 5050 5400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4850 5300 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810271610_UNI-ROYAL-Uniroyal-Elec-0805W8F1002T5E_C17414.pdf" H 4850 5300 50  0001 C CNN
F 4 "JLCPCB" H 4850 5300 50  0001 C CNN "Vendor"
F 5 "C17414" H 4850 5300 50  0001 C CNN "Vendor part#"
F 6 "0805W8F1002T5E" H 4850 5300 50  0001 C CNN "Manufacturer part#"
	1    4850 5300
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 5200 4850 5000
Connection ~ 4850 5000
Wire Wire Line
	4850 5400 4850 5550
Connection ~ 4850 5550
Wire Wire Line
	4850 5550 5000 5550
$Comp
L Device:CP C4
U 1 1 61C38E12
P 1600 6050
F 0 "C4" H 1650 6150 50  0000 L CNN
F 1 "100uF 6.3V" H 1600 5750 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-21_Kemet-B_Pad1.50x2.35mm_HandSolder" H 1638 5900 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1811071223_AVX-TAJB107K006RNJ_C16133.pdf" H 1600 6050 50  0001 C CNN
F 4 "JLCPCB" H 1600 6050 50  0001 C CNN "Vendor"
F 5 "C16133" H 1600 6050 50  0001 C CNN "Vendor part#"
F 6 "TAJB107K006RNJ" H 1600 6050 50  0001 C CNN "Manufacturer part#"
	1    1600 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 61C39219
P 2100 6050
F 0 "C5" H 2150 6150 50  0000 L CNN
F 1 "100uF 6.3V" H 2100 5750 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-21_Kemet-B_Pad1.50x2.35mm_HandSolder" H 2138 5900 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1811071223_AVX-TAJB107K006RNJ_C16133.pdf" H 2100 6050 50  0001 C CNN
F 4 "JLCPCB" H 2100 6050 50  0001 C CNN "Vendor"
F 5 "C16133" H 2100 6050 50  0001 C CNN "Vendor part#"
F 6 "TAJB107K006RNJ" H 2100 6050 50  0001 C CNN "Manufacturer part#"
	1    2100 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 61C3966A
P 2600 6050
F 0 "C6" H 2650 6150 50  0000 L CNN
F 1 "100uF 6.3V" H 2600 5750 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-21_Kemet-B_Pad1.50x2.35mm_HandSolder" H 2638 5900 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1811071223_AVX-TAJB107K006RNJ_C16133.pdf" H 2600 6050 50  0001 C CNN
F 4 "JLCPCB" H 2600 6050 50  0001 C CNN "Vendor"
F 5 "C16133" H 2600 6050 50  0001 C CNN "Vendor part#"
F 6 "TAJB107K006RNJ" H 2600 6050 50  0001 C CNN "Manufacturer part#"
	1    2600 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 5350 1900 5600
Wire Wire Line
	1900 5600 1600 5600
Wire Wire Line
	1900 5600 2100 5600
Wire Wire Line
	2600 5600 2600 5900
Connection ~ 1900 5600
Wire Wire Line
	2100 5900 2100 5600
Connection ~ 2100 5600
Wire Wire Line
	2100 5600 2600 5600
Connection ~ 1600 5600
Wire Wire Line
	1600 5600 1100 5600
Wire Wire Line
	1100 6550 1600 6550
Wire Wire Line
	1900 6550 1900 6650
Wire Wire Line
	1600 6200 1600 6550
Connection ~ 1600 6550
Wire Wire Line
	1600 6550 1900 6550
Wire Wire Line
	2100 6200 2100 6550
Wire Wire Line
	2100 6550 1900 6550
Connection ~ 1900 6550
Wire Wire Line
	2600 6200 2600 6550
Wire Wire Line
	2600 6550 2100 6550
Connection ~ 2100 6550
Wire Wire Line
	1600 5600 1600 5900
$Comp
L Device:Crystal_GND24 Y1
U 1 1 61C827A0
P 6300 3250
F 0 "Y1" V 6100 3100 50  0000 L CNN
F 1 "16 Mz cystal" V 6050 3350 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_3225-4Pin_3.2x2.5mm_HandSoldering" H 6300 3250 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2103291133_Yangxing-Tech-X322516MLB4SI_C13738.pdf" H 6300 3250 50  0001 C CNN
F 4 "JLCPCB" V 6300 3250 50  0001 C CNN "Vendor"
F 5 "C13738" V 6300 3250 50  0001 C CNN "Vendor part#"
F 6 "X322516MLB4SI" V 6300 3250 50  0001 C CNN "Manufacturer part#"
	1    6300 3250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 61C88B9C
P 6800 3300
F 0 "#PWR013" H 6800 3050 50  0001 C CNN
F 1 "GND" H 6805 3127 50  0000 C CNN
F 2 "" H 6800 3300 50  0001 C CNN
F 3 "" H 6800 3300 50  0001 C CNN
	1    6800 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 61C892E9
P 5800 3300
F 0 "#PWR012" H 5800 3050 50  0001 C CNN
F 1 "GND" H 5805 3127 50  0000 C CNN
F 2 "" H 5800 3300 50  0001 C CNN
F 3 "" H 5800 3300 50  0001 C CNN
	1    5800 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3250 5800 3250
Wire Wire Line
	5800 3250 5800 3300
Wire Wire Line
	6500 3250 6800 3250
Wire Wire Line
	6800 3250 6800 3300
$Comp
L Connector:USB_B_Micro J6
U 1 1 61D00017
P 9700 5200
F 0 "J6" H 9470 5189 50  0000 R CNN
F 1 "USB_B_Micro" H 9470 5098 50  0000 R CNN
F 2 "Connector_USB:USB_Mini-B_Wuerth_65100516121_Horizontal" H 9850 5150 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2103051832_Jing-Extension-of-the-Electronic-Co.-920-462A2021S10108_C105424.pdf" H 9850 5150 50  0001 C CNN
F 4 "JLCPCB" H 9700 5200 50  0001 C CNN "Vendor"
F 5 "C105424" H 9700 5200 50  0001 C CNN "Vendor part#"
F 6 "920-462A2021S10108" H 9700 5200 50  0001 C CNN "Manufacturer part#"
	1    9700 5200
	-1   0    0    -1  
$EndComp
$Comp
L Interface_USB:CH340G U4
U 1 1 61D01763
P 8600 5300
F 0 "U4" H 8850 6000 50  0000 C CNN
F 1 "CH340G" H 8950 4650 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 8650 4750 50  0001 L CNN
F 3 "https://datasheet.lcsc.com/lcsc/2008191806_WCH-Jiangsu-Qin-Heng-CH340G_C14267.pdf" H 8250 6100 50  0001 C CNN
F 4 "JLCPCB" H 8600 5300 50  0001 C CNN "Vendor"
F 5 "C14267" H 8600 5300 50  0001 C CNN "Vendor part#"
F 6 "CH340G" H 8600 5300 50  0001 C CNN "Manufacturer part#"
	1    8600 5300
	-1   0    0    -1  
$EndComp
Text Label 8050 4900 2    50   ~ 0
SERIAL_RX
Text Label 8050 5000 2    50   ~ 0
SERIAL_TX
Wire Wire Line
	8200 4900 8050 4900
Wire Wire Line
	8050 5000 8200 5000
Wire Wire Line
	9000 5200 9400 5200
Wire Wire Line
	9400 5300 9000 5300
Text Label 9300 4400 0    50   ~ 0
5V_USB
Wire Wire Line
	9300 4400 9300 5000
Wire Wire Line
	9300 5000 9400 5000
Text Label 6500 1150 0    50   ~ 0
5V_USB
$Comp
L Device:D_Schottky_ALT D3
U 1 1 61DC83A4
P 6500 1550
F 0 "D3" V 6546 1471 50  0000 R CNN
F 1 "D_Schottky_ALT" V 6455 1471 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 6500 1550 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1809140216_Changjiang-Electronics-Tech--CJ-B5819W-SL_C8598.pdf" H 6500 1550 50  0001 C CNN
F 4 "JLCPCB" H 6500 1550 50  0001 C CNN "Vendor"
F 5 "C8598" H 6500 1550 50  0001 C CNN "Vendor part#"
F 6 "B5819W SL" V 6500 1550 50  0001 C CNN "Manufacturer part#"
	1    6500 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6500 1150 6500 1400
Wire Wire Line
	6500 1700 5500 1700
Connection ~ 5500 1700
NoConn ~ 8200 5200
NoConn ~ 8200 5300
NoConn ~ 8200 5400
NoConn ~ 8200 5500
NoConn ~ 8200 5600
$Comp
L power:GND #PWR015
U 1 1 61E1C6F6
P 8600 5900
F 0 "#PWR015" H 8600 5650 50  0001 C CNN
F 1 "GND" H 8605 5727 50  0000 C CNN
F 2 "" H 8600 5900 50  0001 C CNN
F 3 "" H 8600 5900 50  0001 C CNN
	1    8600 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 61E1E08E
P 9750 5650
F 0 "#PWR014" H 9750 5400 50  0001 C CNN
F 1 "GND" H 9755 5477 50  0000 C CNN
F 2 "" H 9750 5650 50  0001 C CNN
F 3 "" H 9750 5650 50  0001 C CNN
	1    9750 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 5600 9800 5650
Wire Wire Line
	9800 5650 9750 5650
Wire Wire Line
	9700 5600 9700 5650
Wire Wire Line
	9700 5650 9750 5650
Connection ~ 9750 5650
NoConn ~ 9400 5400
Text Label 8450 4450 2    50   ~ 0
5V_USB
Wire Wire Line
	8450 4450 8600 4450
Wire Wire Line
	8600 4450 8600 4700
$EndSCHEMATC
