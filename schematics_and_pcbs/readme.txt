
These are the KiCAD project files for this project.

===Main boards===

-imac_g3_333mhz_slot_loading_J20_adapter_board
	This board is the "brains" of the operation, it sends the init sequence
	to the IVAD board and also sends EDID information to any device that
	requests it when conencted to the VGA port.
 
-imac_g3_down_converter_board_adapter
	This board takes 24VAC from the analog board via the the J22 board and
	converts it to standard computer power supply voltages. +12VDC, +5VDC
	and +3.3VDC. This board also has a footprint to include a connector
	to connect a CPU fan.
	
-imac_g3_slot_loading_J22_adapter_board
	This board is essentially a breakout board that allows one to use the 
	built in speakers, power switch, leds and 24VAC.

-surfacemount_version	
	This will be a surface mount version of the original main boards.
	It is currently under development. The idea is to have boards
	that can be assembled by an assembly outfit to bring down the cost.
	
===User contributed boards==

-RPiG3iMac	
	Additional KiCAD projects for a Raspberry Pi Hat and a breakout board
	for the J20 board. These boards were contributed by Rudy https://reng.ca
	, look inside the directory for more details. 
