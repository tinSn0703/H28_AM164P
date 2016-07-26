
/*
AD変換を行うクラス。ポテンジョンメータの値を読むことができる。
 H28 05 10 ver0.0.0
 H28 05 21 ver0.0.1   IOポートの設定を前の逆にした
 H28 05 21 ver0.0.2   メンバ変数の名前の変更
 H28 05 21 ver1.0.0   ADMUXのリセットがうまくいっておらず、複数個用いる場合のAD変換の値が共有されてしまうバグを解消した。
					あと割り込み処理を設定できないようにした。
 H28 05 22 ver2.0.0   メンバ変数をカプセル化した。
*/

#pragma once

#include "H28_AM164P_i_class.h"

class C_AD
{	
	private:
	union U_AD_MUX
	{
		struct S_AD_MUX
		{
			BOOL mux0 :1;
			BOOL mux1 :1;
			BOOL mux2 :1;
			BOOL mux3 :1;
			BOOL mux4 :1;
		};
		
		S_AD_MUX mux_bit;
		E_AD_NUM mux_admux :5;
	};
	
	U_AD_MUX _mem_ad_num;
	
	protected:	
	BOOL Ret_mux0()		{	return _mem_ad_num.mux_bit.mux0;	}
	BOOL Ret_mux1()		{	return _mem_ad_num.mux_bit.mux1;	}
	BOOL Ret_mux2()		{	return _mem_ad_num.mux_bit.mux2;	}
	BOOL Ret_mux3()		{	return _mem_ad_num.mux_bit.mux3;	}
	BOOL Ret_mux4()		{	return _mem_ad_num.mux_bit.mux4;	}
	E_AD_NUM Ret_admux()	{	return _mem_ad_num.mux_admux;		}
	
	void Set_num(E_AD_NUM );
	
	void Set_first();
	void Set(E_AD_NUM ,BOOL );
	
	public:
	C_AD()	{}
	C_AD(E_AD_NUM ,BOOL );

	usint Do();
};

//protected
inline void C_AD::Set_num(E_AD_NUM _arg_ad_num)
{
	_mem_ad_num.mux_admux = _arg_ad_num;
}

inline void C_AD::Set_first()
{
	static BOOL _static_ad_first = FALES;
	
	if (_static_ad_first == FALES)
	{
		ADMUX  = (1<<REFS0);
		ADCSRA = ((1 << ADEN) | (1 << ADPS1) | (1 << ADPS0));
		ADCSRB = 0;
		DIDR0  = 0;
		
		_static_ad_first = TRUE;
	}
}

inline void C_AD::Set(E_AD_NUM _arg_ad_num, BOOL _arg_ad_io_turn = TRUE)
{
	Set_first();
	
	Set_num(_arg_ad_num);
	
	switch (_arg_ad_io_turn)
	{
		case TRUE:
		{
			DDRA  &= ~(1 << Ret_admux());
			PORTA |=  (1 << Ret_admux());
			
			break;
		}
		case FALES:
		{
			DDRA  |=  (1 << Ret_admux());
			PORTA &= ~(1 << Ret_admux());
			
			break;
		}
	}

	DIDR0 |= (1 << Ret_admux());
}

//public
inline C_AD::C_AD(E_AD_NUM _arg_ad_num, BOOL _arg_ad_io_turn = TRUE)
{	
	Set(_arg_ad_num, _arg_ad_io_turn);
}

inline usint C_AD::Do()
{	
	ADMUX += Ret_admux();
	
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1<<ADSC));
	
	usint _ret_data = ADCL;
	_ret_data |= (ADCH << 8);
	
	ADMUX  = (1<<REFS0);
	ADCSRB = 0;
	
	return _ret_data;
}