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

String serialInputBuffer;

unsigned int lastTimestamp = 0;
unsigned int timerAccum = 0;

unsigned int tempTimer;
unsigned int perf_screen_refresh;

void PerfTimer_init(unsigned int & tempTimer)
{
  tempTimer = millis();
}

unsigned int PerfTimer_measure(unsigned int tempTimer)
{
  unsigned int now = millis();
  return now - tempTimer;
}

String customMessage;

void setup() {  
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1); // Instructs the display to draw with a pixel on. 

  Serial.begin(9600);
  Serial.write("Waiting for input!\n");
}

void loop() {  
  PerfTimer_init(tempTimer);
  u8g.firstPage();
  do {  
    draw();
  } while( u8g.nextPage() );
  perf_screen_refresh = PerfTimer_measure(tempTimer);

  update_counter();
  process_input();
  
  // since some time is spent on updating LCD, 
  // time between delta will be bigger than 100ms
  delay(100);   
}

void process_input()
{
  if(Serial.available() > 0)   
  {
    serialInputBuffer += Serial.readString();
  }

  int newLinePos = serialInputBuffer.indexOf('\n');

  if(newLinePos != -1)
  {
    String command = serialInputBuffer.substring(0,newLinePos);
    serialInputBuffer = serialInputBuffer.substring(newLinePos+1);
    Serial.write("Received: ");
    Serial.write(command.c_str());
    Serial.write('\n');
    process_command(command);
  }

  
}

void process_command(String & command)
{
  customMessage = command;
}

void update_counter()
{
  unsigned int now = millis();
  if(lastTimestamp == 0)
  {
    lastTimestamp = now;
  }
  
  timerAccum += now - lastTimestamp;
  lastTimestamp = now;

  while(timerAccum > 1000)
  {
    timerAccum -= 1000;
    counter++;
  }
}
  
void draw(){
  u8g.drawStr( 0, 15, "Hello World");
  u8g.drawStr( 0, 30, String(counter).c_str());  
  u8g.drawStr( 0, 45, customMessage.c_str()); 
  u8g.drawStr( 0, 60, "Refresh: ");
  u8g.drawStr( 80, 60, String(perf_screen_refresh).c_str());
   
}
