#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN  

const byte address[6] = "00001";
boolean button_state = 0;
int check;

//count production
const int Sinal = 2;
int contagem;

void setup() {
  //radio
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter

Serial.begin(9600);

pinMode(Sinal, OUTPUT);
digitalWrite(Sinal, HIGH);

}

void loop() {

  Count();
  check = radio.write(&contagem, sizeof(int)); 
  Serial.println(check); 
  
delay(500);

}

void Count(){
  
  if(digitalRead(Sinal) == 0){
      contagem ++;

      while(digitalRead(Sinal) == 0){
        Serial.print(contagem); 
        Serial.print("\n");
        delay(10); 

      } 

    }
  
  
  }
