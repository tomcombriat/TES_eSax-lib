#include "Pitchbend.h"
#include<Arduino.h>

/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the class file for the class managing Pitchbend
*/



extern byte midi_channel;

Pitchbend::Pitchbend(midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * _MIDI, const unsigned long _response_time):
  response_time(_response_time)
{
  MIDI = _MIDI;
};

void Pitchbend::update()
{
  changed = false;
  if (millis() - last_event_time > response_time)
  {
    last_event_time = millis();
    value = 0;
    for (int i=0;i<AVERAGE;i++) value += values[i];
    value = value >>8;
    if (abs(value) <15) value = 0;
    if (abs(value - previous_value) > 30)
    {
      changed = true;
      previous_value = value;
      MIDI->sendPitchBend(value, midi_channel);

    }
  }
}

bool Pitchbend::has_changed()
{
  return changed;
}


void Pitchbend::set_value(int _value)
{
  values[rolling] = _value;
  rolling++;
  if (rolling >= AVERAGE) rolling = 0;

}

int Pitchbend::get_value()
{
  return value;
}
