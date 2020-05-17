/*
 *  DIO.c
 *
 *  Author: pixels
 */

#include "DIO.h"
#include <avr/io.h>
// write a macro to write a register with a certain value on specific bits locations
#define WRITE_REG(Reg,Value,Mask) Reg&=~(Mask); Reg|=(Value & Mask) 
/* sfrt l bit l hshtghl 3lha
  lw 3yz a7ot 1 f pin 3 yb2a pin3 portb hya l mask (00000100) yb2a l value hya wa7d yb2a reg hya l portb
*/


//read a maco to read specific bits from a register
#define READ_REG(Reg,Mask) Reg & Mask


void DIO_InitPortDirection(uint8_t PortName,uint8_t PortDirection,uint8_t PortMask)
{
	//check the required port, specified bits and direction on the Data Direction Register
	switch(PortName)
	{
		case PB:
		{
			WRITE_REG(DDRB,PortDirection,PortMask); 
		}
		break;
		case PC:
		{
			WRITE_REG(DDRC,PortDirection,PortMask);
		}
		break;
		case PD:
		{
			WRITE_REG(DDRD,PortDirection,PortMask);
		}
		break;
	}	
}
void DIO_WritePort(uint8_t PortName,uint8_t PortData,uint8_t PortMask)
{
	//check the required port, specified bits and value on the Port Data Register
	switch(PortName)
	{
		case PB:
		{
			WRITE_REG(PORTB,PortData,PortMask);// portmask amkn l pins l hktb feh
		}
		break;
		case PC:
		{
			WRITE_REG(PORTC,PortData,PortMask);
		}
		break;
		case PD:
		{
			WRITE_REG(PORTD,PortData,PortMask);
		}
		break;
	}	
}
uint8_t DIO_ReadPort(uint8_t PortName,uint8_t PortMAsk)
{
	//check the required port, specified bits and value from the Port input Register
	uint8_t Data;
	switch(PortName)
	{
		case PB:
		{
			Data = READ_REG(PINB,PortMAsk);
		}
		break;
		case PC:
		{
			Data = READ_REG(PINC,PortMAsk);
		}
														break;
		case PD:
		{
		break;
	}
	return Data;
			Data = READ_REG(PIND,PortMAsk);
		}
}