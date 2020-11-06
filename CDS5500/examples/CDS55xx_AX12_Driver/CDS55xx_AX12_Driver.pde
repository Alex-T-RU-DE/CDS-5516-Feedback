#include <CDS5500.h>

CDS5500 SERVO;

void setup(){
  Serial.begin(1000000);//init Serial baudrate
}

void loop(){
  int i;
//  for(i = 0;i < 1024; i++){
//    SERVO.WritePos(1,i,0x03FF);
//    delay(10);
//  }
//  for(int i = 1024; i > 0; i--){
//    SERVO.WritePos(1,i,0x03FF);
//    delay(10);
//  }

  SERVO.WritePos(1,0x02FF,0x01FF);// Servo ID:1, rotate to the position:0x2FF, rotate speed:0x1FF
  delay(1000);
  SERVO.WritePos(1,0x0000,0x01FF);// Servo ID:1, rotate to the position:0x000, rotate speed:0x1FF
  delay(1000);
  
}
