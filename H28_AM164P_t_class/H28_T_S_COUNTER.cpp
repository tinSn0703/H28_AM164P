
#ifndef _H28_T_S_COUNTER_CPP_
#define _H28_T_S_COUNTER_CPP_ 1

struct S_COUNTER
//タイマを秒数以上にカウントするようの構造体。
//あのカチカチ数を数える奴みたいな感じに使ってね
//05 07 ver0.0.0
{
	private:
	T_COUNT _mem_counter_count;		//カウントの回数
	E_LOGIC _mem_counter_flag :1;	//カウント完了のFlag
	T_VALUE _mem_counter_limit;		//カウントの上限
	
	public:
	S_COUNTER()	{}	
	S_COUNTER(T_VALUE ,T_COUNT ,E_LOGIC );
	
	E_LOGIC Ret_flag()	{	return _mem_counter_flag;	}
	T_COUNT Ret_count()	{	return _mem_counter_count;	}
	T_VALUE Ret_limit()	{	return _mem_counter_limit;	}
	
	void Flag_up();
	void Flag_down();
	
	void Count();
	void Count_up();
	void Count_down();
	void Count_reset();	
	void Check_limit();
};

S_COUNTER::S_COUNTER(T_VALUE _arg_limit,T_COUNT _arg_count = 0,E_LOGIC _arg_flag = FALES)
{
	_mem_counter_count = _arg_count;
	_mem_counter_flag  = _arg_flag;
	_mem_counter_limit = _arg_limit;
}

inline void S_COUNTER::Flag_up()
{
	_mem_counter_flag = TRUE;
}

inline void S_COUNTER::Flag_down()
{
	_mem_counter_flag = FALES;
}

inline void S_COUNTER::Count()
{
	if(_mem_counter_flag == TRUE)
	{
		_mem_counter_count ++;
		
		if(_mem_counter_count == _mem_counter_limit)
		{
			Count_reset();
		}
	}
}

inline void S_COUNTER::Count_up()
{
	_mem_counter_count ++;
}
	
inline void S_COUNTER::Count_down()
{
	_mem_counter_count --;
}

inline void S_COUNTER::Check_limit()
{
	if(_mem_counter_flag == TRUE)
	{
		if(_mem_counter_count == _mem_counter_limit)
		{
			Count_reset();
		}
	}
}

void S_COUNTER::Count_reset()
{
	_mem_counter_count = 0;
	_mem_counter_flag = FALES;
}

#endif