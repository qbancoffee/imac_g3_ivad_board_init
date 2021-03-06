EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "J22 Adapter Board"
Date "2020-03-10"
Rev "2"
Comp ""
Comment1 ""
Comment2 "the microphone, speakers and , 24VAC "
Comment3 "J22 adapter board to interface to the power button,"
Comment4 "Rocky Hill"
$EndDescr
$Comp
L Connector_Generic:Conn_02x13_Odd_Even J1
U 1 1 5E67C6F3
P 5450 2200
F 0 "J1" H 5500 3017 50  0000 C CNN
F 1 "Conn_02x13_Odd_Even" H 5500 2926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x13_P2.54mm_Vertical" H 5450 2200 50  0001 C CNN
F 3 "https://cdn.amphenol-icc.com/media/wysiwyg/files/drawing/67996.pdf" H 5450 2200 50  0001 C CNN
F 4 "digikey" H 5450 2200 50  0001 C CNN "Vendor"
F 5 "3M156308-26-ND" H 5450 2200 50  0001 C CNN "Part#"
	1    5450 2200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5E6841C1
P 9400 4000
F 0 "H1" H 9500 4049 50  0000 L CNN
F 1 "MountingHole_Pad" H 9500 3958 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad" H 9400 4000 50  0001 C CNN
F 3 "~" H 9400 4000 50  0001 C CNN
	1    9400 4000
	1    0    0    -1  
$EndComp
Text Label 5250 1600 2    50   ~ 0
-MICROPHONE
Text Label 5250 1700 2    50   ~ 0
+MICROPHONE
Text Label 5250 2100 2    50   ~ 0
HEADPHONE_1_&_2_GND
Text Label 5250 2200 2    50   ~ 0
+RIGHT_SPEAKER
Text Label 5250 2300 2    50   ~ 0
-RIGHT_SPEAKER
Text Label 5250 2400 2    50   ~ 0
POWER_BUTTON
Text Label 5250 2500 2    50   ~ 0
+GREEN_LED
NoConn ~ 5250 2600
Text Label 5250 2700 2    50   ~ 0
-AC
Text Label 5250 2800 2    50   ~ 0
-AC
Text Label 5750 1600 0    50   ~ 0
MICROPHONE_SHIELD
Text Label 5750 1700 0    50   ~ 0
HEADPHONE_1_&_2_GND
Text Label 5750 1900 0    50   ~ 0
HEADPHONE_1_SENSE
Text Label 5250 1900 2    50   ~ 0
HEADPHONE_2_SENSE
NoConn ~ 5750 2100
Text Label 5750 2300 0    50   ~ 0
-LEFT_SPEAKER
Text Label 5750 2200 0    50   ~ 0
+LEFT_SPEAKER
Text Label 5750 2400 0    50   ~ 0
LEDS_&_POWER_BUTTON_COMMON
Text Label 5750 2500 0    50   ~ 0
+AMBER_LED
NoConn ~ 5750 2600
Text Label 5750 2700 0    50   ~ 0
+AC
Text Label 5750 2800 0    50   ~ 0
+AC
$Comp
L power:GNDREF #PWR01
U 1 1 5E6C6282
P 8800 4650
F 0 "#PWR01" H 8800 4400 50  0001 C CNN
F 1 "GNDREF" H 8805 4477 50  0000 C CNN
F 2 "" H 8800 4650 50  0001 C CNN
F 3 "" H 8800 4650 50  0001 C CNN
	1    8800 4650
	1    0    0    -1  
$EndComp
Text Label 8800 4200 2    50   ~ 0
MICROPHONE_SHIELD
Text Label 8800 4350 2    50   ~ 0
HEADPHONE_1_&_2_GND
Text Label 8800 4500 2    50   ~ 0
LEDS_&_POWER_BUTTON_COMMON
Text Label 5250 1800 2    50   ~ 0
HEADPHONE_2_RIGHT
Text Label 5250 2000 2    50   ~ 0
HEADPHONE_1_RIGHT
Text Label 5750 1800 0    50   ~ 0
HEADPHONE_2_LEFT
Text Label 5750 2000 0    50   ~ 0
HEADPHONE_1_LEFT
Text Label 1900 2200 2    50   ~ 0
-AC
Text Label 1900 2100 2    50   ~ 0
+AC
$Comp
L Connector:AudioJack3 J3
U 1 1 5E6D23B9
P 2650 1650
F 0 "J3" H 2370 1583 50  0000 R CNN
F 1 "AudioJack3" H 2370 1674 50  0000 R CNN
F 2 "Connector_Audio:Jack_3.5mm_CUI_SJ1-3533NG_Horizontal_CircularHoles" H 2650 1650 50  0001 C CNN
F 3 "https://www.cuidevices.com/product/resource/digikeypdf/sj1-353xng.pdf" H 2650 1650 50  0001 C CNN
F 4 "digikey" H 2650 1650 50  0001 C CNN "Vendor"
F 5 "CP1-3533NG-ND" H 2650 1650 50  0001 C CNN "Part#"
	1    2650 1650
	-1   0    0    1   
