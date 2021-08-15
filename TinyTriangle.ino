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

WS2812rvb_t led1;
WS2812rvb_t led2;
WS2812rvb_t led3;
WS2812rvb_t led4;
WS2812rvb_t led5;

uint8_t delayModeOff = 15;
enum mode_t { modeOff, modeSearch, modeGood, modeBad}  displayMode = modeSearch;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_LIFE, OUTPUT);
  pinMode(BP0, INPUT_PULLUP);
  led1.setcolor(rvb_brun, 100);
  led2.setcolor(rvb_blue, 100);
  led3.setcolor(rvb_green, 100);
  led4.setcolor(rvb_pink, 100);
  led5.setcolor(rvb_white, 50);
  //Serial.begin(9600);
  //Serial.print("hello");
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
    jobRefreshLeds();
    
    if (--div10Hz == 0) {
      // 10 Hzt
      div10Hz = 10;

      //10HZ test poussoir
      jobPoussoir();
      
      if (--div1Hz == 0) {
        div1Hz = 10;

        ledLifeStat = !ledLifeStat;
        digitalWrite(LED_LIFE, ledLifeStat);   // turn the LED on (HIGH is the voltage level)

        if (delayModeOff) {
          if (--delayModeOff == 0) {
            displayMode == modeOff;
          }
        }
        
        led3.setcolor((e_rvb)random(0, rvb_black), 100);

        

      }

    }



  }
  delay(1);
}



void jobPoussoir() {
  if ( (digitalRead(BP0) == LOW) != bp0Stat ) {
    bp0Stat=!bp0Stat;
    if (bp0Stat) {
      displayMode = (mode_t)( (displayMode+1) % 4 );
      delayModeOff = 15;
      switch (displayMode) {
        case modeOff: 
        led1.setcolor(rvb_black, 50);
        led2.setcolor(rvb_black, 50);
        led3.setcolor(rvb_black, 50);
        led4.setcolor(rvb_black, 50);
        led5.setcolor(rvb_black, 50);
        break;
        case modeSearch: 
        led1.setcolor(rvb_blue, 50);
        break;
        case modeGood: 
        led1.setcolor(rvb_green, 100);
        break;
        case modeBad: 
        led1.setcolor(rvb_red, 100);
        break;
      }

      
    }
    
    
  }
}



void jobRefreshLeds() {
  led5.write();
  led4.write();
  led3.write();
  led2.write();
  led1.write();
  led2.write();
  led3.write();
  led4.write();
  led5.write();
  led1.reset();
  
  led1.anime();
  led2.anime();
  led3.anime();
  led4.anime();
  led5.anime();
  
}
