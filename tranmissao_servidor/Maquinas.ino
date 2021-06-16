void Count_1() {

  if (digitalRead(Sinal_1) == 1) { // verifica se o sinal de contagem do ciclo foi ativado
    pack_envio.contagem_M1 ++;

    while (digitalRead(Sinal_1) == 1) {
      Serial.print("Coont M1: ");
      Serial.println(pack_envio.contagem_M1);
      if (digitalRead(Sinal_2) == 1 && digitalRead(Sinal_1) == 1 && alterado_1 == false ) {
        pack_envio.contagem_M2 ++;
        alterado_1 = true;
        Serial.print("2");
      }
      delay(10);

    }
    alterado_1 = true;
  }

}

void Count_2() {


  if (digitalRead(Sinal_2) == 1) { // verifica se o sinal de contagem do ciclo foi ativado
  pack_envio.contagem_M2 ++;

    while (digitalRead(Sinal_2) == 1) {
      Serial.print("Coont M2: ");
      Serial.println(pack_envio.contagem_M2);
      if (digitalRead(Sinal_2) == 1 && digitalRead(Sinal_1) == 1 && alterado_2 == false ) {
        pack_envio.contagem_M1 ++;
        alterado_2 = true;
        Serial.print("1");
      }

      delay(10);

    }
    alterado_1 = true;
  }


}
