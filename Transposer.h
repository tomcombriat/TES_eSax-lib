#ifndef _TRANSPOSER_
#define _TRANSPOSER_

#include<Arduino.h>
#include"Modifier.h"

class Transposer: public virtual Modifier
{
 public:
  Transposer();
  Transposer(NoteManager *, Button *);

  void apply();
  void setTranspose(char);
  char getTranspose();


 private:
  char transpose=0;
};


#endif
