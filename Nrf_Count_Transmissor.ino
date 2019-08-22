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
int check;

//Sensor IR
const int Sensor_1 = 20; //PINO DIGITAL UTILIZADO PELO SENSOR 1
const int Sensor_2 = 21; //PINO DIGITAL UTILIZADO PELO SENSOR 2
const int Sensor_3 = 22; //PINO DIGITAL UTILIZADO PELO SENSOR 3
const int Sensor_11 = 23; //PINO DIGITAL UTILIZADO PELO SENSOR 11
const int Sensor_22 = 24; //PINO DIGITAL UTILIZADO PELO SENSOR 22
const int Sensor_33 = 25; //PINO DIGITAL UTILIZADO PELO SENSOR 33

//count production
const int Sinal_1 = 2;
const int Sinal_2 = 3;
int contagem_M1;
int contagem_M2;
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
  
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

  //radio.startListening();

  Serial.begin(9600);

  pinMode(Sinal_1,INPUT_PULLUP);
  digitalWrite(Sinal_1, HIGH);

  pinMode(Sinal_2,INPUT_PULLUP);
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
    contagem_M1 ++;

    while (digitalRead(Sinal_1) == 0) {
      Serial.print("Coont M1: ");
      Serial.println(contagem_M1);

      delay(10);

    }
    alterado_1 = true;
  }

}

void Count_2() {

  if (digitalRead(Sinal_2) == 0) { // verifica se o sinal de contagem do ciclo foi ativado
    contagem_M2 ++;

    while (digitalRead(Sinal_2) == 0) {
      Serial.print("Coont M2: ");
      Serial.println(contagem_M2);

      delay(10);

    }
    alterado_1 = true;
  }
}

void checagem();
////////////////////////////////////////////////////////////////////////---Transmissão
void Transmissao() {

  
    //check = radio.write(&sinal_Transmissao, sizeof(int));
   //checagem();

  if (alterado_1 == true) {
    
   //for(x = 0; x <= 2; x ++ ){
    
    check = radio.write(&contagem_M1, sizeof(int));
    checagem();
    
    check = radio.write(&contagem_M2, sizeof(int));
    checagem();
    
   
   // }
    if (check == 0) {
        
       radio.begin();
                
    }
    
    alterado_1 = false;

     radio.flush_tx(); 
  }
}

void Resetar() {

    radio.startListening();
    radio.read(&x, sizeof(boolean));
 
    if (x == 1) {

      Serial.print("Reset");
      contagem_M1 = 0;
      contagem_M2 = 0;

    }
  


}
////////////////////////////////////////////////////////////////////////---Checagem
void checagem() {

  Serial.println("");
  Serial.println("Verificação de envio: ");
  if (check == 1) {
    Serial.println("Enviado.");
  } else {
    Serial.println("Negado.");
    //    while (check == 0) {
    //      check = radio.write(&contagem_M1, sizeof(int)); // tirar isso daqui
    //      Serial.println("");
    //      Serial.println("reenvio");
    //      delay(100);
    //    }

  }
  Serial.println("");

}
////////////////////////////////////////////////////////////////////////---Silo 1
void Silo1() {

  if ((digitalRead(Sensor_1) == LOW) && Sensor_2 == LOW && Sensor_3 == LOW)
  {
    Serial.println("Nivel critico");
    Nivel_silo_1 = "Nivel critico";
  }

  if ((digitalRead(Sensor_1) == HIGH) && Sensor_2 == LOW && Sensor_3 == LOW)
  {
    Serial.println("Nivel Baixo");
    Nivel_silo_1 = "Nivel Baixo";
  }

  if ((digitalRead(Sensor_1) == HIGH) && Sensor_2 == HIGH && Sensor_3 == LOW)
  {
    Serial.println("Nivel Medio");
    Nivel_silo_1 = "Nivel Medio";
  }

  if ((digitalRead(Sensor_1) == HIGH) && Sensor_2 == HIGH && Sensor_3 == HIGH)
  {
    Serial.println("Nivel Alto");
    Nivel_silo_1 = "Nivel Alto";
  } else {

    Serial.println("BUG 123");

  }

}

////////////////////////////////////////////////////////////////////////---Silo 2
void Silo2() {

  if ((digitalRead(Sensor_11) == LOW) && Sensor_22 == LOW && Sensor_33 == LOW)
  {
    Serial.println("Nivel critico");
    Nivel_silo_2 = "Nivel critico";
  }

  if ((digitalRead(Sensor_11) == HIGH) && Sensor_22 == LOW && Sensor_33 == LOW)
  {
    Serial.println("Nivel Baixo");
    Nivel_silo_2 = "Nivel Baixo";
  }

  if ((digitalRead(Sensor_11) == HIGH) && Sensor_22 == HIGH && Sensor_33 == LOW)
  {
    Serial.println("Nivel Medio");
    Nivel_silo_2 = "Nivel Medio";
  }

  if ((digitalRead(Sensor_11) == HIGH) && Sensor_22 == HIGH && Sensor_33 == HIGH)
  {
    Serial.println("Nivel Alto");
    Nivel_silo_2 = "Nivel Alto";
  } else {

    Serial.println("BUG 321");

  }

}
