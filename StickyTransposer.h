#ifndef _STICKYTRANSPOSER_
#define _STICKYTRANSPOSER_


/*
  Combriat 2023, 2024
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3


  This is the heady file for the class StickyTransposer: permanently change the transposing amount
*/

#include<Arduino.h>
#include"Modifier.h"

class StickyTransposer: public virtual Modifier
{
 public:
  StickyTransposer();
  StickyTransposer(NoteManager *, Button *);

  void apply();
  void setTranspose(char);
  char getTranspose();


 private:
  char transpose=0;
};


#endif
