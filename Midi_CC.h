#ifndef _MIDI_CC_
#define _MIDI_CC_

#include<Arduino.h>
#include<MIDI.h>

/*
  Combriat 2018, 2019, 2020
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3

      
  This is the include file for the class MIDI control changes
*/


class Midi_CC
{
public:
  Midi_CC(byte control, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> *, const unsigned long _response_time ,unsigned long _delta_time, byte _biais=0);
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
