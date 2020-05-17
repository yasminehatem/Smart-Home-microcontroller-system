/*
 * DIO.h
 *	This driver is for --> ATMEGA 8/16/328p <--
 *  Author: pixels
 */ 


#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

#define HIGH	0xFF
#define LOW		0x00
#define OUTPUT	0xFF
#define INPUT	0x00


#define PB 0x01    // 3shan sa3at l switch case fl C msh bt2ra 3'er arkam aw character wa7d -et2kdy mnha brdo-
#define PC 0x02
#define PD 0x03

void DIO_InitPortDirection(uint8_t PortName,uint8_t PortDirection,uint8_t PortMask);
void DIO_WritePort(uint8_t PortName,uint8_t PortData,uint8_t PortMask);
uint8_t DIO_ReadPort(uint8_t PortName,uint8_t PortMAsk);



#endif /* DIO_H_ */