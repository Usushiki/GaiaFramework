//----------------------------------------------------------------//
//						 DebugDefine.hpp						  //		
//																  //
//			About 		�f�o�b�O�萔�w�b�_�[			�@�@�@	�@//
//     	    Last Update  2016/05/26								�@//
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//

//-----------------------------
//���d�C���N���[�h�h�~
//-----------------------------
#pragma once


//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include<Windows.h>

#if defined(_DEBUG) || defined(DEBUG)

#define GAIA_DEBUG

#define DebugProcess(proc) do{proc;}while(0)

#endif

enum class LOG_TYPE
{
	TYPE_ERROR,
	TYPE_WARNING,
	TYPE_NORMAL,
};

