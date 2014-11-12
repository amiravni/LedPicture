#ifndef LED_PATTERNS
#define LED_PATTERNS

#define MAXPTRN 11
#define ROW 8
#define COL 10
#define FADESTEP 10

#define BUILD_SHAPE(PREFIX,NAME) \
{	\
	char xvec[PREFIX ## _PATTERN_SIZE] = {PREFIX ## _PATTERN_X}; \
	char yvec[PREFIX ## _PATTERN_SIZE] = {PREFIX ## _PATTERN_Y}; \
	NAME.buildShape(xvec,yvec,PREFIX ## _PATTERN_SIZE); \
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




#endif
