#ifndef _ARPEGIOMONO_
#define _ARPEGIOMONO_
#include<Arduino.h>
#include "Modifier.h"
#include "CurvedAnalogInput.h"

// TODO
// ADD AN "ARMED" STATE, SET TRUE WHEN JUST BEEN PRESSED, RECORDING THE ARMED TIME
// GET ACCESS TO A ROUGHT SCHEDULER (first in, last out) RECORDING ARMED TIMES, the scheduler will trigger update if needed.
// SUSTAIN SCALING BINDED TO MIDI CC 72, EXTERNALLY


/*
  Combriat 2018, 2019, 2020, 2023
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3


  This is the include file for the class managing arpegiators
*/




class ArpegioMono: public virtual Modifier
{
public:
  ArpegioMono();
  //ArpegioMono(byte * notes);
  // arpegio_mono(const unsigned int N, const float * times, const int * notes);
  //arpegio_mono(const unsigned int N, const float * times,const  int * notes, const char _name);
  ArpegioMono(NoteManager *, Button *, CurvedAnalogInput *);
  void set_notes(const unsigned int N, const float * times, const int * notes);
  void set_notes(const unsigned int N, const float * times, const int * notes, const char _name);
  void set_notes(const unsigned int N, const float * times, const int * notes, const char _name, const String * l_name);
  void set_tempo(unsigned long _tempo);
  void set_sustain_scaling(int _sustain_scaling);
  //int next();
  //int previous();
  void start();
  void stop();
  void pause();
  void unpause();
  void apply();
  bool is_started();
  bool is_armed();
  int get_duration_scaling();
  unsigned int get_N_notes();
  int * get_notes();


private:
  CurvedAnalogInput * trigger;
  int duration_scaling = 1;  // for arp last more than one measure for instance
  unsigned int  N_note_arp;
  float * times_arp;
  int * notes_arp;
  unsigned int  next_index = 0;
  bool started  = false, armed = false, paused = false;
  unsigned long start_time = 0, duration = 500, next_event_time = 0, next_silent_time = 0;
  //short next_note;
  //short previous_note;
  byte previous_note;
  int sustain_scaling = 127; // for shutting down the note before its real end (very electro): 127: full length, 0: no length.
};







#endif
