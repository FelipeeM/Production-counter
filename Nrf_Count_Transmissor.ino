#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN

char Nivel_silo_1;
char Nivel_silo_2;

const byte address[6] = "00001";
boolean button_state = 0;
int check;

//Sensor IR
const int Sensor_1 = 3; //PINO DIGITAL UTILIZADO PELO SENSOR 1
const int Sensor_2 = 4; //PINO DIGITAL UTILIZADO PELO SENSOR 2
const int Sensor_3 = 5; //PINO DIGITAL UTILIZADO PELO SENSOR 3
const int Sensor_11 = 6; //PINO DIGITAL UTILIZADO PELO SENSOR 11
const int Sensor_22 = 7; //PINO DIGITAL UTILIZADO PELO SENSOR 22
const int Sensor_33 = 8; //PINO DIGITAL UTILIZADO PELO SENSOR 33

//count production
const int Sinal = 2;
int contagem;
int enviar;

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
////////////////////////////////////////////////////////////////////////---LOOP
void loop() {

  Count();
  Silo1();
  Silo2();
  Transmissao();

  delay(500);

}
////////////////////////////////////////////////////////////////////////---Count
void Count() {

  if (digitalRead(Sinal) == 0) {
    contagem ++;

    while (digitalRead(Sinal) == 0) {
      Serial.print(contagem);
      Serial.print("\n");
      delay(10);

    }
  }
}
////////////////////////////////////////////////////////////////////////---Transmissão
void Transmissao() {

  check = radio.write(&contagem, sizeof(int));
  checagem();
  check = radio.write(&Nivel_silo_1, sizeof(char));
  checagem();
  check = radio.write(&Nivel_silo_1, sizeof(char));
  checagem();

}
////////////////////////////////////////////////////////////////////////---Checagem
void checagem() {

  Serial.println("");
  Serial.println("Verificação de envio: ");
  if (check == 1) {
    Serial.println("Enviado.");
  } else {
    Serial.println("Negado.");
    while (check == 0) {
      check = radio.write(&contagem, sizeof(int));
      Serial.println("");
      Serial.println("reenvio");
      delay(100);
    }

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
