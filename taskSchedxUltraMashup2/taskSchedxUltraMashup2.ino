//================================================================================================
// modul ULTRA
//================================================================================================

// -----------------------------------------------------------------------------------------------------
// ZMIENNE GLOBALNE 

// ---- definicje dla czujnika Ultra ----
#define Ultrasonic_trigPin 12             // DIGITAL_12
#define Ultrasonic_echoPin 11             // DIGITAL_11
#define Ultrasonic_maxPulse_Length 75000  // maksymalna długość impulsu z czujnika, gdy nie ma przeszkody ok. 70ms
#define Ultrasonic_maxMeasurableDistance  240 // maksymalny zasięg pracy czujnika [240 cm]

// przelaczniki 
#define Ultrasonic_debug 2    // wlacza debugowanie czujnika   0,1,2,3  (bit 1 - czas impulsu i obliczona odleglosc, bit 2 - status

// ---- zmienne globalne dla czujnika Ultra ----
long Ultrasonic_distance=0;     // globalna zmienna odleglosci
enum  {U_noninitialized,U_error,U_false_measurement,  U_OK_dist_measured, U_OK_noobstacle} Ultrasonic_status;    // enum ze stanami czujnika
// U_noninitialized:  nie zainicjalizowany, nie wiemy czyu jest sprawny
// U_error:           wiemy że czujnik nie działa - nie zliczylismy impulsow
// U_OK_dist_measured:       wiemy, ze ostatni pomiar sie udal, wykryto przeszkode w zakresie czujnika
// U_OK_noobstacle:          wiemy, że ostatni pomiar się udał, ale nie widać przeszkody w zakresie czujnika (do 200 lub 400cm, w zaleznosci od zrodla infomracji)


// -----------------------------------------------------------------------------------------------------
// FUNKCJE 

// ---- funkcje obslugi czujnika Ultra ---
void Ultrasonic_setup(void) {
// ustawianie Arduino pod czujnik - umiescic w Setup
  pinMode(Ultrasonic_trigPin, OUTPUT);  //Pin, do którego podłączymy trig jako wyjście
  pinMode(Ultrasonic_echoPin, INPUT);   //a echo, jako wejście
  Ultrasonic_status=U_noninitialized;   // status - na niezainicjalizowany, 
}


