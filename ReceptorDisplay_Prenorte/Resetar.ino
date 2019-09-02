void Resetar(){  
      
       digitalRead(reset);
       x = 1;
        Serial.println(x);
        radio.stopListening(); // parar de ouvir para enviar informaçoes

        Serial.println("Envio resetar");
        check = radio.write(&x, sizeof(boolean));
        checagem();
       
        

        teste.contagem_M1 = 0;
        teste.contagem_M2 = 0;
        check_M1 = 0;
        check_M2 = 0;
         Serial.println(teste.contagem_M1);
         lcd.setCursor(0,0);  
         lcd.print("Maquina 1: "); 
         lcd.println(teste.contagem_M1);

         lcd.setCursor(0,1);  
         lcd.print("Maquina 2: ");
         lcd.println(teste.contagem_M2);
}
