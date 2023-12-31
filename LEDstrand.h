#ifndef _LEDstrand_
#define _LEDstrand_

#include <Adafruit_NeoPixel.h>

/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing the lep strand (NeoPixel)
*/



class LEDstrand
{
  public:
  LEDstrand(Adafruit_NeoPixel*,const byte _num_leds, const unsigned long _response_time);
  void splash() const;
  void update();


  private:
unsigned last_update = 0;
    Adafruit_NeoPixel * strip;
  const byte num_leds;
  const unsigned long response_time;
  

};




#endif
