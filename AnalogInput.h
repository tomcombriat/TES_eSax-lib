#ifndef _ANALOGINPUT_
#define _ANALOGINPUT_

#include<FixMath.h>

/*
  Combriat 2018, 2019, 2020, 2023, 2024
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3

      
  This is the include file for the class managing analog_inputs
*/


#include<Arduino.h>
#include"A_Input.h"



#define MAX_ADC 1024




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

template<uint8_t NBits>  // always output on the full range of int16_t
class AnalogInput2
{
public:
  AnalogInput2(const int _pin, const unsigned long _response_time, const int16_t _dead_zone=10, const int16_t _safety = 10):pin(_pin), response_time(_response_time), dead_zone(_dead_zone), safety(_safety)
  {
    pinMode(pin, INPUT);
    // analogReadResolution(NBits);
  }

  void calibrate()
  {
    int32_t tamp_bias = 0;
    for (byte i=0;i<16;i++) tamp_bias += analogRead(pin);
    bias = tamp_bias >> 4;
  }

  int16_t getValue() {return value;}

  void setInvert(bool _inverted) {inverted = _inverted;}

  bool update()
  {
    changed = false;
    up = 0;
    if (millis() - last_read_time > response_time)
      {
	int16_t new_value;
	last_read_time = millis();
	int32_t internal_value = analogRead(pin) - bias;
	if (previous_internal_value == internal_value) return changed; // no need to compute
	previous_internal_value = internal_value;
	
	if (internal_value > dead_zone)
	  {
	    internal_value -= dead_zone;
	    int32_t scaled_value = (UFix<NBits-1,0>(internal_value) * scaling_factor_pos).asInt();
	    
	    if (scaled_value > 32767) scaled_value = 32767;
	    new_value = scaled_value;
	  }

	else if (internal_value < -dead_zone)
	  {
	    internal_value += dead_zone;
	    int32_t scaled_value = -(UFix<NBits-1,0>(-internal_value) * scaling_factor_neg).asInt();
	    if (scaled_value < -32768) scaled_value = -32768;
	    new_value = scaled_value;
	  }	
	else new_value = 0;
	
	if (inverted) new_value = 65535 - new_value;

	if (new_value != value)
	  {
	    if (value > 15000 && new_value < 15000) up = 1;
	    else if (value < -15000 && new_value > -15000) up = -1;
	    value = new_value;
	    changed = true;
	  }
      }
    return changed;  
  }

  void deCalibrate()
  {
    max_sensor_value = 0;
    min_sensor_value = 65535;
  }

  void calibrateMinMax()
  {
    int16_t tamp_value = analogRead(pin);

    if (tamp_value < min_sensor_value) min_sensor_value = tamp_value;
    if (tamp_value > max_sensor_value) max_sensor_value = tamp_value;
  }

  void setMinMaxSensor(uint16_t min, uint16_t max)
  {
    min_sensor_value = min;
    max_sensor_value = max;
  }

  uint16_t getMinSensor() {return min_sensor_value;}
  uint16_t getMaxSensor() {return max_sensor_value;}

  void computeScalingFactor()
  {
    scaling_factor_pos = ((toUInt(uint16_t(max_sensor_value - safety - dead_zone - bias))).invAccurate()).sL<15>();
    scaling_factor_neg = ((toUInt(uint16_t(bias - dead_zone - safety - min_sensor_value))).invAccurate()).sL<15>();
    
  }

  int8_t getUpDown() {return up;}
  
  static constexpr byte getNbits() {return 16;}


private:
  uint16_t max_sensor_value = 3500, min_sensor_value = 50;
  int16_t value;
  uint16_t bias;
  const int pin;
  const unsigned long response_time;
  unsigned long last_read_time=0;
  const uint16_t dead_zone;
  const uint16_t safety;
  bool inverted, changed;
  UFix<16,16> scaling_factor_neg, scaling_factor_pos;
  int32_t previous_internal_value;
  int8_t up=0;
  

};



#endif
