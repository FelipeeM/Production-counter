void Maquina_1() 
{
  if (teste.contagem_M1 > check_M1)
  {

    lcd.setCursor(0, 0);
    lcd.print("Maquina 1: ");
    lcd.println(teste.contagem_M1);
    lcd.print("     ");
    Serial.println(" ");
    Serial.println("Maquina 1");
    Serial.print("Numero de ciclos: ");
    Serial.println(teste.contagem_M1);
    Serial.println(" ");

    check_M1 = teste.contagem_M1;

  }

}

void Maquina_2() 
{
  if (teste.contagem_M2 > check_M2)
  {
    lcd.setCursor(0, 1);
    lcd.print("Maquina 2: ");
    lcd.println(teste.contagem_M2);
    // lcd.print("     ");
    Serial.println(" ");
    Serial.println("Maquina 2");
    Serial.print("Numero de ciclos: ");
    Serial.println(teste.contagem_M2);
    Serial.println(" ");

    check_M2 = teste.contagem_M2;

  }

}
