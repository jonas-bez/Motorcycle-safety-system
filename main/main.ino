#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serialGSM(27, 26); // RX, TX
SoftwareSerial serialGPS(35, 32); // RX, TX

TinyGPS gps1;
String message = "INITIALIZING";

#define getGps "123"
#define setReleEnabled "456"
#define setReleDisabled "789"

bool temSMS = false;
String telefoneSMS;
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";


void setup() {
  serialGSM.begin(9600); 
  serialGPS.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  configuraGSM();
  Serial.println("SECURITY SYSTEM STARTED!");
  Serial.println(mensagemSMS);
}

void loop() {  
  unsigned long delayGPS = millis();
  while ((millis() - delayGPS) < 500) {
    GetStatusOfGPS();
  }

  unsigned long delayGSM = millis();
  while ((millis() - delayGSM) < 500) {
    GetStatusOfGSM();
  }
}
