#include "Midi_CC.h"


/*
  Combriat 2018, 2019, 2020
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3


  This is the class file for the class MIDI control changes
*/



extern byte midi_channel;

Midi_CC_std::Midi_CC_std(byte _control, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * _MIDI, const unsigned long _response_time, unsigned long _delta_time,  byte _biais):
  control(_control), response_time(_response_time), delta_time(_delta_time), biais(_biais)
{
  value = 0;
  previous_value = -1;
  last_biais_time = 0;
  last_event_time = 0;
  MIDI = _MIDI;
}

int Midi_CC_std::get_value()
{
  return previous_value;
}

void Midi_CC_std::set_value(int _value)
{
  value = _value;
}

byte Midi_CC_std::get_biais()
{
  return biais;
}

void Midi_CC_std::set_biais(byte _biais)
{
  biais = _biais;
}

void Midi_CC_std::increment_biais(int increment)
{
  if (millis() - last_biais_time > delta_time)  // just to limit increase in delta mode (not limited by analog_input timer)
    {
      int tamp_biais = biais + increment;
      if (tamp_biais > 127) tamp_biais = 127;
      if (tamp_biais < 0) tamp_biais = 0;
      biais = tamp_biais;
      last_biais_time = millis();
    }
}

void Midi_CC_std::set_control(byte _control)
{
  control = _control;
}

byte Midi_CC_std::get_control()
{
  return control;
}

bool Midi_CC_std::update()
{
  changed = false;
  if (millis() - last_event_time > response_time)
    {

      max_accessible_range = max((int) 127 - biais,(int) biais);
      int return_value = value * max_accessible_range / 127. + biais;
      if (return_value > 127) return_value = 127;
      if (return_value < 0) return_value = 0;
    


      if (return_value != previous_value)
	{
	  last_event_time = millis();
	  changed = true;
	  previous_value = return_value;
	  MIDI->sendControlChange(control, return_value, midi_channel);
	  return true;
	}
    }
  return changed;
}

bool Midi_CC_std::has_changed()
{
  return changed;
}
