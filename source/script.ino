//Program: Autonomous Drone
//Author: Justinder Uppal (200362124)
//Course: CS 807
//Date: 2022-08-15
//Final Project
//Description: logic for autonomous drone. Enables manual control over bluetooth module. Allows for autonomous take off, landing and hover via take off action. 

//Libraries used 
#include <Servo.h>
#include<Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

//Constants from BMP library via Adafruit 
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

// create servo object to control each ESC individually
Servo ESC1;    
Servo ESC2;
Servo ESC3;
Servo ESC4;

// intial speed calibration for each esc so they start at the same time
int initFront = 12; 
int initRear = 10;
int initLeft = 9;
int initRight = 8;

//initial height value
float initHeight = 0;

//values for each state
bool killSwitch = false;
bool autoLand = false;
bool autoTakeoff = false;

//code recieved over bluetooth
char Incoming_value = 0;       

//overall speed of drone
int speed = 0;

//values to caclulate pitch and roll 
const int MPU_addr1 = 0x68;
float xa, ya, za, roll, pitch;

//Add fruit library for bmp sensor
Adafruit_BMP280 bmp; 

void setup() 
{
    Serial.begin(9600);      //Sets the data rate in bits per second (baud) for serial data transmission

  //Using bmp library as seen in test code provided by library 
  unsigned status;
  status = bmp.begin(0x76);
  
  //default settings for bmp as seen in test code provided by adafruit
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,   
                  Adafruit_BMP280::SAMPLING_X2,   
                  Adafruit_BMP280::SAMPLING_X16,  
                  Adafruit_BMP280::FILTER_X16,    
                  Adafruit_BMP280::STANDBY_MS_500); 
  //store initial height value read by sensor
  initHeight = bmp.readAltitude(1012);
  
  //attaching esc's using pwm
  ESC1.attach(9,1000,2000);  
  ESC2.attach(10,1000,2000); 
  ESC3.attach(11,1000,2000);) 
  ESC4.attach(12,1000,2000);  
  
  //setting intial speed of 0 for each esc

  ESC1.write(0); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.write(0); // (pin, min pulse width, max pulse width in microseconds) 
  ESC3.write(0); // (pin, min pulse width, max pulse width in microseconds) 
  ESC4.write(0); // (pin, min pulse width, max pulse width in microseconds) 

  //setting up the gyroscope and accelerometer 
  Wire.begin();                                      //begin the wire communication
  Wire.beginTransmission(MPU_addr1);                 //begin, send the slave adress (in this case 68)
  Wire.write(0x6B);                                  //make the reset (place a 0 into the 6B register)
  Wire.write(0);
  Wire.endTransmission(true);                        //end the transmission

  //waiting to make sure everything is setup correctly
  delay(1000);

}
void loop()
{
  //check if kill switch has been clicked
  if (!killSwitch)
  {
    //calculating pitch and roll
    Wire.beginTransmission(MPU_addr1);
    Wire.write(0x3B);  
    Wire.endTransmission(false); 
    Wire.requestFrom(MPU_addr1, 6, true);
    int t = Wire.read();
    xa = (t << 8) | Wire.read();
    t = Wire.read();
    ya = (t << 8) | Wire.read();
    t = Wire.read();
    za = (t << 8) | Wire.read();
    //only trigger pitch and roll if speed is greater than 50%
    if (speed > 50)
    {
        roll = atan2(ya , za) * 180.0 / PI;
        pitch = atan2(-xa , sqrt(ya * ya + za * za)) * 180.0 / PI; 
    }
    else {
      roll = 0;
      pitch = 0;
    }
    //if there is data availible from bluetooth
    //if value is u, trigger speed up
    //if value is d, trigger speed down
    //if value is k, trigger kill switch
    //if value is l, trigger auto land
    //if value is t, trigger auto takeoff
    if(Serial.available() > 0)  
    {
      //read incomming bluetooth value
      Incoming_value = Serial.read();    
      if(Incoming_value == 'u')        
      {
        speed = speed + 1;
        digitalWrite(13, HIGH); 
      }
      else if(Incoming_value == 'd')       
      {
        speed = speed - 1;
        digitalWrite(13, LOW); 
      }
      else if(Incoming_value == 'k')           
      {
        killSwitch = true;
      }
      else if(Incoming_value == 'l')           
      {
        autoLand = true;
      }
      else if(Incoming_value == 't')            
      {
        autoTakeoff = true;
      }
  }    
  //only trigger motor speed when speed is set to more than zero
  if (speed > 0)
  {
    //use init speed if value is less than calibrated speed
    if (speed < initFront) 
    {
      //motor speed adjusted for either pitch or roll depending on placement
      ESC4.write(initFront - pitch); 
    }
    else
    {
      ESC4.write(speed - pitch); 
    }
    if (speed < initRear) 
    {
      ESC2.write(initRear + roll); 
    }
    else
    {
      ESC2.write(speed + roll); 
    }
    if (speed < initLeft) 
    {
      ESC1.write(initLeft + pitch); 
    }
    else
    {
      ESC1.write(speed + pitch); 
    }
    if (speed < initRight) 
    {
      ESC3.write(initRight - roll);
    }
    else
    {
      ESC3.write(speed - roll);  
    }
  }
  else 
  {
        //shut motors off if speed less than zero
        ESC1.write(0); // (pin, min pulse width, max pulse width in microseconds) 
        ESC2.write(0); // (pin, min pulse width, max pulse width in microseconds) 
        ESC3.write(0); // (pin, min pulse width, max pulse width in microseconds) 
        ESC4.write(0); // (pin, min pulse width, max pulse width in microseconds) 
  }
 }
 else if (autoLand)
 {
    //logic for auto landing
    ESC1.write(45); // (pin, min pulse width, max pulse width in microseconds) 
    ESC2.write(45); // (pin, min pulse width, max pulse width in microseconds) 
    ESC3.write(45); // (pin, min pulse width, max pulse width in microseconds) 
    ESC4.write(45); // (pin, min pulse width, max pulse width in microseconds) 
    if (initHeight == bmp.readAltitude(1012)) * -1)
    {
      ESC1.write(0); // (pin, min pulse width, max pulse width in microseconds) 
      ESC2.write(0); // (pin, min pulse width, max pulse width in microseconds) 
      ESC3.write(0); // (pin, min pulse width, max pulse width in microseconds) 
      ESC4.write(0); // (pin, min pulse width, max pulse width in microseconds)
      autoLand = false;
    }
 }
 else if (autoTakeoff)
 {    
    //logic for auto takeoff
    ESC1.write(75); // (pin, min pulse width, max pulse width in microseconds) 
    ESC2.write(75); // (pin, min pulse width, max pulse width in microseconds) 
    ESC3.write(75); // (pin, min pulse width, max pulse width in microseconds) 
    ESC4.write(75); // (pin, min pulse width, max pulse width in microseconds) 
    if (1.0 == bmp.readAltitude(1012)) * -1)
    {
      autoTakeoff = false;
      ESC1.write(50); // (pin, min pulse width, max pulse width in microseconds) 
      ESC2.write(50); // (pin, min pulse width, max pulse width in microseconds) 
      ESC3.write(50); // (pin, min pulse width, max pulse width in microseconds) 
      ESC4.write(50); // (pin, min pulse width, max pulse width in microseconds) 
    }
 }
 else 
 {
    //logic for killswitch
    ESC1.write(0); // (pin, min pulse width, max pulse width in microseconds) 
    ESC2.write(0); // (pin, min pulse width, max pulse width in microseconds) 
    ESC3.write(0); // (pin, min pulse width, max pulse width in microseconds) 
    ESC4.write(0); // (pin, min pulse width, max pulse width in microseconds) 
 }
}