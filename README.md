# CDS-5516-Feedback
This library was adapted for servos CDS 5516, which were used by the Hexapod Robot. This library could be used for some other CDS55 and "dynamixel" servos as well.
You can find examples of using the methods.

New features:
- reading voltage from servos ```Get_Voltage(1)```
- reading the current position of servos (0-1024) ```Get_Pos(1)```
- reading temperature of servos ```Get_Temp(1)```
- reading the current load (0-2047) ```Get_Load(1)```


Example:

```C++
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
```
