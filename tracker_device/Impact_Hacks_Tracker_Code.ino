#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

#include <Stepper.h>
const int stepsPerRevolution = 2048;
// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver
// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  // Print a message on both lines of the LCD.
//  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
//  lcd.print("Hello world!");
//  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
//  lcd.print("LCD Tutorial");

  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
  Serial1.begin(9600);
//  lock();
  Serial.println("0");

//  pinMode(22, OUTPUT);
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("ID Required");
}

boolean locked = true;
String answer;
String msg;

void loop() {

  Serial1.print("Connection");
//  Serial.println("Attempt");
  delay(500);
  //Read answer from slave
   while (Serial1.available()) {
   delay(10);
   if (Serial1.available() >0) {
     char c = Serial1.read();  //gets one byte from serial buffer
     answer += c; //makes the string readString
   }
 }
 //Send answer to monitor
  if(answer!=""){
//    Serial.print("Slave recieved : ");
//    Serial.println(answer);
    if (answer.indexOf("Student1")>-1 && locked == true){
      Serial.println("Student1");
      unlock();
      locked = false;
    }
    answer="";
  } else if (locked == false){
//    Serial.println("0");
    lock();
    locked = true;
  }
  
//  if(Serial.available() > 0)  
//  {
//    String id = Serial.readString();      //Read the incoming data and store it into variable Incoming_value
//    Serial.print(id);        //Print Value of Incoming_value in Serial monitor
//    Serial.print("\n");        //New line
//    if (locked){
//      unlock();
//      locked = false;
//    }
//    delay(5000);
//  } else if (locked == false) {
//    lock();
//    locked = true;
//  }
}

void lock() {
//  digitalWrite(22, HIGH);
  lcd.clear();
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Locking...");
  
  // Rotate CW slowly at 5 RPM
  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution*-1/4);
  
  lcd.clear();
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("ID Required");

//  for(int i=0;i<80;i++)
//  {
//    digitalWrite(22,HIGH);
//    delay(5);//wait for 1ms
//    digitalWrite(22,LOW);
//    delay(5);//wait for 1ms
//  }
//  delay(1000);
//  digitalWrite(22, HIGH);
//  delay(1000);
//  digitalWrite(22, LOW);
}

void unlock() {
  lcd.clear();
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Unlocking...");
  
  // Rotate CCW quickly at 10 RPM
  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution/4);
  
  lcd.clear();
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Please Enter");
}

// -----------------------------------------------------------------------------------------------

////#include <SoftwareSerial.h>
////
////SoftwareSerial ArduinoSlave(2,3);
//String answer;
//String msg;
//
//void setup(){
//
//  Serial.begin(9600);
//  Serial.println("ENTER Commands:");
//  ArduinoSlave.begin(9600);
////  ArduinoSlave.print("TEST FROM HERE");
//}
//
//void loop(){
//  //Read command from monitor
////  readSerialPort();
//  Serial1.print("Connection");
//  //Read answer from slave
//   while (Serial1.available()) {
//   delay(10);
//   if (ArduinoSlave.available() >0) {
//     char c = ArduinoSlave.read();  //gets one byte from serial buffer
//     answer += c; //makes the string readString
//   }
// }
// //Send answer to monitor
//  if(answer!=""){
//    Serial.print("Slave recieved : ");
//    Serial.println(answer);
//    answer="";
//  }
//// if (answer == "Student1"){
////  delay(5000);
//// }
// Serial.println("Student1");
// ArduinoSlave.print("Student1");
// delay(200);
//  //Send data to slave
////  if(msg!=""){
////    Serial.print("Master sent : ");
////    Serial.println(msg);
////    ArduinoSlave.print(msg);
////    msg="";
////  }
//}
//
//void readSerialPort(){
// while (Serial.available()) {
//   delay(10);  
//   if (Serial.available() >0) {
//     char c = Serial.read();  //gets one byte from serial buffer
//     msg += c; //makes the string readString
//   }
// }
// Serial.flush();
//}
