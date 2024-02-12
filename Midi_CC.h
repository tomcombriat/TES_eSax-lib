#ifndef _MIDI_CC_
#define _MIDI_CC_

#include<Arduino.h>
#include<MIDI.h>
#include"A_Input.h"

/*
  Combriat 2018, 2019, 2020, 2024
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3

      
  This is the include file for the class MIDI control changes
*/

class MIDI_CC
{
public:
  MIDI_CC(byte _midi_channel, byte _control, const unsigned long _response_time, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * _MIDI, A_Input * _analog_input=NULL):
    midi_channel(_midi_channel), control(_control), response_time(_response_time), MIDI(_MIDI), analog_input(_analog_input)
  {}

  void update(){};
  uint16_t getValue(){return value;}
  byte getChannel(){return midi_channel;}
  byte getControl(){return control;}
  A_Input * getAnalogInput(){return analog_input;}
  void setValue(uint16_t _value){value = _value;}
  void setChannel(byte _channel){midi_channel = _channel;}
  void setControl(byte _control){control = _control;}
  void setAnalogInput(A_Input * _analog_input){analog_input = _analog_input;}
  


protected:
  byte midi_channel;
  byte control;
  const unsigned long response_time;
  midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * MIDI;
  A_Input * analog_input;
  uint16_t value;

};




class Midi_CC_std
{
public:
  Midi_CC_std(byte control, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> *, const unsigned long _response_time ,unsigned long _delta_time, byte _biais=0);
  int get_value();
  void set_value(int _value);
  byte get_biais();
  void set_biais(byte _biais);
  void increment_biais(int increment);
  void set_control(byte _control);
  byte get_control();
  bool update();
  bool has_changed();

private:
  byte control;
  const unsigned long response_time;
  int value, previous_value;
  bool changed;
  float max_accessible_range = 127;
  unsigned long last_biais_time, last_event_time, delta_time;
  byte biais;
  midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * MIDI;
};



#endif
