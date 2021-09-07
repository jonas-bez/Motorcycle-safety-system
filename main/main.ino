#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serialGPS(26, 25); // RX, TX
SoftwareSerial serialGSM(10, 11);

TinyGPS gps1;


bool temSMS = false;
String telefoneSMS;
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";

#define senhaGsm "1234"


void setup() {
  serialGPS.begin(9600);
  serialGSM.begin(9600); 
  Serial.begin(9600);
}

void loop() {

  GetStatusOfGPS();
  GetStatusOfGSM();

}

