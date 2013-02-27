#include <FastSPI_LED.h>

#define NUM_LEDS 32

// Sometimes chipsets wire in a backwards sort of way
//struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
 struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

int fadeToGreen;
long random_led;

#define PIN 4

void setup()
{
  FastSPI_LED.setLeds(NUM_LEDS);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_TM1809);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_LPD6803);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_HL1606);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_595);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2801);

  //FastSPI_LED.setPinCount(PIN);
  FastSPI_LED.setDataRate(3);
  
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
  
  for(int i = 0; i < NUM_LEDS; i++)
    {
    LED_FadeInOut(i, 2,
                  0,
                  0,
                  175,
                  0,
                  0,
                  212,
                  0,
                  255);
    }
  
  fadeToGreen = true;
}

void loop() { 
//  // one at a time
//  for(int j = 0; j < 3; j++) { 
//    for(int i = 0 ; i < NUM_LEDS; i++ ) {
//      memset(leds, 0, NUM_LEDS * 3);
//      switch(j) { 
//        case 0: leds[i].r = 255; break;
//        case 1: leds[i].g = 255; break;
//        case 2: leds[i].b = 255; break;
//      }
//      FastSPI_LED.show();
//      delay(10);
//    }
//  }

//  // growing/receeding bars
//  for(int j = 0; j < 3; j++) { 
//    memset(leds, 0, NUM_LEDS * 3);
//    for(int i = 0 ; i < NUM_LEDS; i++ ) {
//      switch(j) { 
//        case 0: leds[i].r = 255; break;
//        case 1: leds[i].g = 255; break;
//        case 2: leds[i].b = 255; break;
//      }
//      FastSPI_LED.show();
//      delay(10);
//    }
//    for(int i = NUM_LEDS-1 ; i >= 0; i-- ) {
//      switch(j) { 
//        case 0: leds[i].r = 0; break;
//        case 1: leds[i].g = 0; break;
//        case 2: leds[i].b = 0; break;
//      }
//      FastSPI_LED.show();
//      delay(1);
//    }
//  }

//Generate random number within bounds of total number of LEDs in string
fadeToGreen = 0;
random_led = random(0, NUM_LEDS-1);
for(int i = 0; i < NUM_LEDS; i++)
{
//Alternate between green>blue, blue->green fade in/out for random LEDs
  //002288 (blue color)
  //009966 (green color)
  //if(fadeToGreen == random_led)
  //{
    //for(int i = 0; i < NUM_LEDS; i++)
    //{
    LED_FadeInOut(i, 1,
                  0,
                  150,
                  236,
                  0,
                  200,
                  236,
                  0,
                  255);
// LED_FadeInOut(/*random_led*/i, 3,
//                  0,
//                  0,
//                  34,
//                  0,
//                  0,
//                  153,
//                  0,
//                  255);
    //}
    //fadeToGreen = 0;
  }
 // else
for( int j = NUM_LEDS-1 ; j >= 0; j--) 
  {
     LED_FadeInOut(j, 1,
                  0,
                  200,
                  236,
                  0,
                  50,
                  236,
                  0,
                  255);
    fadeToGreen++;
  //}        
}         
}

