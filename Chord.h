#ifndef _CHORD_
#define _CHORD_

#include<Arduino.h>
#include "Modifier.h"

class Chord: public virtual Modifier
{
public:
  Chord();
  //Chord(const unsigned int N, const int * _notes);
  Chord(NoteManager *, Button *);
  void  set_notes( unsigned int N, const int * _notes);
  void  set_notes( unsigned int N, const int * _notes,  char _name);
  void  set_notes( unsigned int N, const int * _notes,  char _name, const String * _long_name);
  void apply();
  const unsigned int get_N_notes() const;
  const int * get_notes() const;

private:
  const int * notes_chord;
  unsigned int N_notes;
};


#endif
