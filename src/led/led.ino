// -------------------------------------------------
// Copyright (c) 2026 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX

const int ledPin = 13;
char command; // Stores the single character received from the phone

void setup()
{
  pinMode(ledPin, OUTPUT);

  // For monitoring activity in the Serial Monitor
  Serial.begin(9600);

  // For communicating with the HC-06
  BTSerial.begin(9600);

  Serial.println("Bluetooth LED control ready.");
}

void loop()
{
  if (BTSerial.available()) {
    command = BTSerial.read();

    // Echo the received character to the Serial Monitor for debugging
    Serial.print("Received: ");
    Serial.println(command);

    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      BTSerial.println("LED ON"); // Confirm back to the phone
      Serial.println("LED ON");   // Also log it locally
    }
    
    if (command == '0') {
      digitalWrite(ledPin, LOW);
      BTSerial.println("LED OFF");
      Serial.println("LED OFF");
    }
  }
}
