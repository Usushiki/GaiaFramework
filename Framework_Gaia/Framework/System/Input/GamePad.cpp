//------------------------------------------------//
//				ゲームパッドクラス				  //
//												  //
//												  //
//			2016. 5.19(Thu)19:43				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//


//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include"GamePad.hpp"


//-----------------------------
//ライブラリリンク
//-----------------------------
#pragma comment(lib, "Xinput9_1_0.lib")    // Xinput用ライブラリ


namespace Gaia
{

	//----------------------------------------
	//!@brief GamePadクラスの実装の詳細
	//----------------------------------------
	class GamePad :: pImpl
	{
	public:
	
		//ゲームパッド状態クラス
		struct GamePadState
		{
			bool         isConnected;    //!< 接続の有無
			XINPUT_STATE state;          //!< ゲームパッドの状態
		};


		//メンバ変数
		DWORD m_userIndex;				//!< ユーザーのゲームパッドのインデックス
		GamePadState m_lastState;       //!< 前回のゲームパッドの状態
		GamePadState m_currentState;    //!< 現在のゲームパッドの状態


		static const int TRIGGER_MAX = 255;    //!< トリガーの最大値
		static const int THUMB_LIMIT = 32767;    //!< スティックの上下限(±)


	public:

		//--------------------------------------------------
		//!@brief コンストラクタ
		//
		//!@param[in] userIndex ゲームパッドのインデックス
		//--------------------------------------------------
		pImpl(DWORD _userIndex)
			:m_userIndex(_userIndex)
			, m_lastState({ false,{0} })
			, m_currentState({ false,{0} })
		{
		}

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~pImpl() = default;


	public:
		
		//----------------------------------------------------------------
		//!@brief  ある状態において指定されたボタンが押されているかどうかを判断
		//
		//!@param[in] state 判定をしたい状態
		//!@brief[in] button 　ボタンコード
		//----------------------------------------------------------------
		inline bool IsButtonDown(const GamePadState& state, Button button)const
		{
			return (state.state.Gamepad.wButtons & button) ? true : false;
		}


		//-----------------------------
		//!@brief スティック値の調整
		//
		//!@param[in] なし
		//
		//!@retval    なし
		//-----------------------------
		void AdjustThumb()
		{
			// 左スティックの値の調整
			AdjustThumb(&m_currentState.state.Gamepad.sThumbLX);
			AdjustThumb(&m_currentState.state.Gamepad.sThumbLY);


			// 右スティックの値の調整
			AdjustThumb(&m_currentState.state.Gamepad.sThumbRX);
			AdjustThumb(&m_currentState.state.Gamepad.sThumbRY);
		}

		//------------------------------------
		//!@brief スティック各軸の値調整
		//
		//!@param[in] *thumb 軸の値
		//
		//!@retval    なし
		//------------------------------------
		void AdjustThumb(SHORT* _thumb)
		{
			// 左スティックのX軸の値の調整
			if (*_thumb <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				*_thumb > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				*_thumb = 0;
			}
			else if (*_thumb < -THUMB_LIMIT)
			{
				*_thumb = -THUMB_LIMIT;
			}
		}

		//------------------------------------------------
		//!@brief スティック値の正規化
		//
		//!@param[in] thumb スティック値
		//
		//!@retval   正規化されたスティック値(0.0～1.0)
		//------------------------------------------------
		float NormalizeThumb(SHORT thumb) const
		{
			return thumb / static_cast<float>(THUMB_LIMIT);
		}

		//-----------------------------
		//!@brief トリガー値の調整
		//
		//!@param[in] なし
		//
		//!@retval    なし
		//-----------------------------
		void AdjustTrigger()
		{
			// 左トリガーの値の調整
			if (m_currentState.state.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				m_currentState.state.Gamepad.bLeftTrigger = 0;
			}


			// 右トリガーの値の調整
			if (m_currentState.state.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				m_currentState.state.Gamepad.bRightTrigger = 0;
			}
		}

		//------------------------------------------------
		//!@brief トリガー値の正規化
		//
		//!@param[in] trigger トリガー値
		//
		//!@retval   正規化されたトリガー値(0.0～1.0)
		//------------------------------------------------
		float NormalizeTrigger(BYTE trigger) const
		{
			return trigger / static_cast<float>(TRIGGER_MAX);
		}
	};

}

namespace Gaia
{

	//-----------------------------
	//!@brief コンストラクタ
	//-----------------------------
	GamePad::GamePad(DWORD userIndex)
		:m_pImpl(std::make_unique<pImpl>(userIndex))
	{

	}

	//-----------------------------
	//!@brief デストラクタ
	//-----------------------------
	GamePad::~GamePad() = default;


	//----------------------------------------------
	//!@brief ゲームパッドが接続されているか
	//
	//!@param[in]  なし
	//
	//!@retval true 接続されている
	//!@retval false 接続されていない
	//----------------------------------------------
	bool GamePad::IsConnected() const
	{
		return m_pImpl->m_currentState.isConnected;
	}