//Flash
//arrLEDToFlash
//lnColorToFlash
//intFlashPeriod
void LED_Flash(long arrLEDToFlash[NUM_LEDS], long lnColorToFlash, int intFlashPeriod)
{
  
  //Iterate through passed in array. Where the element of the array is 1, flash that LED
  

//Fade in/out
//ln_LEDNumberInString = number of LED (0 indexed) to apply the fade in/out effect to
//int_FadeDelay_uSec = delay between color changes
//int_StartColor = Initial color to set the LED to, based on 0-256 color scale
//int_EndColor = End color to set the LED to, based on 0-256 color scale
void LED_FadeInOut(long ln_LEDNumberInString, int int_FadeDelay_uSec, 
              int int_StartColor_r,
              int int_StartColor_g,
              int int_StartColor_b,
              int int_EndColor_r,
              int int_EndColor_g,
              int int_EndColor_b,  
              int int_StartBrightness, int int_EndBrightness)
{
  long i,j,k;
  //Set the inital colors
  
  //iterate through entire brightness only increasing to the limit passed in
  
  //for(int j = 0; j < 3; j++ ) { 
    //leds[ln_LEDNumberInString].r = int_StartColor_r;
    //leds[ln_LEDNumberInString].g = int_StartColor_g;
    //leds[ln_LEDNumberInString].b = int_StartColor_b;
    //FastSPI_LED.show();
    //delay(int_FadeDelay_uSec);
    
    //Fade up
    do
    {
      if(leds[ln_LEDNumberInString].r < int_EndColor_r) leds[ln_LEDNumberInString].r++;
      else if(leds[ln_LEDNumberInString].r > int_EndColor_r) leds[ln_LEDNumberInString].r--;
      
      if(leds[ln_LEDNumberInString].g < int_EndColor_g) leds[ln_LEDNumberInString].g++;
      else if(leds[ln_LEDNumberInString].g > int_EndColor_g) leds[ln_LEDNumberInString].g--;
      
      if(leds[ln_LEDNumberInString].b < int_EndColor_b) leds[ln_LEDNumberInString].b++;
      else if(leds[ln_LEDNumberInString].b > int_EndColor_b) leds[ln_LEDNumberInString].b--;
     
    
    if( (leds[ln_LEDNumberInString].r == int_EndColor_r) &&
        (leds[ln_LEDNumberInString].g == int_EndColor_g)  &&
        (leds[ln_LEDNumberInString].b == int_EndColor_b))
          break;
          
               FastSPI_LED.show();
      delay(int_FadeDelay_uSec);
     
      
    }while(1);
    
    //Fade Down      
    do
    {
      if(leds[ln_LEDNumberInString].r > int_StartColor_r) leds[ln_LEDNumberInString].r--;
      else if(leds[ln_LEDNumberInString].r < int_StartColor_r) leds[ln_LEDNumberInString].r++;
      
      if(leds[ln_LEDNumberInString].g > int_StartColor_g) leds[ln_LEDNumberInString].g--;
      else if(leds[ln_LEDNumberInString].g < int_StartColor_g) leds[ln_LEDNumberInString].g++;
      
      if(leds[ln_LEDNumberInString].b > int_StartColor_b) leds[ln_LEDNumberInString].b--;
      else if(leds[ln_LEDNumberInString].b < int_StartColor_b) leds[ln_LEDNumberInString].b++;
      
           

      if((leds[ln_LEDNumberInString].r == int_StartColor_r) &&
          (leds[ln_LEDNumberInString].g == int_StartColor_g) &&
          (leds[ln_LEDNumberInString].b == int_StartColor_b))
          break;
     
           FastSPI_LED.show();
      delay(int_FadeDelay_uSec);
      
    }while(1);
//            
//
//    for(int k = int_StartBrightness; k < int_EndBrightness; k++) { 
//        switch(j) { 
//          case 0: leds[i].r = (leds[i].r + k) % 256; break;
//          case 1: leds[i].g = (leds[i].g + k) % 256; break;
//          case 2: leds[i].b = (leds[i].b + k) % 256; break;
//        }
//      FastSPI_LED.show();
//      delay(int_FadeDelay_uSec);
//    }
//    for(int k = int_EndBrightness-1; k >= int_StartBrightness; k--) { 
//        switch(j) { 
//          case 0: leds[i].r = (leds[i].r - k) % 256; break;
//          case 1: leds[i].g = (leds[i].g - k) % 256; break;
//          case 2: leds[i].b = (leds[i].b - k) % 256; break;
//        }
//      FastSPI_LED.show();
//      delay(int_FadeDelay_uSec);
//    }
//  }
}
