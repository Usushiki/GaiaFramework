//----------------------------------------------------------------//
//						 DebugDefine.hpp						  //		
//																  //
//			About 		デバッグ定数ヘッダー			　　　	　//
//     	    Last Update  2016/05/26								　//
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//

//-----------------------------
//多重インクルード防止
//-----------------------------
#pragma once


//-----------------------------
//ヘッダファイルのインクルード
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

