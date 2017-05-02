#include <Wire.h>
#include <SeeedOLED.h>


void setup()
{
  Wire.begin();  
  SeeedOled.init();  //initialze SEEED OLED display
  DDRB|=0x21;         
  PORTB |= 0x21;

  SeeedOled.clearDisplay();           //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();       //Set display to Normal mode
  SeeedOled.setPageMode();            //Set addressing mode to Page Mode
  SeeedOled.setTextXY(2,0);           //Set the cursor to 3rd Page, 0th Column  
  SeeedOled.putString("Temp:");
  SeeedOled.putNumber(34);
  SeeedOled.putString("C");
  SeeedOled.setPageMode(); 
  SeeedOled.setTextXY(3,0);           //Set the cursor to 3rd Page, 0th Column  
  SeeedOled.putString("HumS:");
  SeeedOled.putNumber(20);
  SeeedOled.putString("%");
  SeeedOled.setTextXY(4,0);           //Set the cursor to 3rd Page, 0th Column  
  SeeedOled.putString("HumA:");
  SeeedOled.putNumber(30);
  SeeedOled.putString("%");
  SeeedOled.setTextXY(5,0);           //Set the cursor to 3rd Page, 0th Column  
  SeeedOled.putString("Luz:");
  SeeedOled.putNumber(15);
  SeeedOled.putString("lumen");
  SeeedOled.setTextXY(6,0);           //Set the cursor to 3rd Page, 0th Column  
  SeeedOled.putString("Flujo:");
  SeeedOled.putNumber(12);
  SeeedOled.putString("%");

  

}

void loop()
{
  
}


