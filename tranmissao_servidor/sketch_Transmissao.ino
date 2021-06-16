#include <SPI.h>
#include <RF24.h>

#define radioID 1   //Informar "0" para um dispositivo e "1" para o outro dispositivo
RF24 radio(9, 10); // CE, CSN

//-------------Inicio------------------Silos
#define sensor1 22
#define sensor2 24
#define sensor3 26
#define sensor11 23
#define sensor22 25
#define sensor33 27

int valor_s1;
int valor_s2;
int valor_s3;

int valor_s11;
int valor_s22;
int valor_s33;

//-------------Fim----------------------Silos

//-------------Inicio-------------------Radio
const byte address[][6] = {"00001", "00002"};
//-------------Fim----------------------Radio

//-------------Inicio-------------------Count
#define Sinal_1 2
#define Sinal_2 3
//-------------Fim----------------------Count
//-------------Inicio------------------Pack
struct pack {

  boolean reset;
  int contagem_M1;
  int contagem_M2;
  char silo_1[16] = "\0";
  char silo_2[16] = "\0";

};

pack pack_envio;
//--------------Fim-------------------Pack


const int reset_Pin = 5;

boolean x = 0;
boolean alterado_1 = false;
boolean alterado_2 = false;

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

  pinMode(Sinal_1,INPUT_PULLUP);
 digitalWrite(Sinal_1, HIGH);
 pinMode(Sinal_2, INPUT_PULLUP);
  digitalWrite(Sinal_2, HIGH);

  pinMode(sensor1, INPUT_PULLUP);
   digitalWrite(sensor1, HIGH);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(sensor3, INPUT_PULLUP);
  pinMode(sensor11, INPUT_PULLUP);
  pinMode(sensor22, INPUT_PULLUP);
  pinMode(sensor33, INPUT_PULLUP);

  pinMode(reset_Pin, OUTPUT);
  digitalWrite(reset_Pin, HIGH);

}
//--------------------------------LOOP
void loop() 
{
 //Serial.println(digitalRead(Sinal_1));
 //Serial.println(digitalRead(Sinal_2));
  Count_1();
  Count_2();
  Silos();
  Transmissao();
  resetar();

}
///--------------------------------------------------Transmissão
void Transmissao()
{

  if (alterado_1 == true) {
    
    radio.stopListening();          //para de ler informaçoes do outro pipe
  
    checagem(radio.write(&pack_envio, sizeof(pack_envio)));
    
    alterado_1 = false;

    radio.flush_tx();
  }
}

//--------------------------------------------------------Checagem
String checagem(int check)
{

  Serial.println("");
  Serial.print("Verificação de envio: ");
  if (check == 1) {
    Serial.println("Enviado.");
  } else {
    Serial.println("Negado.");
    radio.begin();
  }
  
  Serial.println("");

}
