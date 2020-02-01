# Use slot loading iMac G3 as a monitor
iMac G3 IVAD board initialization with an arduino or raspberry pi

<!-- toc -->
- [Chasis Connectors and Pinouts](#Chasis-Connectors-and-Pinouts)
- [Wiring VGA cable](#Wiring-VGA-cable)
- [Preparing the Raspberry Pi](#Preparing-the-Raspberry-Pi)
    * [What to install](#What-to-install)
-   * [Wiring Raspberry Pi](#Wiring-Raspberry-Pi)
- [Wiring Arduino Uno](#Wiring-Arduino-Uno)
- [Wiring Arduino Nano](#Wiring-Arduino-Nano)
- [Wiring Arduino Uno to transmit EDID](#Wiring-Arduino-Uno-to-transmit-EDID)
- [Wiring Arduino Nano to transmit EDID](#Wiring-Arduino-Nano-to-transmit-EDID)


## Chasis Connectors and Pinouts
![ChasisConnectors](connectors_and_boards.png?raw=true "Chasis connectors")

## Wiring VGA cable
![VGACable](vga_adapter.png?raw=true "VGA Cable")

## Preparing the Raspberry Pi
![WiringRPI](raspberry_pi_wiring.png?raw=true "Wiring RPI")

### What to install
- Install the latest raspian image using a regular monitor.
- Enable ssh , you'll need this to login from another computer when you don't have a display
- Enable I2C
- Install i2c-tools
- Install git
- Copy init_ivad.py

### Wiring Raspberry Pi

In all cases, the IVAD board needs to be initialized when the power analog board is
turned on for the first time. To do this, the initialization sequence must be sent using the
I2C lines(SDA & SCL) on the Raspberry Pi's GPIO header. Connect the I2C lines according to the diagram
above.



## Wiring Arduino Uno
![WiringArduinoUno](arduino_uno_wiring.png?raw=true "Wiring Arduino Uno")

## Wiring Arduino Nano
![WiringArduinoNano](arduino_nano_wiring.png?raw=true "Wiring Arduino Nano")

## Wiring Arduino Uno to transmit EDID
![WiringArduinoUnoToXmitEdid](arduino_uno_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Uno to transmit EDID")


## Wiring Arduino Nano to transmit EDID
![WiringArduinoNanotoXmitEdid](arduino_nano_wiring_to_transmit_edid.png?raw=true "Wiring Arduino Nano to transmit EDID")
