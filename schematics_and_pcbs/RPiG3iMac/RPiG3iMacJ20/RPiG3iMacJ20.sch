EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "Raspberry Pi Hat Interface - iMac G3 J20"
Date "2022-03-20"
Rev "1.1"
Comp "R Engineering Inc."
Comment1 "https://reng.ca"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Screw_Terminal_01x05 J3
U 1 1 62437725
P 2900 1700
F 0 "J3" H 2980 1742 50  0000 L CNN
F 1 "Screw_Terminal_01x05" H 2980 1651 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MPT-0,5-5-2.54_1x05_P2.54mm_Horizontal" H 2900 1700 50  0001 C CNN
F 3 "~" H 2900 1700 50  0001 C CNN
	1    2900 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J1
U 1 1 6243937F
P 1500 1450
F 0 "J1" H 1550 1767 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 1550 1676 50  0000 C CNN
F 2 "Rudy:Harwin_M20-7810345_2x03_P2.54mm_Vertical" H 1500 1450 50  0001 C CNN
F 3 "~" H 1500 1450 50  0001 C CNN
	1    1500 1450
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J2
U 1 1 6243A6BB
P 2850 1150
F 0 "J2" H 2900 1467 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 2900 1376 50  0000 C CNN
F 2 "Rudy:Harwin_M20-7810345_2x03_P2.54mm_Vertical" H 2850 1150 50  0001 C CNN
F 3 "~" H 2850 1150 50  0001 C CNN
	1    2850 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1550 2100 1550
Wire Wire Line
	2100 1550 2100 1700
Wire Wire Line
	2100 1700 2150 1700
Wire Wire Line
	1700 1350 2100 1350
Wire Wire Line
	2350 1350 2350 1000
$Comp
L power:+5V #PWR02
U 1 1 6243B369
P 2350 1000
F 0 "#PWR02" H 2350 850 50  0001 C CNN
F 1 "+5V" H 2365 1173 50  0000 C CNN
F 2 "" H 2350 1000 50  0001 C CNN
F 3 "" H 2350 1000 50  0001 C CNN
	1    2350 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 1150 2400 1150
Wire Wire Line
	2400 1150 2400 1500
Wire Wire Line
	2400 1500 2700 1500
Wire Wire Line
	2650 1250 2450 1250
Wire Wire Line
	2450 1250 2450 1600
Wire Wire Line
	2450 1600 2700 1600
Wire Wire Line
	3150 1150 3350 1150
Wire Wire Line
	3350 1150 3350 1350
Wire Wire Line
	3350 1350 2500 1350
Wire Wire Line
	2500 1350 2500 1800
Wire Wire Line
	2500 1800 2700 1800
Wire Wire Line
	3150 1250 3300 1250
Wire Wire Line
	3300 1250 3300 1400
Wire Wire Line
	3300 1400 2550 1400
Wire Wire Line
	2550 1400 2550 1900
Wire Wire Line
	2550 1900 2700 1900
$Comp
L power:GND #PWR01
U 1 1 62381E89
P 2100 2000
F 0 "#PWR01" H 2100 1750 50  0001 C CNN
F 1 "GND" H 2105 1827 50  0000 C CNN
F 2 "" H 2100 2000 50  0001 C CNN
F 3 "" H 2100 2000 50  0001 C CNN
	1    2100 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2000 2100 1700
Connection ~ 2100 1700
$Comp
L power:PWR_FLAG #FLG01
U 1 1 62382A48
P 2100 1000
F 0 "#FLG01" H 2100 1075 50  0001 C CNN
F 1 "PWR_FLAG" H 2100 1173 50  0000 C CNN
F 2 "" H 2100 1000 50  0001 C CNN
F 3 "~" H 2100 1000 50  0001 C CNN
	1    2100 1000
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 623830A9
P 2150 1600
F 0 "#FLG02" H 2150 1675 50  0001 C CNN
F 1 "PWR_FLAG" H 2150 1773 50  0000 C CNN
F 2 "" H 2150 1600 50  0001 C CNN
F 3 "~" H 2150 1600 50  0001 C CNN
	1    2150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 1600 2150 1700
Connection ~ 2150 1700
Wire Wire Line
	2150 1700 2700 1700
Wire Wire Line
	2100 1000 2100 1350
Connection ~ 2100 1350
Wire Wire Line
	2100 1350 2350 1350
NoConn ~ 3150 1050
NoConn ~ 2650 1050
NoConn ~ 1200 1350
NoConn ~ 1700 1450
NoConn ~ 1200 1450
NoConn ~ 1200 1550
$Comp
L Device:LED D1
U 1 1 62384DBD
P 2750 2300
F 0 "D1" H 2743 2045 50  0000 C CNN
F 1 "LED" H 2743 2136 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 2750 2300 50  0001 C CNN
F 3 "~" H 2750 2300 50  0001 C CNN
	1    2750 2300
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 62387C4E
P 2750 2650
F 0 "D2" H 2743 2395 50  0000 C CNN
F 1 "LED" H 2743 2486 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 2750 2650 50  0001 C CNN
F 3 "~" H 2750 2650 50  0001 C CNN
	1    2750 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 623887ED
P 2750 3050
F 0 "D3" H 2743 2795 50  0000 C CNN
F 1 "LED" H 2743 2886 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 2750 3050 50  0001 C CNN
F 3 "~" H 2750 3050 50  0001 C CNN
	1    2750 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 1350 2350 2300
Wire Wire Line
	2350 2300 2600 2300
Connection ~ 2350 1350
Wire Wire Line
	2500 1800 2500 2650
Wire Wire Line
	2500 2650 2600 2650
Connection ~ 2500 1800
Wire Wire Line
	2550 1900 2550 3050
Wire Wire Line
	2550 3050 2600 3050
Connection ~ 2550 1900
$Comp
L Device:R R2
U 1 1 6238A391
P 3350 2650
F 0 "R2" V 3557 2650 50  0000 C CNN
F 1 "220" V 3466 2650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3280 2650 50  0001 C CNN
F 3 "~" H 3350 2650 50  0001 C CNN
	1    3350 2650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 6238A7E0
P 3350 3050
F 0 "R3" V 3557 3050 50  0000 C CNN
F 1 "220" V 3466 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3280 3050 50  0001 C CNN
F 3 "~" H 3350 3050 50  0001 C CNN
	1    3350 3050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6238CB3A
P 3650 3300
F 0 "#PWR03" H 3650 3050 50  0001 C CNN
F 1 "GND" H 3655 3127 50  0000 C CNN
F 2 "" H 3650 3300 50  0001 C CNN
F 3 "" H 3650 3300 50  0001 C CNN
	1    3650 3300
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 6239577C
P 3050 2300
F 0 "JP1" H 3050 2505 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 3050 2414 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3050 2300 50  0001 C CNN
F 3 "~" H 3050 2300 50  0001 C CNN
	1    3050 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 62389FDD
P 3350 2300
F 0 "R1" V 3557 2300 50  0000 C CNN
F 1 "470" V 3466 2300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3280 2300 50  0001 C CNN
F 3 "~" H 3350 2300 50  0001 C CNN
	1    3350 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3650 2300 3650 2650
Wire Wire Line
	3650 2300 3500 2300
Wire Wire Line
	3500 2650 3650 2650
Connection ~ 3650 2650
Wire Wire Line
	3650 2650 3650 3050
Wire Wire Line
	3500 3050 3650 3050
Connection ~ 3650 3050
Wire Wire Line
	3650 3050 3650 3300
Wire Wire Line
	2900 3050 3200 3050
Wire Wire Line
	2900 2650 3200 2650
$EndSCHEMATC