int a0 = 1;

float a = 0;
float b = 0;
float c = 0;
float d = 0;


void setup() {
 Serial.begin(9600);

   pinMode(3, OUTPUT);
   pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
     pinMode(9, OUTPUT);
}

void loop() {
  
  ///////------------------------------------------------------------------------------------------------------------
 int x = 40;
int y = 40;

 

//  rozmieszczenie wyprowadzeń
//   9   6                  układ xy jak na matmie  
//   5   3
// -----------------------start----------------------
      analogWrite(6,a0);
      analogWrite(3,a0);
      analogWrite(5,a0);
      analogWrite(9,a0);

  if (x>2 && y>2) {

      c = a0/cos(max(x,y));
      
      analogWrite(6,c);

      analogWrite(3,a0);
      analogWrite(5,a0);
      analogWrite(9,a0);

    
  }
   else if (x>2 && y<-2) {
      a = a0/cos(max(abs(x),abs(y)));
      Serial.println(a);
      analogWrite(6,a0);

      analogWrite(3,a);

      analogWrite(5,a0);
      analogWrite(9,a0);





   

  } else if (x<-2 && y<-2) {

       b = a0/cos(max(abs(x),abs(y)));
      analogWrite(6,a0);

      analogWrite(3,a0);
      
      analogWrite(5,b);
      analogWrite(9,a0);



    
  }
   else if (x<-2 && y>2) {
       d = a0/cos(max(abs(x),abs(y)));
      analogWrite(6,a0);

      analogWrite(3,a0);
      
      analogWrite(5,a0);
      analogWrite(9,d);



    
  }
  // przechył x+
    else if (x > 2)
  {
    
    int e = a0/cos(x);
    
    analogWrite(3,e);
    analogWrite(6,e);
  
  }
  // przechyłł x-
   else if (x < -2)
  {
    int e = a0/cos(abs(x));
    analogWrite(5,e);
    analogWrite(9,e);

 
  
  
  }
  // przechył y+
   else if (y > 2)
  {
    int e = a0/cos(y);
    analogWrite(9,e);
    analogWrite(6,e);
  
  
  
  }
  // przechył y-
   else if (y < -2)
  {
  int e = a0/cos(abs(y));
    analogWrite(3,e);
    analogWrite(5,e);
   
  
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