#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[][6] = {"00001","00002" };
boolean button_state = 0;
//Pinos

const int reset = 3;
int contagem_M1 = 0;
int contagem_M2 = 0;
int check_M1;
int check_M2;
int check;

void setup() {
  
  Serial.begin(9600);
 
  //radio
  radio.begin();
 
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);   //Setting the address at which we will receive the data
  
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
 
 //botoes
  pinMode(reset, OUTPUT);
  digitalWrite(reset, HIGH);

}
void Receber();
void Resetar();
void Maquina_1();
void Maquina_2();

void loop(){


  radio.startListening();              // ler informaçoes do outro pipe 

  
  Receber();
  Maquina_1();
  Maquina_2();
  //Resetar();
  delay(200);

}
 


void Receber() {


  while(radio.available()) { //verifica se a conexão esta habilitada
    //Serial.println("conexao ativa");
    radio.read(&contagem_M1, sizeof(int));
    Serial.print("contagem_M1: ");
    Serial.println(contagem_M1);

    delay(100);

    radio.read(&contagem_M2, sizeof(int));
    Serial.print("contagem_M2: ");
    Serial.println(contagem_M2);
    
    delay(100);
  }
  
  delay(50);

}

void Resetar(){
     // Serial.println(digitalRead(reset));
      if (digitalRead(reset) == 0){

        radio.stopListening(); // parar de ouvir para enviar informaçoes

        Serial.println("Envio resetar");
        check = radio.write(&reset, sizeof(int));
        Serial.print("checagem: ");
        Serial.println(digitalRead(reset));

        contagem_M1 = 0;
        contagem_M2 = 0;
        check_M1 = 0;
        check_M2 = 0;

              
      }


}

void Maquina_1(){

    
        
   if (contagem_M1 > check_M1)
    {
       Serial.println(" ");
       Serial.println("Maquina 1");
       Serial.print("Numero de ciclos: ");
       Serial.println(contagem_M1);
       Serial.println(" ");

       check_M1 = contagem_M1; 

    }
    
}

void Maquina_2(){

         
        
   if (contagem_M2 > check_M2)
    {
       Serial.println(" ");
       Serial.println("Maquina 2");
       Serial.print("Numero de ciclos: ");
       Serial.println(contagem_M2);
       Serial.println(" ");

       check_M2 = contagem_M2; 

    }
    
}

