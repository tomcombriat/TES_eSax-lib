#ifndef _A_INPUT_
#define _A_INPUT_



#include<Arduino.h>

// TODO: en fait, il faut 2 N bits: un en intern pour la resolution native de l'adc et un en externe pour la resolution de sortie pour pouvoir gérer facilement oversampling et curvature.


// Mother class for both AnalogInput and Curved input.
class A_Input
{
public:
  A_Input(const int _pin, const unsigned long _response_time, const byte _N_bits): pin(_pin), response_time(_response_time), N_bits(_N_bits) {};

  void update(){};
  int getValue(){return value;};
  byte getNBits(){return N_bits;};
  

protected:
  const int pin;
  const unsigned long response_time;
  const byte N_bits;
  int value;


};




#endif


