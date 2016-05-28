//----------------------------------------------------------------//
//							GameTimer.h							  //		
//																  //
//			About 	タイマークラスのヘッダー　			　　	　//
//     	    Last Update  2015/07/25								　//
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




//-----------------------------
//GameTimerクラス
//-----------------------------
namespace Gaia
{
	namespace Utility
	{

		class Timer
		{
		public:
			static const UINT SECOND = 1000000;		//1秒単位

		private:
			static LARGE_INTEGER s_Frequency;	//タイマ―周波数

			LARGE_INTEGER m_Count;				//カウンタ


		public:

			//--------コンストラクタ-------//
			Timer();

			//--------デストラクタ-------//
			~Timer() = default;

			//時間のリセット
			void Reset();


			//--------アクセッサ-------//

			//時間の取得
			UINT GetTime() const;	
		};
	}//namespace Utility
}//namespace Gaia
