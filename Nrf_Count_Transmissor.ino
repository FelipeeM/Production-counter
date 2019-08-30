      
#include <SPI.h>
#include <RF24.h>

#define radioID 1   //Informar "0" para um dispositivo e "1" para o outro dispositivo
RF24 radio(9, 10); // CE, CSN      



char Nivel_silo_1;
char Nivel_silo_2;

const byte address[][6] = {"00001", "00002"};
boolean reset = 0;
boolean alterado_1 = false;
boolean alterado_2 = false;
int sinal_Transmissao = 1 ;

  //int teste.contagem_M1;
 // int teste.contagem_M2; 
  
  struct Ciclos{
 
    String cod = "Maq";
    int contagem_M1;
    int contagem_M2;
};

Ciclos teste;

//count production
const int Sinal_1 = 2;
const int Sinal_2 = 3;
boolean x = 0;

int enviar;

void setup() {
  //radio
  radio.begin();                  //Starting the Wireless communication

#if radioID == 0
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
#else
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
#endif

  radio.setPALevel(RF24_PA_MIN);  

  //radio.startListening();

  Serial.begin(9600);

  pinMode(Sinal_1, INPUT_PULLUP);
  digitalWrite(Sinal_1, HIGH);

  pinMode(Sinal_2, INPUT_PULLUP);
  digitalWrite(Sinal_2, HIGH);


}

void Count_1();
void Count_2();
//void Silo1();
//void Silo2();
void Transmissao();
void Resetar();
////////////////////////////////////////////////////////////////////////---LOOP
void loop() {
  radio.stopListening();          //para de ler informaçoes do outro pipe

  Count_1();
  Count_2();
  //Silo1();
  Transmissao();
  Resetar();
  delay(10);

}
////////////////////////////////////////////////////////////////////////---Count
void Count_1() {

  if (digitalRead(Sinal_1) == 0) { // verifica se o sinal de contagem do ciclo foi ativado
    teste.contagem_M1 ++;

    while (digitalRead(Sinal_1) == 0) {
      Serial.print("Coont M1: ");
      Serial.println(teste.contagem_M1);
      if (digitalRead(Sinal_2) == 0 && digitalRead(Sinal_1) == 0 && alterado_1 == false ) {
        teste.contagem_M2 ++;
        alterado_1 = true;
        Serial.print("2");
      }
      delay(10);

    }
    alterado_1 = true;
  }

}

void Count_2() {


  if (digitalRead(Sinal_2) == 0) { // verifica se o sinal de contagem do ciclo foi ativado
    teste.contagem_M2 ++;

    while (digitalRead(Sinal_2) == 0) {
      Serial.print("Coont M2: ");
      Serial.println(teste.contagem_M2);
      if (digitalRead(Sinal_2) == 0 && digitalRead(Sinal_1) == 0 && alterado_2 == false ) {
        teste.contagem_M1 ++;
        alterado_2 = true;
        Serial.print("1");
      }

      delay(10);

    }
    alterado_1 = true;
  }


}

void checagem();
////////////////////////////////////////////////////////////////////////---Transmissão
void Transmissao()
{


  if (alterado_1 == true) {

    checagem(radio.write(&teste, sizeof(teste)));
//    checagem(radio.write(&teste.contagem_M2, sizeof(int)));

      alterado_1 = false;

      radio.flush_tx();
  }
}

void Resetar()
{

  radio.startListening();
  radio.read(&x, sizeof(boolean));

  if (x == 1) {

    Serial.print("Reset");
    teste.contagem_M1 = 0;
    teste.contagem_M2 = 0;

  }



}
////////////////////////////////////////////////////////////////////////---Checagem
String checagem(int check)
{

  Serial.println("");
  Serial.println("Verificação de envio: ");
  if (check == 1) {
    Serial.println("Enviado.");
  } else {
    Serial.println("Negado.");
    radio.begin();

  }

return 0;
Serial.println("");

}


