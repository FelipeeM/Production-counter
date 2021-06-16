

void Silos()
{
   valor_s1 = digitalRead(sensor1);
   valor_s2 = digitalRead(sensor2);
   valor_s3 = digitalRead(sensor3);

   valor_s11 = digitalRead(sensor11);
   valor_s22 = digitalRead(sensor22);
   valor_s33 = digitalRead(sensor33);
  
  //---------------------------Silo_1------------------------------
  if ((valor_s1 == 0) && valor_s2 == 0 && valor_s3 == 0) {
    strcpy(pack_envio.silo_1, "Nivel Alto");             //Função para adicionar valor a uma string 
  } if ((valor_s1 == 0) && valor_s2 == 0 && valor_s3 == 1) {
    strcpy(pack_envio.silo_1, "Nivel Medio");
  } if ((valor_s1 == 0) && valor_s2 == 1 && valor_s3 == 1) {
    strcpy(pack_envio.silo_1, "Nivel Baixo");
  }if ((valor_s1 == 1) && valor_s2 == 1 && valor_s3 == 1) {
    strcpy(pack_envio.silo_1, "Nivel Critico");
  }
  //----------------------------Silo_2-----------------------------

  if ((valor_s11 == 0) && valor_s22 == 0 && valor_s33 == 0) {
     strcpy(pack_envio.silo_2, "Nivel Alto");              //Função para adicionar valor a uma string
  } if ((valor_s11 == 0) && valor_s22 == 0 && valor_s33 == 1) {
    strcpy(pack_envio.silo_2, "Nivel Medio");
  } if ((valor_s11 == 0) && valor_s22 == 1 && valor_s33 == 1) {
    strcpy(pack_envio.silo_2, "Nivel Baixo");
  }if ((valor_s11 == 1) && valor_s22 == 1 && valor_s33 == 1) {
    strcpy(pack_envio.silo_2, "Nivel Critico");
  }

}
