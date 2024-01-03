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
  void setTranspose(int);
  int getTranspose();


 private:
  int transpose;
};


#endif
