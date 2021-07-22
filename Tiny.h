#pragma once

#define __BOARD__NANO RF__
#define D_println(x) Serial.print(F(#x " => '")); Serial.print(x); Serial.println("'");

//   atTiny
//#define PB5 //1 Reset
//#define PB3 //2 Q2
//#define PB4 //3 Q1
//#define GND // 4
//#define PB0 // 5
//#define PB1 // 6
//#define PB2 // 7
//#define VCC // 8
//---------------------

#define LED_LIFE  PB1
#define LED_1     PB0
#define LED_ON  HIGH

//#define pinBP0 PB3 // D2
#define PIN_WS2812 PB2
