#define PIN 2

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(80, PIN, NEO_GRB + NEO_KHZ800);

#include "Led_Patterns.h"
#include "Hebrew_Letter_patterns.h"
#include "Unicode_Patterns.h"




void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  pattern Resh,Vav,Taf,Heart;
  
  BUILD_SHAPE(RESH,Resh);
  BUILD_SHAPE(VAV,Vav);
  BUILD_SHAPE(TAF,Taf);
  BUILD_SHAPE(HEART,Heart);

  char y=0;
  for (char x=-5; x<COL-4;x++)    
  {
    Resh.updateBias(x,y);
    Resh.updateColor(strip.Color(0, 0, 255));
    Resh.printPattern(false);
    Vav.updateBias(-1 + x,1 + y);
    Vav.updateColor(strip.Color(0, 0, 255));
    Vav.printPattern(false);   
    Taf.updateBias(-5 + x,1 + y);
    Taf.updateColor(strip.Color(0, 0, 255));
    Taf.printPattern(false);  
    Heart.updateBias( x, 4+y);
    Heart.updateColor(strip.Color(255, 0, 0));
    Heart.printPattern(false);  
    strip.show();
    delay(200);
    matrixClear();
  }

  char x = COL-5;
  Resh.printPattern(false);
  Vav.printPattern(false);   
  Taf.printPattern(false);  
 Heart.printPattern(false);  
  strip.show();    
  delay(1000);

  while(1) {
    for(int j=0; j<255; j++) {
      Resh.updateColorWheel(j);
      Vav.updateColorWheel(j);   
      Taf.updateColorWheel(j);  
      Heart.updateColorFadeRed();        
      Resh.printPattern(false);
      Vav.printPattern(false);   
      Taf.printPattern(false);  
     Heart.printPattern(false);        

      strip.show();
      delay(50);      
    }

  }


}




