/*
  TinyTriangle

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#include "Tiny.h"
#include "WS2812.h"

uint8_t div10Hz = 10;
uint8_t div1Hz = 10;

const uint8_t ledsMAX = 9;
WS2812rvb_t leds[ledsMAX];

uint8_t delayModeOff = 20;
enum mode_t { modeOff, modeSearch, modeGood, modeBad}  displayMode = modeSearch;
uint8_t displayStep = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_LIFE, OUTPUT);
  pinMode(BP0, INPUT_PULLUP);
  for (uint8_t N = 0; N < ledsMAX; N++) {
    leds[N].setcolor(rvb_white, 30, 1000,1000);
  }
}


uint32_t milli1 = millis();
bool ledLifeStat = true;
bool bp0Stat = false;

// the loop function runs over and over again forever
void loop() {
  uint16_t delta = millis() - milli1;
  if (  delta >= 10 ) {
    milli1 += 10;

    // 100 Hzt rafraichissement bandeau
    jobRefreshLeds(10);

    if (--div10Hz == 0) {
      // 10 Hzt
      div10Hz = 10;

      //10HZ test poussoir
      jobPoussoir();
    }
    if (--div1Hz == 0) {
      div1Hz = 25;

      ledLifeStat = !ledLifeStat;
      digitalWrite(LED_LIFE, ledLifeStat);   // turn the LED on (HIGH is the voltage level)

      if (delayModeOff) {
        if (--delayModeOff == 0) {
          displayMode = modeOff;
        }
      }
      // animation
      if (displayStep < ledsMAX) {
        switch (displayMode) {
          case modeOff:
            leds[displayStep].setcolor(rvb_black, 50);
            break;
          case modeSearch:
            leds[displayStep].setcolor(rvb_lightblue, 100, 1000, 1000);
            break;
          case modeGood:
            leds[displayStep].setcolor(rvb_green, 80,  400, 400);
            break;
          case modeBad:
            leds[displayStep].setcolor(rvb_orange, 80, 1400, 1400);
            break;
        }
      }
      displayStep = (displayStep + 1) % (ledsMAX + 6);






    }



  }
  //delay(1);
}



void jobPoussoir() {
  if ( (digitalRead(BP0) == LOW) != bp0Stat ) {
    bp0Stat = !bp0Stat;
    if (bp0Stat) {
      displayMode = (mode_t)( (displayMode + 1) % 4 );
      delayModeOff = 250;
      displayStep = 0;
    }


  }
}


// 110 HZ
void jobRefreshLeds(const uint8_t delta) {
  leds[0].write();
  leds[1].write();
  leds[2].write();
  leds[3].write();
  leds[4].write();
  leds[5].write();
  leds[6].write();
  leds[7].write();
  leds[8].write();
  leds[0].reset();

  leds[0].anime(delta);
  leds[1].anime(delta);
  leds[2].anime(delta);
  leds[3].anime(delta);
  leds[4].anime(delta);
  leds[5].anime(delta);
  leds[6].anime(delta);
  leds[7].anime(delta);
  leds[8].anime(delta);

}
