#ifndef _read_shift_
#define _read_shift_



/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the the shift registers
*/


/*

#define NUMBER_OF_SHIFT_CHIPS   3

#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

// Width of pulse to trigger the shift register to read and latch.





int ploadPin        = 7;  // Connects to Parallel load pin the 165
int clockEnablePin  = 9;  // Connects to Clock Enable pin the 165
int dataPin         = 8; // Connects to the Q7 pin the 165
int clockPin        = 14; // Connects to the Clock pin the 165

unsigned int read_shift_regs();
*/


//#define POLYPHONY 12


#define PULSE_WIDTH_USEC   3
class TouchRead
{
 public:
  TouchRead(int _ploadPin, int _clockEnablePin, int _dataPin, int _clockPin, byte _nChip)
    {
      ploadPin = _ploadPin;
      clockEnablePin = _clockEnablePin;
      dataPin = _dataPin;
      clockPin = _clockPin;
      DATA_WIDTH = _nChip*3;
      pinMode(ploadPin, OUTPUT);
      pinMode(clockEnablePin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, INPUT);
    }
  
  unsigned int read_shift_regs(){

    long bitVal;
  unsigned int bytesVal = 0;

  /* Trigger a parallel Load to latch the state of the data lines,
  */
  digitalWrite(clockEnablePin, HIGH);  // can I remove that ?
  digitalWrite(ploadPin, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(ploadPin, HIGH);
  digitalWrite(clockEnablePin, LOW);  // and that? Yes, put to GND all the time should work

  /* Loop to read each bit value from the serial out line
     of the SN74HC165N.
  */
  for (int i = 0; i < DATA_WIDTH; i++)
  {
    bitVal = digitalRead(dataPin);
    bytesVal |= (bitVal << ((DATA_WIDTH - 1) - i));

    /* Pulse the Clock (rising edge shifts the next bit).
    */
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(clockPin, LOW);
  }
  return (bytesVal);
  }
  
 private:
  int ploadPin, clockEnablePin, dataPin, clockPin;
  int DATA_WIDTH;
};

#endif
