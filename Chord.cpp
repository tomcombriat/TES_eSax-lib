#include "Chord.h"

Chord::Chord() {};

Chord::Chord(NoteManager* _manager, Button* _button)
  : Modifier(_manager, _button, CHORD_TYPE) {}

/*
Chord::Chord( unsigned int N,  int * _notes)
{
  N_notes = N;
  notes_chord = _notes;
  }*/

void Chord::set_notes( unsigned int N, const int * _notes)
{
  N_notes = N;
  notes_chord = _notes;
}

void Chord::set_notes( unsigned int N, const int * _notes, char _name)
{
  N_notes = N;
  notes_chord = _notes;
  name = _name;
}

void Chord::set_notes( unsigned int N, const int * _notes,  char _name, const String * _long_name)
{
  N_notes = N;
  notes_chord = _notes;
  name = _name;
  long_name = _long_name;
}

void Chord::apply()
{
  if (button->is_pressed())
    {
      bool common = false;
      byte * note = manager->get_note();
      for (unsigned int i = 1; i < N_notes; i++)
	{
	  for (byte j = 1; j < POLYPHONY; j++)
	    {
	      if (notes_chord[i]+note[0] == note[j])
		{
		  common = true; // note already in note table
		  break;
		}
	    }
	  if (!common)
	    {
	      for (byte j = 1; j < POLYPHONY; j++)
		{
		  if (note[j] == 0) note[j] = notes_chord[i]+note[0];
		  break;
		}
	    }

	}
    }


  /*
    for (unsigned int i = 1; i < N_notes; i++)
    {
    bool common = false;
    for (byte j = 1; j < POLYPHONY; j++) // search for a common note
    {
    if (previous_note[j] == note[0] + notes_chord[i])
    {

    common = true;
    note[j] = note[0] + notes_chord[i];
    break;
    }
    }
    if (!common) // no common note for Chord found, take the first slot available
    {
    for (byte j = 1; j < POLYPHONY; j++)
    {
    if (previous_note[j] == 0 && note[j] == 0)
    {
    note[j] = note[0] + notes_chord[i];
    break;
    }
    }
    }
    }*/
}

const unsigned int Chord::get_N_notes() const
{
  return N_notes;
}

const int * Chord::get_notes() const
{
  return notes_chord;
}
