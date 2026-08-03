// -------------------------------------------------
// Copyright (c) 2026 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include <SoftwareSerial.h>
 
// Use pins 2 and 3 as RX and TX for the HC-05
SoftwareSerial BTSerial(2, 3);
 
void setup()
{
  // Match the AT mode baud rate in the Serial Monitor
  Serial.begin(9600);

  // HC-06 communication, must match the module's configured baud rate
  BTSerial.begin(9600);

  Serial.println("Ready. Type AT commands below.");
}
 
void loop()
{
  // Forward anything received from the HC-05 to the Serial Monitor
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

  // Forward anything typed in the Serial Monitor to the HC-05
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
