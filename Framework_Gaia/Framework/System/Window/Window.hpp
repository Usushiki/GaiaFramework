
//------------------------------------------------//
//				Windowの作成、表示				  //
//												  //
//					参考HP　　　　　　　　　　 　 //　　　
//			猫でもわかるWindowsプログラミング	  //
//	http://www.kumei.ne.jp/c_lang/index_sdk.html  //
//												  //
//												  //
//			2015.6.30(Tue)14:20					  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//

//-----------------------------
//多重インクルード防止
//-----------------------------
#pragma once



//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include<Windows.h>
#include<memory>

namespace Gaia {

	//-----------------------------
	//ウィンドウクラス
	//-----------------------------

	class Window 
	{
		

	public:

		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		Window();

	
	public:
		

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~Window();

		//--------アクセッサ-------//

		//ウィンドウハンドルの取得
		HWND GetWindowHandle() const;

		//終了コードの取得
		int  GetExitCode()	   const;


		//メッセージ処理
		bool HandleMessage();

	private:
		//pimplイディオム
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;

	public:

		//ウィンドウプロシージャ	
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

		//ファクトリ
		static std::unique_ptr<Window> Create(int, int, LPCWSTR name);

	

	};

}