/***********************************
***  ShiftBrite Arduino Library  ***
***  by Rory Nugent				 ***
***  http://prizepony.us		 ***
***  v01 - first official build  ***
***  last updated 09/21/2010	 ***
***********************************/

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "WConstants.h"
#include "pins_arduino.h"
#include "ShiftBrite.h"

void ShiftBrite::init(uint16_t initialRed, uint16_t initialGreen, uint16_t initialBlue)
{
  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(enablepin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  SPCR = (1<<SPE) | (1<<MSTR) | (0<<SPR1) | (0<<SPR0);
  digitalWrite(latchpin, LOW); 
  digitalWrite(enablepin, LOW);

  setAll(initialRed, initialGreen, initialBlue);
  update();
}

void ShiftBrite::set(uint8_t led, uint16_t red, uint16_t green, uint16_t blue)
{
  ledValues[led][0] = red;
  ledValues[led][1] = green;
  ledValues[led][2] = blue;
}

void ShiftBrite::setAll(uint16_t red, uint16_t green, uint16_t blue)
{
  for(uint8_t i = 0; i < NUM_LEDS; i++)
  {
    ledValues[i][0] = red;
    ledValues[i][1] = green;
    ledValues[i][2] = blue;
  }
}

void ShiftBrite::update(void)
{
  uint16_t red, green, blue;
  red = green = blue = 0;

  for (int h = 0; h < NUM_LEDS; h++) {
    red = ledValues[h][0];
    green = ledValues[h][1];
    blue = ledValues[h][2];
    sendPacket(B00, red, green, blue);
  }

  delayMicroseconds(15);
  digitalWrite(latchpin,HIGH); // latch data into registers
  delayMicroseconds(15);
  digitalWrite(latchpin,LOW);

  for (int z = 0; z < NUM_LEDS; z++) sendPacket(B01, red, green, blue);
  
  delayMicroseconds(15);
  digitalWrite(latchpin,HIGH); // latch data into registers
  delayMicroseconds(15);
  digitalWrite(latchpin,LOW);

  clear();
}

void ShiftBrite::clear(void)
{
  for(uint8_t h = 0; h < NUM_LEDS; h++) { 
    ledValues[h][0] = ledValues[h][1] = ledValues[h][2] = 0; 
  }
}

int ShiftBrite::length(void)
{
  return int(NUM_LEDS);
}

void ShiftBrite::sendPacket(uint8_t command, uint16_t red, uint16_t green, uint16_t blue) {
  if (command == B01) {
    red = 120;
    green = 100;
    blue = 100;
  }

  SPDR = command << 6 | blue>>4;
  while(!(SPSR & (1<<SPIF)));
  SPDR = blue << 4 | red >> 6;
  while(!(SPSR & (1<<SPIF)));
  SPDR = red << 2 | green >> 8;
  while(!(SPSR & (1<<SPIF)));
  SPDR = green;
  while(!(SPSR & (1<<SPIF)));
}

int ShiftBrite::getVersion()
{
	return version;
}

ShiftBrite shiftbrite;



