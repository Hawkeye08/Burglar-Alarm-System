# Burglar-Alarm-System

This is a code on Arduino UNO for a Burglar Alarm System Interfacing an 16x2 LCD using I2C, an RFID Sensor (MFRC522), a Buzzer (Connected between A0 and Ground) and an Ultrasonic Sensor (HC-SR04).

The idea is to create a simple system, which detects anyone unauthorised entering a specific location and Rings the Buzzer if wrong RFID card is shown, or if someone crosses the path of the ultrasonic without authorising themselves by showing the registered RFID card.

Included Libraries -
LiquidCrystal_I2C.h,
SPI.h,
MFRC522.h,
NewPing.h

Code has comments for easy understanding of each line or loop.
