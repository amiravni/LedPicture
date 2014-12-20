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


void colorPixel2D(char x, char y, uint32_t c, boolean isShow, int dly)
{
  if (y%2) {   
    strip.setPixelColor(((int)y+1)*(COL)- (int)x-1, c);      
 //     Serial.println(((int)y+1)*(COL)- (int)x-1);
  }
  else{   
    strip.setPixelColor((int)y*COL + (int)x, c);  
//  Serial.println((int)y*COL + (int)x);
  }
  if (isShow) {
    strip.show();
    delay(dly);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(int WheelPos) {
  WheelPos = WheelPos%256;
  
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



void Square(int bias, int colorBias, uint32_t r1,uint32_t r2,uint32_t r3,uint32_t r4,boolean isShow,int dly)
{
  int x=bias;
  int y=bias;
  int i =0;
  for (int idx=0;idx<bias;idx++)
  i = i + 40-8*bias;
  
   for ( x+bias; x<COL-1-bias;x++)  {
       colorPixel2D(x, y, r1, isShow,dly);
   }
   for ( y+bias; y<ROW-1-bias;y++)  {
       colorPixel2D(x, y, r2, isShow,dly);
   }   
    for (x-bias; x>0+bias ;x--)  {
      colorPixel2D(x, y, r3, isShow,dly);
 }     
 for (y-bias; y>0+bias ;y--)  {
    colorPixel2D(x, y, r4, isShow,dly);
 }        
}


void Square(int bias, int colorBias,boolean isShow,int dly)
{
  int x=bias;
  int y=bias;
  int i =0;
  int wheelMult=1;
  i = i+bias*32;
  
   for ( x+bias; x<COL-1-bias;x++)  {
     colorPixel2D(x, y, Wheel( wheelMult*i+colorBias),  isShow,dly);
   }
   for ( y+bias; y<ROW-1-bias;y++)  {
     colorPixel2D(x, y, Wheel( wheelMult*i+colorBias),  isShow,dly);
   }   
    for (x-bias; x>0+bias ;x--)  {
     colorPixel2D(x, y, Wheel( wheelMult*i+colorBias),  isShow,dly);
 }    
 for (y-bias; y>0+bias ;y--)  {
     colorPixel2D(x, y, Wheel( wheelMult*i+colorBias),  isShow,dly);
 }        
}


class pattern {
public:
  pattern(): ptrnSize(0),biasX(0),biasY(0),xVec(NULL),yVec(NULL),color(NULL),fadeDir(NULL) {}
  
  ~pattern()
   {
     if (xVec != NULL)
       free(xVec);
     if (yVec != NULL)
       free(yVec);
     if (color != NULL)
       free(color);
     if (fadeDir != NULL)
       free(fadeDir);
   }
   
  void printPattern(boolean isShow,int dly) {

    for ( char d=0;d<ptrnSize;d++)
    {
      if (xVec[d] + biasX >= 0 && xVec[d] + biasX <COL && yVec[d]+ biasY >= 0 && yVec[d]+ biasY <ROW) {
        colorPixel2D(xVec[d] + biasX, yVec[d]+ biasY, color[d], isShow,dly);
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

  void updateVec(char* xVecTMP, char* yVecTMP)
  {
    if(xVec == NULL || yVec == NULL)
      return;
    
    memcpy(xVec, xVecTMP, ptrnSize);
    memcpy(yVec, yVecTMP, ptrnSize);

  }

  void allocateShape(byte s_ptrn)
  {
    if (s_ptrn <= MAXPTRN)
    {
      xVec = (char * )malloc(sizeof(char)*s_ptrn);
      yVec = (char * )malloc(sizeof(char)*s_ptrn);
      color =(uint32_t * )malloc(sizeof(uint32_t)*s_ptrn);
      fadeDir = (boolean * )malloc(sizeof(boolean)*s_ptrn);
      for (byte i=0; i<s_ptrn; i++)
        fadeDir[i] = false;
    }
  }

  void buildShape(char ptrn_x_vec[], char ptrn_y_vec[],byte s_ptrn)
  {
    ptrnSize = s_ptrn;
    allocateShape(s_ptrn);
    updateVec(ptrn_x_vec, ptrn_y_vec);
    updateColor( strip.Color(0, 0, 255));
    updateBias(0,0);
  }
  
  void printData() 
  {
       for (char i=0;i<ptrnSize;i++) {
         Serial.println( (int)xVec[i] );
         Serial.println( (int)yVec[i] );
         Serial.println( color[i] );
         Serial.println( (int)biasX );
         Serial.println( (int)biasY );
             Serial.println("************");
       }
    
  }

private:
  char * xVec;
  char * yVec;
  uint32_t * color;
  char ptrnSize;
  char biasX;
  char biasY;  
  boolean * fadeDir;
};

void movePatternX (pattern* ptrn, char xStart, char xEnd, char y, uint32_t clr, int dly) { 
  for (char x=xStart; x<xEnd;x++)    
  {
    ptrn->updateColor(strip.Color(0, 0, 0));
    ptrn->printPattern(false,0);        
    ptrn->updateBias(x,y);
    ptrn->updateColor(clr);
    ptrn->printPattern(false,0);
    strip.show();
    delay(dly);    
  }
}

void movePatternY (pattern* ptrn, char yStart, char yEnd, char x, uint32_t clr, int dly) { 
  for (char y=yStart; y>=yEnd;y--)    
  {
    ptrn->updateColor(strip.Color(0, 0, 0));
    ptrn->printPattern(false,0);        
    ptrn->updateBias(x,y);
    ptrn->updateColor(clr);
    ptrn->printPattern(false,0);
    strip.show();
    delay(dly);    
  }
}

#endif
