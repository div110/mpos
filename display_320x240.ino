//D7 - Orange
//D6 - Green
//D5 - Blue
//D4 - Brown
//D3 - Yellow

//GND - White
//VCC - Purple

#include <SPI.h>
#include "Ucglib.h"

Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
int line = 5;
void setup(void) {
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.setPrintPos(0,10);
  ucg.setColor(255, 0, 255);
  ucg.print("kanye west");
  ucg.setPrintPos(0,20);
  ucg.print("bob dylan");
  ucg.setPrintPos(0,30);
  ucg.print("twenty one pilost");
}

void loop(void) {
  //ucg.setFont(ucg_font_helvB08_tr);
  ucg.setPrintPos(0,line);
  ucg.setColor(255, 0, 255);
  //ucg.print("Hello World!");
  //ucg.setPrintPos(220,300);
  //ucg.setColor(255, 255, 255);
  // nakresli vyplněný box danou barvou
  // from [0, 80] 160 pixels long
  // and 20 pixels tall
  ucg.drawBox(0, line, 40, 1);
  delay(500);
  ucg.setColor(0,0,0);
  ucg.drawBox(0,line,40,1);

   
  //ucg.drawBox(0,0,120,320);
  //ucg.setColor(0,0,0);
  //ucg.setPrintPos(radek,radek);
  //ucg.print("Hello World!");
  //delay(0);
  line = line + 10;
  
}
