#include"StickyTransposer.h"


/*
  Combriat 2023, 2024
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3


  This is the heady file for the class StickyTransposer: permanently change the transposing amount
*/

StickyTransposer::StickyTransposer(){}

StickyTransposer::StickyTransposer(NoteManager* _manager, Button* _button) : Modifier(_manager, _button, STICKYTRANSPOSE_TYPE) {}

void StickyTransposer::apply()
{
  if (button->has_been_released())
    {
      manager->incrementTranspose(transpose);
    }
}

void StickyTransposer::setTranspose(char _transpose)
{
  transpose = _transpose;
}

char StickyTransposer::getTranspose()
{
  return transpose;
}
