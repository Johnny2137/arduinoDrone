/*
    Arduino and ADXL345 Accelerometer - 3D Visualization Example 
     by Dejan, https://howtomechatronics.com
*/
#include <Wire.h>  // Wire library - used for I2C communication

int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs
float roll,pitch,rollF,pitchF=0;
float x,y,x1,y1;
double deg = 2*PI/180;
int a0 = 1;

float A, B, C, D;  //moce silnikow
float DiffX, DiffY; //żądane roznice mocy silnikow w osiach


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

  //-----------------------
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
     // kalibracja żyroskopu
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

  x1 = 0.94 * x1 + 0.06 * roll ;
  y1 = 0.94 * y1 + 0.06 * pitch;



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
  x = 0.94 * x + 0.06 * roll  -x1  ;
  y = 0.94 * y + 0.06 * pitch -y1  ;


  




    
  // STABILIZACJA
  
	//Ustaw moc, tutaj tez bedzie mozna stale zmieniac P
  // Ustaw moc silnikow na P, jak chcesz miec reszte do dopisz po prostu C i D
  float P =0.1; //ustaw se jaka moc chcesz
  A = P;
  B = P;
  C = P;
  D = P;
    
      
   
    
	//DiffX okresla jaka chceny roznice mocy miedzy silnikami A i B, moze to byc zaleznosc sinusowa, cosinusowa, albo cokolwiek tam chcemy
  DiffX=0.5*sin(x);
  //to samo ale dla Y, silniki C i D
  DiffY=0.5*sin(y);
    
  //sprowadz roznice do zakresu od -1 do 1
  DiffX = max(-1.0f, min(1.0f, DiffX));
    
  // DiffX= roznica, ustawia moce aby spelnic rownanie A - B = DiffX
	A += DiffX;
	B -= DiffX;
	
	
	//muj specjalny sos, zapewnia ze zamiast probowac zwiekszyc moc silnika ponad 1, program zmniejszy moc tego drugiego silnika
	if (A>1 || B>1) {
		float wykroczenie = (max(A,B) -1);
		A= A - wykroczenie;
		B= B - wykroczenie;
	}
	if (A<0 || B<0) {
		float wykroczenie =  (min(A,B));
		A= A - wykroczenie;
		B= B - wykroczenie;
	}
		
	
  // Opcjonalne: Obetnij A i B do zakresu od 0 do 1, wydaje mi sie ze powyzszy program juz temu zapobiega
  A = max(0.0f, min(1.0f, A));
  B = max(0.0f, min(1.0f, B));


  // Output A i B
  Serial.print("A:");
  Serial.print(A);
  Serial.print("B:");
  Serial.print(B);
    
    
    
    
    
  //to samo ale dla Y
    
    
  //sprowadz roznice do zakresu od -1 do 1
  DiffY = max(-1.0f, min(1.0f, DiffY));
    
  // DiffY= roznica, ustawia moce aby spelnic rownanie A - B = DiffY
	C += DiffY;
	D -= DiffY;
	
	
	//muj specjalny sos, zapewnia ze zamiast probowac zwiekszyc moc silnika ponad 1, program zmniejszy moc tego drugiego silnika
	if (C>1 || D>1) {
		float wykroczenie = (max(C,D) -1);
		C= C - wykroczenie;
		D= D - wykroczenie;
	}
	if (C<0 || D<0) {
		float wykroczenie =  (min(C,D));
		C= C - wykroczenie;
		D= D - wykroczenie;
	}
		
	
  // Opcjonalne: Obetnij A i B do zakresu od 0 do 1, wydaje mi sie ze powyzszy program juz temu zapobiega
  C = max(0.0f, min(1.0f, C));
  D = max(0.0f, min(1.0f, D));


  // Output C i D
  Serial.print("C:");
  Serial.print(C);
  Serial.print("D:");
  Serial.print(D);


  //silniki

  analogWrite(6,int(255*A));
  analogWrite(3,int(255*B));
  analogWrite(5,int(255*C));
  analogWrite(9,int(255*D));






}