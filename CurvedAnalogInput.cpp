#include "CurvedAnalogInput.h"


// TODO: RATIONALIZE A BIT...

CurvedAnalogInput::CurvedAnalogInput(const int _pin, const short _global_max , int _biais, const unsigned long _response_time, const short _N_bits_low, const short _N_bits_high, const float _unbiased_threshold): pin(_pin), global_max(_global_max), response_time(_response_time), N_bits_low(_N_bits_low), N_bits_high(_N_bits_high), unbiased_threshold(_unbiased_threshold)
{
  
  pinMode(pin, INPUT);
  biais = biais;
  min_output = 0;
  max_output = 1 << (N_bits_low + N_bits_high);
  LSB_mask = 0;
  for (unsigned short i = 0; i < N_bits_low; i++) LSB_mask += 1 << i;
  calibrate();
}


void CurvedAnalogInput::update()
{
  changed = false;
  if (millis() - last_read_time > response_time)
    {
      int value = analogRead(pin) - biais;  // next 3 lines: 15micros
      last_read_time = millis();
      value += analogRead(pin) - biais;
    
      if (value != previous_raw_value) // the bigger the curvature the flatter it is a low values
	{
	  previous_raw_value = value;
	  int tamp_output_value = scaling_factor * (value + curvature * value * (value - current_max));
	  if (tamp_output_value > max_output) tamp_output_value = max_output;
	  if (tamp_output_value < min_output) tamp_output_value = min_output;
	  if (tamp_output_value != output_value) {
	    changed = true;
	    output_value = tamp_output_value;
	  }
	}
      //value = analogRead(pin) - biais;
    }
}


int CurvedAnalogInput::MSB()
{
  if (output_value > threshold) return output_value >> N_bits_low;
  else return 0;
}

int CurvedAnalogInput::LSB()
{
  if (output_value > threshold) return (output_value & LSB_mask);
  else return 0;
}

int CurvedAnalogInput::value()
{

  if (output_value > threshold) return (output_value); // Maybe put that in the update?
  else return 0;
}

void CurvedAnalogInput::calibrate()
{
  biais = analogRead(pin);
  threshold = unbiased_threshold * biais;
  compute_coef();
}


void CurvedAnalogInput::set_sensitivity(int8_t _sensitivity)
{
  sensitivity = _sensitivity;
  if (sensitivity > 10) sensitivity = 10;
  if (sensitivity < -10) sensitivity = -10;
  compute_coef();
}

int8_t CurvedAnalogInput::get_sensitivity() {
  return sensitivity;
}

void CurvedAnalogInput::set_curvature(int8_t _curvature_index)
{
  curvature_index = _curvature_index;
  if (curvature_index > 10) curvature_index = 10;
  if (curvature_index < -10) curvature_index = -10;

  compute_coef();
}

int8_t CurvedAnalogInput::get_curvature() {
  return curvature_index;
}

bool CurvedAnalogInput::has_changed() {
  return changed;
}

void CurvedAnalogInput::set_min_max(short _min, short _max)
{
  max_output = _max;
  min_output = _min;
}


void CurvedAnalogInput::compute_coef()
{
  current_max = (global_max - biais) - 1.*(global_max - biais) * sensitivity / 10;
  scaling_factor = 1.*max_output / current_max;
  curvature = 1.*curvature_index / (10 * current_max);
}
