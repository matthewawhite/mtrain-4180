# What is MTrain
The MTrain is a new devboard based on the Cortex M7 being developed by [RoboJackets](https://robojackets.org/) to replace the Mbed in our robotics applications. The MTrain has many advantages over the Mbed, most notably:
* Hardware Floating Point Unit
* 256 MB of Flash Memory
* 256 MB of RAM
* JTAG support
* Ability to support Over the Air Firmware Updates
* High Speed USB (480 Mbps)
* 100 Mbps Ethernet

# 4180 Project
For the 4180 project we have implemented the API for DigitalIO and I2C on the MTrain. Our demo specifically connects a pushbutton to an led through the MTrain to demonstrate the DigitalIO while also sending `Hello I2C!` over the I2C line to an Mbed which then displays it on the LCD screen.

# Code
### MTrain
The code that runs on the MTrain can be found in the repo connected to this website or by following this [link](https://github.com/matthewawhite/mtrain-4180)
The specific code that was written for this project can be found in the following locations:
* DigitalIO
   * [Headers](https://github.com/matthewawhite/mtrain-4180/blob/master/BSP/Inc/gpio.h)
   * [Source](https://github.com/matthewawhite/mtrain-4180/blob/master/BSP/Src/gpio.c)
* I2C
   * [Headers](https://github.com/matthewawhite/mtrain-4180/blob/master/BSP/Inc/i2c.h)
   * [Source](https://github.com/matthewawhite/mtrain-4180/blob/master/BSP/Src/i2c.c)

### Mbed
The code that runs on the Mbed can be found in the Mbed repository [here](https://os.mbed.com/users/mwhite98/code/4180_Project/)

# Demonstration Setup
## Software Setup
### MTrain
1. Clone the repo with our code found [here](https://github.com/matthewawhite/mtrain-4180)
2. Connect the MTrain over JTag using the adapter
3. Flash the MTrain by running `make test-communicate_i2c-prog` from the mtrain-4180 folder

### Mbed
1. Build and download the project found [here](https://os.mbed.com/users/mwhite98/code/4180_Project/)
2. Copy the bin file to the Mbed over USB

## Hardware Setup
### Requirements
* 1x Functional MTrain
   * The pcb and other necessary production information can be found [here](https://github.com/RoboJackets/mtrain-pcb)
* 1x Mbed
* 1x LED
* 1x Pushbutton
* 1x uLCD-144-G2
* 1x Breadboard
* 1x JLink Segger and JTag adapter (For flashing the MTrain)

### Setup
#### Ground
* Connect the Ground lines of the Mbed and the MTrain to the Ground rail of the breadboard
#### I2C Lines
* Connect pin 25 on the MTrain to pin 10 on the Mbed
* Connect pin 26 on the MTrain to pin 9 on the Mbed
#### Pushbutton and LED
* Connect pin 3 on the MTrain to one side of the pushbutton
* Connect the other side of the pushbutton to the LED
* Connect the other side of the LED to ground
#### LCD Screen
* Connect +5V on the LCD screen to the VU pin on the MBed
* Connect Ground on the LCD screen to the ground rail
* Connect pin 30 of the Mbed to the reset pin of the LCD screen
* Connect pin 28 of the Mbed to the TX pin of the LCD screen
* Connect pin 27 of the Mbed to the RX pin of the LCD screen
#### USB Power
* Connect the Mbed to USB power first
* Connect the MTrain to USB power

## Results
If everything was done correctly pushing the button should turn on the LED and the LCD screen should be repeatedly flashing `Hello I2C!` as shown in the video linked below:
![Blinking_I2C](media/Blinking_I2C.mp4)
