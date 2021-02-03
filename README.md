# Automated curtain
This GitHub repository contains project files to automate your IKEA curtain. It works by directly driving the bar that rolls up the curtain with a NEMA17 stepper motor. The hardware can be driven by any Arduino. In my case I used an Adafruit Feather HUZZAH because my original plan was to connect it to my Google Home. I cancelled that idea because I actually don't like Google Home. So I opted for a physical switch.

# Parts list
- NEMA17 stepper motor
- 3D-printed parts (see OUTPUT for STL files)
- Lasercut parts (see OUTPUT for DXF files)
- A pulley for the motor (you can also print this, but it is not really recommended). The pulley for the curtain bar is printed because it has uncommen dimensions.
- A belt (the pulley of the curtain bar is designed for the 2GT type)
- A power supply (5V, 12V, does not matter that much, perhaps you'll also need some converters)
- Any Arduino-like microcontroller
- Wire
- Stepper Driver (I used the DRV8825, does not really matter)

Feel free to contact me for any questions/problems, etc...
