

void setup() {
 Serial.begin(9600);

   pinMode(3, OUTPUT);
   pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
     pinMode(9, OUTPUT);
}

void loop() {
  
  ///////------------------------------------------------------------------------------------------------------------
 int x = 50;
int y = 100;

 

 //  a  y+  b
 // - <-x-> +
 //  c  y-  d
  // silnik b
  // if (x > 2 && y >2)
  // {
  //   digitalWrite(5, HIGH);
   
  
  
  // }
  // // silnik c
  //  else if (x < -2 && y <-2)
  // {
  // digitalWrite(6, HIGH);
    
  
  
  // }
  // // silnik a
  //  else if (x < -2 && y >2)
  // {
  // digitalWrite(3, HIGH);
      
  
  
  // }
  // // silnik d
  //  else if (x > 2 && y >-2)
  // {
  // digitalWrite(9, HIGH);
      
  
  
  // }


  // przechył x+
    if (x > 2)
  {
  
    digitalWrite(3,HIGH);
    digitalWrite(6,HIGH);
  
  }
  // przechyłł x-
   else if (x < -2)
  {
  digitalWrite(5,HIGH);
  digitalWrite(9,HIGH);
  
  
  }
  // przechył y+
   else if (y > 2)
  {
  digitalWrite(9,HIGH);
  digitalWrite(6,HIGH);
   
  
  
  }
  // przechył y-
   else if (y < -2)
  {
  
   digitalWrite(3,HIGH);
  digitalWrite(5,HIGH);
  
  }
  else if (x>2 && y>2) {
    digitalWrite(5,HIGH);
  }
  
  
 // analogWrite(3, a);
 // analogWrite(5,b);
 // analogWrite(6,c);
 // analogWrite(9,d);
//
//Serial.println("o     o");
//Serial.println("  | | ");
//Serial.println("  | | ");
//Serial.println("o     o");

}