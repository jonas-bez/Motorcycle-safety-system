void GetStatusOfGSM(){
  leGSM();

  if (comandoGSM != "") {
      Serial.println(comandoGSM);
      ultimoGSM = comandoGSM;
      comandoGSM = "";
  }
  
  if (temSMS) {      
     mensagemSMS.trim();

     Serial.println("Chegou Mensagem!!");
     Serial.println();
    
     Serial.print("Remetente: ");  
     Serial.println(telefoneSMS);
     Serial.println();
    
     Serial.print("Data/Hora: ");  
     Serial.println(dataHoraSMS);
     Serial.println();
    
     Serial.println("Mensagem:");  
     Serial.println(mensagemSMS);
     Serial.println();
     
     if (mensagemSMS == "123") {
       Serial.println("Chegou Mensagem 123");
       Serial.println("ENVIANDO Mensagem ");
       Serial.println(message);
       enviaSMS(telefoneSMS, message);
     } else if (mensagemSMS == "456") {
       Serial.println("Chegou Mensagem 456");
       enviaSMS(telefoneSMS, "SMS Recebido e Senha 456");
     } else if (mensagemSMS == "789") {
       Serial.println("Chegou Mensagem 789");
       enviaSMS(telefoneSMS, "SMS Recebido e Senha 789");
     } else {
       Serial.println("codigo incorreto");
       enviaSMS(telefoneSMS, "codigo incorreto");
     }
          
     temSMS = false;
  }
}

void leGSM()
{
  static String textoRec = "";
  static unsigned long delay1 = 0;
  static int count=0;  
  static unsigned char buffer[64];

  if (serialGSM.available()) {            
 
     while(serialGSM.available()) {         
   
        buffer[count++] = serialGSM.read();     
        if(count == 64)break;
     }

     textoRec += (char*)buffer;
     delay1   = millis();
     
     for (int i=0; i<count; i++) {
         buffer[i]=NULL;
     } 
     count = 0;                       
  }


  if ( ((millis() - delay1) > 100) && textoRec != "" ) {

     if ( textoRec.substring(2,7) == "+CMT:" ) {
        temSMS = true;
     }

     if (temSMS) {
            
        telefoneSMS = "";
        dataHoraSMS = "";
        mensagemSMS = "";

        byte linha = 0;  
        byte aspas = 0;
        for (int nL=1; nL < textoRec.length(); nL++) {

            if (textoRec.charAt(nL) == '"') {
               aspas++;
               continue;
            }                        
          
            if ( (linha == 1) && (aspas == 1) ) {
               telefoneSMS += textoRec.charAt(nL);
            }

            if ( (linha == 1) && (aspas == 5) ) {
               dataHoraSMS += textoRec.charAt(nL);
            }

            if ( linha == 2 ) {
               mensagemSMS += textoRec.charAt(nL);
            }

            if (textoRec.substring(nL - 1, nL + 1) == "\r\n") {
               linha++;
            }
        }
     } else {
       comandoGSM = textoRec;
     }
     
     textoRec = "";  
  }     
}


void enviaSMS(String telefone, String mensagem) {
  serialGSM.print("AT+CMGS=\"" + telefone + "\"\n");
  serialGSM.print(mensagem + "\n");
  serialGSM.print((char)26); 
}

void configuraGSM() {
   serialGSM.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 
}
