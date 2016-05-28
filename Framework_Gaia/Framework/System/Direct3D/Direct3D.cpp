//----------------------------------------------------------------//
//					      Direct3D.cpp							　//		
//																  //
//					  About 		DirectXクラスのソース		　//
//     	  		    Last Update  2015/07/13						  //
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//




//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include<DirectXColors.h>
#include"Direct3D.hpp"





//-----------------------------
//ライブラリリンク
//-----------------------------
#pragma comment(lib,"d3d11.lib")		//DirectX11ライブラリ	

#pragma comment(lib,"DirectXTK.lib")	//DirectXTKライブラリ


namespace Gaia
{

	//----------------------------------------
	//!@brief Drect3Dクラスの実装の詳細
	//----------------------------------------
	class Direct3D::pImpl
	{
		//メンバ変数
	public:

		HWND m_hWindow;												//ウィンドウハンドル


		ComPtr<ID3D11Device>			m_pd3dDevice;				//DirectX11のデバイス
		ComPtr<ID3D11DeviceContext>		m_pd3dImmeidiateContext;	//コンテキスト
		ComPtr<IDXGISwapChain>			m_pSwapChain;				//スワップチェーン
		ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;		//レンダーターゲットビュー
		ComPtr<ID3D11Texture2D>			m_pDepthStencil;			//深度ステンシル
		ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;		//深度ステンシルビュー


		UINT m_RenderTargetWidth;									//レンダーターゲット幅
		UINT m_RenderTargetHeight;									//レンダーターゲットの高さ

	public:

		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		pImpl()
			:m_hWindow(nullptr)
			, m_pd3dDevice(nullptr)
			, m_pd3dImmeidiateContext(nullptr)
			, m_pSwapChain(nullptr)
			, m_pRenderTargetView(nullptr)
			, m_pDepthStencilView(nullptr)
			, m_pDepthStencil(nullptr)
			, m_RenderTargetHeight(0)
			, m_RenderTargetWidth(0)
		{

		}

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~pImpl() = default;

	public:
		//----------------------------------------
		//!@brief デバイスリソースの作成
		//
		//!@param[in] なし
		//
		//!@retval    S_OK   成功
		//!@retval    E_FAIL 失敗
		//----------------------------------------
		HRESULT CreateDeviceResources()
		{
			UINT createDeviceFlag = 0;

			HRESULT hr = S_OK;


#ifdef _DEBUG
			createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;	//デバッグレイヤーをサポートするフラグ
#endif

			D3D_DRIVER_TYPE DriverTypes[] =
			{
				D3D_DRIVER_TYPE_HARDWARE,
				D3D_DRIVER_TYPE_WARP,
				D3D_DRIVER_TYPE_REFERENCE,
			};

			UINT numDriverTypes = ARRAYSIZE(DriverTypes);


			D3D_FEATURE_LEVEL FeatureLevels[] =
			{
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1,
			};

			D3D_FEATURE_LEVEL featureLevel;


			UINT numFeatureLevel = ARRAYSIZE(FeatureLevels);


			//デバイスとデバイスコンテキストを作成
			D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				createDeviceFlag,
				FeatureLevels,
				ARRAYSIZE(FeatureLevels),
				D3D11_SDK_VERSION,
				&m_pd3dDevice,
				&featureLevel,
				&m_pd3dImmeidiateContext
			);

			//クライアント領域の取得
			RECT rc;

			GetClientRect(m_hWindow, &rc);

			m_RenderTargetWidth = rc.right - rc.left;
			m_RenderTargetHeight = rc.bottom - rc.top;


			//スワップチェーン
			hr = CreateSwapChain();
			if (FAILED(hr)) {
				return hr;
			}

			//バックバッファと深度ステンシルビューを作成
			hr = CreateBackBufferDepthStencil();
			if (FAILED(hr)) {
				return hr;
			}


			return S_OK;
		}

