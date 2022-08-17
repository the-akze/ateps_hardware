//#include <SoftwareSerial.h>
//#define rxPin 2
//#define txPin 3
//#define baudrate 38400
//String msg;
//SoftwareSerial hc05(rxPin ,txPin);
//
//void setup(){
//  pinMode(53, OUTPUT);
//  digitalWrite(53, HIGH);
//  delay(1000);
//  pinMode(rxPin,INPUT);
//  pinMode(txPin,OUTPUT);
//  Serial.begin(9600);
//  Serial.println("ENTER AT Commands:");
//  hc05.begin(baudrate);
//}
//
//void loop(){
//  readSerialPort();
//  if(msg!="") hc05.println(msg);
//  if (hc05.available()>0){
//    Serial.write(hc05.read());
//  }
//}
//
//void readSerialPort(){
//  msg="";
//  while (Serial.available()) {
//    delay(10);
//    if (Serial.available() >0) {
//      char c = Serial.read();  //gets one byte from serial buffer
//      msg += c; //makes the string readString
//    }
//  }
//}

#include <SoftwareSerial.h>

SoftwareSerial ArduinoMaster(2,3);
String msg;

void setup(){
  Serial.begin(9600);
  ArduinoMaster.begin(9600);
  ArduinoMaster.print("TEST");
}

void loop(){
  readSerialPort();
  
  // Send answer to master
  if(msg!=""){
    Serial.print("Master sent : ");
    Serial.println(msg);
//    if (msg == "Connection"){
      ArduinoMaster.print("Student1");
//    }
    msg=""; 
  }
}

void readSerialPort(){
 while (ArduinoMaster.available()) {
   delay(10); 
   if (ArduinoMaster.available() >0) {
     char c = ArduinoMaster.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
   }
 }
 ArduinoMaster.flush();
}
