# ParkingSystem
final:
    It's for arduino to  control ultra sound, we use the distance which between cars and ultra sound to 
 
  distinguish if there is a car parking in th space. To avoid some cats and dog even leaves may stay on ultra sound so we use two or more 
 
  to prevent this situation. After this, we use uart transmit to ble module. 

BLEPeripheral:
    It's development environment is on IAR Which write for firmware. To use ble connect with central we need to construct a new characteristis
  
  to connect with it. After connected, we need to establish  a new event to notify periodly with gateway(central), that is try to use ble 
  
  transmit data to gate way.

gateway:
  Installation

1.Please donwnload "Bluepy" module from https://github.com/IanHarvey/bluepy

2.Check wtether there is "hcitool" module in your linux system or command "apt-get install hcitool"
 
3.Install Bluepy module and use "blescan.py" (at /bluepy/bluepy) to check the module installed properly

4.Please download "parsepy" module from  https://github.com/milesrichardson/ParsePy or use Parse Rest API (https://parse.com/docs/rest/guide)
  

parkingAPP:
 It's ios  App to show information from database(Parse). We can updating new information and motify it in real time. The great ideal for this App 

 is that we have a new iteam about "waiting number". "Waiting number" is a number of cars who want to park car in the space, it can achieve 

 bypass by too many cars in one parking space.
  

  
