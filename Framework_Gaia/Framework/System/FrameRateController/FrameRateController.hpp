//----------------------------------------------------------------//
//					  FrameRateController.h						  //		
//																  //
//			About 	フレームレート管理クラスのヘッダー　　　	　//
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
#include<memory>
#include<Windows.h>
#include"../../Utility/Timer.hpp"


//-----------------------------
//FrameRateControllerクラス
//-----------------------------
namespace Gaia
{
	
		class FrameRateController
		{
			//初期設定フレームレート
			static const UINT S_FRAME_RATE_DEFAULT = 60;	
	
		public:

			//-----------------------------
			//!@brief コンストラクタ
			//-----------------------------
			FrameRateController(UINT FrameRate = S_FRAME_RATE_DEFAULT);

			//-----------------------------
			//!@brief デストラクタ
			//-----------------------------
			~FrameRateController();

			//--------アクセッサ-------//
			void SetFrameRate(UINT);
			double GetFrameRate() const;
			bool GetIsSkip() const;



			//計測の開始
			void Start();

			//フレームレートの調節
			void Regulate();


		private:

			//pImplイディオム
			class pImpl;
			std::unique_ptr<pImpl> m_pImpl;
		};
	
}