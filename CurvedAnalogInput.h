#ifndef _CURVED_ANALOG_
#define _CURVED_ANALOG_

#include<Arduino.h>
/*
  Combriat 2018, 2019, 2020
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3


  This is the include file for the class managing "curved" analog input: mainly for the breath sensor
*/



class CurvedAnalogInput
{
public:
  CurvedAnalogInput(const int _pin, const short _global_max , int _biais, const unsigned long _response_time, const short _N_bits_low, const short _N_bits_high, const float _unbiased_threshold=0);

  void update();
  int MSB(), LSB(),value();
  void calibrate();
  void set_sensitivity(int8_t _sensitivity);
  int8_t get_sensitivity();
  void set_curvature(int8_t _curvature_index);
  int8_t get_curvature();
  bool has_changed();
  void set_min_max(short _min, short _max);


private:
  const int pin;
  const short global_max;
  const unsigned long response_time;
  const short N_bits_low, N_bits_high;
  const float unbiased_threshold;
  short biais, current_max;
  int previous_raw_value = 0;
  int output_value = 0 ;
  int threshold = 0,LSB_mask;
  float scaling_factor, curvature;
  short min_output = 0, max_output = 127;
    
  int8_t sensitivity = 0, curvature_index = 0;
  bool changed = false;
    
  unsigned long last_read_time = 0;
  void compute_coef();
    
  int mask;




};



#endif
