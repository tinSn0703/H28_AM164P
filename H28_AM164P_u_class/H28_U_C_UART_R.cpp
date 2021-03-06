﻿
/*
受信のみ可能なUART系列のクラス
 H28 05 13 ver 0.0.0
 H28 05 16 ver 0.1.0 継承でC_TIMER_insideをとっつけて,class内部のカウントをこいつで行うようにした。
 H28 05 23 ver 0.2.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART_base.cpp"

class C_UART_R : public virtual C_UART_base , public C_TIMER_inside
{
	private:
	E_UART_FLAG _mem_uart_r_flag_in :2; //最後の受信状態の記録
	
	protected:	
	void Set(E_UART_ADDR ,BOOL );
	
	public:
	C_UART_R() {}
	C_UART_R(E_UART_ADDR ,BOOL );
	
	void Set_isr(BOOL );
	void Check();
	T_DATA In();

	E_UART_FLAG Ret_flag()	{	return _mem_uart_r_flag_in;	}
		
	friend void operator >> (C_UART_R &, T_DATA &);
};

//protevted
inline void 
C_UART_R::
Set
(
	E_UART_ADDR _arg_uart_r_addr, 
	BOOL _arg_uart_r_nf_isr
)
/*
コンストラクタの中身みたいなもの。中身をまるっとコンストラクタに移してもいいかもしれない

	_arg_uart_r_addr : UARTの番号
	_arg_uart_r_nf_isr : 割り込み処理のONOFF
*/
{
	Set_base(_arg_uart_r_addr,EU_REC);
	
	Set_isr(_arg_uart_r_nf_isr);
	
	C_TIMER_inside::Set(80);
	
	_mem_uart_r_flag_in = EU_NONE;
	
	UCSRB |= (1 << RXEN); //受信許可
}

//public
inline 
C_UART_R::
C_UART_R
(
	E_UART_ADDR _arg_uart_r_addr, 
	BOOL _arg_uart_r_nf_isr = FALES
)
/*
	_arg_uart_r_addr : UARTの番号
	_arg_uart_r_nf_isr : 割り込み処理のONOFF
*/
{	
	Set(_arg_uart_r_addr,_arg_uart_r_nf_isr);
}

inline void C_UART_R::Set_isr(BOOL _arg_uart_r_nf_isr)
{
	switch (_arg_uart_r_nf_isr)
	{
		case TRUE:	UCSRB |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB &= ~(1 << RXCIE);	break; //Off
	}
}

void C_UART_R::Check()
{	
	UCSRB |= (1 << RXEN); //受信許可
	
	C_TIMER_inside::Start();
	
	while (1)
	{
		if ((C_TIMER_inside::Ret_flag() & CHECK_BIT_TF(UCSRA,RXC)) == TRUE)	//受信完了
		{
			C_TIMER_inside::End();
			
			_mem_uart_r_flag_in = EU_SUCCE;
			break;
		}
		
		if (C_TIMER_inside::Check() == TRUE)	//カウント完了(タイムアウト)
		{
			_mem_uart_r_flag_in = EU_ERROR;
			break;
		}
	}
}

T_DATA C_UART_R::In()
{
	Check(); //受信チェック
	
	if (_mem_uart_r_flag_in == EU_ERROR)	return IN_ERROR;
	
	T_DATA _ret_data = 0;
		
	if (UCSRB & ((1<<UCSZ2) | (1<<RXB8)))	_ret_data = (1 << 8);	//9bit通信時
	
	_ret_data |= UDR;
	
	_mem_uart_r_flag_in = EU_NONE;
	
	return _ret_data;
}

void 
operator >>
(
	C_UART_R &_arg_uart_r,
	T_DATA &_arg_uart_r_in_data
)
{
	_arg_uart_r_in_data = _arg_uart_r.In();
}