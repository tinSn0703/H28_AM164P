
#pragma once

#include "H28_AM164P.h"

typedef unsigned char T_PORT;

enum E_IO_PORT_ADDR
{
	EI_PORTA = 0x00,
	EI_PORTB = 0x03,
	EI_PORTC = 0x06,
	EI_PORTD = 0x09,
};

enum E_IO_NUM
{
	EI_IO0 = 0,
	EI_IO1 = 1,
	EI_IO2 = 2,
	EI_IO3 = 3,
	EI_IO4 = 4,
	EI_IO5 = 5,
	EI_IO6 = 6,
	EI_IO7 = 7,	
};

enum E_AD_NUM
{
	EA_AD0,
	EA_AD1,
	EA_AD2,
	EA_AD3,
	EA_AD4,
	EA_AD5,
	EA_AD6,
	EA_AD7,
};

#define AD_ERROR 0xffff

enum E_IO_MODE
{
	EI_IN  = 0,
	EI_OUT = 1,
};

#include "H28_AM164P_i_class/H28_AM164P_i_class.h"