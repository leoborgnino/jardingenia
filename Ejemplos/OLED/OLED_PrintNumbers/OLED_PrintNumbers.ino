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
  SeeedOled.setTextXY(0,0);           //Set the cursor to 0th Page, 0th Column  
  SeeedOled.putNumber(40963755);           //Print number
  SeeedOled.setTextXY(1,0);           //Set the cursor to 1st Page, 0th Column  
  SeeedOled.putNumber(0xFFFF);        //Print number
  SeeedOled.setTextXY(2,0);           //Set the cursor to 2nd Page, 0th Column  
  SeeedOled.putNumber(0xFFFFFFFF);    //Print number
  SeeedOled.setTextXY(4,0);           //Set the cursor to 3rd Page, 0th Column  
  SeeedOled.putString("holaaaaaaaaaaaaaaaaaaa");
  
  
  SeeedOled.clearDisplay(); 
  SeeedOled.setTextXY(0,0); 
  SeeedOled.putString("Flor");
  SeeedOled.setTextXY(1,0);    
  SeeedOled.putString("Juan");
  SeeedOled.setTextXY(2,0);    
  SeeedOled.putString("Leo");
  SeeedOled.setTextXY(3,0);    
  SeeedOled.putString("Julia");
  

}

void loop()
{
  
}


