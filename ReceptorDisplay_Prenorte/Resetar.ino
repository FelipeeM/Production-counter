void resetar()
{
  //nao mexer na ordem 
//  resetar_In();
  if (digitalRead(reset_Pin) == 0){
  Resetar_Out();
  }  
}

void Resetar_Out()
{  
        
        radio.stopListening(); // parar de ouvir para enviar informaçoes   
              
        Serial.println("Envio resetar");
          pack_envio.reset = 1;
          checagem(radio.write(&pack_envio, sizeof(pack_envio)));    
          pack_envio.reset = 0;
         
         lcd.setCursor(0,0);  
         lcd.print("Maquina 1: "); 
         lcd.println(pack_envio.contagem_M1);

         lcd.setCursor(0,1);  
         lcd.print("Maquina 2: ");
         lcd.println(pack_envio.contagem_M2);

          
         zerarContagem();
         
}
void resetar_In()
{
  radio.stopListening();
  while (radio.available()) {
  Serial.println("----------Dentro de Reset----------");
  radio.read(&pack_envio, sizeof(pack_envio));

  if (pack_envio.reset == 1) {

      pack_envio.contagem_M1 = 0;
      pack_envio.contagem_M2 = 0;
    
      pack_envio.reset = 0;
  }
 }
}

void zerarContagem()
{
  
        pack_envio.contagem_M1 = 0;
        pack_envio.contagem_M2 = 0;
          check_M1 = 0;
          check_M2 = 0;
          
          displayReset();
          
  }
