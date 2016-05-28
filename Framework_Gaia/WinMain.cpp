//------------------------------------------------//
//				Windowの作成、表示				  //
//												  //
//					参考HP　　　　　　　　　　 　 //　　　
//			猫でもわかるWindowsプログラミング	  //
//	http://www.kumei.ne.jp/c_lang/index_sdk.html  //
//												  //
//												  //
//			2016 .5.12(Thu)11:28				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//


//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------

#include<Windows.h>
#include<wchar.h>

#include<d3d11.h>
#include<DirectXColors.h>
#include<memory>

#include"Framework\System\Debug\DebugLog.hpp"

#include"Framework\System\Window\Window.hpp"
#include"Framework\System\Direct3D\Direct3D.hpp"


// 名前空間 ===================================================
using namespace Gaia;


//---------------------------------------------------------------------------------------------------------------------------//
//													メイン関数																 //
//																															 //	
//									
//
//		HINSTANCE hInstance       インスタンスハンドル(アプリを表す値が入る)												 //
//      HINSTANCE hPrevInstance   16bit時代の名残。今は使われておらずNULLが入っている										 //
//		LPWSTR     lpCmdLine       文字列へのポインタ。コマンドライン引数として渡されたNULLで終わる文字列へのポインタ		 //
//      int       nCmdShow        ウィンドウをどのように表示するかを指定した値												 //
//																															 //	
//																															 //
//---------------------------------------------------------------------------------------------------------------------------//
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	std::unique_ptr<Window>   pWindow;
	std::unique_ptr<Direct3D> pDirect3D;

	pWindow = Window::Create(640, 480, L"Test");
	pDirect3D.reset(Direct3D::Create(pWindow->GetWindowHandle()));

	DebugLog(LOG_TYPE::TYPE_NORMAL,"normal","  ");


	while (pWindow->HandleMessage())
	{
		ID3D11DeviceContext* pDeviceConText = pDirect3D->GetDeviceContext();
		IDXGISwapChain* pSwapChain = pDirect3D->GetSwapChain();
	
		
		//バックバッファのクリア
		pDeviceConText->ClearRenderTargetView(pDirect3D->GetRenderTargetView(), DirectX::Colors::MidnightBlue);

		//深度バッファのクリア
		pDeviceConText->ClearDepthStencilView(pDirect3D->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


		//バックバッファの表示
		pSwapChain->Present(0, 0);

	}

	

//	DebugLogFileLine(LOG_TYPE::TYPE_NORMAL, "Test", i);


	return pWindow->GetExitCode();
}