#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serialGPS(35, 32); // RX, TX
SoftwareSerial serialGSM(27, 26); // RX, TX

TinyGPS gps1;

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
  serialGPS.begin(9600);
  serialGSM.begin(9600); 
  Serial.begin(9600);
  configuraGSM();

  Serial.println("Sketch Iniciado!");

}

void loop() {  

unsigned long delayGPS = millis();
while((millis() - delayGPS)< 1000){
  serialGPS.listen();
  GetStatusOfGPS();
}

unsigned long delayGSM = millis();
while((millis() - delayGSM)< 1000){
  serialGSM.listen();
  GetStatusOfGSM();
}

}
