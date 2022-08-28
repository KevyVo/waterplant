// include library to read and write from flash memory
#include <Preferences.h>
#include "utilz.h"
#define AOUT_PIN 36 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor

Preferences preferences;
int Max;
int Zero;

void setup() {
  Serial.begin(9600);

  preferences.begin("haha", false);
  Serial.println("Hello welcome to waterplant");

  Zero = preferences.getUInt("zero", 0);
  Max = preferences.getUInt("max", 0);

  preferences.end();

  Serial.println(Zero);
  Serial.println(Max);
}

void loop() {
  while(true){
    if (Serial.available() > 0){
      char temp = Serial.read();
      if (temp == 'c'){
        calibrate(preferences, Zero, Max);
      }else if(temp == 'p'){
        break;
      }
    }
  }

  int value = filterReading(Zero, Max);
  Serial.print("Moisture value: ");
  Serial.println(value);

  preferences.end();

  Serial.println(Zero);
  Serial.println(Max);

  delay(500);

  // Restart ESP
  ESP.restart();
}
