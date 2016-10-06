#include "U8glib.h"


//**************************************************
// Change this constructor to match your display!!!
// Corresponding pins on 12864ZW: E, R/W, RS
// Expected parameters for this ctor: Clock (sck), Data-In (mosi), Chip-Select (cs)
// See details: https://github.com/olikraus/u8glib/wiki/tdisplaysetup
// And:         https://github.com/olikraus/u8glib/wiki/device#st7920-128x64
U8GLIB_ST7920_128X64 u8g(8, 9, 10, U8G_PIN_NONE);
//**************************************************

int counter = 0;

void setup() {  
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1); // Instructs the display to draw with a pixel on. 
}

void loop() {  
  
  u8g.firstPage();
  do {  
    draw();
  } while( u8g.nextPage() );
  
  // since some time is spent on updating LCD, 
  // display counter will be slightly slower than 1 sec
  counter++;
  delay(1000);   
}
  
void draw(){
  u8g.drawStr( 0, 20, "Hello World");
  u8g.drawStr( 0, 50, String(counter).c_str());  
}
