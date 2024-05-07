/*
    Arduino and ADXL345 Accelerometer - 3D Visualization Example 
     by Dejan, https://howtomechatronics.com
*/
#include <Wire.h>  // Wire library - used for I2C communication

int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs
float roll,pitch,rollF,pitchF=0;
float x,y;
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
  x = 0.94 * x + 0.06 * roll;
  y = 0.94 * y + 0.06 * pitch;

if (x>2 && y>2) {
    digitalWrite(6,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    digitalWrite(9,LOW);
  }
   else if (x>2 && y<-2) {
    digitalWrite(3,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(5,LOW);
    digitalWrite(9,LOW);

  } else if (x<-2 && y<-2) {
    digitalWrite(5,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(6,LOW);
    digitalWrite(9,LOW);
  }
   else if (x<-2 && y>2) {
    digitalWrite(9,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
  }
  // przechył x+
    else if (x > 2)
  {
  
    digitalWrite(3,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(5,LOW);
  
  }
  // przechyłł x-
   else if (x < -2)
  {
  digitalWrite(5,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(3,LOW);
    digitalWrite(6,LOW);
  
  
  }
  // przechył y+
   else if (y > 2)
  {
  digitalWrite(9,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(3,LOW);
    digitalWrite(5,LOW);
   
  
  
  }
  // przechył y-
   else if (y < -2)
  {
  
   digitalWrite(3,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(9,LOW);
    digitalWrite(6,LOW);
  
  }


  // Serial.print(x);
  // Serial.print("/");
  // Serial.println(y);
}