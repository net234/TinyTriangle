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

WS2812rvb_t led1;
WS2812rvb_t led2;
WS2812rvb_t led3;
WS2812rvb_t led4;
WS2812rvb_t led5;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_LIFE, OUTPUT);
  pinMode(LED_1, OUTPUT);
  led1.setcolor(rvb_brun, 100);
    led2.setcolor(rvb_blue, 100);
    led3.setcolor(rvb_green,100);
     led4.setcolor(rvb_pink,100);
     led5.setcolor(rvb_white,50);
  //Serial.begin(9600);
  //Serial.print("hello");
}
uint32_t milli1 = millis();
uint32_t milli2 = millis();
bool led1Stat = true;
bool ledLifeStat = true;
// the loop function runs over and over again forever
void loop() {

  if (millis() - milli1  >= 100) {
    milli1 += 100;
    led1Stat = !led1Stat;
    //digitalWrite(LED_1, led1Stat);
    // //   digitalWrite(L, led1Stat);
    led1.write();
led2.write();
led3.write();    
led4.write();    
led5.write();  
    //    //   led4.write();
    led1.reset();
  }

  if (millis() - milli2   >= 1000) {
    milli2 += 1000;
    ledLifeStat = !ledLifeStat;
    digitalWrite(LED_LIFE, ledLifeStat);   // turn the LED on (HIGH is the voltage level)
    led3.setcolor((uint8_t)random(0,rvb_black), 100);
  }
}
