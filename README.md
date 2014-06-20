# FanControl by CyberPlant



The a sample code for automatic speed control for the fan.
__________

# Description


Is, a compact device with a combination of some simple and useful functions.
The CyberPlant Automatic Fan Control measures temperature via the ds18b20 sensor.
the  temperature  sensor can be installed on the device or any other location
One single sensor can be connected directly to the device itself, or multiple sensors can be connected in series, for more precise ambient temperature reading. 
The CyberPlant Automatic Fan Control has offers smooth adjustments to the fan resolution speed. 
The combination of all the functions offer a precise versatile aid to controlling the temperature.

The fan motor takes its power directly from AC current running at 50Hz or 60Hz.

How does it work?
Setting up the CyberPlant Automatic Fan Control is very simple.

There are only two buttons required to set the programmable options.
With these, we can set the desired temperature values and also the Manual or Automatic Modes.

Automatic Mode.
During automatic mode if the temperature exceeds the set value, the electric charge will pulse every 2 seconds to add momentum.
If the temperature drops below the set value the fan speed will decrease until it stops. 
If the air temperature remains constant no change will occur.

This method allows the device to set the optimal speed for the fan, it prevents the temperature from exceeding the predetermined limit, reducing the total fan revolutions to the minimum possible and thereby saving on power consumption and noise levels.

On Manual Mode.
If you press the two buttons simultaneously the device will enter manual mode.
Here we can manually set the required power to the appliance and the settings are stored in non-volatile memory.
To switch back to automatic mode again just press both buttons simultaneously.

All logical parts are built on the ATmega328 microcontroller running the Arduino IDE. 
The Arduino board provides I2C Pins for connecting the device to other microcontrollers and a 6-pin to USB-TTL for easy program customisation which makes it all a very flexible and easily modifiable.to fit all your needs.
For example, maybe you would like to connect the device to the Internet this is easily done with the Arduino Internet Shield. 

or maybe you want the opposite, to heat the air in the room? It is easy! You can easily change the configuration of the device.


FanControl works with 220V AC and 110V AC at 50 Hz and 60 Hz And allows you to control the current to 4 amperes



It can display temperature in Celsius and Fahrenheit. 

FanControl is a simple and intuitive device with a great potential for modification and expansion. 
Use your imagination and a set of ready-made programs from Arduino IDE can build the automation of your dreams. 
This is an open source project. 

CyberPlant - help to people and love to plants


### Specifications

Temp sensor - DS18B20
Triac - 4A
works with 220V AC and 110V AC at 50 Hz and 60 Hz



[WWW.CYBERPLANT.INFO](http://www.cyberplant.info)