#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#define tempMax 56

unsigned long currentTime;
unsigned long cloopTime;
volatile float temp1,temp2,perc_temp;
volatile int blinkPage = 0; 


void setup()   {                
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  currentTime = millis();
  cloopTime = currentTime;
}


void loop() {
  currentTime = millis();
  temp1=13;                                      //Temperatura de la terma
  temp2=15;  
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      display.clearDisplay();
      if (blinkPage==0)
        {
         display.setTextColor(BLACK, WHITE);
         blinkPage=1;
        }
      else
        {
         display.setTextColor(WHITE); 
         blinkPage=0;
        }
      display.setCursor(0,0);
      display.println("    ON    ");
      display.print( " ");
      display.print(temp1,0);
      display.print( "C  ");
      perc_temp=max(0,temp1-temp2)/(tempMax-temp2)*100;
      display.print (perc_temp,0);
      display.println("%  ");
      display.display();  
   }
   
   
}
