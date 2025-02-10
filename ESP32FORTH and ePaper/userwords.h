/* userwords.h for ESP32forth and Adafruit graphics library
This is tailored for ePaper display GDEY075T7 connected by SPI/ePaper adaptor board.
For different display type change specific header files.
For documentation try this links:
https://learn.adafruit.com/adafruit-gfx-graphics-library?view=all
http://adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x.html

*/

#include <GxEPD2_BW.h> // Include the B/W e-paper library
#include <Adafruit_GFX.h> // Include Adafruit GFX for graphics commands
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#define DISPLAY_TYPE_GDEY075T7

#if __has_include("gdey/GxEPD2_750_GDEY075T7.h")
   #include "gdey/GxEPD2_750_GDEY075T7.h"
   #endif 
// pins for ePaper display connection
  #define MOSI   23
  #define CLK   18
  #define SS    5
  #define DC    17 
  #define RST   16  
  #define BUSY  4 
  // #define POWER 2 // power of display from out pin does not work?

typedef GxEPD2_BW<GxEPD2_750_GDEY075T7, GxEPD2_750_GDEY075T7::HEIGHT> DisplayType;
DisplayType display(GxEPD2_750_GDEY075T7(SS, DC, RST, BUSY));

#define USER_WORDS \
X("D.init", dinit, display.init(); ) \
X("D.setRotation",setrot, display.setRotation(n0); DROP; ) \
X("D.display", disp, display.display(); ) \
X("D.fillScreen", filscr, display.fillScreen(n0); DROP;) \
X("D.setCursor", setcur, display.setCursor(n1,n0); DROPn(2);) \
X("D.drawPixel", drpix, display.drawPixel(n2,n1,n0); DROPn(3);) \
X("D.drawLine", drlin, display.drawLine(n4,n3,n2,n1,n0); DROPn(5);) \
X("D.drawFastVLine", drfavlin, display.drawFastVLine(n3,n2,n1,n0); DROPn(4);) \
X("D.drawFastHLine", drfahlin, display.drawFastHLine(n3,n2,n1,n0); DROPn(4);) \
X("D.drawRect", drrect, display.drawRect(n4,n3,n2,n1,n0); DROPn(5);) \
X("D.fillRect", firect, display.fillRect(n4,n3,n2,n1,n0); DROPn(5);) \
X("D.drawCircle", drcirc, display.drawCircle(n3,n2,n1,n0); DROPn(4);) \
X("D.fillCircle", ficirc, display.fillCircle(n3,n2,n1,n0); DROPn(4);) \
X("D.drawRoundRect", drrore, display.drawRoundRect(n5,n4,n3,n2,n1,n0); \
     DROPn(6);) \
X("D.fillRoundRect", firore, display.fillRoundRect(n5,n4,n3,n2,n1,n0); \
     DROPn(6);) \
X("D.drawTriange", drtri, display.drawTriangle(n6,n5,n4,n3,n2,n1,n0); \
     DROPn(7);) \
X("D.fillTriange", fitri, display.fillTriangle(n6,n5,n4,n3,n2,n1,n0); \
     DROPn(7);) \
X("D.FreeSans18", fsan, display.setFont(&FreeSans18pt7b);) \
X("D.FreeSansBold18", fsanbold, display.setFont(&FreeSansBold18pt7b);) \
X("D.drawChar", drchar, display.drawChar(n5,n4,n3,n2,n1,n0); \
     DROPn(6);) \
X("D.setTextColor", settcol, display.setTextColor(n0); DROP;) \
X("D.setTextSize", settsiz, display.setTextSize(n0); DROP;) \
X("D.setTextWrap", settwrp, display.setTextWrap(n0); DROP;) \
X("D.print", print, display.print(c0); DROP;) \
X("D.println", println, display.println(c0); DROP;) \
X("D.drawBitmap", drbitm, display.drawBitmap(n5,n4,b3,n2,n1,n0); DROPn(6);) \
X("D.powerOff", pwroff, display.powerOff(); ) \
X("D.hibernate", hibern, display.hibernate();) 


     
                    
