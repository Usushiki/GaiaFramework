//----------------------------------------------------------------//
//					       FrameRateController.cpp				　//		
//																  //
//				  About 	フレームレート管理クラスのソース	　//
//     	  		    Last Update  2015/07/25						  //
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
#include"FrameRateController.hpp"

namespace Gaia
{
	//----------------------------------------
	//!@brief FrameRateControllerクラスの実装の詳細
	//----------------------------------------
	class FrameRateController::pImpl
	{
		//メンバ変数
	public:
		std::unique_ptr<Utility::Timer> m_pTimer;		//タイマー
		double m_FrameRate;								//フレーム数
		UINT m_StartTime;								//計測開始時間[ns]
		UINT m_FrameTime;								//1フレーム当たり時間[ns]
		UINT m_ElapsedTime;								//経過時間[ns]
		UINT m_ElapsedTime_Total;						//総経過時間[ns]

		int m_FrameCount;								//フレームカウンター

		bool m_IsSkip;

	public:

		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		pImpl(UINT _FrameRate = S_FRAME_RATE_DEFAULT)
			:m_FrameRate(0)
			,m_StartTime(0)
			,m_FrameTime(0)
			, m_FrameCount(0)
			, m_ElapsedTime(0)
			, m_ElapsedTime_Total(0)
			, m_IsSkip(false)
			, m_pTimer(nullptr)
		{
			SetFrameRate(_FrameRate);
			m_pTimer = std::make_unique<Utility::Timer>();
		}

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~pImpl() = default;

	private:
		//-----------------------------
		//!@brief 更新
		//
		//!@param[in] なし
		//
		//!@retval なし
		//-----------------------------
		void Update()
		{
			//カウントアップ
			m_FrameCount++;

			//1フレームの経過時間を総経過時間に加算
			m_ElapsedTime_Total += m_ElapsedTime;

			//総経過時間が1秒を超えるなら
			if (m_ElapsedTime_Total >= m_pTimer->SECOND) {

				//1秒経過するまでのフレーム数を算出
				m_FrameRate = static_cast<double>(m_FrameRate*m_pTimer->SECOND) / m_ElapsedTime_Total;

				//カウンタと総経過時間をリセット
				m_FrameCount = 0;
				m_ElapsedTime_Total = 0;
			}

		}

	public:

		//-----------------------------
		//!@brief 計測開始
		//
		//!@param[in] なし
		//
		//!@retval なし
		//-----------------------------
		void Start()
		{
			m_pTimer->Reset();
			m_StartTime = m_pTimer->GetTime();

		}

		
		//-----------------------------
		//!@brief フレームレートの調整
		//
		//!@param[in] なし
		//
		//!@retval なし
		//-----------------------------
		void Regulate()
		{
			//1フレームの経過時間を算出
			m_ElapsedTime = m_pTimer->GetTime() - m_StartTime;


			//フレームレートの調節
			if (m_ElapsedTime < m_FrameTime)
			{
				m_IsSkip = false;

				//キューや高い競合状態のロックの確認の防止
				//現スレッドより高い優先度を持つスレッドが実行可能時、残りのタイムスライスを破棄
				Sleep(0);

				//スリープループ
				while (m_ElapsedTime < m_FrameTime)
				{
					//次の命令を遅らせる(プロセッサー固有時間)
					_mm_pause();

					//経過時間の更新
					m_ElapsedTime = m_pTimer->GetTime() - m_StartTime;
				}

			}
			else
				m_IsSkip = true;


			//更新
			Update();

			//フレーム開始時間の更新
			m_StartTime = m_pTimer->GetTime();

		}

		//-----------------------------
		//!@brief フレームレートの設定
		//
		//!@param[in] なし
		//
		//!@retval なし
		//-----------------------------
		void SetFrameRate(UINT _frameRate)
		{
			//1フレーム当たりの時間を計算
			m_FrameTime = m_pTimer->SECOND / _frameRate;
		}

	};
}

namespace Gaia
{
	using namespace Utility;

		//----------------------------------------------------------
		//!@brief		コンストラクタ								
		//															
		//!@param[in] framerate		初期フレームレート				
		//	
		//!@note   指定がない場合はデフォルト値の60をセット			
		//----------------------------------------------------------
		FrameRateController::FrameRateController(UINT framerate)
			:m_pImpl(std::make_unique<pImpl>(framerate))
		{
			
		}

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		FrameRateController::~FrameRateController()
		{

		}


		//---------------------------------------------------
		//!@brief		フレームレートの計測開始			
		//													
		//!@param[in]	なし								
		//													
		//!@retval  　 なし									
		//---------------------------------------------------
		void FrameRateController::Start()
		{
			m_pImpl->Start();
		}


		//---------------------------------------------------
		//!@brief		フレームレートの調節				
		//													
		//!@param[in]	なし								
		//													
		//!@retval  　  なし								
		//---------------------------------------------------
		void FrameRateController::Regulate()
		{
			m_pImpl->Regulate();
		}


		//---------------------------------------------------
		//!@brief			フレームレートの設定			
		//													
		//!@param[in]	 framerate  フレームレート			
		//													
		//!@retval  　　 なし								
		//---------------------------------------------------
		void FrameRateController::SetFrameRate(UINT framerate)
		{
			m_pImpl->SetFrameRate(framerate);
		}


		//---------------------------------------------------
		//!@brief		フレームレートの取得				
		//													
		//!@param[in]	なし								
		//													
		//!@retval   フレームレート							
		//---------------------------------------------------
		double FrameRateController::GetFrameRate() const
		{
			return m_pImpl->m_FrameRate;
		}


		//---------------------------------------------------
		//!@brief			スキップフラグの取得			
		//													
		//!@param[in]	なし								
		//													
		//!@retval  　フレームをスキップするかのフラグ		
		//---------------------------------------------------
		bool FrameRateController::GetIsSkip() const
		{
			return m_pImpl->m_IsSkip;
		}



	
}
