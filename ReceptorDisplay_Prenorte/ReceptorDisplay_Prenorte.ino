//#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <UIPEthernet.h> 

#define radioID 0   //Informar "0" para um dispositivo e "1" para o outro dispositivo

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
EthernetServer server(80); //PORTA EM QUE A CONEXÃO SERÁ FEITA
RF24 radio(9, 10); // CE, CSN
const byte address[][6] = {"00001","00002" };

boolean button_state = 0;
boolean x; 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //ATRIBUIÇÃO DE ENDEREÇO MAC AO ENC28J60
byte ip[] = { 192, 168, 0, 155 }; //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR. EX: 192.168.1.110  **** ISSO VARIA, NO MEU CASO É: 192.168.0.175


  struct Ciclos{
 
    String cod = "Maq";
    int contagem_M1;
    int contagem_M2;
};

Ciclos teste;

//Pinos

const int reset = 3;
int check_M1;
int check_M2;
int check;

void setup() {
  lcd.begin (16,2);
  
  server.begin(); 
  Ethernet.begin(mac, ip);
  
  Serial.begin(9600);
  //radio
    radio.begin();
 
    #if radioID == 0
      radio.openWritingPipe(address[0]);
      radio.openReadingPipe(1, address[1]);
    #else
      radio.openWritingPipe(address[1]);
      radio.openReadingPipe(1, address[0]);
    #endif
    
       
       lcd.setCursor(4,0);  
       lcd.print("PRENORTE");
       lcd.setCursor(3,1);  
       lcd.print("Sistem 1.0");
       lcd.setBacklight(LOW);
       delay(500);
       lcd.setBacklight(HIGH); 
       delay(500);
       lcd.setBacklight(LOW);
       delay(500);
       lcd.setBacklight(HIGH);
       delay(500);
       lcd.setBacklight(LOW);
       lcd.setCursor(3,0);  
       lcd.print("Aguardando");
       lcd.setCursor(1,1);
       lcd.print("informacoes...");
       delay(500);
       lcd.setBacklight(HIGH);

  
    radio.setPALevel(RF24_PA_MIN); 

     
 //botoes
  pinMode(reset, OUTPUT);
  digitalWrite(reset, HIGH);

}
//voids
  void Receber();
  void Resetar();
  void Maquina_1();
  void Maquina_2();


void loop(){

 
  radio.startListening();              // ler informaçoes do outro pipe 
  servidor();
  Receber();
  Maquina_1();
  Maquina_2();
  if (digitalRead(reset) == 0){
  Resetar();
  }
  delay(200);

}
 


void Receber() {


  while(radio.available()) { //verifica se a conexão esta habilitada
    Serial.println("conexao ativa");
    radio.read(&teste, sizeof(teste));
    radio.flush_rx(); 
  }
  
  delay(10);

}


void checagem() {

  Serial.println("");
  Serial.println("Verificação de envio: ");
  if (check == 1) {
    Serial.println("Enviado.");
  } else {
    Serial.println("Negado.");

  }
  Serial.println("");

}
