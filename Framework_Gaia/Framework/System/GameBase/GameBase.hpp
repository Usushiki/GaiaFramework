//----------------------------------------------------------------//
//					      GameBase.h							　//		
//																  //
//			About 	ゲームのベースとなる基底クラスのヘッダー　　　//
//     	    Last Update  2015/07/20								　//
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//

//-----------------------------
//多重インクルード防止
//-----------------------------
#pragma once




//-----------------------------
//クラス前方宣言
//-----------------------------
namespace Gaia
{
	class Window;
	class Direct3D;
	class FrameRateController;
	
}



//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include<memory>

#include<string>
#include<Windows.h>

#include<d3d11.h>


#include"../Window/ScreenMode.hpp"


//-----------------------------
//GameBaseクラス
//-----------------------------
namespace Gaia
{

	class GameBase
	{
	private:
		

		std::unique_ptr<Window>			  	 m_pWindow;					//ウィンドウ
		std::unique_ptr<Direct3D>			 m_pDirect3D;				//DirectXオブジェクト
		std::unique_ptr<FrameRateController> m_pFrameRateController;	//フレームレート管理オブジェクト

		std::wstring	m_GameTitle;				//ゲームタイトル
		int				m_ScreenWidth;				//画面幅
		int				m_ScreenHeight;				//画面の高さ


	public:
		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		GameBase(LPCWSTR, int, int);

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		virtual ~GameBase();


		//--------アクセッサ-------//
		HWND GetWindowHandle()const;						//ウィンドウハンドルの取得

		ID3D11Device*			GetDevice()const;			//デバイスの取得
		ID3D11DeviceContext*	GetDeviceContext()const;	//デバイスコンテキストの取得
		IDXGISwapChain*			GetSwapChain()const;		//スワップチェーンの取得
		ID3D11RenderTargetView*	GetRenderTargetView()const;	//レンダーターゲットビューの取得
		ID3D11DepthStencilView*	GetDepthStencilView()const;	//深度ステンシルビューの取得
		double GetFrameRate()const;							//フレームレートの取得
		void SetFrameRate(int);								//フレームレートの設定


		//--------実行関数-------//
		int Run(ScreenMode);

		//--------------------------内部実装関数--------------------------//
	private:

		//システム初期化
		bool InitializeBaseSystem();

		//初期化
		virtual bool Initialize() = 0;

		//更新
		virtual void Update() = 0;

		//描画
		virtual void Render() = 0;

		//後始末
		virtual void Finalize() = 0;

	};


}