		//----------------------------------------
		//!@brief スワップチェーンの作成
		//
		//!@param[in] なし
		//
		//!@retval    S_OK   成功
		//!@retval    E_FAIL 失敗
		//----------------------------------------
		HRESULT CreateSwapChain()
		{
			HRESULT hr = S_OK;

			// スワップチェーンの設定
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 1;
			sd.BufferDesc.Width = m_RenderTargetWidth;
			sd.BufferDesc.Height = m_RenderTargetHeight;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 0;	//リフレッシュレートはDXGIの自動設定に任せる
			sd.BufferDesc.RefreshRate.Denominator = 0;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = m_hWindow;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //フルスクリーンへの切り替えの時に表示モードを変更する

															   //Alt+Enterで画面モードを変更しないようにする
			ComPtr<IDXGIDevice1> pDXGIDevice;
			ComPtr<IDXGIAdapter> pDXGIAdapter;
			ComPtr<IDXGIFactory> pDXGIFactory;


			//インターフェース取得
			hr = m_pd3dDevice.As(&pDXGIDevice);
			if (FAILED(hr)) {
				return hr;
			}

			//アダプター取得
			hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
			if (FAILED(hr)) {
				return hr;
			}

			//ファクトリー取得
			hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (LPVOID*)&pDXGIFactory);
			if (FAILED(hr)) {
				return hr;
			}

			//スワップチェーンの作成
			pDXGIFactory->CreateSwapChain(m_pd3dDevice.Get(), &sd, &m_pSwapChain);
			if (FAILED(hr)) {
				return hr;
			}

			//フルスクリーンの不具合修正のためにバッファをリサイズ
			m_pSwapChain->ResizeBuffers(sd.BufferCount, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);


			return S_OK;
		}

		
		//-------------------------------------------------------
		//!@brief バックバッファと深度ステンシルビューの作成
		//
		//!@param[in] なし
		//
		//!@retval    S_OK   成功
		//!@retval    E_FAIL 失敗
		//-------------------------------------------------------
		HRESULT CreateBackBufferDepthStencil()
		{
			HRESULT hr = S_OK;

			////////////////////////
			//バックバッファの作成//
			////////////////////////
			ID3D11Texture2D* pBackBuffer = nullptr;
			hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			if (FAILED(hr)) {
				return hr;
			}

			//バックバッファに指定されているテクスチャ情報を取得
			D3D11_TEXTURE2D_DESC descBackBuffer;
			pBackBuffer->GetDesc(&descBackBuffer);


			//レンダーターゲットビューを作成
			hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_pRenderTargetView.GetAddressOf());
			pBackBuffer->Release();
			if (FAILED(hr)) {
				return hr;
			}


			//////////////////////
			//深度バッファの作成//
			//////////////////////


			//深度ステンシルテクスチャの作成
			//バックバッファに指定されたテクスチャ情報をもとに作成
			CD3D11_TEXTURE2D_DESC descDepth(descBackBuffer);

			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;
			hr = m_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &m_pDepthStencil);
			if (FAILED(hr)) {
				return hr;
			}


			//深度ステンシルビューの作成
			CD3D11_DEPTH_STENCIL_VIEW_DESC descDSV(D3D11_DSV_DIMENSION_TEXTURE2D, descDepth.Format);
			hr = m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &descDSV, &m_pDepthStencilView);
			if (FAILED(hr)) {
				return hr;
			}

			////////////////////////////
			//レンダーターゲットの設定//
			////////////////////////////
			m_pd3dImmeidiateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());


			//////////////////////////
			//　ビューポートの作成　//
			//////////////////////////
			CD3D11_VIEWPORT vp(0.0f, 0.0f, (FLOAT)m_RenderTargetWidth, (FLOAT)m_RenderTargetHeight);
			m_pd3dImmeidiateContext->RSSetViewports(1, &vp);

			return S_OK;
		}

		
		//----------------------------------------
		//!@brief 初期化処理
		//
		//!@param[in] _hWindow ウィンドウハンドル
		//
		//!@retval    S_OK   成功
		//!@retval    E_FAIL 失敗
		//----------------------------------------
		HRESULT Initialize(HWND _hWindow)
		{
			m_hWindow = _hWindow;

			if (FAILED(CreateDeviceResources()))
			{
				return E_FAIL;
			}

			//初期化に成功
			return S_OK;
		}

		//--------------------------------------------------------------
		//!@brief		スクリーンモードの設定							
		//																
		//!@param[in]	スクリーンモード  　true		フルスクリーン	
		//!@param[in]				 　　　 false     ウィンドウモード	
		//																
		//!@retval       なし											
		//--------------------------------------------------------------
		HRESULT SetScreenMode(bool _screenMode)
		{
			return m_pSwapChain->SetFullscreenState(_screenMode,nullptr);
		}
	};
}

