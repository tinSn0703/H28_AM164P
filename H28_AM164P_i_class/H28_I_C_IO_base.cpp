
/*
IOピン用クラスの基礎。宣言しないでね。
 H28 05 11 ver0.0.0
 H28 05 18 ver0.1.0 メンバを削減して派生先に移した
 H28 05 22 ver1.0.0 PORTH以降しか使えなかったバグを叩き潰したついでに抽象クラスにした。
 H28 05 22 ver1.0.1 抽象クラスの使い方がよくわからんかったからpublicのないクラスにした。宣言しても意味ないよ。
 H28 05 23 ver1.0.2 抽象クラスにした
 H28 05 23 ver1.0.3 やっぱりやめた
*/

#pragma once

#include "H28_AM164P_i_class.h"

class C_IO_base
{
	private:
	E_IO_PORT_ADDR _mem_io_base_addr :8;
	E_IO_MODE  _mem_io_base_mode :1;
	
	protected:
	void Set_base_addr(E_IO_PORT_ADDR );
	void Set_base_mode(E_IO_MODE );
	
	E_IO_PORT_ADDR Ret_base_addr()	{	return _mem_io_base_addr;	}
	E_IO_MODE Ret_base_mode()		{	return _mem_io_base_mode;	}
	
	#define	PIN  _SFR_IO8(Ret_base_addr() + 0)
	#define DDR  _SFR_IO8(Ret_base_addr() + 1)
	#define PORT _SFR_IO8(Ret_base_addr() + 2)
	
	void Set_base(E_IO_PORT_ADDR ,E_IO_MODE ,T_PORT );
	
	public:
	
	~C_IO_base()
	{
		switch (Ret_base_mode())
		{
			case EI_IN:	 DDR  &= ~DDR;	break;
			case EI_OUT: PORT &= ~PORT;	break;
		}
	}
};

//protected
inline void C_IO_base::Set_base_addr(E_IO_PORT_ADDR _arg_io_base_addr)
{
	_mem_io_base_addr = _arg_io_base_addr;
}

inline void C_IO_base::Set_base_mode(E_IO_MODE _arg_io_base_mode)
{
	_mem_io_base_mode = _arg_io_base_mode;
}

inline void C_IO_base::Set_base(E_IO_PORT_ADDR _arg_io_base_addr, E_IO_MODE _arg_io_base_mode, T_PORT _arg_io_base_num)
{	
	_mem_io_base_addr = _arg_io_base_addr;
	_mem_io_base_mode = _arg_io_base_mode;
	
	switch (_arg_io_base_mode)
	{
		case EI_OUT:
		{
			DDR  |=  _arg_io_base_num;
			PORT &= ~_arg_io_base_num;
			
			break;
		}
		case EI_IN:
		{
			DDR  &= ~_arg_io_base_num;
			PORT |=  _arg_io_base_num;
			
			break;
		}
	}
}