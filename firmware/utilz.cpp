#include "utilz.h"

int filterReading(int Zero, int Max)
{
  int value = analogRead(A0); // read the analog value from sensor
  value = map(value, Zero, Max, 0, 100);

  return value;
}

int findCurrentAvg(int t, int trys) {
  int avg = 0;
  for (int i = 0; i < trys; i++){
    avg = avg + analogRead(A0);
    delay(t);
  }

  avg = avg/10;

  return avg;
}


void WaitForIt(char C)
{
  while (true)
  {
    if (Serial.available() > 0)
      if (Serial.read() == C)
        break;
  }
}

void calibrate(Preferences& pref, int& Zero, int& Max) {
  pref.begin("haha", false);
  
  Serial.println("Hello welcome to the calibration stage of the water plant");
  Serial.println("Set the Zero of the sensor, type y to continue");
  
  WaitForIt('y');
  Serial.println("Calibrating...");
  
  Zero = findCurrentAvg(1000, 10);
  Serial.print("This is the calibrate zero value: ");
  Serial.println(Zero);

  delay(1000);

  Serial.println("Set the Max of the sensor, type y to continuee");
  
  WaitForIt('y');
  Serial.println("Calibrating...");

  Max = findCurrentAvg(1000, 10);
  Serial.print("This is the calibrate Max value: ");
  Serial.println(Max);

  pref.putUInt("zero", Zero);
  pref.putUInt("max", Max);
  
  pref.end();

  Serial.println("Calibration completed");
}
