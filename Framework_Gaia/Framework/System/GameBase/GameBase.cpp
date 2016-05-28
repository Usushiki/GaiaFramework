//----------------------------------------------------------------//
//					      GameBase.cpp							　//		
//																  //
//			  About 	ゲームのベースとなる基底クラスのソース	　//
//     	  		    Last Update  2015/07/25						  //
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//

// 多重インクルード防止 ===================================================
#pragma once

//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include"GameBase.hpp"

#include"../Direct3D/Direct3D.hpp"
#include"../Window/Window.hpp"
#include"../FrameRateController/FrameRateController.hpp"
#include"../Input/InputManager.hpp"

#include<crtdbg.h>
#include<cstdlib>

namespace Gaia
{

	//----------------------------------------------
	//!@brief コンストラクタ
	//
	//!@param[in] title  ウィンドウのタイトル
	//!@param[in] width  ウィンドウ幅
	//!@param[in] height ウィンドウの高さ
	//----------------------------------------------
	GameBase::GameBase(LPCWSTR title, int width, int height)
		:m_GameTitle(title)
		, m_ScreenWidth(width)
		, m_ScreenHeight(height)
		, m_pWindow(nullptr)
		, m_pDirect3D(nullptr)
		, m_pFrameRateController(nullptr)
	{
#ifdef _DEBUG
		// メモリーリーク検出のための設定
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif 
	}


	//-----------------------------
	//!@brief デストラクタ
	//-----------------------------
	GameBase::~GameBase()
	{
	}


	//----------------------------------------------
	//!@brief		システムの初期化				
	//												
	//!@param[in] なし								
	//												
	//!@retval 	  true		初期化成功				
	//		  	  false     失敗					
	//----------------------------------------------
	bool GameBase::InitializeBaseSystem()
	{
		//ウィンドウの作成
		m_pWindow = Window::Create(m_ScreenWidth, m_ScreenHeight, m_GameTitle.c_str());
		if (!m_pWindow) {
			MessageBox(nullptr, L"ウィンドウの作成に失敗しました", nullptr, MB_OK);
			return false;
		}

		//Direct3Dオブジェクトを作成
		m_pDirect3D.reset(Direct3D::Create(m_pWindow->GetWindowHandle()));
		if (!m_pDirect3D)
		{
			MessageBox(nullptr, L"Direct3Dの設定に失敗しました", nullptr, MB_OK);
			return false;
		}

		m_pFrameRateController = std::make_unique<FrameRateController>(60);

		BYTE device = InputDevice::GAMEPAD | InputDevice::KEYBOARD | InputDevice::MOUSE;
		//InputManager::Get();


		//初期化成功
		return true;
	}


	//----------------------------------------------
	//!@brief		デバイスの取得				 
	//											 
	//!@param[in]	なし						 
	//											 
	//!@retval  	デバイスのポインタ			 
	//----------------------------------------------
	ID3D11Device* GameBase::GetDevice() const
	{
		return m_pDirect3D->GetDevice();
	}


	//----------------------------------------------
	//!@brief		デバイスコンテキストの取得		
	//												
	//!@param[in]	なし							
	//												
	//!@retval  	デバイスコンテキストのポインタ	
	//----------------------------------------------
	ID3D11DeviceContext* GameBase::GetDeviceContext() const
	{
		return m_pDirect3D->GetDeviceContext();
	}


	//----------------------------------------------
	//!@brief		スワップチェーンの取得			
	//												
	//!@param[in]	なし							
	//												
	//!@retval  	スワップチェーンのポインタ		
	//----------------------------------------------
	IDXGISwapChain* GameBase::GetSwapChain() const
	{
		return m_pDirect3D->GetSwapChain();
	}


	//-------------------------------------------------
	//!@brief		レンダーターゲットビューの取得	
	//												
	//!@param[in]	なし							
	//												
	//!@retval  	レンダーターゲットビューのポインタ
	//-------------------------------------------------
	ID3D11RenderTargetView* GameBase::GetRenderTargetView() const
	{
		return m_pDirect3D->GetRenderTargetView();
	}


	//----------------------------------------------
	//!@brief		レンダーターゲットビューの取得	
	//												
	//!@param[in]	なし							
	//												
	//!@retval  	深度ステンシルビューのポインタ	
	//----------------------------------------------
	ID3D11DepthStencilView* GameBase::GetDepthStencilView() const
	{
		return m_pDirect3D->GetDepthStencilView();
	}


	//----------------------------------------------
	//!@brief		ウィンドウハンドルの取得		
	//												
	//!@param[in]	なし							
	//												
	//!@retval  	ウィンドウハンドル				
	//----------------------------------------------
	HWND GameBase::GetWindowHandle() const
	{
		return m_pWindow->GetWindowHandle();
	}


	//----------------------------------------------
	//!@brief		フレームレートの取得			
	//												
	//!@param[in]	なし							
	//												
	//!@retval  	フレームレート					
	//----------------------------------------------
	double GameBase::GetFrameRate() const
	{
		return m_pFrameRateController->GetFrameRate();
		
	}


	//----------------------------------------------
	//!@brief		フレームレートの設定			
	//												
	//!@param[in]	framerate フレームレート		
	//												
	//!@retval  	なし							
	//----------------------------------------------
	void GameBase::SetFrameRate(int framerate)
	{
		m_pFrameRateController->SetFrameRate(framerate);
	}


	//---------------------------------------------------------
	//!@brief		実行関数								
	//														
	//!@param[in]	なし									
	//														
	//!@retval  	ExitCode ウィンドウメッセージの終了コード
	//!@retval		    0	 異常終了						
	//---------------------------------------------------------
	int GameBase::Run(ScreenMode screenmode)
	{
		//システムを初期化
		if (!InitializeBaseSystem()) {
			return 0;
		}

		//ゲームの初期化
		if (!Initialize()) {
			Finalize();
			return 0;
		}



		//ウィンドウモードの設定
		m_pDirect3D->SetScreenMode(isBool(screenmode));

		//フレームレートの計測を開始
		m_pFrameRateController->Start();

		//メッセージループ
		while (m_pWindow->HandleMessage()) {

			//フレームレートの調節
			m_pFrameRateController->Regulate();

			//ゲームの更新
			Update();

			//1フレームに一回
			if (!m_pFrameRateController->GetIsSkip())
				//ゲームの描画
				Render();

		}

		//ゲームの後始末
		Finalize();

		//終了コードを返す
		return m_pWindow->GetExitCode();

	}

}