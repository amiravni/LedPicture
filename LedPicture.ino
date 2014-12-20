#define PIN 2
#define PROGS 10
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(80, PIN, NEO_GRB + NEO_KHZ800);

#include "Led_Patterns.h"
#include "Hebrew_Letter_patterns.h"
#include "Unicode_Patterns.h"

int colorBias=0;
int dlyall = 50;
int intCounter=0;
int intflag=0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  attachInterrupt(1, moveCounter, FALLING);
}

void loop() {

  pattern Resh,Vav,Taf,Heart;

  BUILD_SHAPE(RESH,Resh);
  BUILD_SHAPE(VAV,Vav);
  BUILD_SHAPE(TAF,Taf);
  BUILD_SHAPE(HEART,Heart);

  Resh.updateBias( COL-5, 0);
  Vav.updateBias( COL-6, 1);
  Taf.updateBias( COL-10, 1);
  Heart.updateBias( 5, 4);


  int dly = 1;

  while (dlyall <175)
  {
    dlyall=dlyall*1.1;
    for (int bias=3;bias>=0;bias--) {
      colorBias= colorBias+16;
      Square(bias,colorBias,Wheel( colorBias),Wheel( colorBias),Wheel( colorBias),Wheel( colorBias),false,0);
      strip.show();
      Square(bias,colorBias,strip.Color(0, 0, 0),strip.Color(0, 0, 0),strip.Color(0, 0, 0),strip.Color(0, 0, 0) ,false,0);
      delay(dlyall);
    }
  }

  int count=0;
  while( count < 500) {
    for (int bias=0;bias<1;bias++) {
      colorBias= colorBias%256+1;
      Square(bias,colorBias,false,0);
      strip.show();
    }
    delay(5);
    count++;
  }

  Square(0,colorBias,strip.Color(0, 0, 0),strip.Color(0, 0, 0),strip.Color(0, 0, 0),strip.Color(0, 0, 0) ,true,30);

  movePatternX (&Resh, -4, COL-4, 0, strip.Color(0, 0, 255), 150); 
  movePatternX (&Vav, -3, COL-5, 1, strip.Color(0, 0, 255), 150); 
  movePatternX (&Taf, -8, COL-9, 1, strip.Color(0, 0, 255), 150);   
  movePatternY (&Heart, 9, 4, 5, strip.Color(255, 0,0), 150);  

  for(int j=140; j<255; j++) {
    Resh.updateColorWheel(j);
    Vav.updateColorWheel(j);   
    Taf.updateColorWheel(j);  
    Resh.printPattern(false,0);
    Vav.printPattern(false,0);   
    Taf.printPattern(false,0);  
    strip.show();
    delay(20);           
  }

  while(1) {
    if(intCounter%PROGS==0) {
      for(int j=0; j<255; j++) {
        if (intflag){ 
          intflag=0;
          break; 
        }
        Resh.updateColorWheel(j);
        Vav.updateColorWheel(j);   
        Taf.updateColorWheel(j);  
        Heart.updateColorFadeRed();        
        Resh.printPattern(false,0);
        Vav.printPattern(false,0);   
        Taf.printPattern(false,0);  
        Heart.printPattern(false,0);        

        strip.show();
        delay(50);      
      }
    }
    else if (intCounter%PROGS==1)
    {      
      movePatternX (&Heart, 5, 11, 4, strip.Color(255, 0,0), 150); 
      intCounter++;
    }
    else if (intCounter%PROGS==2)
    {      
      Resh.updateColor(strip.Color(0, 0, 255));
      Vav.updateColor(strip.Color(0, 0, 255));   
      Taf.updateColor(strip.Color(0, 0, 255));  
      Resh.printPattern(true,30);
      Vav.printPattern(true,30);   
      Taf.printPattern(true,30);         
    } 
    else if (intCounter%PROGS==3)
    {      
      Resh.updateColor(strip.Color(0, 255, 0));
      Vav.updateColor(strip.Color(0, 255, 0));   
      Taf.updateColor(strip.Color(0, 255,0));  
      Resh.printPattern(true,30);
      Vav.printPattern(true,30);   
      Taf.printPattern(true,30);         
    }   
    else if (intCounter%PROGS==4)
    {      
      Resh.updateColor(strip.Color(255, 0, 0));
      Vav.updateColor(strip.Color(255, 0, 0));   
      Taf.updateColor(strip.Color(255, 0 ,0));  
      Resh.printPattern(true,30);
      Vav.printPattern(true,30);   
      Taf.printPattern(true,30);

    }
    else if (intCounter%PROGS>=5 && intCounter%PROGS<9) {
      if (intflag){ 
        intflag=0;
        matrixClear();
      }
      colorBias= colorBias%256+1;
      Square(intCounter%PROGS-5,colorBias,false,0);
      strip.show();
      delay(10);
    }
    else if (intCounter%PROGS==9)
    {
      if (intflag){ 
        intflag=0;
        matrixClear();
      }      
      movePatternX (&Resh, -4, COL-4, 0, strip.Color(0, 0, 255), 150); 
      movePatternX (&Vav, -3, COL-5, 1, strip.Color(0, 0, 255), 150); 
      movePatternX (&Taf, -8, COL-9, 1, strip.Color(0, 0, 255), 150);   
      movePatternY (&Heart, 9, 4, 5, strip.Color(255, 0,0), 150);    
      for(int j=140; j<255; j++) {
        Resh.updateColorWheel(j);
        Vav.updateColorWheel(j);   
        Taf.updateColorWheel(j);  
        Resh.printPattern(false,0);
        Vav.printPattern(false,0);   
        Taf.printPattern(false,0);  
        strip.show();
        delay(20);           
      }      
      intCounter++;
    }  
  }
}

void moveCounter() {
  intCounter++;
  intflag=1;
}







