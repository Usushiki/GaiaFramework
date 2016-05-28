//----------------------------------------------------------------//
//							 Mouse.hpp							　//		
//																  //
//			About 		マウス入力検知クラスのヘッダー　　		　//
//     	    Last Update  2016/05/21	22:45						　//
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

//-----------------------------
//マウスクラス
//-----------------------------
namespace Gaia
{
	class Mouse
	{
	public:

		//仮想ボタンコード
		enum  Button : BYTE
		{
			LEFT = VK_LBUTTON,
			RIGHT = VK_RBUTTON,
			WHEEL  = VK_MBUTTON, 
		};

	
	public:
		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		explicit Mouse(HWND hWindow);

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~Mouse();


	public:
		// 指定されたボタンが押されているかどうかを判断
		bool GetIsButtonDown(Button button) const;

		// 指定されたボタンが押されていないかどうかを判断
		bool GetIsButtonUp(Button button) const;

		// 指定されたボタンが押されたかどうかを判断
		bool GetIsButtonPressed(Button button) const;

		// 指定されたボタンが離されたかどうかを判断
		bool GetIsButtonReleased(Button button) const;


		// ホイールの回転量の取得
		int GetWheelDelta() const;


		// マウスポインタの座標の取得
		POINT GetPointerPosition() const;

		// マウスポインタのX座標の取得
		LONG GetPointerPositionX() const;

		// マウスポインタのY座標の取得
		LONG GetPointerPositionY() const;


	public:
		// マウスの状態の更新
		void Update();

	private:

		//pimplイディオム
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;


	};
}