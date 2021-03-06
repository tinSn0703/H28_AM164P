﻿
/*
カウント程度はできる。機能的にはStopWatchのようなもの
 H28 05 10 ver 0.0.0
 H28 05 20 ver 0.1.0 C_TIMER_baseのコンストラクタでコンストラクタの設定をすることにした.
 H28 05 20 ver 1.0.0 C_TOMER_baseに設定用の関数と変数を移し、動作系の関数の中身を持ってきた
*/

#pragma once

#include "H28_T_C_TIMER_base.cpp"

class C_TIMER : public virtual C_TIMER_base
{	
	protected:
	void Set(E_TIMER_MODE , BOOL );
	void Set(E_TIMER_MODE ,E_CLOCK ,T_VALUE ,BOOL );
	
	public:
	C_TIMER()	{}
	C_TIMER(E_TIMER_MODE , BOOL );
	C_TIMER(E_TIMER_MODE ,E_CLOCK ,T_VALUE ,BOOL );
	
	void Start();
	void Start(E_CLOCK ,T_VALUE );
	
	BOOL Flag_timer(BOOL );
	
	void Stop();
};

//protected
inline void C_TIMER::Set(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr = FALES)
{
	C_TIMER_base::Set_base(_arg_timer_mode, _arg_timer_nf_isr);
}

inline void C_TIMER::Set(E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, T_VALUE _arg_timer_counter, BOOL _arg_timer_nf_isr = FALES)
{
	C_TIMER_base::Set_base(_arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
}

//public
inline C_TIMER::C_TIMER(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr = FALES)
{
	Set(_arg_timer_mode, _arg_timer_nf_isr);
}

inline C_TIMER::C_TIMER(E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, T_VALUE _arg_timer_counter, BOOL _arg_timer_nf_isr = FALES)
{
	Set(_arg_timer_mode, _arg_timer_clock, _arg_timer_counter, _arg_timer_nf_isr);
}

inline void C_TIMER::Start()
{
	Stop();
	
	COUNTERH = ((C_TIMER_base::Ret_base_counter() >> 8) & 0xff);
	COUNTERL = (C_TIMER_base::Ret_base_counter() & 0xff);
	
	TCCR1B |= C_TIMER_base::Ret_base_clock();
}

inline void C_TIMER::Start(E_CLOCK _arg_timer_clock, T_VALUE _arg_timer_counter)
{
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
	
	Stop();
	
	COUNTERH = ((_arg_timer_counter >> 8) & 0xff);
	COUNTERL = (_arg_timer_counter & 0xff);
	
	TCCR1B |= _arg_timer_clock;
}

BOOL C_TIMER::Flag_timer(BOOL _arg_timer_continue = TRUE)
{
	usint mode_bit = 0;
	
	switch (C_TIMER_base::Ret_base_mode())
	{
		case ET_CAPUTER:	mode_bit = ICF;		break;
		case ET_COMPARE:	mode_bit = OCFA;	break;
		case ET_OVERFLOW:	mode_bit = TOV;		break;
	}
	
	if (CHECK_BIT_TF(TIFR1,mode_bit))
	{
		TIFR1 |= (1 << mode_bit);
		
		if (_arg_timer_continue)	Start();
		
		return TRUE;
	}
	
	return FALES;
}

inline void C_TIMER::Stop()
{
	TCCR1B &= ~TIME_SET_BIT;
}
