# Modify a slot loading iMac G3 to use it as a monitor
iMac G3 IVAD board initialization with an arduino or raspberry pi

<!-- toc -->
- [Chasis Connectors and Pinouts](#Chasis-Connectors-and-Pinouts)
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
- [Powering the CRT on and off](#Powering-the-CRT-on-and-off)
- [See Also](#See-Also)
   * [Videos](#Videos)


## Chasis Connectors and Pinouts
![ChasisConnectors](connectors_and_boards.png?raw=true "Chasis connectors")

### Removing the logic board
The connector drawings in the above [diagram](#Chasis-Connectors-and-Pinouts) represent the cables
coming from the CRT analog board that plug into the logic board. To expose these, the logic board must
be removed.

## Wiring VGA cable
![VGACable](vga_adapter.png?raw=true "VGA Cable")

### Making the cable
This is perhaps the most time consuming part of the whole process because not all VGA cables are made the same so the colors for the cable I used may not be the colors used in your cable. Here are the steps I took.<br>


- Find a VGA cable to cut.
- Cut the cable so that you have at least one of the ferrite chokes left on the cable.
- Cut away the cable jacket such that the wires are at a comfortable handling length. 3 to 4 inches
- Strip each wire and ring them out to find what color corresponds to each pin on the DB15 connector.
- Use the [diagram](#Wiring-VGA-cable) above and map your cable to J20 using the DB15 pin numbers as the key.
- Option 1 ,use a 20 pin header and solder the DB15 wires to it then plug it into J20.
- Option 2, cut the required wires from J20 and splice them with VGA cable. Solder and use shrink tubing if you can but twisting them and electrical tape works as well. Make sure to leave enough wire on J20 in the event you need to reattach the wires.



## Preparing the Raspberry Pi
![WiringRPI](raspberry_pi_wiring.png?raw=true "Wiring RPI")

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
-Edit config.txt
```bash
sudo nano /boot/config.txt
```
-Add the following to the bottom of the file and save
```
#iMac G3 settings
hdmi_group=2
hdmi_mode=18
```

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
![WiringArduinoUno](arduino_uno_wiring.png?raw=true "Wiring Arduino Uno")

## Wiring Arduino Nano
![WiringArduinoNano](arduino_nano_wiring.png?raw=true "Wiring Arduino Nano")

### Loading and Running the initialization sketch
write here

## Wiring Arduino Uno to transmit EDID
![WiringArduinoUnoToXmitEdid](arduino_uno_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Uno to transmit EDID")

## Wiring Arduino Nano to transmit EDID
![WiringArduinoNanotoXmitEdid](arduino_nano_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Nano to transmit EDID")


## Powering the CRT on and off
![CRTOnAndOff](crt_power_on_and_off.png?raw=true "CRT On and Off")

## See Also
### Videos
- [Booting an non-modded iMac G3 to confirm the CRT turns on](https://youtu.be/meIzAyQd0t0)
- [Initializing IVAD board with an Arduino Uno](https://youtu.be/JLaHMjQ7idI)
- [Using iMac G3 as a second monitor with custom modeline](https://youtu.be/iSCjOOsf-QQ)
- [Tweaking the modeline to make the iMac G3 fullscreen](https://youtu.be/1DeY3o7P60g)
- [Sending the EDID via the VGA cable to a connected computer](https://youtu.be/KzHUogEQob4)
- [Using CRT without the logic board](https://youtu.be/MbTqhlqsKoY)
- [Running DOSBOX](https://youtu.be/PG7bluXxrPA)
- [Initializing the CRT using only a Raspberry Pi](https://youtu.be/isjo-4vQxwM)
