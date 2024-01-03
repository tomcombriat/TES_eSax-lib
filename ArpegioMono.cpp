#include "ArpegioMono.h"



/*
  Combriat 2018, 2019, 2020, 2023
  This file is part of the OS embedded in the e-sax - TES
  This code is under GPL3


  This is the class file for the class managing arpegiators
*/

extern byte global_mode;

ArpegioMono::ArpegioMono() {}

ArpegioMono::ArpegioMono(NoteManager* _manager, Button* _button, CurvedAnalogInput * _trigger)
  : Modifier(_manager, _button, ARP_TYPE), trigger(_trigger) {}



/*
  ArpegioMono::ArpegioMono(unsigned int N, float * times, int * notes)
  {
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  duration_scaling = int (times[N - 1] + 1);
  }

  ArpegioMono::ArpegioMono(unsigned int N, float * times, int * notes, char _name)
  {
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  arp_name = _name;
  duration_scaling = int (times[N - 1] + 1);
  }*/

void ArpegioMono::set_notes(const unsigned int N, const float * times, const int * notes)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  duration_scaling = int (times[N - 1] + 1);
}

void ArpegioMono::set_notes(const unsigned int N, const float * times, const int * notes, const char _name)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  name = _name;
  duration_scaling = int (times[N - 1] + 1);

}

void ArpegioMono::set_notes(const unsigned int N, const float * times, const int * notes, const char _name, const String * l_name)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  name = _name;
  long_name = l_name;
  duration_scaling = int (times[N - 1] + 1);
}


void ArpegioMono::set_tempo(unsigned long temp)
{
  duration = temp;
}



void ArpegioMono::apply() //Now 2micros!
{
  if (button->has_been_pressed()) arm();
  if (button->has_been_released()) stop();
  if (armed && trigger->value() && !started && !paused) start();
  if (trigger->value()==0) stop();

  // TODO: add logic for armed state
  if (started)
    {
      byte * note = manager->get_note();
      if (note[0] != 0)
	{
	  if (note[0] != previous_note) // restart on changing note
	    {
	      previous_note = manager->note[0];
	      start();
	    }

	  if (millis() >= next_event_time)
	    {
	      float next_duration = 0.;


	      // Updating the next note
	      if (notes_arp[next_index] != -255)
		{
		  for (byte i=0;i<POLYPHONY;i++) note[i]+= notes_arp[next_index];
		}
	      
	      else// next_note = 0;  //silent note
		{
		  for (byte i=0;i<POLYPHONY;i++) note[i]= 0;
		}


	      // Calculation the time for next note
	      //next_event_time += duration * next_duration ;

	      if (global_mode == 2) next_index += 1;  //MODE_ARPEGIO
	      else if (global_mode == 4) //MODE_ARPEGIO_RAND
		{
		  unsigned int next_index_tamp = next_index;
		  while (next_index_tamp == next_index || notes_arp[next_index_tamp] == notes_arp[next_index])    next_index_tamp = random(0, N_note_arp);
		  next_index = next_index_tamp;
		}


	      if (next_index == N_note_arp) next_index = 0; //rollback

	      if (next_index == 0) next_duration = duration_scaling  + times_arp[0] - times_arp[N_note_arp - 1]; //rollback
	      else next_duration = times_arp[next_index] - times_arp[next_index - 1];


	      next_silent_time = next_event_time + (( (unsigned long) (duration * next_duration * sustain_scaling)) >> 7);
	      next_event_time += duration * next_duration ;


	      //return true;
      
	    }
	  if (millis() >= next_silent_time) for (byte i=0;i<POLYPHONY;i++) note[i]= 0; //next_note = 0;  // if needed to shut down the note before the end
    
	}  // if (manager->get_note()[0] !=0)

      else {
	previous_note = 0;
	for (byte i=0;i<POLYPHONY;i++) note[i]= 0;
      }
      //return false;  // arp not started
    }

}


/*
  int ArpegioMono::next()
  {
  return next_note;
  }

  int ArpegioMono::previous()
  {
  return previous_note;
  }*/

void ArpegioMono::start()
{
  start_time = millis();
  next_index = 0;
  next_event_time = start_time;
  started = true;
  //paused = false;
}

void ArpegioMono::stop()
{
  armed = false;
  started = false;
}

void ArpegioMono::pause() // have all conditions to play (trigger and notes) but is prevented (to make room to another one.
{
  started = false;
  paused = true;
}

void ArpegioMono::unpause()
{
  //if (armed) started = true;
  paused = false;
}

bool ArpegioMono::is_started()
{
  return started;
}

bool ArpegioMono::is_armed()
{
  return armed;
}

void ArpegioMono::arm()
{
  armed = true;
  armed_time = millis();
}


int ArpegioMono::get_duration_scaling()
{
  return duration_scaling;
}

unsigned int ArpegioMono::get_N_notes()
{
  return N_note_arp;
}

int * ArpegioMono::get_notes()
{
  return notes_arp;
}

void ArpegioMono::set_sustain_scaling(int _sustain_scaling)
{
  sustain_scaling = _sustain_scaling;
}
