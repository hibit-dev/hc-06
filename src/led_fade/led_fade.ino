// -------------------------------------------------
// Copyright (c) 2026 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(2, 3); // RX, TX
 
const int pwmPin = 9;
String inputBuffer = ""; // Accumulates incoming characters until a full command arrives
 
void setup()
{
  pinMode(pwmPin, OUTPUT);

  // For monitoring activity in the Serial Monitor
  Serial.begin(9600);

  // For communicating with the HC-06
  BTSerial.begin(9600);

  Serial.println("Bluetooth LED control ready.");
}
 
void loop()
{
  while (BTSerial.available()) {
    char c = BTSerial.read();
 
    if (c == '\n') {
      // Newline signals the end of a command, process what we've collected
      processCommand(inputBuffer);
      
      // Clear the buffer ready for the next command
      inputBuffer = "";
    } else {
      // Keep appending characters until the newline arrives
      inputBuffer += c;
    }
  }
}
 
void processCommand(String cmd)
{
  cmd.trim(); // Strip any stray whitespace or carriage returns
 
  if (cmd.startsWith("B:")) {
    // Extract the number after "B:" and convert it to an integer
    int value = cmd.substring(2).toInt();

    // constrain() clamps the value to the valid PWM range 0-255
    value = constrain(value, 0, 255);

    analogWrite(pwmPin, value);
    
    BTSerial.print("Brightness set to: ");
    BTSerial.println(value); // Confirm back to the phone

    Serial.print("Brightness set to: ");
    Serial.println(value);   // Also log it locally
  } else {
    BTSerial.println("Unknown command. Try B:0 to B:255");
    Serial.println("Unknown command received");
  }
}
