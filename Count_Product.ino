//contador produção
 const int Sinal = 2;
 int contagem;

void setup() {
 
  pinMode(Sinal, OUTPUT);
  digitalWrite(Sinal, HIGH);
   
  Serial.begin(9600);
}

void loop() {
  
    Count();
    delay(10);
  
}
void Count() {

  if(digitalRead(Sinal) == 0){
      contagem ++;

      while(digitalRead(Sinal) == 0){
        Serial.print(contagem); 
        Serial.print("\n");
        delay(10); 

      } 
    }

}


