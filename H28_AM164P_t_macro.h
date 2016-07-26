
#pragma once

#include "H28_AM164P.h"

typedef float T_TIME;

/* MACRO TIMER ************************************************************/
enum E_TIMER_MODE
//�^�C�}�[�̃��[�h�B4bit
{
	ET_OVERFLOW = 4,/*���*/
	ET_CAPUTER  = 6,/*�ߊl*/
	ET_COMPARE  = 8,/*��r*/
};

enum E_CLOCK
//�N���b�N�B3bit
{
	EC_0    = 0x1,
	EC_8    = 0x2,
	EC_64   = 0x3,
	EC_256  = 0x4,
	EC_1024 = 0x5,
};

#include "H28_AM164P_t_class/H28_AM164P_t_class.h"