namespace Gaia 
{


	//-----------------------------
	//!@brief コンストラクタ
	//-----------------------------
	Direct3D::Direct3D()
		:m_pImpl(std::make_unique<pImpl>())
	{

	}

	//-----------------------------
	//!@brief デストラクタ
	//-----------------------------
	Direct3D::~Direct3D() = default;
	

	//-------------------------------------------------------
	//!@brief		デバイスの取得							
	//														
	//!@param[in]	なし									
	//														
	//!@retval  	デバイスのポインタ						
	//-------------------------------------------------------
	ID3D11Device* Direct3D::GetDevice() const
	{
		return m_pImpl->m_pd3dDevice.Get();
	}



	//-------------------------------------------------------
	//!@brief		デバイスコンテキストの取得				
	//														
	//!@param[in]	なし									
	//														
	//!@retval   	デバイスコンテキストのポインタ		
	//-------------------------------------------------------
	ID3D11DeviceContext* Direct3D::GetDeviceContext() const
	{
		return m_pImpl->m_pd3dImmeidiateContext.Get();
	}

	//-------------------------------------------------------
	//!@brief		スワップチェーンの取得				
	//																	
	//!@param[in]	なし										
	//																	
	//!@retval   	スワップチェーンのポインタ	
	//-------------------------------------------------------
	IDXGISwapChain* Direct3D::GetSwapChain() const
	{
		return m_pImpl->m_pSwapChain.Get();
	}

	//-------------------------------------------------------
	//!@brief		レンダーターゲットビューの取得			
	//														
	//!@param[in]	なし									
	//														
	//!@retval   	レンダーターゲットビューのポインタ	
	//-------------------------------------------------------
	ID3D11RenderTargetView* Direct3D::GetRenderTargetView() const
	{
		return m_pImpl->m_pRenderTargetView.Get();
	}

	//-------------------------------------------------------
	//!@brief		レンダーターゲットビューの取得			
	//														
	//!@param[in]	なし									
	//														
	//!@retval   	深度ステンシルビューのポインタ		
	//-------------------------------------------------------
	ID3D11DepthStencilView* Direct3D::GetDepthStencilView() const
	{
		return m_pImpl->m_pDepthStencilView.Get();
	}


	//-------------------------------------------------------
	//!@brief		スクリーンモードの設定
	//														
	//!@param[in]	true		フルスクリーン	
	//				false     　ウィンドウモード
	//
	//!@retval		なし   				
	//-------------------------------------------------------
	HRESULT Direct3D::SetScreenMode(bool isFullScreen)
	{
		return m_pImpl->SetScreenMode(isFullScreen);
	}


}

namespace Gaia
{
	//-------------------------------------------------------
	//!@brief			ファクトリメソッド	
	//															
	//!@param[in] hWindow  ウィンドウハンドル				
	//														
	//!@retval      生成されたオブジェクトのポインタ
	//
	//!@note		Direct3Dのオブジェクトを生成する
	//-------------------------------------------------------
	Direct3D* Direct3D::Create(HWND hWindow)
	{
		//オブジェクト生成
		Direct3D* pDirect3D = new Direct3D();

		if (!pDirect3D)
		{
			return nullptr;
		}

		//初期化
		if (FAILED(pDirect3D->m_pImpl->Initialize(hWindow)))
		{
			pDirect3D->m_pImpl->m_pd3dImmeidiateContext->ClearState();

			delete pDirect3D;

			return nullptr;
		}

		//オブジェクトの生成に成功
		return pDirect3D;
	}
}
