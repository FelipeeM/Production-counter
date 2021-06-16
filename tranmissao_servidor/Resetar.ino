void resetar()
{
  //nao mexer na ordem 
  resetar_In();
//  if (digitalRead(reset_Pin) == 0){
//  resetar_Out();
//  }
  
}

void resetar_In()
{
  radio.startListening();// receber informaçoes
  while (radio.available()) { // verifica a conexao
  Serial.println("----------Dentro de Reset----------");
  radio.read(&pack_envio, sizeof(pack_envio));

  if (pack_envio.reset == 1) {

    pack_envio.contagem_M1 = 0;
    pack_envio.contagem_M2 = 0;
    
    pack_envio.reset = 0;
  }
 }
}
void resetar_Out()
{
  radio.stopListening(); // parar de ouvir para enviar informaçoes
  pack_envio.reset = 1;
  checagem(radio.write(&pack_envio, sizeof(pack_envio)));    
  pack_envio.reset = 0;
  zerarContagem();
}
void zerarContagem()
{
        pack_envio.contagem_M1 = 0;
        pack_envio.contagem_M2 = 0;
      
  }
