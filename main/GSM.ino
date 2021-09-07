void GetStatusOfGSM() {
  serialGSM.listen(); //só pode escutar uma serial por vez por isso essa função
  unsigned long delayGSM = millis();

  while ((millis() - delayGSM) < 1000) {
    leGSM();

    if (comandoGSM != "") {
      Serial.println(comandoGSM);
      ultimoGSM = comandoGSM;
      comandoGSM = "";
    }

    if (temSMS) {

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

      mensagemSMS.trim();
      if (mensagemSMS == senhaGsm) {
        Serial.println("Enviando SMS de Resposta.");

        float flat, flon;
        unsigned long age;

      }
      temSMS = false;
    }

    break;
  }
}

void leGSM() {
  static String textoRec = "";
  static unsigned long delay1 = 0;
  static int count = 0;
  static unsigned char buffer[64];

  serialGSM.listen();
  
  if (serialGSM.available()) {

    while (serialGSM.available()) {
      buffer[count++] = serialGSM.read();
      if (count == 64) break;
    }

    textoRec += (char * ) buffer;
    delay1 = millis();

    for (int i = 0; i < count; i++) {
      buffer[i] = NULL;
    }
    count = 0;
  }

  if (((millis() - delay1) > 100) && textoRec != "") {

    if (textoRec.substring(2, 7) == "+CMT:") {
      temSMS = true;
    }

    if (temSMS) {

      telefoneSMS = "";
      dataHoraSMS = "";
      mensagemSMS = "";

      byte linha = 0;
      byte aspas = 0;
      for (int nL = 1; nL < textoRec.length(); nL++) {

        if (textoRec.charAt(nL) == '"') {
          aspas++;
          continue;
        }

        if ((linha == 1) && (aspas == 1)) {
          telefoneSMS += textoRec.charAt(nL);
        }

        if ((linha == 1) && (aspas == 5)) {
          dataHoraSMS += textoRec.charAt(nL);
        }

        if (linha == 2) {
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