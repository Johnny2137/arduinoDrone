/*
    Arduino and ADXL345 Accelerometer - 3D Visualization Example 
     by Dejan, https://howtomechatronics.com
*/
#include <Wire.h>  // Wire library - used for I2C communication

int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs
float roll,pitch,rollF,pitchF=0;
float x,y;
double deg = 2*PI/180;
int a0 = 10;

int a = 0;
int b = 0;
int c = 0;
int d = 0;



void setup() {
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
 
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
  Wire.endTransmission();
  delay(10);

  //Off-set Calibration
  //X-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1E);
  Wire.write(1);
  Wire.endTransmission();
  delay(10);
  //Y-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1F);
  Wire.write(-2);
  Wire.endTransmission();
  delay(10);

  //Z-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x20);
  Wire.write(-9);
  Wire.endTransmission();
  delay(10);
   pinMode(3, OUTPUT);
   pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
     pinMode(9, OUTPUT);
}

void loop() {
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read() | Wire.read() << 8); // X-axis value
  X_out = X_out / 256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
  Y_out = Y_out / 256;
  Z_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
  Z_out = Z_out / 256;

  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
  pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180 / PI;

  // Low-pass filter
  x = 0.94 * x + 0.06 * roll ;
  y = 0.94 * y + 0.06 * pitch;


// silnniki



    analogWrite(6,a0);
    analogWrite(3,a0);
    analogWrite(5,a0);
    analogWrite(9,a0);

     if (x>2 && y>2) {

    //  c = a0/cos(max(x,y));
      byte mx = max(x,y);
      c = min (round(a0/cos(abs(2*mx*PI/180))),255);
      analogWrite(6,c);

      analogWrite(3,a0);
      analogWrite(5,a0);
      analogWrite(9,a0);

    
  }
   else if (x>2 && y<-2) {
    //  a = a0/cos(max(abs(x),abs(y)));
       byte mx = max(abs(x),abs(y));
      a = min (round(a0/cos(abs(2*mx*PI/180))),255);
      analogWrite(6,a0);

      analogWrite(3,a);

      analogWrite(5,a0);
      analogWrite(9,a0);

   

  } else if (x<-2 && y<-2) {

      // b = a0/cos(max(abs(x),abs(y)));
        byte mx = max(abs(x),abs(y));
       b = min (round(a0/cos(abs(2*mx*PI/180))),255);
      analogWrite(6,a0);

      analogWrite(3,a0);
      
      analogWrite(5,b);
      analogWrite(9,a0);



    
  }
   else if (x<-2 && y>2) {
      // d = a0/cos(max(abs(x),abs(y)));
        byte mx = max(abs(x),abs(y));
      d = min (round(a0/cos(abs(2*mx*PI/180))),255);
      analogWrite(6,a0);

      analogWrite(3,a0);
      
      analogWrite(5,a0);
      analogWrite(9,d);



    
  }
  // przechył x+
    else if (x > 2)
  {
    int e = min (round(a0/cos(abs(2*x*PI/180))),255);
    analogWrite(3,e);
    analogWrite(6,e);
  
  }
  // przechyłł x-
   else if (x < -2)
  {
    int e = min (round(a0/cos(abs(2*x*PI/180))),255);
    analogWrite(5,e);
    analogWrite(9,e);

 
  
  
  }
  // przechył y+
   else if (y > 2)
  {
    int e = min (round(a0/cos(abs(2*y*PI/180))),255);
    analogWrite(9,e);
    analogWrite(6,e);
  
  
  
  }
  // przechył y-
   else if (y < -2)
  {
  int e = min (round(a0/cos(abs(2*y*PI/180))),255);
    analogWrite(3,e);
    analogWrite(5,e);
   
  
  }


  // Serial.print(x);
  // Serial.print("/");
  // Serial.println(y);
}