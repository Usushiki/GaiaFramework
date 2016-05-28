//----------------------------------------------------------------//
//					      InputManager.hpp						　//		
//																  //
//			About 		入力マネージャークラスのヘッダー　	　　　//
//     	    Last Update  2016/05/22	00:19						　//
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
#include<memory>
#include"Keyboard.hpp"
#include"GamePad.hpp"
#include"Mouse.hpp"

#include"../../Utility/Singleton.hpp"

namespace Gaia
{
	//入力デバイス
	enum InputDevice : BYTE
	{
		KEYBOARD = 0x01,
		GAMEPAD = 0x02,
		MOUSE = 0x04,
	};

	class InputManager :public  Utility::Singleton<InputManager>
	{
		//フレンドクラス
		friend class Utility::Singleton<InputManager>;


	private:
		std::unique_ptr<Keyboard>   m_pKeyboard = nullptr;	//キーボード
		std::unique_ptr<GamePad[]>  m_pGamePad = nullptr;	//ゲームパッド
		std::unique_ptr<Mouse>      m_pMouse = nullptr;		//マウス
	
		InputDevice m_InputDevice;

	private:

		
		//-----------------------------
		//!@brief コンストラクタ
		//----------------------------
		InputManager();
	
	public:

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~InputManager() = default;

	public:
		Keyboard* GetKeyboard()			const;	//キーボードオブジェクトの取得
		GamePad*  GetGamePad(int)		const;	//ゲームパッドオブジェクトの取得
		Mouse*	  GetMouse()			const;	//マウスオブジェクトの取得


		//更新
		void Update();

		HRESULT Initialize(HWND,BYTE);

	};
}
