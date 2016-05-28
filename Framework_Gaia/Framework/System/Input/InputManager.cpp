//------------------------------------------------//
//			インプットマネージャークラス		  //
//												  //
//												  //
//			2016. 5.22(Sun)10:38				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//

//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include"InputManager.hpp"


//-----------------------------
//ライブラリリンク
//-----------------------------
#pragma comment(lib, "Xinput9_1_0.lib")    // Xinput用ライブラリ



namespace Gaia
{

	//-----------------------------
	//!@brief コンストラクタ
	//-----------------------------
	InputManager::InputManager()
		:Singleton()
	{

	}

	//------------------------------------------------------------
	//!@brief	　	キーボードオブジェクトを取得	
	//															
	//!@param[in] 　なし		
	//
	//!@retval     キーボードオブジェクトのポインタ				
	//------------------------------------------------------------
	Keyboard* InputManager::GetKeyboard() const
	{
		return m_pKeyboard.get();		
	}

	//------------------------------------------------------------
	//!@brief	　	ゲームパッドオブジェクトを取得	
	//															
	//!@param[in] 　なし		
	//
	//!@retval     ゲームパッドオブジェクトのポインタ				
	//------------------------------------------------------------
	GamePad* InputManager::GetGamePad(int _index) const
	{
		return &m_pGamePad[_index];
	}

	//------------------------------------------------------------
	//!@brief	　	マウスオブジェクトを取得	
	//															
	//!@param[in] 　なし		
	//
	//!@retval     マウスオブジェクトのポインタ				
	//------------------------------------------------------------
	Mouse* InputManager::GetMouse() const
	{
		return m_pMouse.get();
	}


	//------------------------------------------------------------
	//!@brief	　	更新	
	//															
	//!@param[in] 　なし		
	//
	//!@retval     なし				
	//------------------------------------------------------------
	void InputManager::Update()
	{
		//キーボードの更新
		if (m_InputDevice & InputDevice::KEYBOARD)
		{
			m_pKeyboard->Update();
		}

		//ゲームパッドの更新
		if (m_InputDevice & InputDevice::GAMEPAD)
		{
			for (int i = 0; i < XUSER_MAX_COUNT; i++)
			{
				m_pGamePad[i].Update();
			}
		}

		//マウスの更新
		if (m_InputDevice & InputDevice::MOUSE)
		{
			m_pMouse->Update();
		}
	}

	//-----------------------------------------------
	//!@brief	初期化処理				 
	//												 
	//!@param[in]    _hWindow      ウィンドウハンドル		 
	//!@param[in]    _inputDevice  使用するインプットデバイス	  
	//												 
	//!@retval   S_OK     成功
	//!@retval   E_FAIL   失敗
	//-----------------------------------------------
	HRESULT InputManager::Initialize(HWND _hWindow, BYTE _inputDevice)
	{
		m_InputDevice = (InputDevice)_inputDevice;

		//キーボードオブジェクトを生成
		if (_inputDevice & InputDevice::KEYBOARD)
		{
			m_pKeyboard = std::make_unique<Keyboard>();
		}

		//マウスオブジェクトを生成
		if (_inputDevice & InputDevice::MOUSE)
		{
			m_pMouse = std::make_unique<Mouse>(_hWindow);

			if (!m_pMouse)
			{
				return E_FAIL;
			}
		}

		//ゲームパッドオブジェクトを生成
		if (_inputDevice & InputDevice::GAMEPAD)
		{
			m_pGamePad.reset(new GamePad[XUSER_MAX_COUNT]);

			if (!m_pGamePad) 
			{
				return E_FAIL;
			}
		}

		return S_OK;
	}

}