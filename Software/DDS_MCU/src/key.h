#ifndef SRC_KEY_H_
#define SRC_KEY_H_

#include "BUS_FPGA.h"
#include "lcd_serial.h"
//#include "uart.h"

#define KEY_BASE CS0
unsigned char data;
unsigned char key_value;
unsigned char read_key()
{
    data = IORD(CS0,0);
    switch(data)
    {
        case 0x11:
            key_value = 1;
            break;
        case 0x12:
            key_value = 2;
            break;
        case 0x14:
            key_value = 3;
            break;
        case 0x18:
            key_value = 4;
            break;
        case 0x21:
            key_value = 5;
            break;
        case 0x22:
            key_value = 6;
            break;
        case 0x24:
            key_value = 7;
            break;
        case 0x28:
            key_value = 8;
            break;
        case 0x41:
            key_value = 9;
            break;
        case 0x42:
            key_value = 10;
            break;
        case 0x44:
            key_value = 11;
            break;
        case 0x48:
            key_value = 12;
            break;
        case 0x81:
            key_value = 13;
            break;
        case 0x82:
            key_value = 14;
            break;
        case 0x84:
            key_value = 15;
            break;
        case 0x88:
            key_value = 16;
            break;
        default: key_value = 0;
    }
    return key_value;
}
void KEY4x4_ISR()
{
  unsigned int keyvalue=IORD(KEY_BASE,0);
  switch(keyvalue)
  {
  case 0x11:
	//  uart_TxSting("hello world!");
	  DispString57At(5,50,"0x11");
    break;
  case 0x12:
	//  uart_TxDec(4530,4);
	  DispString57At(5,50,"0x12");
    break;
  case 0x14:
	//  uart_TxHex(0xaa551,5);
	  DispString57At(5,50,"0x14");
    break;
  case 0x18:
	//  uart_TxFloat(23.456,2,3);
	  DispString57At(5,50,"0x18");
    break;
  case 0x21:
	  DispString57At(5,50,"0x21");
    break;
  case 0x22:
	  DispString57At(5,50,"0x22");
    break;
  case 0x24:
	  DispString57At(5,50,"0x24");
    break;
  case 0x28:
	  DispString57At(5,50,"0x28");
    break;
  case 0x41:
	  DispString57At(5,50,"0x41");
    break;
  case 0x42:
	  DispString57At(5,50,"0x42");
    break;
  case 0x44:
	  DispString57At(5,50,"0x44");
    break;
  case 0x48:
	  DispString57At(5,50,"0x48");
    break;
  case 0x81:
	  DispString57At(5,50,"0x81");
    break;
  case 0x82:
	  DispString57At(5,50,"0x82");
    break;
  case 0x84:
	  DispString57At(5,50,"0x84");
    break;
  case 0x88:
	  DispString57At(5,50,"0x88");
    break;
  default:;
  }
}

#endif
