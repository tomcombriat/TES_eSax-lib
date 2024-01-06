#ifndef _ANALOGINPUT_
#define _ANALOGINPUT_

/*
  Combriat 2018, 2019, 2020, 2023, 2024
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3

      
  This is the include file for the class managing analog_inputs
*/


#include<Arduino.h>






#define MAX_ADC 1024



// Mother class for both AnalogInput and Curved input.
class A_Input
{
public:
  A_Input(){};
  A_Input(const int _pin, const unsigned long _response_time, const byte _N_bits): pin(_pin), response_time(_response_time), N_bits(_N_bits) {};

  void update(){};
  int getValue(){return value;};
  byte getNBits(){return N_bits;};
  

protected:
  int pin;
  unsigned long response_time;
  byte N_bits;
  int value;


};









class AnalogInput: public virtual A_Input
{
public:
  AnalogInput(const int _pin, const unsigned long _response_time, byte _N_bits,int _biais = 0, const int _dead_zone=0, const int _safety=0, float _scaling_factor = 1.);
    
  bool update();
  //int value();
  void calibrate();
  void set_biais(int _biais);
  void set_invert(bool _inverted);
  void set_scaling_factor(float _scaling_factor);
  void compute_scaling_factor(int target);
  bool has_changed();
  void set_min_max(int _min, int _max);
  int up_down();
  void calibrate_min_max();
  void precalibrate_min_max();
  void set_input_range(uint16_t ir);
  uint16_t get_input_range();

private:
  //const int pin;
  int biais;
  //const unsigned long response_time;
  const int dead_zone;
  const int safety;  
  float scaling_factor;
  //int previous_raw_value;
  int min_value, max_value;
    
  bool changed = false;
  
  unsigned long last_read_time = 0;
  int up = 0;
  bool inverted = false;
  int biased_min = 0, biased_max = 0;
  int target_output = 0;

  uint16_t input_range = 0;
    
    


};



#endif
