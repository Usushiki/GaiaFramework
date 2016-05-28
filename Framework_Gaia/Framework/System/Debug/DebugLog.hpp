//----------------------------------------------------------------//
//					      DebugLog.hpp							　//		
//																  //
//			About   出力ウィンドウへのログを表示			　　　//
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
#include"DebugDefine.hpp"

#include<Windows.h>
#include<sstream>


#ifdef GAIA_DEBUG

#include<crtdbg.h>


#endif // DEBUG 


#define DebugLogFileLine(...)DebugProcess(Debug::Log(__VA_ARGS__,__FILE__,__LINE__) )
#define DebugLog(LOG_TYPE,...)DebugProcess(Debug::Log(LOG_TYPE,__VA_ARGS__))
//#define DebugLog(...)DebugProcess(Debug::Log(__VA_ARGS__))
#define STR(var) #var


//-----------------------------
//DebugLogクラス
//-----------------------------

namespace Gaia 
{
	namespace Debug
	{
	/*	template<typename T, template...Args>
		inline void Log(const T& message, const Args&... args)
		{
#ifdef GAIA_DEBUG
			std::wstringstream wss;
			wss << message;

			Log(wss, args...);
#endif
		}*/


		template<typename T,typename... Args>
		inline void Log(LOG_TYPE type,const T& message,const Args&... args)
		{
#ifdef GAIA_DEBUG
		
		
			std::wstringstream wss;
	
			wss << STR(type);

			wss << "  ";
			wss << message;
			
			
			Log(wss,args...);
#endif
		}

		

		template<typename T,typename... Args>
		inline void Log(std::wstringstream& wss,const T& message, const Args&... args)
		{
#ifdef GAIA_DEBUG
			wss << message;
			wss << "  ";
			Log(wss, args...);
#endif
		}


	
		inline void Log(std::wstringstream& wss)
		{
#ifdef GAIA_DEBUG
			wss << "  ";
			wss << L'\n';

			OutputDebugString(wss.str().c_str());
#endif
		}

	}
	
}