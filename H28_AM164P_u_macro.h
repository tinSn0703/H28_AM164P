
#ifndef _H28_AM164P_U_MACRO_H_
#define _H28_AM164P_U_MACRO_H_ 1

#ifndef _H28_AM164P_H_
#error "Include <H28_AM164P.h>"
#endif

/*UART*/
typedef unsigned short int T_DATA;

#define IN_ERROR 0xfff 
//このマクロは12bit以上ないと使えないから気を付けろよ。by H28 May 13のSn

enum E_UART_FLAG
{
	EU_NONE,
	EU_SUCCE,
	EU_ERROR,
};

//USART NUMBER SET COMAND
enum E_UART_ADDR
{
	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,
};

//USART MODE SET COMAND
enum E_UART_MODE
{
	EU_TRA, //trancmit mode
	EU_REC, //receive  mode
};

/************************************************************************/
#include "H28_AM164P_u_class/H28_AM164P_u_class.h"
#include "H28_AM164P_u_class/H28_AM164P_u_func.h"
/************************************************************************/

#endif /*_H28_AM640_U_MACRO_H_*/