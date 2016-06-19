
/*
複数のPORTにまたがったり、pin数を変えたりしてIOピンの設定ができる。
 H28 05 09 ver0.0.0
*/

#ifndef _H28_I_C_IO_PIN_CPP_
#define _H28_I_C_IO_PIN_CPP_ 1

class C_IO_pin : public C_IO_base
{
	private:
	E_NUM_PORT _mem_io_pin_addr[16];
	E_NUM_IO   _mem_io_pin_bit[16];
	E_MODE_IO _mem_io_pin_mode :1;
	T_NUM _mem_io_pin_num :8;
	
	public:
	C_IO_pin(T_NUM ,E_MODE_IO );
	
	void Set(T_NUM ,E_NUM_PORT ,E_NUM_IO );
	
	void Out(T_NUM );
	void Out_num(T_NUM ,E_LOGIC );
	
	T_NUM In();
	E_LOGIC In_num(T_NUM );
	
	T_NUM Ret_pin_num();
};

C_IO_pin::C_IO_pin(T_NUM _arg_io_pin_num,E_MODE_IO _arg_io_pin_mode)
{
	_mem_io_pin_num = _arg_io_pin_num;
	_mem_io_pin_mode = _arg_io_pin_mode;
}

void C_IO_pin::Set(T_NUM _arg_io_pin_num,E_NUM_PORT _arg_io_pin_addr,E_NUM_IO _arg_io_pin_bit)
{	
	_mem_io_pin_addr[_arg_io_pin_num] = _arg_io_pin_addr;
	_mem_io_pin_bit[_arg_io_pin_num] = _arg_io_pin_bit;
	
	C_IO_base::Set_base_addr(_arg_io_pin_addr);
	
	if (_mem_io_pin_mode == EM_IN)
	{
		DDR  &= ~(1 << _arg_io_pin_bit);
		PORT |=  (1 << _arg_io_pin_bit);
	}
	else
	{
		DDR  |=  (1 << _arg_io_pin_bit);
		PORT &= ~(1 << _arg_io_pin_bit);
	}
}

void C_IO_pin::Out(T_NUM _arg_io_pin_out_data)
{
	for (T_NUM i = 0; i < _mem_io_pin_num; i++)
	{
		Out_num(i, CHECK_BIT_TF(_arg_io_pin_out_data,i));
	}
}

inline void C_IO_pin::Out_num(T_NUM _arg_io_pin_out_bit,E_LOGIC _arg_io_pin_nf_out)
{
	C_IO_base::Set_base_addr(_mem_io_pin_addr[_arg_io_pin_out_bit]);
	
	if (_arg_io_pin_nf_out == TRUE)
	{
		PORT |=  (1 << _mem_io_pin_bit[_arg_io_pin_out_bit]);
	}
	else
	{
		PORT &= ~(1 << _mem_io_pin_bit[_arg_io_pin_out_bit]);
	}
}

T_NUM C_IO_pin::In()
{
	T_NUM _ret_io_pin_in_data = 0;
	
	for (T_NUM i = 0; i< _mem_io_pin_num; i++)
	{
		_ret_io_pin_in_data |= (In_num(i) << i);
	}
	
	return _ret_io_pin_in_data;
}

inline E_LOGIC C_IO_pin::In_num(T_NUM _arg_io_pin_in_bit)
{
	C_IO_base::Set_base_addr(_mem_io_pin_addr[_arg_io_pin_in_bit]);
	
	return CHECK_BIT_TF(PIN,_mem_io_pin_bit[_arg_io_pin_in_bit]);
}

inline T_NUM C_IO_pin::Ret_pin_num()
{
	return _mem_io_pin_num;
}

#endif