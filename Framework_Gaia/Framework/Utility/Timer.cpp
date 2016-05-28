//----------------------------------------------------------------//
//							Timer.cpp							　//		
//																  //
//			  About 	タイマークラスのソース					　//
//     	  		    Last Update  2016/05/12 22:33				  //
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//

// 多重インクルード防止 ===================================================
#pragma once



//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include"Timer.hpp"


namespace Gaia
{
	namespace Utility
	{

		//静的メンバ変数の実体
		LARGE_INTEGER Timer::s_Frequency = { 0 };



		//-----------------------------
		//!@brief　コンストラクタ
		//-----------------------------
		Timer::Timer()
		{

			if (s_Frequency.QuadPart == 0)
			{
				//CPU周波数の取得
				QueryPerformanceFrequency(&s_Frequency);
			}

			//計測開始カウントを設定
			QueryPerformanceCounter(&m_Count);

		}


		//--------------------------------------------------------------
		//!@brief				時間[ns]の取得							
		//																
		//!@param[in]	なし											
		//																
		//!@retval 		計測開始時点からのもとめた現在時間[ns]			
		//--------------------------------------------------------------
		UINT Timer::GetTime()const
		{
			LARGE_INTEGER currentTime;

			//現在のパフォーマンスカウンタを取得
			QueryPerformanceCounter(&currentTime);


			//カウンタの差分を求める
			LONGLONG calcTime = currentTime.QuadPart - m_Count.QuadPart;


			//差分を周波数で割り処理時間を算出
			return static_cast<UINT>(calcTime*SECOND / s_Frequency.QuadPart);
		}


		//----------------------------------------------------------
		//!@brief	    カウンタのリセット							
		//															
		//!@param[in]	なし										
		//															
		//!@retval		なし										
		//----------------------------------------------------------
		void Timer::Reset()
		{
			QueryPerformanceCounter(&m_Count);
		}
	
	}//namespace Utility
}//namespace Gaia