# Use slot loading iMac G3 as a monitor
iMac G3 IVAD board initialization with an arduino or raspberry pi

<!-- toc -->
- [Chasis Connectors and Pinouts](#Chasis-Connectors-and-Pinouts)
- [Wiring VGA cable](#Wiring-VGA-cable)
- [Preparing the Raspberry Pi](#Preparing-the-Raspberry-Pi)
    * [What to install](#What-to-install)
-   * [Wiring The Raspberry Pi and testing the connection](#Wiring-The-Raspberry-Pi-and-testing-the-connection)
- [Wiring Arduino Uno](#Wiring-Arduino-Uno)
- [Wiring Arduino Nano](#Wiring-Arduino-Nano)
- [Wiring Arduino Uno to transmit EDID](#Wiring-Arduino-Uno-to-transmit-EDID)
- [Wiring Arduino Nano to transmit EDID](#Wiring-Arduino-Nano-to-transmit-EDID)
- [Powering the CRT on and off](#Powering-the-CRT-on-and-off)


## Chasis Connectors and Pinouts
![ChasisConnectors](connectors_and_boards.png?raw=true "Chasis connectors")

## Wiring VGA cable
![VGACable](vga_adapter.png?raw=true "VGA Cable")

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

### Wiring The Raspberry Pi and testing the connection

In all cases, the IVAD board needs to be initialized when the power analog board is
turned on for the first time. To do this, the initialization sequence must be sent using the
I2C lines(SDA & SCL) on the Raspberry Pi's GPIO header. Connect the I2C lines according to the diagram
above.

- Use i2cdetect to probe the IVAD board. Make sure the iMac is plugged in, it does not have to be turned on for this.

```bash
i2cdetect -y 1
```
- Confirm it found address's 46 and 53, if no luck, check the wiring. The output should look somhting like the following.
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


## Wiring Arduino Uno
![WiringArduinoUno](arduino_uno_wiring.png?raw=true "Wiring Arduino Uno")

## Wiring Arduino Nano
![WiringArduinoNano](arduino_nano_wiring.png?raw=true "Wiring Arduino Nano")

## Wiring Arduino Uno to transmit EDID
![WiringArduinoUnoToXmitEdid](arduino_uno_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Uno to transmit EDID")

## Wiring Arduino Nano to transmit EDID
![WiringArduinoNanotoXmitEdid](arduino_nano_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Nano to transmit EDID")


## Powering the CRT on and off
![CRTOnAndOff](crt_power_on_and_off.png?raw=true "CRT On and Off")