$EndComp
Text Label 1100 1300 2    50   ~ 0
+MICROPHONE
Text Label 2250 1750 2    50   ~ 0
-MICROPHONE
Wire Wire Line
	2450 1750 2400 1750
Text Label 1850 2700 2    50   ~ 0
-LEFT_SPEAKER
Text Label 1850 2800 2    50   ~ 0
+LEFT_SPEAKER
Text Label 1850 3000 2    50   ~ 0
+RIGHT_SPEAKER
Text Label 1850 2900 2    50   ~ 0
-RIGHT_SPEAKER
Text Label 1850 2400 2    50   ~ 0
POWER_BUTTON
Text Label 1900 2300 2    50   ~ 0
+GREEN_LED
Text Label 1850 2500 2    50   ~ 0
+AMBER_LED
Text Label 1850 2600 2    50   ~ 0
LEDS_&_POWER_BUTTON_COMMON
$Comp
L Device:R_Small_US R2
U 1 1 5E6EFBD0
P 2350 2500
F 0 "R2" V 2300 2400 50  0000 C CNN
F 1 "220" V 2300 2600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2350 2500 50  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 2350 2500 50  0001 C CNN
F 4 "digikey" H 2350 2500 50  0001 C CNN "Vendor"
F 5 "CF14JT220RCT-ND" H 2350 2500 50  0001 C CNN "Part#"
	1    2350 2500
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R1
U 1 1 5E6F12A4
P 2350 2300
F 0 "R1" V 2300 2200 50  0000 C CNN
F 1 "220" V 2300 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2350 2300 50  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 2350 2300 50  0001 C CNN
F 4 "digikey" H 2350 2300 50  0001 C CNN "Vendor"
F 5 "CF14JT220RCT-ND" H 2350 2300 50  0001 C CNN "Part#"
	1    2350 2300
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5E71AC86
P 8800 4000
F 0 "#FLG0101" H 8800 4075 50  0001 C CNN
F 1 "PWR_FLAG" H 8800 4173 50  0000 C CNN
F 2 "" H 8800 4000 50  0001 C CNN
F 3 "~" H 8800 4000 50  0001 C CNN
	1    8800 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 4000 8800 4600
Wire Wire Line
	9400 4600 8800 4600
Wire Wire Line
	9400 4100 9400 4600
Connection ~ 8800 4600
Wire Wire Line
	8800 4600 8800 4650
$Comp
L Connector:Screw_Terminal_01x10 J2
U 1 1 5E7501BB
P 2800 2500
F 0 "J2" H 2880 2492 50  0000 L CNN
F 1 "Screw_Terminal_01x10" H 2880 2401 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_PT-1,5-10-5.0-H_1x10_P5.00mm_Horizontal" H 2800 2500 50  0001 C CNN
F 3 "https://www.phoenixcontact.com/pxc-oc-itemdetail-pdf-web/eshop?lineItemType=LineItem&UID=1935857" H 2800 2500 50  0001 C CNN
F 4 "digikey" H 2800 2500 50  0001 C CNN "Vendor"
F 5 "277-9080-ND" H 2800 2500 50  0001 C CNN "Part#"
	1    2800 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2100 1900 2100
Wire Wire Line
	1900 2200 2600 2200
Wire Wire Line
	2600 2300 2450 2300
Wire Wire Line
	2250 2300 1900 2300
Wire Wire Line
	2600 2400 1850 2400
Wire Wire Line
	2600 2500 2450 2500
Wire Wire Line
	1850 2500 2250 2500
Wire Wire Line
	1850 2600 2600 2600
Wire Wire Line
	2600 2700 1850 2700
Wire Wire Line
	1850 2800 2600 2800
Wire Wire Line
	2600 2900 1850 2900
Wire Wire Line
	1850 3000 2600 3000
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J4
U 1 1 5E7BF001
P 4650 4000
F 0 "J4" H 4700 4317 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 4700 4226 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 4650 4000 50  0001 C CNN
F 3 "https://cdn.amphenol-icc.com/media/wysiwyg/files/drawing/67996.pdf" H 4650 4000 50  0001 C CNN
F 4 "digikey" H 4650 4000 50  0001 C CNN "Vendor"
F 5 "609-3234-ND" H 4650 4000 50  0001 C CNN "Part#"
	1    4650 4000
	1    0    0    -1  
