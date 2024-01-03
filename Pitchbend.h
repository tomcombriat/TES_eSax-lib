#ifndef _PITCHBEND_
#define _PITCHBEND_

#include<MIDI.h>

#define AVERAGE 256


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing pitchbend
*/


class Pitchbend
{
  public:
  Pitchbend(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * _MIDI, const unsigned long _response_time);
    bool has_changed();
    void update();
    void set_value(int PB);
    int get_value();

  private:
  midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * MIDI;
  unsigned long response_time, last_event_time;
    int value, previous_value;
    int values[AVERAGE];
    int rolling = 0;
    bool changed;
};



#endif
