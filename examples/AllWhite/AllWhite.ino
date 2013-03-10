#include "shiftbrite.h"

void setup()
{
  /*
  Call shiftbrite.init() to initialize your Arduino for use with the ShiftBrite LEDs.
  You may also set an initial color for all LEDs on start-up by passing red, green, and blue
  values as unsigned 16-bit integer parameters (uint16_t).
  i.e. shiftbrite.init(1023, 1023, 1023);
  */
  shiftbrite.init();
}

void loop()
{
  // step through all available LEDs and set their color individually
  for(int i = 0; i < shiftbrite.length(); i++)
  {
    shiftbrite.set(i, 1023, 1023, 1023);
  }
  
  /* shiftbrite.update() sends data to all the ShiftBrite LEDs.
  This is when LEDs actually change. */
  shiftbrite.update();  
}
