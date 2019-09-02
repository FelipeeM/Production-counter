

int ledPin = 8; //PINO DIGITAL UTILIZADO PELO LED
String readString = String(30); //VARIÁVEL PARA BUSCAR DADOS NO ENDEREÇO (URL)
int status = 0; //DECLARAÇÃO DE VARIÁVEL DO TIPO INTEIRA(SERÁ RESPONSÁVEL POR VERIFICAR O STATUS ATUAL DO LED)

void servidor() {
  EthernetClient client = server.available(); //CRIA UMA CONEXÃO COM O CLIENTE
  if (client) { // SE EXISTE CLIENTE FAZ
    while (client.connected()) {//ENQUANTO EXISTIR CLIENTE CONECTADO, FAZ
      if (client.available()) { //SE O CLIENTE ESTÁ HABILITADO, FAZ
        char c = client.read(); //LÊ CARACTER A CARACTER DA REQUISIÇÃO HTTP
        if (readString.length() < 100) //SE O ARRAY FOR MENOR QUE 100, FAZ
        {
          readString += c; // "readstring" VAI RECEBER OS CARACTERES LIDO
        }
        if (c == '\n') { //SE ENCONTRAR "\n" É O FINAL DO CABEÇALHO DA REQUISIÇÃO HTTP, FAZ
          if (readString.indexOf("?") < 0) { //SE ENCONTRAR O CARACTER "?", FAZ
          }
          else //SENÃO, FAZ
            if (readString.indexOf("ledParam=1") > 0) { //SE ENCONTRAR O PARÂMETRO "ledParam=1", FAZ
              digitalWrite(ledPin, HIGH); //LIGA O LED
              status = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ LIGADO)
            } else { //SENÃO, FAZ
              digitalWrite(ledPin, LOW); //DESLIGA O LED
              status = 0; //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ DESLIGADO)
            }
          client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
          client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
          client.println();
          
          //AS LINHAS ABAIXO CRIAM A PÁGINA HTML
          client.println("<body style=background-color:#ADD8E6>"); //DEFINE A COR DE FUNDO DA PÁGINA
          client.println("<center><font color='blue'><h1>PRENORTE 1.0</font></center></h1>"); //ESCREVE "PRENORTE 1.0" NA PÁGINA
        
          client.println("<h1><Leftr>Maquina 1</center></h1>"); //ESCREVE "MAQUINA 1" NA PÁGINA
          client.println("<h2><Left>N de ciclos: C</center></h2>"); //ESCREVE "MAQUINA 1" NA PÁGINA

          client.println("<h1><Left>Maquina 2</center></h1>"); //ESCREVE "MAQUINA 2" NA PÁGINA
          client.println("<h2><Left>N de ciclos: C </center></h2>"); //ESCREVE "MAQUINA 1" NA PÁGINA
         
          
          
          client.println("<center><font size='5'>Portao principal</center>");
          if (status == 1) { //SE VARIÁVEL FOR IGUAL A 1, FAZ
            //A LINHA ABAIXO CRIA UM FORMULÁRIO CONTENDO UMA ENTRADA INVISÍVEL(hidden) COM O PARÂMETRO DA URL E CRIA UM BOTÃO APAGAR (CASO O LED ESTEJA LIGADO)
            client.println("<center><form method=get name=LED><input type=hidden name=ledParam value=0 /><input type=submit value=FECHAR></form></center>");
          } else { //SENÃO, FAZ
            //A LINHA ABAIXO CRIA UM FORMULÁRIO CONTENDO UMA ENTRADA INVISÍVEL(hidden) COM O PARÂMETRO DA URL E CRIA UM BOTÃO ACENDER (CASO O LED ESTEJA DESLIGADO)
            client.println("<center><form method=get name=LED><input type=hidden name=ledParam value=1 /><input type=submit value=ABRIR></form></center>");
          }
          
          if (status == 1) { //SE VARIÁVEL FOR IGUAL A 1, FAZ
            client.println("<center><font color='green' size='5'>ABERTO</center>"); //ESCREVE "LIGADO" EM COR VERDE NA PÁGINA
          } else { //SENÃO, FAZ
            client.println("<center><font color='red' size='5'>FECHADO</center>"); //ESCREVE "DESLIGADO" EM COR VERMELHA NA PÁGINA
          }
          client.println("<hr />"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("<hr />"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("</body></html>"); //FINALIZA A TAG "body" E "html"
          readString = ""; //A VARIÁVEL É REINICIALIZADA
          client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
        }
      }
    }
  }
}
