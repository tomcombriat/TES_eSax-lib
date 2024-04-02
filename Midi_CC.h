#ifndef _MIDI_CC_
#define _MIDI_CC_

#include<Arduino.h>
#include<MIDI.h>
//#include"A_Input.h"
#include "AnalogInput.h"
#include<FixMath.h>

/*
  Combriat 2018, 2019, 2020, 2024
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3

      
  This is the include file for the class MIDI control changes
*/


/*
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

  };*/




class Midi_CC_std
{
public:
  Midi_CC_std(byte control, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> *, const unsigned long _response_time, byte _biais=0);
  byte getValue();
  void setValue(byte _value);
  byte getBias();
  void setBias(byte _biais);
  void setDeltaMode(bool _mode);
  bool getDeltaMode();
  //void increment_biais(int increment);
  void setControl(byte _control);
  byte getControl();
  bool update();
  bool hasChanged();
  
  void setAnalogInput(AnalogInputVirtual * _analog_input) {analog_input = _analog_input;};  
  AnalogInputVirtual * getAnalogInput() {return analog_input;};

private:
  byte control;
  const unsigned long response_time;
  SFix<8,7> value, previous_value,bias; // SF to check out of bounds  
  SFix<15,0> raw_value;
  bool changed,delta_mode = true;
  unsigned long last_event_time;
  byte biais;
  midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * MIDI;
  AnalogInputVirtual * analog_input = NULL;
};



class Midi_CC_HQ
{
public:
  Midi_CC_HQ(byte control_msb, byte control_lsb, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> *, const unsigned long _response_time);
  uint16_t getValue() {return value.asInt();};
  void setValue(uint16_t _value) {raw_value = _value;};
  void setControlMSB(byte _control) {control_msb = _control;};
  byte getControlMSB() {return control_msb;};
  void setControlLSB(byte _control) {control_lsb = _control;};
  byte getControlLSB() {return control_lsb;};
  bool update();
  bool hasChanged() {return true;};
  
  void setAnalogInput(AnalogInputVirtual * _analog_input) {analog_input = _analog_input;};  
  AnalogInputVirtual * getAnalogInput() {return analog_input;};

private:
  byte control_msb, control_lsb;
  const unsigned long response_time;
  UFix<16,0> raw_value;
  UFix<14,0> value, previous_value;
  bool changed;
  unsigned long last_event_time;
  
  midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * MIDI;
  AnalogInputVirtual * analog_input = NULL;
};



#endif
