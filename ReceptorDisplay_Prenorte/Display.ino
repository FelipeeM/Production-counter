

void displayInicio()
{

       lcd.clear();
       lcd.setCursor(3,0);  
       lcd.print("PRENORTE");
       lcd.setCursor(3,1);  
       lcd.print("Sistem 1.0");
       lcd.setBacklight(LOW);
       delay(500);
       lcd.setBacklight(HIGH); 
       delay(500);
       lcd.setBacklight(LOW);
       delay(500);
       lcd.setBacklight(HIGH);
       delay(500);
       lcd.setBacklight(LOW);
       lcd.setCursor(3,0);  
       lcd.print("Aguardando");
       lcd.setCursor(1,1);
       lcd.print("informacoes...");
       delay(500);
       lcd.setBacklight(HIGH);


   
}
void displayReset()
{

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Maquina 1: ");
    lcd.println(pack_envio.contagem_M1);
    lcd.setCursor(0, 1);
    lcd.print("Maquina 2: ");
    lcd.println(pack_envio.contagem_M2);
 
}

