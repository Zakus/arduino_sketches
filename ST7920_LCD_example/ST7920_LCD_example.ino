#include "U8glib.h"


//**************************************************
// Change this constructor to match your display!!!
U8GLIB_ST7920_128X64 u8g(8, 9, 10, U8G_PIN_NONE);
//**************************************************

int counter = 0;

void setup() {  
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1); // Instructs the display to draw with a pixel on. 
}

void loop() {  
  counter++;
  u8g.firstPage();
  do {  
    draw();
  } while( u8g.nextPage() );
  delay(1000);   
}
  
void draw(){
  u8g.drawStr( 0, 20, "Hello World");
  u8g.drawStr( 0, 50, String(counter).c_str());  
}
