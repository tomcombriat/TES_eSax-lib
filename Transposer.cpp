#include"Transposer.h"

Transposer::Transposer(){}

Transposer::Transposer(NoteManager* _manager, Button* _button) : Modifier(_manager, _button, TRANSPOSE_TYPE) {}

void Transposer::apply()
{
  if (button->is_pressed())
    {
      byte * note = manager->get_note();
      for (byte i=0;i<POLYPHONY;i++)  
	{
	  if (note[i] !=0) note[i]+=transpose;
	}
    }
}

void Transposer::setTranspose(char _transpose)
{
  transpose = _transpose;
}

char Transposer::getTranspose()
{
  return transpose;
}
