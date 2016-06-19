
#ifndef _H28_U_C_UART_R_M_CPP_
#define _H28_U_C_UART_R_M_CPP_ 1

#include "H28_U_C_UART_base.cpp"

class C_UART_R_M : protected virtual C_UART_base
{	
	protected:
	void Set(E_UART_ADDR ,E_LOGIC );
	
	public:
	C_UART_R_M() {}
	C_UART_R_M(E_UART_ADDR ,E_LOGIC );
	
	void Set_isr(E_LOGIC );
	uchar In();
};

//protevted
inline void C_UART_R_M::Set(E_UART_ADDR _arg_uart_r_addr, E_LOGIC _arg_uart_r_nf_isr)
{
	Set_base(_arg_uart_r_addr,EU_REC);
	
	Set_isr(_arg_uart_r_nf_isr);
	
	UCSRB |= (1 << RXEN); //受信許可
}

//public
inline C_UART_R_M::C_UART_R_M(E_UART_ADDR _arg_uart_r_addr, E_LOGIC _arg_uart_r_nf_isr = FALES)
{
	Set(_arg_uart_r_addr,_arg_uart_r_nf_isr);
}

inline void C_UART_R_M::Set_isr(E_LOGIC _arg_uart_r_nf_isr)
{
	switch (_arg_uart_r_nf_isr)
	{
		case TRUE:	UCSRB |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB &= ~(1 << RXCIE);	break; //Off
	}
}

inline uchar C_UART_R_M::In()
{		
	while (!(UCSRA & (1<<RXC)));
	
	uchar _ret_data = UDR;
	
	return _ret_data;
}

#endif