	//----------------------------------------------
	//!@brief 指定したボタンが押されているか
	//
	//!@param[in]  button　判断したいボタンのコード
	//
	//!@retval true 押されている
	//!@retval false 押されていない
	//----------------------------------------------
	bool GamePad::IsButtonDown(Button _button)const
	{
		return m_pImpl->IsButtonDown(m_pImpl->m_currentState,_button);
	}

	//----------------------------------------------
	//!@brief 指定したボタンが押されていないか
	//
	//!@param[in]  button　判断したいボタンのコード
	//
	//!@retval true 押されていない
	//!@retval false 押されている
	//----------------------------------------------
	bool GamePad::IsButtonUp(Button _button) const
	{
		return !m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button);
	}

	//----------------------------------------------
	//!@brief 指定したボタンが押されてたか
	//
	//!@param[in]  button　判断したいボタンのコード
	//
	//!@retval true 押されている
	//!@retval false 押されていない
	//
	//!@note 押された瞬間を検知
	//----------------------------------------------
	bool GamePad::IsButtonPressed(Button _button) const
	{
		return m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button) &&
			  !m_pImpl->IsButtonDown(m_pImpl->m_lastState, _button);
	}

	//----------------------------------------------
	//!@brief 指定したボタンが離されたか
	//
	//!@param[in]  button　判断したいボタンのコード
	//
	//!@retval true 押されていない
	//!@retval false 押されてる
	//
	//!@note 離された瞬間を検知
	//----------------------------------------------
	bool GamePad::IsButtonReleased(Button _button) const
	{
		return !m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button) &&
				m_pImpl->IsButtonDown(m_pImpl->m_lastState, _button);
	}

	//----------------------------------------------
	//!@brief 左スティックのX軸の値を取得
	//
	//!@param[in] なし
	//
	//!@retval 左スティックX軸の値(0.0 ～ 1.0)
	//----------------------------------------------
	float GamePad::GetLeftThumbX() const
	{
		return m_pImpl->NormalizeThumb( m_pImpl->m_currentState.state.Gamepad.sThumbLX);
	}

	//----------------------------------------------
	//!@brief 左スティックのY軸の値を取得
	//
	//!@param[in] なし
	//
	//!@retval 左スティックY軸の値(0.0 ～ 1.0)
	//----------------------------------------------
	float GamePad::GetLeftThumbY() const
	{
		return m_pImpl->NormalizeThumb(m_pImpl->m_currentState.state.Gamepad.sThumbLY);
	}


	//----------------------------------------------
	//!@brief 右スティックのX軸の値を取得
	//
	//!@param[in] なし
	//
	//!@retval 右スティックX軸の値(0.0 ～ 1.0)
	//----------------------------------------------
	float GamePad::GetRightThumbX() const
	{
		return m_pImpl->NormalizeThumb(m_pImpl->m_currentState.state.Gamepad.sThumbRX);
	}

	//----------------------------------------------
	//!@brief 右スティックのY軸の値を取得
	//
	//!@param[in] なし
	//
	//!@retval 右スティックY軸の値(0.0 ～ 1.0)
	//----------------------------------------------
	float GamePad::GetRightThumbY() const
	{
		return m_pImpl->NormalizeThumb(m_pImpl->m_currentState.state.Gamepad.sThumbRY);
	}

	//----------------------------------------------
	//!@brief 左トリガーの値を取得
	//
	//!@param[in] なし
	//
	//!@retval 左トリガーの値(0.0 ～ 1.0)
	//----------------------------------------------
	float GamePad::GetLeftTrigger() const
	{
		return m_pImpl->NormalizeTrigger(m_pImpl->m_currentState.state.Gamepad.bLeftTrigger);
	}

	//----------------------------------------------
	//!@brief 右トリガーの値を取得
	//
	//!@param[in] なし
	//
	//!@retval 右トリガーの値(0.0 ～ 1.0)
	//----------------------------------------------
	float GamePad::GetRightTrigger() const
	{
		return m_pImpl->NormalizeTrigger(m_pImpl->m_currentState.state.Gamepad.bRightTrigger);
	}

	//----------------------------------------------
	//!@brief 更新
	//
	//!@param[in] なし
	//
	//!@retval なし
	//----------------------------------------------
	void GamePad::Update()
	{
		//現在の状態の保存
		m_pImpl->m_lastState = m_pImpl->m_currentState;

		
		//現在の状態を取得	
		DWORD result = XInputGetState(m_pImpl->m_userIndex, &m_pImpl->m_currentState.state);
		
		

		if (result == ERROR_SUCCESS)
		{
			m_pImpl->m_currentState.isConnected = true;

			m_pImpl->AdjustThumb();
			m_pImpl->AdjustTrigger();
		}
		else
		{
			m_pImpl->m_currentState.isConnected = false;
		}
		
	}

}