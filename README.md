# Pet-Feeder
Google Assistant controlled IoT based Pet Feeder using NodeMCU 

Introduction :

Our project is automatic pet monitoring and feeding system using Internet of Things. Human interference on the part of taking care of pet when they are busy is difficult. And hence our system will be efficient enough to overcome the hurdles faced by human in taking care of pet.

Components Required:
•	NodeMCU ESP8266 : 
NodeMCU is a low-cost open source IoT platform. It initially included firmware which runs on the ESP8266 Wi-Fi SoC from Espressif Systems, and hardware which was based on the ESP-12 module. Later, support for the ESP32 32-bit MCU was add•ed.

•	Servo Motor : 
A servomotor is a rotary actuator or linear actuator that allows for precise control of angular or linear position, velocity and acceleration. It consists of a suitable motor coupled to a sensor for position feedback•

Working :
•After uploading the code to the NodeMCU

•Now Say "Okay Google. Feed my pet" to yo•r Google Assistant. Google Assistant will  recognize the phrase and respond with "Feeding your pet."

•After that it rotates the servo motor fr•m its initial position 0⁰ to 90⁰ and after a delay, it returns to its initial position.

•You can also feed your pet at a specific•time. For that we have used three strings i.e., “Morning”, “Afternoon” and “Evening”. 

•This is how you can feed your pet using •oogle Assistant. If you want to feed your pet at a specific time instead of morning, afternoon and evening, go to IFTTT and change the Google assistant settings from ‘Say a phrase with text ingredient’ to ‘Say a phrase with a number’.•
