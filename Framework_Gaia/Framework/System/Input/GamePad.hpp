//----------------------------------------------------------------//
//					      GamePad.hpp							　//		
//																  //
//			About 		ゲームパッドクラスのヘッダー　		　　　//
//     	    Last Update  2016/05/21	22:42						　//
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
#include<Xinput.h>
#include<memory>


//-----------------------------
//ゲームパッドクラス
//-----------------------------
namespace Gaia
{
	
	class GamePad
	{
	
	public:
		//! @brief 仮想ボタンコード
		enum Button : WORD
		{
			UP = XINPUT_GAMEPAD_DPAD_UP,
			DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
			LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
			RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
			START = XINPUT_GAMEPAD_START,
			BACK = XINPUT_GAMEPAD_BACK,
			L_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,
			R_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
			L_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,
			R_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			A = XINPUT_GAMEPAD_A,
			B = XINPUT_GAMEPAD_B,
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y,
		};


	private:

		//pimplイディオム
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;

		
	public:

		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		explicit GamePad(DWORD userIndex = 0);

	public:

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~GamePad();

		
	public:
		// ゲームパッドが接続されているかどうかを判断
		bool IsConnected() const;


		// 指定されたボタンが押されているかどうかを判断
		bool IsButtonDown(Button button) const;

		// 指定されたボタンが押されていないかどうかを判断
		bool IsButtonUp(Button button) const;

		// 指定されたボタンが押されたかどうかを判断
		bool IsButtonPressed(Button button) const;

		// 指定されたボタンが離されたかどうかを判断
		bool IsButtonReleased(Button button) const;


		// 左スティックのX軸の値の取得
		float GetLeftThumbX() const;

		// 左スティックのY軸の値の取得
		float GetLeftThumbY() const;

		// 右スティックのX軸の値の取得
		float GetRightThumbX() const;

		// 右スティックのY軸の値の取得
		float GetRightThumbY() const;


		// 左トリガーの値の取得
		float GetLeftTrigger() const;

		// 右トリガーの値の取得
		float GetRightTrigger() const;
		
	public:
		// ゲームパッドの状態の更新
		void Update();
	
	};
}
