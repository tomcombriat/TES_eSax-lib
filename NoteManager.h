#ifndef _NOTEMANAGER_
#define _NOTEMANAGER_

#include<Arduino.h>
#include <read_shift_reg.h>



const byte POLYPHONY = 12;

/*
  Combriat 2018, 2019, 2020
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3

      
  This is the include file for the class managing the mapping between keys and notes
*/





class NoteManager {
public:
  NoteManager(TouchRead*);
  bool update();
  byte* get_note();
  byte* get_previous_note();
  byte note[POLYPHONY] = { 0 };
  byte previous_note[POLYPHONY] = { 0 };



private:
  unsigned int previous_touch_no_mod = 0;
  TouchRead* TR;
};



#endif
