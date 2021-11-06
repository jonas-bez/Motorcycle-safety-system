void GetStatusOfGPS() {
  bool recebido = false;
  String message = "";

  while (serialGPS.available()) {
    char cIn = serialGPS.read();
    recebido = gps1.encode(cIn);
  }

  if (recebido) {
    message += ("----------------------------------------");
    unsigned long idadeInfo;
    float latitude, longitude;

    gps1.f_get_position( & latitude, & longitude, & idadeInfo);

    message = getLocalization(message, latitude, longitude, idadeInfo);
    message = getDateTime(message, idadeInfo);
    message = getHeight(message);
    message = getSpeed(message);
    message = getDirection(message);
    message = getPrecision(message);

    Serial.println(message);
  }
}
  String getLocalization(String message, float latitude, float longitude, long idadeInfo) {
  if ((latitude != TinyGPS::GPS_INVALID_F_ANGLE) && (longitude != TinyGPS::GPS_INVALID_F_ANGLE)) {
    message += "\n";
    message += ("Link para Google Maps:   https://maps.google.com/maps/?&z=10&q=");
    message += String(latitude, 6);
    message += ",";
    message += String(longitude, 6);
  }

  if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
    message += "\n";
    message += ("Latitude: ");
    message += String(latitude, 6);
  }

  if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
    message += "\n";
    message += String("Longitude: ");
    message += String(longitude, 6);
  }

  if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
    message += "\n";
    message += ("Idade da Informacao (ms): ");
    message += (idadeInfo);
  }
  return message;
}

String getDateTime(String message, unsigned long idadeInfo) {
  int ano;
  byte mes, dia, hora, minuto, segundo, centesimo;
  gps1.crack_datetime( & ano, & mes, & dia, & hora, & minuto, & segundo, & centesimo, & idadeInfo);
  //data
  message += "\n";
  message += "Data (GMT): ";
  message += String(dia);
  message += "/";
  message += String(mes);
  message += "/";
  message += String(ano);

  //Hora
  message += "\n";
  message += "Horario (GMT): ";
  message += String(hora - 3);
  message += ":";
  message += String(minuto);
  message += ":";
  message += String(segundo);
  message += ":";
  message += String(centesimo);

  return message;
}

String getHeight(String message) {
  float altitudeGPS;
  altitudeGPS = gps1.f_altitude();
  if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
    message += "\n";
    message += "Altitude (cm): ";
    message += String(altitudeGPS);
  }
  return message;
}

String getSpeed(String message) {

  float velocidade;
  velocidade = gps1.f_speed_kmph(); //km/h

  message += "\n";
  message += "Velocidade (km/h): ";
  message += String(velocidade, 2); //Conversão de Nós para Km/h
  return message;
}

String getDirection(String message) {
  unsigned long sentido;
  sentido = gps1.course();

  message += "\n";
  message += "Sentido (grau): ";
  message += String(float(sentido) / 100, 2);
  return message;
}

String getPrecision(String message) {
  unsigned short satelites;
  unsigned long precisao;
  satelites = gps1.satellites();
  precisao = gps1.hdop();

  if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
    message += "\n";
    message += "Satelites: ";
    message += String(satelites);
  }

  if (precisao != TinyGPS::GPS_INVALID_HDOP) {
    message += "\n";
    message += "Precisao (centesimos de segundo): ";
    message += String(precisao);
  }
  return message;
}
