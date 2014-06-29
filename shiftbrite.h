/***********************************
***  ShiftBrite Arduino Library  ***
***  by Rory Nugent				 ***
***  http://prizepony.us		 ***
***  v01 - first official build  ***
***  last updated 09/21/2010	 ***
***********************************/

#ifndef _ShiftBrite_h
#define _ShiftBrite_h

#include <stdint.h>

#define NUM_LEDS 15

#define clockpin 13   // CI
#define enablepin 10  // EI
#define latchpin 9    // LI
#define datapin 11    // DI

class ShiftBrite
{
public:
  void init(uint16_t initialRed = 0, uint16_t initialGreen = 0, uint16_t initialBlue = 0);
  void set(uint8_t led, uint16_t red, uint16_t green, uint16_t blue);
  void setAll(uint16_t red, uint16_t green, uint16_t blue);
  void update();
  void clear();
  int length();
  int getVersion(); 

  uint16_t ledValues[NUM_LEDS][3]; 

private:
  void sendPacket(uint8_t command, uint16_t red, uint16_t green, uint16_t blue);
  static const uint8_t version = 1;		// stored software version
};

extern ShiftBrite shiftbrite;

#endif
