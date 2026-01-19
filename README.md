# Add custom boards to an iMac G3 DV(slot loader) in order to use it as a monitor without having to destroy it.


See the wiki for an explantion of how this was done.<BR>

<H2>Wiki explaining how this was done.</H2>
 
- [Wiki explaining how this was done.](https://github.com/qbancoffee/imac_g3_ivad_board_init/wiki)

If you have a dead logic board but a functioning CRT then these boards can let you use your
iMac G3 DV as a VGA monitor so that you can use a modern desktop with it. You can even hand wire the 
whole thing without the need for the boards if you so wish.

Even if you have a perfectly functional iMac G3 DV you can remove your logic board and use these boards
to convert your iMac G3 DV into a VGA monitor without harming your iMac G3 and when you want your iMac back, you can remove the custom boards and plug your original logic board back in and still use your iMac G3 as an original apple product.
These boards are designed to plug right in without having to modify the case and attached things.

However....

# --->DO THIS AT YOUR OWN RISK<--- as things may break as you dissasemble your iMac and you can get shocked.

Although low risk, things can always go wrong, so be careful.

- The inner bezel is extremely fragile and routintely breaks.
- The CRT can hold a charge and shock you even if the iMac is not plugged in.
- Static discharge from your hands can destroy electronics so "GROUND THYSELF"

 I've documented much of the iMac G3 slot loader chasis connector pinouts on this repo and used 
 it as a guide to make breakout circuit boards than can plug right into the chassis connectors and provide
 standard connections so that a regular computer can use things like the CRT,speakers, power button, audio
 jacks, the down-converter board ect..
 
 It wasn't easy but luckily a lot of people have shared their findings online..
 
 There is working code here for both the arduino and raspberry pi to initialize the IVAD board so that you can use it as a monitor.
 
The current initialization sketch waits for button presses on an arduino pin to send the initialization sequence
to the IVAD board but you can just uncomment "initIvadBoard();" in "setup()" to send it as soon as it's powered.

</br>

Also, you might have to modify values in the init sequence to get the brightness, contrast and screen geometry
just right for your setup. below is an example from the init sketch.


```
  writeToIvad( 0x46, 0x04, 0x80);//red x-30
  writeToIvad( 0x46, 0x05, 0xB0);// green x
  writeToIvad( 0x46, 0x06, 0x78); //blue x-38

  writeToIvad( 0x46, 0x07, 0xB1); //horizontal position
  writeToIvad( 0x46, 0x08, 0xF8); //vertical size
  ```


<!-- toc -->
- [Success stories](#Success-Stories)
- [Goals](#Goals)
- [Chassis Connectors and Pinouts](#Chassis-Connectors-and-Pinouts)
    * [Removing the logic board](#Removing-the-logic-board)
- [Wiring VGA cable](#Wiring-VGA-cable)
    * [Making the cable](#Making-the-cable)
- [Preparing the Raspberry Pi](#Preparing-the-Raspberry-Pi)
    * [What to install](#What-to-install)
    * [Configure Resolution and Refresh Rate](#Configure-Resolution-and-Refresh-Rate)
-   * [Wiring The Raspberry Pi and testing the connection](#Wiring-The-Raspberry-Pi-and-testing-the-connection)
- [Wiring Arduino Uno](#Wiring-Arduino-Uno)
- [Wiring Arduino Nano](#Wiring-Arduino-Nano)
    * [Loading and Running the initialization sketch](#Loading-and-Running-the-initialization-sketch)
- [Wiring Arduino Uno to transmit EDID](#Wiring-Arduino-Uno-to-transmit-EDID)
- [Wiring Arduino Nano to transmit EDID](#Wiring-Arduino-Nano-to-transmit-EDID)
- [Powering the down converter board PAV](#Powering-the-down-converter-board-PAV)
- [Powering the CRT on and off](#Powering-the-CRT-on-and-off)
- [See Also](#See-Also)
   * [See the boards](#Boards)
   * [Getting adapter boards](#Ordering-Boards)
   * [Acknowledgements](#Acknowledgements)
   * [Videos](#Videos)
## Success Stories
- [Apple IIe using the iMac G3 as a monitor](https://www.reddit.com/r/VintageApple/comments/fox7b8/my_half_retro_battle_station/)
- [Apple IIe using the iMac G3 as a monitor 2 ](https://old.reddit.com/r/VintageApple/comments/fmoi5d/slot_loading_imac_g3_vga_input_hack/)
- [oshimai running windows on a pc104 computer](https://vimeo.com/415301897)
- [oshimais' repo with links to videos](https://github.com/shuuryou/imacg3)
- [A Nintendo Switch connected to an iMac G3](https://www.reddit.com/r/crtgaming/comments/k3hf02/imac_g3_crt_connected_to_switch/)
- [Check out the iMacSTer repo by wikerwaka it's impressive!](https://github.com/wickerwaka/iMacSTer)
- [Wikerwaka testing the iMacSTer](https://youtu.be/8O5fEVcCo0Q)
- [Wikerwaka assembling the iMacSTer](https://youtu.be/OmDPnWWWzPM)
- [Matt Gray upgrades an iMac G3 it now runs on Apple silicon](https://youtu.be/WoYBuP4Bxiw)

## Goals

The main goal is to convert the iMac G3 into a VGA monitor whithout sacrificing the original CRT and
using as much of the iMac as possible. The difficult part is tricking the IVAD board into thinking it is 
still connected to a G3 logic board. the idea is to capture the init sequence and reimplement it using
a microcontoller like an arduino.

Once achieved, one can connect a standard computer to it as if it were a regular monitor with speakers.
One can even include a motherboard on the inside of the G3 basically converting it into a modern computer.

Here are the goals

- [x] Capture IVAD board initialization sequence from the Imac logic board to the IVAD board and implement with mcu & rpi.
- [x] Document how to control brightness, contrast, screen goemetry ect via the i2c lines.
- [x] Document as much of the pinouts as possible on the the chassis connectors .
- [x] [Design circuit boards that will plug into the connectors and allow one to use the on/off button,
speakers, power LED, mic ect..](#Boards)
- [x] Design the circuit boards with through hole components so that anyone can build these with just a soldering iron and
solder.
- [x] Use the original down-converter board(kind of like a power supply) to power things like
an amplifier and a slot loading DVD drive.




## Chassis Connectors and Pinouts
![ChassisConnectors](images/connectors_and_boards.png?raw=true "Chassis connectors")

### Removing the logic board
The connector drawings in the above [diagram](#Chassis-Connectors-and-Pinouts) represent the cables
coming from the CRT analog board that plug into the logic board. To expose these, the logic board must
be removed.

## Wiring VGA cable
![VGACable](images/vga_adapter.png?raw=true "VGA Cable")

### Making the cable
This is perhaps the most time consuming part of the whole process because not all VGA cables are made the same so the colors for the cable I used may not be the colors used in your cable. Here are the steps I took.<br>


- Find a VGA cable to cut.
- Cut the cable so that you have at least one of the ferrite chokes left on the cable.
- Cut away the cable jacket such that the wires are at a comfortable handling length. 3 to 4 inches
- Strip each wire and ring them out to find what color corresponds to each pin on the DE15 connector.
- Use the [diagram](#Wiring-VGA-cable) above and map your cable to J20 using the DE15 pin numbers as the key.
- Option 1 ,use a 20 pin header and solder the DE15 wires to it then plug it into J20.
- Option 2, cut the required wires from J20 and splice them with VGA cable. Solder and use shrink tubing if you can but twisting them and electrical tape works as well. Make sure to leave enough wire on J20 in the event you need to reattach the wires.



## Preparing the Raspberry Pi
![WiringRPI](images/raspberry_pi_wiring.png?raw=true "Wiring RPI")

### What to install
- Install the latest raspian image using a regular monitor.
- Connect to your network and get the ip address for the pi by opening a terminal and issuing the following.
```bash
ifconfig
```
If you connected using wifi then the ip address is under wlan0: , inet.<br>
If you connected using a cable the the ip adress is under eth0: inet<br>
- Enable ssh , you'll need this to login from another computer when you don't have a display.
- Enable I2C.
- Install i2c-tools & git.
- ssh to the pi from a terminal if your on a Mac or linux. If you're on Windows use putty to ssh to the pi I'm assuming
the username is "pi" but replace this with the the username you've created for the pi.

```bash
sudo apt-get update && sudo apt-get -y install i2c-tools git
```
- Install smbus and RPI.GPIO for python using pip for the python version you have.
```bash
sudo pip install smbus RPI.GPIO
```
- Clone the iMac IVAD init repo
```bash
git clone https://github.com/qbancoffee/imac_g3_ivad_board_init.git
cd imac_g3_ivad_board_init
```
- Copy init_ivad.py to /usr/local/bin & and make it executeable
```bash
sudo cp init_ivad.py /usr/local/bin
sudo chmod +x /usr/local/bin/init_ivad.py
```
- Edit rc.local and add the script. Make sure it's added to the line before "exit 0 " or it will not run.
It also needs to be made executable since by default it doesn't do anything.
```bash
sudo nano /etc/rc.local
```

- It should look something like this
```
#!/bin/sh -e
#
# rc.local
#
# This script is executed at the end of each multiuser runlevel.
# Make sure that the script will "exit 0" on success or any other
# value on error.
#
# In order to enable or disable this script just change the execution
# bits.
#
# By default this script does nothing.

# Print the IP address
_IP=$(hostname -I) || true
if [ "$_IP" ]; then
  printf "My IP address is %s\n" "$_IP"
fi

/usr/local/bin/init_ivad.py

exit 0

```

- Ctrl-x to save and exit

- Make rc.local executable
```bash
sudo chmod +x /etc/rc.local
```

### Configure Resolution and Refresh Rate
- Edit config.txt
```bash
sudo nano /boot/config.txt
```
- The newer Raspberry Pi OS uses the VC4 V3D driver that causes the video to go blank. Comment the line that enables it and add the Fake VC4 V3D driver.
```
# Enable DRM VC4 V3D driver
#dtoverlay=vc4-kms-v3d
dtoverlay=vc4-fkms-v3d

```
Newer versions of the Raspberry Pi OS will ignore video modes specified in /boot/config.txt if the EDID sent from the monitor is corrupt or missing. Since we are not sending EDID information to the raspberry pi from the iMac we need to tell the OS to ignore the EDID and set the correct video mode.
- Add the following to the bottom of the file and save.
```
#iMac G3 settings
hdmi_ignore_edid=0xa5000080
hdmi_group=2
hdmi_mode=18
```
Here is a video where I perform the above steps.
- [Modding an iMac G3 DV using only a Raspberry Pi](https://youtu.be/xSiqchucFE4)
### Wiring The Raspberry Pi and testing the connection

In all cases, the IVAD board needs to be initialized when the power analog board is
turned on for the first time. To do this, the initialization sequence must be sent using the
I2C lines(SDA & SCL) on the Raspberry Pi's GPIO header. Connect the I2C lines according to the diagram
above and connect the VGA cable to the HDMI port using a HDMI to VGA converter.

- Use i2cdetect to probe the IVAD board. Make sure the iMac is plugged in, it does not have to be turned on for this.

```bash
i2cdetect -y 1
```
- Confirm it found address's 46 and 53, if no luck, check the wiring and make sure I2C is enabled. The output should look something like the following.
```    
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- 46 -- -- -- -- -- -- -- -- -- 
50: -- -- -- 53 -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --
```
- [Turn on the monitor](#Powering-the-CRT-on-and-off) and run the initialization script.The iMac should make
a nice old school "CRT IS ON"  sound. 
```bash
/usr/local/bin/init_ivad.py
```
If there are errors, make sure the iMac is plugged in and check the wiring.<br>
If there are no errors and there is nothing on the screen, move the mouse or press a key.
The raspberry pi might have turned off the display due to inactivity.

- With the IVAD initialized, Reboot the Raspberry Pi.

## Wiring Arduino Uno
![WiringArduinoUno](images/arduino_uno_wiring.png?raw=true "Wiring Arduino Uno")

## Wiring Arduino Nano
![WiringArduinoNano](images/arduino_nano_wiring.png?raw=true "Wiring Arduino Nano")

### Loading and Running the initialization sketch
write here

## Wiring Arduino Uno to transmit EDID
![WiringArduinoUnoToXmitEdid](images/arduino_uno_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Uno to transmit EDID")

## Wiring Arduino Nano to transmit EDID
![WiringArduinoNanotoXmitEdid](images/arduino_nano_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Nano to transmit EDID")

## Powering the down converter board PAV
![WiringPAV](images/imac_g3_slot_loading_pav_board.png?raw=true "Powering the PAV board")

The CRT analog board provides 24v AC to the PAV or down converter board through the logic board via the J22 
connector. you can directly connect the PAV board and the analog board through the J22 connector and
the PAV board will produce the typical mother board volytages. +12v, +5v +3.3v ect...

## Powering the CRT on and off
![CRTOnAndOff](images/crt_power_on_and_off.png?raw=true "CRT On and Off")

## See Also
### Boards
# J20 Board
What it does.
- detects button presses
- sends the init sequence to the IVAD boar
- sends the "turn-on" signal to the down-converter board
- has a control line "PROT" that when 5 volts are applied turns everythin off. A shut-off signal can be sent here.
- powers the green LED
- sends EDID information via VGA cable so that a connected computer knows how to configure the monitor for use.
</br>

This board works but as of March 23 2020 it needs a slight modification to make it more robust.
# Rendition
![J20](images/J20_board.png?raw=true "J20 VGA adapter board")
# Board installed
![J20Installed](images/J20_board_installed.jpg?raw=true "J20 VGA adapter board installed")
</br>

# Rendiiton of Rev 2 of the J20 board.
![J20REV2](images/J20_board_rev2.png?raw=true "J20 VGA adapter board Rev 2")
</br>

# J22 Board
What it does.
- provides access to the microphone and the speakers
- provides access to the power button
- provides access to the green LED
- provides access to the amber LED
- provides access to the headphone jacks 
- routes 24 VAC from the analog(CRT) board to the the down converter break out board.
</br>

This board has been tested and mostly worked. I found that the mic was miswired
but I've since fixed that.
![J22](images/J22_board.png?raw=true "J22 speaker/mic/led/power button breakout board")
![J22Installed](images/J22_board_installed.jpg?raw=true "J22 speaker/mic/led/power button breakout board installed")
</br>
# Down-converter breakout board
What it does
- provides a 24 VAC input from the J22 board into the down-converter board
- provides a "turn-on" input for the J20 board, this is DCO, which stands for Down Converter On
- provides 3.3 VDC out from the down-converter board that turns on and off with the CRT.
- provides   5 VDC out from the down-converter board that turns on and off with the CRT.
- provides  12 VDC out from the down-converter board that turns on and off with the CRT.
- provides a constant  8 VDC standby voltage when all is off and 12 VDC when all is on.
- provided a constant 15 VDC standby voltage when all is off and 24 VDC when all is on.
</br>
The down-conveter uses the 24 VAC coming from J22 in order to power the original logic board and drives. Some people have called this the iMac G3 power supply. This is what it looks like.

![DCB](/images/removing_down_converter_board.png?raw=true "Removing down-converter board")
</br>
# Rendition
![DCB1](images/down_converter_breakout_board.png?raw=true "Breakout board for the down-converter board so one can power things.")
</br>
# Actual Board
![DCB2](images/down_converter_breakout_board.jpg?raw=true "Breakout board for the down-converter board so one can power things.")
</br>
# Board installed
![DCB3](images/down_converter_breakout_board_installed.jpg?raw=true "Breakout board for the down-converter board so one can power things.")

</br>

### Ordering Boards
All PCB manufacturers should accept gerber files to manufacture boards so I've decided
to design these in KiCAD which is suite of open source EDA programs to create schematics and
design PCBs. There are no limitations to the size of the board and you don't have to order from
a specific vendor.

Recently I've been using https://jlcpcb.com/ and the turn arounds are fast for the price.
In the "schematics_and_pcbs" folder are the three kicad projects for each board, each in its own folder.
I've included the gerber files and zipped them up for convenience, they are in the gerber directory
for each project. To order you can just upload the zip file to https://jlcpcb.com/ or whatever company you choose
and you should get them in the mail. There is a bill of materials included in each project folder. It's a csv file
that includes the reference number, the part number and vendor so you can order the componets to build the boards.
I like to buy from digikey but obviously you can find a vendor that fits your needs.

### Acknowledgements

- [patriciooholegu for inspiring me to do this with an eMac](https://forums.macrumors.com/threads/i-have-decided-to-hack-emacs-crt-to-work-with-any-standard-motherboard.1754089/post-19353472)
- [ym58 for providing the video connector wiring.](https://www.tonymacx86.com/threads/imac-g3-slot-mod-video-connector.125515/)
- [Eric Bylenga for providing the pinout for the PAV board.](http://bylenga.ddns.net/index.php?page=vcr.php)
- [sparpet for capturing and sharing the IVAD initialization code](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-25819428)
- [jamie-g for providing a way to adjust monitor settings via i2c](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-25679538)
- [iMac speaker replacement by TEch Chrunch](https://youtu.be/yc8NGDw5aSQ)
- [DrJekyll_XYZ for providing xrandr output that lead to creating an EDID](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-28272422)
- [DrJekyll_XYZ for suggesting the PAM8403 chip for audio](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-28249216)
- [anotherelise for providing another init sequence](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-28346679)
- [anotherelise for providing IVAD CRT property adjustment capture](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-28349738)
- [oshimai for extracting several EDID's and fiding one that works flawlessly](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-28359571)
- [oshimai for coming up with the idea of monitoring VSYNC to use as a signal to shut off the CRT](https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-28345426)

### Videos
- [Booting an non-modded iMac G3 to confirm the CRT turns on](https://youtu.be/meIzAyQd0t0)
- [Initializing IVAD board with an Arduino Uno](https://youtu.be/JLaHMjQ7idI)
- [Using iMac G3 as a second monitor with custom modeline](https://youtu.be/iSCjOOsf-QQ)
- [Tweaking the modeline to make the iMac G3 fullscreen](https://youtu.be/1DeY3o7P60g)
- [Sending the EDID via the VGA cable to a connected computer](https://youtu.be/KzHUogEQob4)
- [Using CRT without the logic board](https://youtu.be/MbTqhlqsKoY)
- [Running DOSBOX](https://youtu.be/PG7bluXxrPA)
- [Initializing the CRT using only a Raspberry Pi](https://youtu.be/isjo-4vQxwM)
- [Powering the iMac G3 on and off using an arduino and two transistors](https://youtu.be/-TeNbAcnvbk)
- [Powering the Down Convetrer Board without the logic board](https://youtu.be/xmISR5iBjTU)
- [Using CRT on second iMac without logic board](https://youtu.be/UcsI3FVfpCM)
- [Powering an arduino nano with only the triclke voltage provided by the analog board](https://youtu.be/KuT7AKvZXhk)
- [iMac G3 speaker repair](https://youtu.be/jgs-gkoiUrA)
- [Testing replacement speakers with smooth criminal](https://youtu.be/Vm1vN6xlomQ)
- [Testing an SBC inside the iMac G3 ](https://youtu.be/ZOYHHg9NhZA)
- [Powering a computer using the iMac's down converter board](https://youtu.be/1DuaIlEZ5WU)
- [Using a PAM8403 board to drive the speakers on the iMac G3](https://youtu.be/jEA85s0Cqyg)
- [Testing Retropie with iMac G3 monitor](https://youtu.be/S1fnj0tsFQA)
- [Testing J20 board for the first time](https://youtu.be/_IMhMkrIE4M)
- [Testing the J22 board with a raspberry pi](https://youtu.be/HR-qM3-7SYA)
- [Testing audio via the J22 breakout board 1](https://youtu.be/MyON9M_RYCk)
- [Testing audio via the J22 breakout board 2](https://youtu.be/EDeFRHsqa5c)
- [Testing the down converter breakout board for the first time.](https://youtu.be/BQKrsIXOSxU)
- [Mirroring an iMac G3 DV with this iMac G3 monitor hack](https://youtu.be/4jHPZWJs-aY)
- [All three boards installed and working.](https://youtu.be/dqxeiFkvuYg)
- [Rapberry Pi + Arduino powered iMac G3 hybrid running RetroPie](https://youtu.be/CLCZFmmEnno)
- [Adjusting iMac G3 picture settings via a serial terminal](https://youtu.be/9LLsHE3xdBA)
- [Adjusting iMac G3 picture settings with a java based GUI](https://youtu.be/zrzcvThxDeY)
- [Monitoring VSYNC to shut CRT off](https://youtu.be/fBMyjlEAZAw)
- [Cloning compiling and running oshimai's gui](https://youtu.be/DqM9bZfvwgM)
- [Stable arduino sketch that can communicate with oshimais GUI](https://youtu.be/inmUAiIA7sg)
- [Oshimais GUI running on a raspberry pi3 under mono](https://youtu.be/g9aLTrW5eaU)
- [Making a desktop recording the iMac G3 monitor with a raspberry pi, running oshimais gui](https://youtu.be/JA01o5xfwxg)
- [Assembling the J20 adapter board](https://youtu.be/qILuajxscnE)
- [Assembling the J22 adapter board](https://youtu.be/JCPRYKbwKyk)
- [Using a Gert VGA 666 adapter + Raspberry pi 3 with an Imac G3 monitor](https://youtu.be/5H0nzaTycOg)
- [Playing a round of among us using the iMac G3 as a monitor](https://youtu.be/MomKAUGT8i8)
- [Playing minecraft using the iMac G3 as a monitor](https://youtu.be/VxJVShNo72g)
- [Converting an iMac G3 DV into a monitor start to finish](https://youtu.be/guVSI1aqcJg)
- [Playing Duck Hunt and Super Mario Bros with my NES on the iMac G3](https://youtu.be/wCEGIwrCOMQ)
- [Playing "The Legend of Zelda" with my NES on the iMac G3](https://youtu.be/OpjjOnSjGQU)
- [Using my CoCo 2 on the iMac G3](https://youtu.be/9cu0CFqIWnc)
- [Modding an iMac G3 DV using only a Raspberry Pi](https://youtu.be/xSiqchucFE4)
