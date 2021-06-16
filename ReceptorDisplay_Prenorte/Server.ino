

String readString = String(30); //VARIÁVEL PARA BUSCAR DADOS NO ENDEREÇO (URL)
int status = 0; //DECLARAÇÃO DE VARIÁVEL DO TIPO INTEIRA(SERÁ RESPONSÁVEL POR VERIFICAR O STATUS ATUAL DO LED)

void servidor() {

  EthernetClient client = server.available(); //CRIA UMA CONEXÃO COM O CLIENTE
  if (client) { // SE EXISTE CLIENTE FAZ
    if (client.connected()) {//ENQUANTO EXISTIR CLIENTE CONECTADO, FAZ
      if (client.available()) { //SE O CLIENTE ESTÁ HABILITADO, FAZ
        char c = client.read(); //LÊ CARACTER A CARACTER DA REQUISIÇÃO HTTP
        if (readString.length() < 100) //SE O ARRAY FOR MENOR QUE 100, FAZ
        {
          readString += c; // "readstring" VAI RECEBER OS CARACTERES LIDO
        }
        if (c == '\n') { //SE ENCONTRAR "\n" É O FINAL DO CABEÇALHO DA REQUISIÇÃO HTTP, FAZ
            if (readString.indexOf("?") < 0) { //SE ENCONTRAR O CARACTER "?", FAZ
            }
//             else //SENÃO, FAZ
//            if (readString.indexOf("zerar=1") > 0) { //SE ENCONTRAR O PARÂMETRO "ledParam=1", FAZ       
//                Resetar();
//                status = 1;
//                
//            } else { //SENÃO, FAZ
//              status = 0; //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ DESLIGADO)
//            }
             
          client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
          client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
          client.println("Refresh: 5");//TEMPO DE ATUALIZACAO DA PAGINA
          client.println();
                 
         //----------------------------------------------------------------------------------------------
          client.println("<head><title>Projeto</title></head>"); //DEFINE A COR DE FUNDO DA PÁGINA
          client.println("<body style=background-color:#ADD8E6>"); //DEFINE A COR DE FUNDO DA PÁGINA
          client.println("<center><font color='blue'><h1>PRENORTE 1.0</font></center></h1>"); //ESCREVE "PRENORTE 1.0" NA PÁGINA
        //----------------------------------------------------------------------------------------------
          client.println("<h1><Center>Maquina 1 // Maquina 2</Center></h1>"); 
          client.println("<h2><Center>");
          client.println(pack_envio.contagem_M1);
          client.println("//"); 
          client.println(pack_envio.contagem_M2);
          client.println("</Center></h2>");
          client.println("<h1><Center>Silo 1 // Silo 2</Center></h1>");
          client.println("<h2><Center>");
          client.println(pack_envio.silo_1);
          client.println("//");
          client.println(pack_envio.silo_2);
          client.println("</Center></h2>");
        //----------------------------------------------------------------------------------------------  
//          client.println("<center><a href=\"/?zerar\">Zerar</a></center>");
//        if (status == 1) {
//            client.println("<center><form method=get name=RESET><input type=hidden name=zerar value=0 /><input type=submit value=Zerar></form></center>");
//
//          }else{
//
//            client.println("<center><form method=get name=RESET><input type=hidden name=zerar value=1/><input type=submit value=Zerar></form></center>");
//            };

        //----------------------------------------------------------------------------------------------  
          client.println("<hr />"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("<hr />"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("</body></html>"); //FINALIZA A TAG "body" E "html"
          readString = ""; //A VARIÁVEL É REINICIALIZADA
          client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
          
//          if(readString.indexOf("?zerar") > 0)
//          {
//            displayReset();
//          }else{
//            
//            }
//          readString="";

        }
      }
    }
  }
}
