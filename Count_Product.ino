//count production
 const int  = 2;
 int count;
 
  
void setup() {

   pinMode(Signal, OUTPUT);
   digitalWrite(Signal, HIGH);
   
   Serial.begin(9600);
}

void loop() {



    if(digitalRead(Signal) == 0){
      contagem ++;

      while(digitalRead(Signal) == 0){
        Serial.print(count); 
        Serial.print("\n");
        delay(10); 

      } 

    }

}
