#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serialGPS(35, 32); // RX, TX
//SoftwareSerial serialGSM(34, 35); // RX, TX

TinyGPS gps1;

bool temSMS = false;
String telefoneSMS;
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";

#define getGps "123"
#define setReleEnabled "456"
#define setReleDisabled "789"
#define pinBotaoCall 12
#define numeroCall "999834459" 


void setup() {
  serialGPS.begin(9600);
//  serialGSM.begin(9600); 
  Serial.begin(9600);
//  pinMode(pinBotaoCall, INPUT_PULLUP);
  Serial.println("Sketch Iniciado!");
//  serialGSM.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 

}

void loop() {

GetStatusOfGPS();
//  GetStatusOfGSM();

}