$EndComp
Text Label 4450 3900 2    50   ~ 0
HEADPHONE_2_RIGHT
Text Label 4450 4000 2    50   ~ 0
HEADPHONE_2_SENSE
Text Label 4450 4100 2    50   ~ 0
HEADPHONE_1_RIGHT
Text Label 4950 3900 0    50   ~ 0
HEADPHONE_2_LEFT
Text Label 4950 4000 0    50   ~ 0
HEADPHONE_1_SENSE
Text Label 4950 4100 0    50   ~ 0
HEADPHONE_1_LEFT
$Comp
L power:GNDREF #PWR0101
U 1 1 5E7ABB1A
P 2400 1800
F 0 "#PWR0101" H 2400 1550 50  0001 C CNN
F 1 "GNDREF" H 2405 1627 50  0000 C CNN
F 2 "" H 2400 1800 50  0001 C CNN
F 3 "" H 2400 1800 50  0001 C CNN
	1    2400 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1800 2400 1750
Connection ~ 2400 1750
Wire Wire Line
	2400 1750 2250 1750
$Comp
L Device:R_Small_US R3
U 1 1 5E816887
P 1650 700
F 0 "R3" V 1550 650 50  0000 C CNN
F 1 "2.2k" V 1550 800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1650 700 50  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1650 700 50  0001 C CNN
F 4 "digikey" H 1650 700 50  0001 C CNN "Vendor"
F 5 "CF14JT2K20CT-ND" H 1650 700 50  0001 C CNN "Part#"
	1    1650 700 
	0    1    1    0   
$EndComp
Text Label 2200 1650 2    50   ~ 0
MICROPHONE_POWER
Wire Wire Line
	2450 1650 2200 1650
Text Label 1450 700  2    50   ~ 0
MICROPHONE_POWER
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5E84A05B
P 2000 700
F 0 "JP1" H 2050 800 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 2350 600 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 2000 700 50  0001 C CNN
F 3 "~" H 2000 700 50  0001 C CNN
	1    2000 700 
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C1
U 1 1 5E850CDF
P 1700 1100
F 0 "C1" V 1750 1200 50  0000 C CNN
F 1 "1uF" V 1566 1100 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 1700 1100 50  0001 C CNN
F 3 "http://nichicon-us.com/english/products/pdfs/e-usa_usr.pdf" H 1700 1100 50  0001 C CNN
F 4 "digikey" H 1700 1100 50  0001 C CNN "Vendor"
F 5 "493-14556-1-ND" H 1700 1100 50  0001 C CNN "Part#"
	1    1700 1100
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP2
U 1 1 5E8585A4
P 1350 1300
F 0 "JP2" V 1304 1368 50  0000 L CNN
F 1 "SolderJumper_3_Open" V 1395 1368 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm" H 1350 1300 50  0001 C CNN
F 3 "~" H 1350 1300 50  0001 C CNN
	1    1350 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 1100 1550 1100
Wire Wire Line
	2400 1550 2450 1550
Wire Wire Line
	2150 700  2400 700 
Wire Wire Line
	1850 700  1750 700 
Wire Wire Line
	1550 700  1500 700 
Wire Wire Line
	1350 1550 1350 1500
Wire Wire Line
	1200 1300 1100 1300
Wire Wire Line
	1800 1100 2400 1100
Wire Wire Line
	2400 1100 2400 1550
Wire Wire Line
	1350 1550 2400 1550
Connection ~ 2400 1550
Text Notes 2650 1250 0    50   ~ 0
This circuit is to be able to use an electret microphone\nthat does contain a circuit in the package. To use the circuit\nsolder JP1 and solder pads 1 and 2 of JP2.\n\nTo connect directly to the mic from the computer, solder \npads 2 and 3 on JP2 and leave JP1 unsoldered\n\nJP3 is for testing 5V in the circuit. Don't use it.
$Comp
L Jumper:SolderJumper_2_Open JP3
U 1 1 5E88296C
P 1200 850
F 0 "JP3" H 1200 750 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 1000 650 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 1200 850 50  0001 C CNN
F 3 "~" H 1200 850 50  0001 C CNN
	1    1200 850 
	1    0    0    -1  
$EndComp
Text Label 1050 850  2    50   ~ 0
+GREEN_LED
Wire Wire Line
	1350 850  1500 850 
Wire Wire Line
	1500 850  1500 700 
Connection ~ 1500 700 
Wire Wire Line
	1500 700  1450 700 
Wire Wire Line
	1550 1100 1550 900 
Wire Wire Line
	1550 900  2400 900 
Wire Wire Line
	2400 900  2400 700 
Connection ~ 1550 1100
Wire Wire Line
	1550 1100 1600 1100
$EndSCHEMATC
