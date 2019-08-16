#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN

char Nivel_silo_1;
char Nivel_silo_2;

const byte address[][6] = {"00001", "00002"};
boolean reset = 0;
boolean alterado_1 = false;
boolean alterado_2 = false;

int check;

//Sensor IR
const int Sensor_1 = 3; //PINO DIGITAL UTILIZADO PELO SENSOR 1
const int Sensor_2 = 4; //PINO DIGITAL UTILIZADO PELO SENSOR 2
const int Sensor_3 = 5; //PINO DIGITAL UTILIZADO PELO SENSOR 3
const int Sensor_11 = 6; //PINO DIGITAL UTILIZADO PELO SENSOR 11
const int Sensor_22 = 7; //PINO DIGITAL UTILIZADO PELO SENSOR 22
const int Sensor_33 = 8; //PINO DIGITAL UTILIZADO PELO SENSOR 33

//count production
const int Sinal_1 = 2;
const int Sinal_2 = 3;
int contagem_M1;
int contagem_M2;


int enviar;

void setup() {
  //radio
  radio.begin();                  //Starting the Wireless communication

  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);   //Setting the address at which we will receive the data

  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

  //radio.startListening();

  Serial.begin(9600);

  pinMode(Sinal_1, OUTPUT);
  digitalWrite(Sinal_1, HIGH);

  pinMode(Sinal_2, OUTPUT);
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
 // Resetar();
  //Silo1();
  //Silo2();
  Transmissao();

  delay(500);

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
    alterado_2 = true;
  }
}

void checagem();
////////////////////////////////////////////////////////////////////////---Transmissão
void Transmissao() {

  if (alterado_1 == true) {
    Serial.print("entrou no if trasnmissao 1 : ");
    check = radio.write(&contagem_M1, sizeof(int));
    checagem();

    alterado_1 = false;

  }

  if (alterado_2 == true) {
    Serial.print("entrou no if trasnmissao 2 : ");
    check = radio.write(&contagem_M2, sizeof(int));
    checagem();

    alterado_2 = false;

  }

}

void Resetar() {

  radio.startListening();

  while (radio.available()) { //verifica se a conexão esta habilitada


    Serial.println("dentro de reset");
    radio.read(&reset, sizeof(int));
    if (digitalRead(reset) == 0) {

      Serial.print("Reset");
      contagem_M1 = 0;
      contagem_M2 = 0;

    }
  }
  radio.stopListening();

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
