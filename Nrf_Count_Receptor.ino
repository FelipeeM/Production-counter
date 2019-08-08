#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
boolean button_state = 0;
int led_pin = 3;
int contagem;
void setup() {
pinMode(6, OUTPUT);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver
}
void loop()
{
  // Serial.print("Antes do if principal");
   //Serial.print("\n");
if (radio.available())              //Looking for the data.
{
                //Saving the incoming data
radio.read(&contagem, sizeof(int));    //Reading the data

Serial.println(contagem);

delay(1000);
}


}
