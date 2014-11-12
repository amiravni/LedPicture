#define PIN 2
#define ROW 8
#define COL 10
#define MAXPTRN 11
#define FADESTEP 10

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

  void buildResh() {
    ptrnSize = 5;
    char xVecTMP[5] = { 
      1,2,3,3,3             };
    char yVecTMP[5] = { 
      0,0,0,1,2            };
    updateVec(xVecTMP, yVecTMP);   
  }

  void buildVav() {
    ptrnSize = 4;
    char xVecTMP[4] = {    
      0,1,1,1               };
    char yVecTMP[4] = {   
      0,0,1,2             };
    updateVec(xVecTMP, yVecTMP);   
  } 

  void buildTaf() {
    ptrnSize = 9;
    char xVecTMP[9] = {     
      1,2,3,3,3,1,1,1,0                };
    char yVecTMP[9] = {  
      1,1,1,2,3,1,2,3,3             };
    updateVec(xVecTMP, yVecTMP);   
  }     

  void buildHeart() {
    ptrnSize = 11;
    char xVecTMP[11] = {     
      1,3,0,1,2,3,4,1,2,3,2                };
    char yVecTMP[11] = {   
      0,0,1,1,1,1,1,2,2,2,3             };
    updateVec(xVecTMP, yVecTMP);   
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
  Resh.buildResh();
  Vav.buildVav();
  Taf.buildTaf();
  Heart.buildHeart();
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




  /*
  // Some example procedures showing how to display to the pixels:
   colorWipe(strip.Color(255, 255, 255), 50); // Red
   delay(5000);
   // colorWipe(strip.Color(0, 255, 0), 50); // Green
   // colorWipe(strip.Color(0, 0, 255), 50); // Blue
   // Send a theater pixel chase in...
   theaterChase(strip.Color(127, 127, 127), 50); // White
   theaterChase(strip.Color(127,   0,   0), 50); // Red
   theaterChase(strip.Color(  0,   0, 127), 50); // Blue
   
   rainbow(20);
   rainbowCycle(20);
   theaterChaseRainbow(50);
   */
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

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
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





