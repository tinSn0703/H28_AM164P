
/*
INのみ可能なIO系のクラス
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_baseのメンバの一部を映した
 H28 05 22 ver1.0.0 C_IO_baseのバージョンアップへの対応
*/

#pragma once

#include "H28_I_C_IO_base.cpp"

class C_IO_IN : public virtual C_IO_base
{
	protected:
	void Set(E_IO_PORT_ADDR ,T_PORT );
	
	public:
	C_IO_IN(){}
	C_IO_IN(E_IO_PORT_ADDR ,E_IO_NUM );
	C_IO_IN(E_IO_PORT_ADDR ,T_PORT );

	T_PORT In();
	BOOL In_num(E_IO_NUM );
	
	T_PORT In_turn();
	BOOL In_turn_num(E_IO_NUM );
};

//protected
inline void C_IO_IN::Set(E_IO_PORT_ADDR _arg_io_in_addr, T_PORT _arg_io_in_num_byte)
{
	C_IO_base::Set_base(_arg_io_in_addr, EI_IN, _arg_io_in_num_byte);
}

//public
C_IO_IN::C_IO_IN(E_IO_PORT_ADDR _arg_io_in_addr, E_IO_NUM _arg_io_in_num_bit)
{
	Set(_arg_io_in_addr, (1 << _arg_io_in_num_bit));
}

C_IO_IN::C_IO_IN(E_IO_PORT_ADDR _arg_io_in_addr, T_PORT _arg_io_in_num_byte)
{
	Set(_arg_io_in_addr, _arg_io_in_num_byte);
}

inline T_PORT C_IO_IN::In()
{
	return (T_PORT)PIN;
}

inline BOOL C_IO_IN::In_num(E_IO_NUM _arg_io_in_num_bit)
{
	return CHECK_BIT_TF(PIN, _arg_io_in_num_bit);
}

inline T_PORT C_IO_IN::In_turn()
{
	return (T_PORT)(~PIN);
}

inline BOOL C_IO_IN::In_turn_num(E_IO_NUM _arg_io_in_num_bit)
{
	return CHECK_BIT_TF(~PIN, _arg_io_in_num_bit);
}