#ifndef _MODIFIER_
#define _MODIFIER_

#include "NoteManager.h"
#include "Button.h"

#define TRANSPOSE_TYPE 0
#define STICKYTRANSPOSE_TYPE 1
#define ARP_TYPE 2
#define CHORD_TYPE 3

class Modifier
{
 public:
  Modifier(){};
  
  Modifier(NoteManager* _manager, Button* _button, byte _type)
    : manager(_manager), button(_button), type(_type) {};

  void apply(){};
    char get_name()
  {
    return name;
  };
  
  String * get_long_name()
  {
    return long_name;
  };

  void setButton(Button * _button)
  {
    button = _button;
  }
  
protected:
  NoteManager * manager;
  Button * button;
  char name;
  String * long_name;
  byte type;

};


#endif
