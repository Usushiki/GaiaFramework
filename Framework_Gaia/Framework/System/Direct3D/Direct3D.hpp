//----------------------------------------------------------------//
//					      Direct3D.h							　//		
//																  //
//					  About 	DirectXクラスのヘッダー			　//
//     	  		    Last Update  2016/05/12 12:07				  //
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
#include<d3d11.h>
#include<wrl.h>
#include<memory>




//-----------------------------
//DirectXクラス
//-----------------------------

namespace Gaia {

	class Direct3D final
	{

		template<typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

	private:
		//--------コンストラクタ-------//
		Direct3D();

	public:
		//--------デストラクタ-------//
		~Direct3D();

		//--------アクセッサ-------//
		ID3D11Device*			GetDevice()const;			//デバイスの取得
		ID3D11DeviceContext*	GetDeviceContext()const;	//デバイスコンテキストの取得
		IDXGISwapChain*			GetSwapChain()const;		//スワップチェーンの取得
		ID3D11RenderTargetView*	GetRenderTargetView()const;	//レンダーターゲットビューの取得
		ID3D11DepthStencilView*	GetDepthStencilView()const;	//深度ステンシルビューの取得

		HRESULT SetScreenMode(bool);						//スクリーンモードを設定

		//--------ファクトリ-------//
		static Direct3D* Create(HWND);

	private:
		//pImplイディオム
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;

	};
}

