#include "Midi_CC.h"


/*
  Combriat 2018, 2019, 2020
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3


  This is the class file for the class MIDI control changes
*/



extern byte midi_channel;

Midi_CC_std::Midi_CC_std(byte _control, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * _MIDI, const unsigned long _response_time, byte _biais):
  control(_control), response_time(_response_time), biais(_biais)
{
  value = 0;
  previous_value = -1;
  last_event_time = 0;
  MIDI = _MIDI;
}

byte Midi_CC_std::get_value()
{
  return value.asInt();
}

void Midi_CC_std::set_value(byte _value)
{
  value = _value;
}

byte Midi_CC_std::get_bias()
{
  return bias.asInt();
}

void Midi_CC_std::set_bias(byte _bias)
{
  bias = _bias;
}



void Midi_CC_std::set_control(byte _control){control = _control;}

byte Midi_CC_std::get_control(){return control;}

bool Midi_CC_std::update()
{
  changed = false;
  if (millis() - last_event_time > response_time)
    {  
      if (analog_input != NULL) raw_value = (analog_input->getValue());
      
      if (!delta_mode)
	{
	  if (raw_value.sR<8>() > bias) {auto mul = (UFix<8,0>(128) - bias).sR<15>(); // sR<15> to divide by the range of the input.	  
	    value = raw_value * mul + bias;
	  }
	  else if (raw_value.sR<8>() < bias)
	    {
	    auto mul = (bias).sR<15>();
	    value = raw_value * mul + bias;
	  }
      
	  // checking the bounds
	  if (value > UFix<7,0>(127)) value = 127;
	  else if (value < SFix<1,0>(0)) value = 0; 
	}
	  
      else  // delta mode
	{
	  bias = bias + raw_value.sR<16>();
	  if (bias > UFix<7,0>(127)) bias = 127;
	  else if (bias < SFix<1,0>(0)) bias = 0;
	  value = bias;
	} 
  
      

      if (value != previous_value)
	{
	  last_event_time = millis();
	  changed = true;
	  if (value.asInt() != previous_value.asInt()) MIDI->sendControlChange(control, value.asInt(), midi_channel);
	  previous_value = value;
	  
	  return true;
	}
    }
  return changed;
}

bool Midi_CC_std::has_changed(){return changed;}
