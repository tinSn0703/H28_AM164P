
#ifndef _H28_AM164P_U_FUNC_H_
#define _H28_AM164P_U_FUNC_H_ 1

#define UCSRA_F(_def_addr)	_SFR_MEM8(_def_addr + 0)
#define UCSRB_F(_def_addr)	_SFR_MEM8(_def_addr + 1)
#define UCSRC_F(_def_addr)	_SFR_MEM8(_def_addr + 2)
#define UBRRL_F(_def_addr)	_SFR_MEM8(_def_addr + 4)
#define UBRRH_F(_def_addr)	_SFR_MEM8(_def_addr + 5)
#define UDR_F(_def_addr)	_SFR_MEM8(_def_addr + 6)

/*bit UCSRA*/
#define RXC  7
#define TXC	 6
#define UDRE 5
#define FE	 4
#define DOR  3
#define UPE  2
#define U2X  1
#define MPCM 0

/*bit UCSRB*/
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN  4
#define TXEN  3
#define UCSZ2 2
#define RXB8  1
#define TXB8  0

/*bit UCSRC*/
#define UMSEL1 7
#define UMSEL0 6
#define UPM1   5
#define UPM0   4
#define USBS   3
#define UCSZ1  2
#define UCSZ0  1
#define UCPOL  0

void F_Set_uart(E_UART_ADDR _arg_uart_addr)
{
	UBRRH_F(_arg_uart_addr) = 0x00;
	UBRRL_F(_arg_uart_addr) = 0x04;
	//F_CPU=10MHz 250kbps
	
	UCSRA_F(_arg_uart_addr) = (1<<U2X);
	//Double teransmission spead
	
	UCSRB_F(_arg_uart_addr) &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//割り込み許可以外は全部OFF。おあとに設定してね
	
	UCSRC_F(_arg_uart_addr) = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
}

void F_Set_usrt_bit9(E_UART_ADDR _arg_uart_addr, E_LOGIC _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	UCSRB_F(_arg_uart_addr) |=  (1 << UCSZ2);	break; //On
		case FALES:	UCSRB_F(_arg_uart_addr) &= ~(1 << UCSZ2);	break; //Off
	}
}

void F_Set_uart_isr(E_UART_ADDR _arg_uart_addr, E_UART_MODE _arg_uart_mode, E_LOGIC _arg_uart_nf_isr)
{
	uchar _tenp_bit = 0;
	
	switch (_arg_uart_mode)
	{
		case EU_REC:	_tenp_bit = RXCIE;	break;
		case EU_TRA:	_tenp_bit = TXCIE;	break;
	}
	
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	UCSRB_F(_arg_uart_addr) |=  (1 << _tenp_bit);	break; //On
		case FALES:	UCSRB_F(_arg_uart_addr) &= ~(1 << _tenp_bit);	break; //Off
	}
}

template <class T>
void F_Out_uart(E_UART_ADDR _arg_uart_addr, T _arg_uart_out_data)
{	
	UCSRB_F(_arg_uart_addr) |= (1 << TXEN); //送信許可する。
	
	while (!(UCSRA_F(_arg_uart_addr) & (1 << UDRE))); //送信が可能になるまで待機
	
	if ((CHECK_BIT_TF(UCSRB_F(_arg_uart_addr),UCSZ2) & CHECK_BIT_TF(_arg_uart_out_data,8)) == TRUE)
	{
		UCSRB_F(_arg_uart_addr) |= (1 << TXB8);
	}

	UDR_F(_arg_uart_addr) = (_arg_uart_out_data & 0xff);
	
	while (!(UCSRA_F(_arg_uart_addr) & (1 << TXC))); //送信完了まで待機
	
	UCSRA_F(_arg_uart_addr) |= (1 << TXC);
}

template <class T>
T F_In_uart(E_UART_ADDR _arg_uart_addr)
{
	T _ret_data = 0;
	
	while(!(UCSRA_F(_arg_uart_addr) & (1 << RXC)));
	
	if (UCSRB_F(_arg_uart_addr) & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_data = (1 << 8);	//9bit通信時
	}
	
	_ret_data |= UDR_F(_arg_uart_addr);
	
	return _ret_data;
}

#endif