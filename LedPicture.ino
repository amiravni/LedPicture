#define PIN 2
#define ROW 8
#define COL 10
#define MAXPTRN 11
#define FADESTEP 10

#include "Led_Patterns.h"
#include "Hebrew_Letter_patterns.h"
#include "Unicode_Patterns.h"

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(80, PIN, NEO_GRB + NEO_KHZ800);



class pattern {
public:
  pattern() {
    biasX = 0;
    biasY = 0;
      for ( char d=0;d<MAXPTRN;d++)    fadeDir[d]=false;
  }

  void printPattern(boolean isShow) {

    for ( char d=0;d<ptrnSize;d++)
    {
      if (xVec[d] + biasX >= 0 && xVec[d] + biasX <COL && yVec[d]+ biasY >= 0 && yVec[d]+ biasY <ROW) {
        colorPixel2D(xVec[d] + biasX, yVec[d]+ biasY, color[d], isShow);
      }
    }
  }      

  void updateColor(uint32_t colorTMP ) {
    for (char i=0;i<ptrnSize;i++) {
      color[i] = colorTMP;
    }
  }

  void updateColorWheel(int j) {
    for (char i=0;i<ptrnSize;i++) {
      color[i] = Wheel(j+  (int)(biasY + yVec[i])*COL + (int)(biasX + xVec[i]) );
    }
  }  
  
  void updateColorFadeRed() {
     for (char i=0;i<ptrnSize;i++) {
       if (fadeDir[i]) {
       color[i] = ((color[i] >> 16) +FADESTEP ) << 16 ;
       if ((color[i] >> 16) > 255 - FADESTEP) fadeDir[i]=false;
       }
       else {
      color[i] = ((color[i] >> 16) -FADESTEP ) << 16 ;
       if ((color[i] >> 16) < FADESTEP) fadeDir[i]=true;      
     }
    }
  }    

  void updateBias(char biasXTMP, char biasYTMP ) {
    biasX = biasXTMP;
    biasY = biasYTMP;
  }  

  void updateVec(char* xVecTMP, char* yVecTMP) {

    for (char i=0;i<ptrnSize;i++) {
      xVec[i] = xVecTMP[i];
      yVec[i] = yVecTMP[i];
    }

  }

  void buildShape(char ptrn_x_vec[], char ptrn_y_vec[],byte s_ptrn)
  {
    ptrnSize = s_ptrn;
    for (byte i=0; i<s_ptrn; i++)
    {
      updateVec(ptrn_x_vec, ptrn_y_vec);
    }
  }
 

private:
  char xVec[MAXPTRN];
  char yVec[MAXPTRN];
  uint32_t color[MAXPTRN];
  char ptrnSize;
  char biasX;
  char biasY;  
  boolean fadeDir[MAXPTRN];

};

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  pattern Resh,Vav,Taf,Heart;
  
  BUILD_SHAPE(RESH_PATTERN_X,RESH_PATTERN_Y,RESH_PATTERN_SIZE,Resh);
  BUILD_SHAPE(VAV_PATTERN_X,VAV_PATTERN_Y,VAV_PATTERN_SIZE,Vav);
  BUILD_SHAPE(TAF_PATTERN_X,TAF_PATTERN_Y,TAF_PATTERN_SIZE,Taf);
  BUILD_SHAPE(HEART_PATTERN_X,HEART_PATTERN_Y,HEART_PATTERN_SIZE,Heart);

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

void matrixClear()
{
  for (int x=0; x<COL*ROW;x++)  {
    strip.setPixelColor(x, strip.Color(0, 0, 0));
  }
  strip.show();
}

void colorPixel2D(char x, char y, uint32_t c, boolean isShow)
{
  if (y%2) {   
    strip.setPixelColor(((int)y+1)*(COL)- (int)x-1, c);      
  }
  else{   
    strip.setPixelColor((int)y*COL + (int)x, c);  
  }
  if (isShow) {
    strip.show();
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(int WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else if (WheelPos < 255) {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else
  {
    WheelPos -= 255;  
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}





