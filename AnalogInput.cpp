#include "AnalogInput.h"


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing AnalogInputs
*/


// TODO: get rid of MAX_ADC, and compute it at initialization


AnalogInput::AnalogInput(const int _pin, const unsigned long _response_time, byte _N_bits, int _biais, const int _dead_zone, const int _safety, float _scaling_factor):
  A_Input(_pin, _response_time, _N_bits),
  /* pin(_pin),*/ biais(_biais), /*response_time(_response_time),*/ dead_zone(_dead_zone), safety(_safety), scaling_factor(_scaling_factor)
{
  pinMode(pin, INPUT);
  min_value = -10000;
  max_value = 10000;
}

bool AnalogInput::has_changed()
{
  return changed;
}

bool AnalogInput::update()
{
  changed = false;
  if (millis() - last_read_time > response_time)
  {
    last_read_time = millis();
    int new_value = analogRead(pin);
    if (inverted) new_value = MAX_ADC - new_value;

    new_value -= biais;
    if (value > dead_zone) new_value -= dead_zone;
    else if (value < dead_zone) new_value += dead_zone;
    else new_value = 0;


    new_value *= scaling_factor;
    if (new_value > max_value) new_value = max_value;
    else if (new_value < min_value) new_value = min_value;

    if (new_value != value)
    {
      if (value > 100 && new_value < 100) up = 1;
      else if (value < -100 && new_value > -100) up = -1;
      else up = 0;
      value = new_value;
      changed = true;
    }
  }
  return changed;
}
/*
int AnalogInput::getValue()
{
  return value;
  }*/

void AnalogInput::calibrate()
{
  int calib = 0;
  for (int i = 0; i < 16; i++) calib += analogRead(pin);
  calib = calib >> 4;
  if (inverted) biais = MAX_ADC - calib;
  else  biais = calib;
}

void AnalogInput::set_biais(int _biais)
{
  biais = _biais;
}

void AnalogInput::set_scaling_factor(float _scaling_factor)
{
  scaling_factor = _scaling_factor;
}

void AnalogInput::set_min_max(int min, int max)
{
  min_value = min;
  max_value = max;
}

int AnalogInput::up_down()
{
  int prev_up = up;
  up = 0;
  return prev_up;
}

void AnalogInput::set_invert(bool _inverted)
{
  inverted = _inverted;
}

void AnalogInput::compute_scaling_factor(int target)
{
  target_output = target;
  scaling_factor = 1.*target_output / input_range;
}

void AnalogInput::precalibrate_min_max()
{
  input_range = 0;
  biased_min = 0;
  biased_max = 0;
}

void AnalogInput::calibrate_min_max()
{
  int value = analogRead(pin);
  if (inverted) value = MAX_ADC - value;
  value = (value - biais) - safety - dead_zone;
  if (value > biased_max) biased_max = value;
  if (value < biased_min) biased_min = value;
  /*
    input_range = min(-biased_min, biased_max);
    if (input_range < 1000) input_range=1000;*/
  set_input_range(min(-biased_min, biased_max));
}

void AnalogInput::set_input_range(uint16_t ir)
{
  input_range = ir;
  if (input_range < 1000) input_range = 1000;
}

uint16_t AnalogInput::get_input_range()
{
  return input_range;
}
