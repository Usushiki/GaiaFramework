//----------------------------------------------------------------//
//							 Mouse.cpp							　//		
//																  //
//			About 		マウス入力検知クラスのソース　　		　//
//     	    Last Update  2016/05/21	22:45						　//
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//

//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include"Mouse.hpp"
#include<CommCtrl.h>

//-----------------------------
//ライブラリリンク
//-----------------------------
#pragma comment(lib, "comctl32.lib")    //コモンコントロールライブラリ


namespace Gaia
{
	//----------------------------------------
	//!@brief Mouseクラスの実装の詳細
	//----------------------------------------
	class Mouse::pImpl
	{
	public:

		//マウス状態
		struct MouseState
		{
			BYTE buttonState;		//ボタン状態
			int wheelDelta;			//ホイールの回転量
			POINT pointerPosition;	//マウスポインターの座標
		};

		MouseState m_lastState;		//前回のマウスの状態
		MouseState m_currentState;	//現在のマウスの状態

		int m_wheelDelta;			//ホイールの回転量

		HWND m_hWindow;				//ウィンドウハンドル


	public:
		//------------------------------------------
		//!@brief コンストラクタ
		//
		//!@param[in] _hWindow ウィンドウハンドル
		//------------------------------------------
		pImpl(HWND _hWindow)
			:m_hWindow(_hWindow)
			, m_currentState({ 0,0,{0,0} })
			, m_lastState({ 0,0,{0,0} })
		{
			//ウィンドウのサブクラス化
			UINT_PTR subclassID		= reinterpret_cast<DWORD_PTR>(this);
			DWORD_PTR referenceData = reinterpret_cast<DWORD_PTR>(this);
			SetWindowSubclass(_hWindow, Procedure, subclassID, referenceData);
		}

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~pImpl()
		{
			//サブクラス化の解除
			UINT_PTR subclassID = reinterpret_cast<DWORD_PTR>(this);
			RemoveWindowSubclass(m_hWindow, Procedure, subclassID);
		}

		//----------------------------------------------
		//!@brief	ホイール状態更新
		//
		//!@param[in] _delta ホイールの回転量 
		//
		//!@retval なし
		//----------------------------------------------
		void UpdateWheel(int _delta)
		{
			m_wheelDelta += _delta;
		}

		//-------------------------------------------------------------
		//!@brief  	指定されたボタンがある状況下に押されているかを判定
		//
		//!@param[in] _state　  マウスの状態
		//!@param[in] _button   検知したいボタンのコード
		//
		//!@retval true  押されている
		//		   false 押されていない 
		//-------------------------------------------------------------
		inline bool IsButtonDown(const MouseState& _state, Button _button)
		{
			return (_state.buttonState & _button) ? true : false;
		}

	public:
		//------------------------------------------------------------------
		//! @brief マウス・プロシージャ
		//!
		//! @param[in] hWindow     ウィンドウハンドル
		//! @param[in] uMessage    メッセージの識別子
		//! @param[in] wParam      メッセージの1番目のパラメータ
		//! @param[in] lParam      メッセージの2番目のパラメータ
		//! @param[in] uIdSubclass サブクラスID
		//! @param[in] dwRefData   参照データ
		//!
		//! @retval メッセージ処理の結果(送信されたメッセージによって異なる)
		//------------------------------------------------------------------
		static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage,
			WPARAM wParam, LPARAM lParam,
			UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
		{
			// メッセージの処理
			switch (uMessage)
			{
			case WM_MOUSEWHEEL:

				Mouse* mouse = reinterpret_cast<Mouse*>(dwRefData);
				if (mouse)
				{
					mouse->m_pImpl->UpdateWheel(GET_WHEEL_DELTA_WPARAM(wParam));
					return 0;
				}
				break;

			}
			// 自分で処理しないメッセージはWindowsに任せる
			return DefSubclassProc(hWindow, uMessage, wParam, lParam);
		}
	};
}



