void Maquina_1() 
{
  if (pack_envio.contagem_M1 > check_M1)
  {
    

    lcd.setCursor(0, 0);
    lcd.print("Maquina 1: ");
    lcd.println(pack_envio.contagem_M1);
    lcd.print("     ");
    Serial.println(" ");
    Serial.println("Maquina 1");
    Serial.print("Numero de ciclos: ");
    Serial.println(pack_envio.contagem_M1);
    Serial.println(" ");
    
//     Serial.println("-----Silos-----");
//     Serial.println(pack_envio.silo_2);
//     Serial.println(pack_envio.silo_1);
     
    
    check_M1 = pack_envio.contagem_M1;

  }

}

void Maquina_2() 
{
  if (pack_envio.contagem_M2 > check_M2)
  {
    lcd.setCursor(0, 1);
    lcd.print("Maquina 2: ");
    lcd.println(pack_envio.contagem_M2);
    // lcd.print("     ");
    Serial.println(" ");
    Serial.println("Maquina 2");
    Serial.print("Numero de ciclos: ");
    Serial.println(pack_envio.contagem_M2);
    Serial.println(" ");

//     Serial.println("-----Silos-----");
//     Serial.println(pack_envio.silo_1);
//     Serial.println(pack_envio.silo_2);
      
    check_M2 = pack_envio.contagem_M2;

  }

}
