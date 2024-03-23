#ifndef _read_shift_
#define _read_shift_

#include<SPI.h>



/*
  Combriat 2018, 2019, 2020, 2024
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


  
  

enum SR_TYPE {SR_LEGACY, SR_SPI};



#define PULSE_WIDTH_USEC   3

class TouchRead
{
public:
  TouchRead(const int _ploadPin, const int _clockEnablePin, const int _dataPin, const int _clockPin, const byte _nChip): ploadPin(_ploadPin), clockEnablePin(_clockEnablePin), dataPin(_dataPin), clockPin(_clockPin), nChip(_nChip), type(SR_LEGACY)
  {
    DATA_WIDTH = nChip<<3;
    pinMode(ploadPin, OUTPUT);
    pinMode(clockEnablePin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, INPUT);
  }

  TouchRead(const int _ploadPin, SPIClass * _SPI, const byte _nChip): ploadPin(_ploadPin), TR_SPI(_SPI), nChip(_nChip), type(SR_SPI)
  {
    pinMode(ploadPin, OUTPUT);
  }
  
  unsigned int read_shift_regs(){

    
    long bitVal;
    unsigned int bytesVal = 0;

    switch (type){
    case SR_LEGACY: // Bit-banging

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
      break;

    case SR_SPI:  // native SPI

      digitalWrite(ploadPin, LOW);
      delayMicroseconds(PULSE_WIDTH_USEC);
      digitalWrite(ploadPin, HIGH);
      TR_SPI->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
      for (byte i=0;i<nChip;i++) bytesVal += TR_SPI->transfer(0)<<(i<<3);
      TR_SPI->endTransaction();
      break;
    }
    return (bytesVal);

    
  }
  
private:
  const int ploadPin, clockEnablePin=0, dataPin=0, clockPin=0;
  int DATA_WIDTH;
  const byte type;
  const byte nChip;
  SPIClass * TR_SPI=NULL;
};

#endif
