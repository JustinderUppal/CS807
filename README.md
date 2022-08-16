# CS807 - Final Project: Autonomous Drone
This project is the creation of an autonomous drone capable of landing, taking off and hovering. The user has the ability to also manual control the drone over bluetooth. The drone is based off of the arduino platform.

# Front view of Autonomous drone 
![Screenshot 2022-08-15 205440](https://user-images.githubusercontent.com/111323535/184788481-43c00640-b747-4dfa-9cf0-d7c03a7f4f0c.png)
# Rear view of autonomous drone
![Screenshot 2022-08-15 205604](https://user-images.githubusercontent.com/111323535/184788647-2dd8464c-1a93-4b0f-afa7-4c2e22d8d021.png)
# Side view of autonomous drone
![Screenshot 2022-08-15 205532](https://user-images.githubusercontent.com/111323535/184788595-664bfbf9-445d-43b0-95ab-5fedf00a0046.png)

# Build instructions
Below is a block diagram of the project on how each component is connected to each other. Note that the there are 4 motors, 4 electronic speed controls, and 2 batteries.
![Untitled - Frame 1 (3)](https://user-images.githubusercontent.com/111323535/184789134-a539e0c1-d1bf-44fb-b3a9-93628ab459d4.jpg)

# Repository Contents
This is the directories and contents of the repository:
1. Drone: This folder contains the 3d files used to print the final prototype drone. They are sourced from the thingiverse website from the author Brendan22 https://www.thingiverse.com/thing:304237. 
2. Source: This folder contains the final source code used for the project and all the necessary test files that were accessed during the creation of the project. Note: All authors and sources of the test files are included at the top of each file. 
3. Test bench: This folder contains the 3d files used to print the test bench. The a2212 mount file was sourced from the thingiverse website from the author Cezar_Borogua https://www.thingiverse.com/thing:3013397

# Requirements and Materielas
Libraries used for the project are:
1. ADAFRUIT BMP280 Library: directly availible in the arduino IDE for download

The materials used for this project are:
1. Ender 5 pro for 3D printing
2. 3D printer fillament 
3. 4 propeller motors along with 4 esc (unbranded esc and a2212/6t motors)
4. Barometer bmp280 created by adafruit
5. Accelerometer and Gyroscope (gy-521)
6. Generic bluetooth module
7. 2 lipo-2s batteries 
8. Ardunino Uno

#Usasge 
1. Upload the code to the arduino uno via the arduino ide. The ide is availible for download on the Arduino website. 
2. Plug in the batteries to the 4 propeller motors, this will automatically power on the Arduino uno board. 
3. Once powered on, the arduino will cycle through the initial phase of setup. Setup is complete once the beeping of the motor initialization has finished. 
4. Download and install a arduino bluetooth application on the phone. Use the configured text strings on the gamepad which are located in the script.ino file. These text strings trigger specific actions within the aruino logic. For example, passing a u across bluetooth will trigger the speed to increase where as passing a d will decrease the speed. The key ledgend is listed in the script file. 
5. To shut off the drone, trigger the killswitch and unplug the batteries. 

#Contributors
1. Justinder Uppal - I am the sole contributor to this repository and report

#Credits
1. Code credits are listed under the test files 
2. Dr. Trevor Tomesh - CS 807 Instructor
