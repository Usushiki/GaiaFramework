//----------------------------------------------------------------//
//					      Keyboard.hpp							　//		
//																  //
//			About 		キーボード入力検知クラスのヘッダー　　　　//
//     	    Last Update  2016/05/13	09:21						　//
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
//Keyboardクラス
//-----------------------------
namespace Gaia 
{

	class Keyboard 
	{
		
	public:
		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		Keyboard();

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~Keyboard();


		//更新
		void Update();


		//指定したキーが押されているか
		bool GetIsKeyDown(BYTE) const;

		//指定されたキーが押されていないか
		bool GetIskeyUp(BYTE) const;

		//指定されたキーが押されたか
		bool GetIsKeyPress(BYTE) const;

		//指定されたキーが離されたか
		bool GetIsKeyRelease(BYTE) const;

		//指定されたキーが1フレーム前に押されていたか
		bool GetIsKeyDownLastFrame(BYTE) const;

		//キーがどれか1つでも押されているか
		bool GetIsKeyInputAll();

	private:

		//pimplイディオム
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;


	};
}
