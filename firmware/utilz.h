#ifndef UTILZ_H
#define UTILZ_H

#include <Preferences.h>
#include <Arduino.h>

int findCurrentAvg(int t, int trys);
void WaitForIt(char C);
void calibrate(Preferences& pref, int& Zero, int& Max);
int filterReading(int Zero, int Max);

#endif