int Ultrasonic_measureDistance(void){
// pomiar odleglosci - ustawia zmienne globalne: Ultrasonic_distance i Ultrasonic_status
// umiescic w loop
  
  long Ultrasonic_pulselength;
  
  // --- impuls wyzwalajacy czujnika
  digitalWrite(Ultrasonic_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(Ultrasonic_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Ultrasonic_trigPin, LOW);
  // --- pomiar dlugosci impulsu odpowiedzi czujnika
  Ultrasonic_pulselength = pulseIn(Ultrasonic_echoPin, HIGH, Ultrasonic_maxPulse_Length);
  // wynik pomiaru w mikrosekundach, ograniczony do 75ms (bo domyslnie w arduino czeka do 1s, a z czujnika max to 70 ms), 
  // mierzymy czas impulsu w stanie wysokim

  if (Ultrasonic_pulselength==0) {                  
    // wynik 0, gdy czas impulsu > ~75ms, 
    // czyli czujnik nie daje sygnalu - awaria sprzętu - ustaw status
    Ultrasonic_status=U_error;
    // gdy blad pomiaru to  nie zmieniamy zachowanej poprzedniej wartosci Ultrasonic_distance, 
    ;
    // ale mozemy zrobic inaczej i np odkomentowac 0 
    //Ultrasonic_distance=0;
    // lub odkomentowac wartosc maksymalna pomiaru
    //Ultrasonic_distance = Ultrasonic_maxMeasurableDistance;
  } 
  else if (Ultrasonic_pulselength > 69000)  {     
    // wynik ~69700 oznacza, ze czujnik działa, pomiar OK, ale nie widzi przeszkody w zakresie pracy czujnika
    // ustaw status na: U_OK_noobstacle
    Ultrasonic_status=U_OK_noobstacle;

    // i tutaj - do wyboru, mozemy nie zmieniac wartosci Ultrasonic_distance
    // lub mozemy ustawic na sztywno max. wartosc zakresu czujnika 
    Ultrasonic_distance = Ultrasonic_maxMeasurableDistance;
  }
  else if (Ultrasonic_pulselength > (Ultrasonic_maxMeasurableDistance*58) )  {     
    //
    Ultrasonic_status=U_false_measurement;
    // i tutaj - do wyboru, mozemy nie zmieniac wartosci Ultrasonic_distance
    ;
  } 
  else {
    // czas impulsu >0 i <69000, czyli prawidlowy wynik pomiaru - oblicz odleglosc
    Ultrasonic_distance = Ultrasonic_pulselength / 58;
    // ustaw status na: U_OK_dist_measured
    Ultrasonic_status=U_OK_dist_measured;
  }


 if (Ultrasonic_debug & 1)  {      // wykonywane tylko gdy przelacznik debugowy ma zapalony bit 1
   Serial.print("pulse[us]:");  
   Serial.print(Ultrasonic_pulselength);  
   Serial.print(" calc.dist[cm]:");  
   Serial.print(Ultrasonic_pulselength/58);  
   Serial.print(" ");  
  }
  
 }

 


void Ultrasonic_print_result(void) {
 if (Ultrasonic_debug & 2)  {      // wykonywane tylko gdy przelacznik debugowy ma zapalony bit 2
   switch (Ultrasonic_status) {
    case U_error:
           Serial.print("[ERROR     ] ");  
          break;
    case U_false_measurement:
           Serial.print("[FALSE meas] ");  
          break;
         
    case U_OK_dist_measured:
           Serial.print("[OK-meas   ] ");  
          break;
    case U_OK_noobstacle:
           Serial.print("[OK-no det ] ");  
          break;
    case U_noninitialized:
    default:
          Serial.print("[no init    ] ");        
          break;
   }
 }
 Serial.print("WYNIK:"); Serial.print(Ultrasonic_distance);  Serial.println(" cm");

}

  


//================================================================================================
// modul task scheduler
//================================================================================================

// -----------------------------------------------------------------------------------------------------
// ZMIENNE GLOBALNE 

// -----------------------------------------------------------------------------------------------------
// FUNKCJE 

void Task1(void)  {
  static unsigned long Task1_TimeSaved = 0;
  unsigned long ActualTimeMS = 0;

  static enum  {startup, Task1state_A,Task1state_B} Task1_state, Task1_state_prev;  

  // start tasku
  if (Task1_state==startup) {Task1_state=Task1state_A; Task1_state_prev=startup;}

  ActualTimeMS = millis();
  
  // jesli jest zmiana stanu, zapamietaj czas zmiany
  if (Task1_state!=Task1_state_prev) {
   Task1_TimeSaved=ActualTimeMS;
   Task1_state_prev=Task1_state;
  }

  switch (Task1_state) {
    #define Task1_state_A_TMO  500UL
    case Task1state_A:
        if ( (ActualTimeMS-Task1_TimeSaved) >= Task1_state_A_TMO ) {
          Task1_state=Task1state_B;
        }
        //Serial.print(".");
    break;

    case Task1state_B:
        Serial.println("*");
        Ultrasonic_measureDistance();
        Task1_state=Task1state_A;
    break;

  }
}
        

void Task2(void)  {
  static unsigned long Task2_TimeSaved = 0;
  unsigned long ActualTimeMS = 0;

  static enum  {startup, Task2state_X,Task2state_Y,Task2state_Z} Task2_state, Task2_state_prev;  

  // start tasku
  if (Task2_state==startup) {Task2_state=Task2state_Z; Task2_state_prev=startup;}

  ActualTimeMS = millis();
  
  // jesli jest zmiana stanu, zapamietaj czas zmiany
  if (Task2_state!=Task2_state_prev) {
   Task2_TimeSaved=ActualTimeMS;
   Task2_state_prev=Task2_state;
  }

  switch (Task2_state) {

    #define Task2_state_X_TMO  1500UL
    case Task2state_X:
        if ( (ActualTimeMS-Task2_TimeSaved) >= Task2_state_X_TMO ) {
          Task2_state=Task2state_Y;
        }
        Serial.print("X");
    break;

    #define Task2_state_Y_TMO  800UL
    case Task2state_Y:
        if ( (ActualTimeMS-Task2_TimeSaved) >= Task2_state_Y_TMO ) {
          Task2_state=Task2state_Z;
        }
        Serial.print("Y");
    break;

    #define Task2_state_Z_TMO  1000UL
    case Task2state_Z:
        if ( (ActualTimeMS-Task2_TimeSaved) >= Task2_state_Z_TMO ) {
          Task2_state=Task2state_X;
        }
        Serial.print("Z");
    break;
  }

}

void Task3(void)  {
  static unsigned long Task3_TimeSaved = 0;
  unsigned long ActualTimeMS = 0;

  static enum  {startup, Task3state_A,Task3state_B} Task3_state, Task3_state_prev;  

  // start tasku
  if (Task3_state==startup) {Task3_state=Task3state_A; Task3_state_prev=startup;}

  ActualTimeMS = millis();
  
  // jesli jest zmiana stanu, zapamietaj czas zmiany
  if (Task3_state!=Task3_state_prev) {
   Task3_TimeSaved=ActualTimeMS;
   Task3_state_prev=Task3_state;
  }

  switch (Task3_state) {
    #define Task3_state_A_TMO  2000UL
    case Task3state_A:
        if ( (ActualTimeMS-Task3_TimeSaved) >= Task3_state_A_TMO ) {
          Task3_state=Task3state_B;
        }
        //Serial.print(",");
    break;

    case Task3state_B:
        Ultrasonic_print_result();
        Task3_state=Task3state_A;
    break;

  }
}



//================================================================================================
// --== standardowe procedury Arduino ==--
//================================================================================================

void setup() {
  Serial.begin (9600);  // bo bedziemy pisac na port szeregowy
  Ultrasonic_setup();   // setup czujnika Ultradzwiekowaego
}


void loop(){
  Task1();
  Task2();
  Task3();
  delay(100); // ten delay ma byc wylaczony~!
}