namespace Gaia
{
	//-----------------------------
	//!@brief コンストラクタ
	//-----------------------------
	Mouse::Mouse(HWND _hWindow)
		:m_pImpl(std::make_unique<pImpl>(_hWindow))
	{

	}

	//-----------------------------
	//!@brief デストラクタ
	//-----------------------------
	Mouse::~Mouse() = default;


	//------------------------------------------------------------
	//!@brief	  	 指定されたボタンが押されているかを判定		
	//															
	//															
	//!@param[in] _button			判定したいボタンのコード			
	//															
	//!@retval  true  ボタンが押されている						
	//          false ボタンが押されていない									
	//------------------------------------------------------------
	bool Mouse::GetIsButtonDown(Button _button) const
	{
		return m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button);
	}

	//------------------------------------------------------------
	//!@brief	  	 指定されたボタンが押されていないかを判定		
	//															
	//															
	//!@param[in] _button			判定したいボタンのコード			
	//															
	//!@retval  true  ボタンが押されていない						
	//          false ボタンが押されている									
	//------------------------------------------------------------
	bool Mouse::GetIsButtonUp(Button _button) const
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
	bool Mouse::GetIsButtonPressed(Button _button) const
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
	bool Mouse::GetIsButtonReleased(Button _button) const
	{
		return !m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button) &&
				m_pImpl->IsButtonDown(m_pImpl->m_lastState, _button);
	}

	//----------------------------------------------
	//! @brief ホイールの回転量(ノッチ)の取得
	//
	//! @param なし
	//
	//! @retval ホイールの回転量(ノッチ)
	//----------------------------------------------
	int Mouse::GetWheelDelta() const
	{
		return m_pImpl->m_currentState.wheelDelta / WHEEL_DELTA;
	}

	//----------------------------------------------
	//! @brief マウスポインタの座標を取得
	//
	//! @param なし
	//
	//! @retval マウスポインタの座標
	//----------------------------------------------
	POINT Mouse::GetPointerPosition() const
	{
		return m_pImpl->m_currentState.pointerPosition;
	}

	//----------------------------------------------
	//! @brief マウスポインタのX座標を取得
	//
	//! @param なし
	//
	//! @retval マウスポインタのX座標
	//----------------------------------------------
	LONG Mouse::GetPointerPositionX() const
	{
		return m_pImpl->m_currentState.pointerPosition.x;
	}

	//----------------------------------------------
	//! @brief マウスポインタのY座標を取得
	//
	//! @param なし
	//
	//! @retval マウスポインタのY座標
	//----------------------------------------------
	LONG Mouse::GetPointerPositionY() const
	{
		return m_pImpl->m_currentState.pointerPosition.y;
	}

	//----------------------------------------------
	//! @brief マウス状態の更新
	//
	//! @param なし
	//
	//! @retval なし
	//----------------------------------------------
	void Mouse::Update()
	{
		//現在の状態の保存
		m_pImpl->m_lastState = m_pImpl->m_currentState;

		//ボタンの現在の状態を取得
		m_pImpl->m_currentState.buttonState = 0;

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			m_pImpl->m_currentState.buttonState |= Button::LEFT;
		}

		if (GetKeyState(VK_RBUTTON) & 0x8000)
		{
			m_pImpl->m_currentState.buttonState |= Button::RIGHT;
		}

		if (GetKeyState(VK_MBUTTON) & 0x8000)
		{
			m_pImpl->m_currentState.buttonState |= Button::WHEEL;
		}

		//ホイール回転量の取得
		m_pImpl->m_currentState.wheelDelta = m_pImpl->m_wheelDelta;
		m_pImpl->m_wheelDelta = 0;

		//マウスポインターの座標を取得
		GetCursorPos(&m_pImpl->m_currentState.pointerPosition);
		ScreenToClient(m_pImpl->m_hWindow, &m_pImpl->m_currentState.pointerPosition);

	}
}

