#include <CDS5500.h>

CDS5500 SERVO;

void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000);
}

void loop() {
  Serial.print("\nPosition: ");
  Serial.print(SERVO.Get_Pos(1));
  Serial.print("\nTemperatue: ");
  Serial.print(SERVO.Get_Temp(1));
  Serial.print("\nVoltage ");
  Serial.print(SERVO.Get_Voltage(1));
  Serial.print("\nLoad ");
  Serial.print(SERVO.Get_Load(1));
  delay(1000);
  Serial.print("\n-------------------");
}
