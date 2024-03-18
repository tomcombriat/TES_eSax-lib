#ifndef _CURVED_ANALOG_
#define _CURVED_ANALOG_

#include<Arduino.h>
#include<FixMath.h>
/*
  Combriat 2018, 2019, 2020, 2024
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


template<uint8_t NBits>  // always output on the full range of uint16_t
class CurvedAnalogInput2
{
public:
  CurvedAnalogInput2(const int _pin, const unsigned long _response_time, const int16_t _threshold=10): pin(_pin), response_time(_response_time), internal_threshold(_threshold)
  {
    pinMode(pin, INPUT);
  }

  void calibrate()
  {
    int32_t tamp_bias = 0;
    for (byte i=0;i<16;i++) tamp_bias += analogRead(pin);
    bias = tamp_bias >> 4;
  }

   uint16_t getValue() {return value;}


  /** Compute the scaling factor and the curvature factor depending on the bias and the max sensor value
TODO: move to private once tests are over
   */
  void computeCoef()
  {
    UFix<16,0> max_input = max_sensor_value - bias - 1.*(max_sensor_value - bias) * sensitivity / 10;
    scaling_factor = toUInt(65535) * max_input.invAccurate();
    curvature = 1.*curvature_index / (10 * max_input.asInt());
    /*Serial.println(1.*curvature_index / (10 * max_input.asInt()));
    Serial.print("bb ");
    Serial.println(bias);*/
  }

  void setCurvature(int8_t _curvature_index)
  {
    curvature_index = _curvature_index;
    if (curvature_index > 10) curvature_index = 10;
    if (curvature_index < -10) curvature_index = -10;

    computeCoef();
  }

  int8_t getCurvature() {
    return curvature_index;
  }


  void setSensitivity(int8_t _sensitivity)
  {
    sensitivity = _sensitivity;
    if (sensitivity > 10) sensitivity = 10;
    if (sensitivity < -10) sensitivity = -10;
    computeCoef();
  }

  void update()
  {
  if (millis() - last_read_time > response_time)
    {
      last_read_time = millis();
      int32_t value = analogRead(pin) - bias;
      //Serial.println(value);
      /* Serial.print(scaling_factor.asFloat());
      Serial.print(" ");
      Serial.println(curvature.asFloat());*/
      if (value < 0) value = 0;
      UFix<NBits,0> valueFM = value;
      if (value != previous_internal_value)
	{
	  auto scaled_value = scaling_factor * (valueFM + curvature * valueFM * (valueFM - UFix<NBits,0>(max_sensor_value)));
	  //Serial.println(scaled_value.asInt());
					       
	}
      

      
    }

  }
  

  
  

  


 private:
  uint16_t max_sensor_value = 3500, value, bias=0;
  const int pin;
  const unsigned long response_time;
  unsigned long last_read_time;
  const int16_t internal_threshold;
  int32_t  previous_internal_value;
  int8_t sensitivity, curvature_index;
  UFix<8,8> scaling_factor, curvature;
};

#endif
