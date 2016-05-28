//------------------------------------------------//
//				Windowの作成、表示				  //
//												  //
//					参考HP　　　　　　　　　　 　 //　　　
//			猫でもわかるWindowsプログラミング	  //
//	http://www.kumei.ne.jp/c_lang/index_sdk.html  //
//												  //
//												  //
//			2016. 5.12(Thu)11:55				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//


//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include "Window.hpp"


namespace Gaia 
{

	//----------------------------------------
	//!@brief Windowクラスの実装の詳細
	//----------------------------------------
	class Window::pImpl
	{
	public:

		//メンバ変数
		HWND m_hWindow = nullptr;	//ウィンドウハンドル													
		MSG  m_msg = { 0 };		//メッセージキュー		

	public:

		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		pImpl() = default;

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~pImpl() = default;

		//---------------------------------------------
		//!@brief 初期化
		//
		//!@param[in]  _width ウィンドウの幅
		//!@param[in]  _width ウィンドウの高さ
		//!@param[in]  _name  ウィンドウ幅タイトル
		//
		//!@retval  S_OK		成功					 
		//!@retval  E_FAIL		失敗			
		//---------------------------------------------
		HRESULT InitWindow(int _width, int _height, LPCWSTR _name)
		{
			HINSTANCE hInstance = GetModuleHandle(nullptr);

			WNDCLASSEX wcex;		//ウィンドウクラス
			ZeroMemory(&wcex, sizeof(wcex));



			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;		//ウィンドウのスタイルを指定
			wcex.lpfnWndProc = Window::WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			wcex.hIcon = LoadIcon(hInstance, L"ICON");
			wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = nullptr;
			wcex.lpszClassName = L"GameWindow";
			wcex.hIconSm = LoadIcon(hInstance, L"ICON");

			//初期化失敗
			if (!RegisterClassEx(&wcex))
				return E_FAIL;


			//ウィンドウスタイルの設定
			DWORD windowStyle = WS_OVERLAPPEDWINDOW	//基本スタイル
				& ~WS_MAXIMIZEBOX					//最大化ボタンの無効化
				& ~WS_THICKFRAME;					//ウィンドウサイズ変更の無効化


													//サイズの算出
			RECT rect{ 0, 0, _width, _height };

			AdjustWindowRect(&rect, windowStyle, FALSE);


			int windowWidth = rect.right - rect.left;
			int windowHeight = rect.bottom - rect.top;




			//ウィンドウを生成
			m_hWindow = CreateWindow(wcex.lpszClassName,
				_name,										//ウィンドウのタイトル
				windowStyle,								//ウィンドウのスタイル
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				windowWidth,								//ウィンドウ幅
				windowHeight,								//ウィンドウ高さ
				nullptr,
				nullptr,
				wcex.hInstance,
				nullptr
			);


			if (!m_hWindow)
				//初期化失敗
				return E_FAIL;

			//ウィンドウを表示
			ShowWindow(m_hWindow, SW_SHOWNORMAL);


			//初期化成功
			return S_OK;
		}



	};

}

namespace Gaia
{


	//-----------------------------
	//!@brief コンストラクタ
	//-----------------------------
	Window::Window()
		:m_pImpl(std::make_unique<pImpl>())
	{
		ZeroMemory(&m_pImpl->m_msg, sizeof(m_pImpl->m_msg));	//メッセージキューを初期化

	}

	//-----------------------------
	//!@brief デストラクタ
	//-----------------------------
	Window::~Window() = default;

	//----------------------------------------------
	//!@brief	メッセージを取り扱う	
	//										
	//!@param	なし			
	//
	//!@retval  true	WM_QUIT以外を受け取ったとき
	//!@retval  false   WM_QUITを受け取ったとき
	//-----------------------------------------------
	bool Window::HandleMessage()
	{
		//ポスト済みメッセージの処理
		while (PeekMessage(&m_pImpl->m_msg, nullptr, 0, 0, PM_REMOVE)) {

			//WM_QUITの時の処理
			if (m_pImpl->m_msg.message == WM_QUIT)
				return false;

			//WM_QUIT以外の処理
			TranslateMessage(&m_pImpl->m_msg);
			DispatchMessage(&m_pImpl->m_msg);
		}

		return true;
	}

	//---------------------------------------
	//!@brief   ウィンドウハンドルの取得
	//
	//!@param　なし
	//
	//!@retval ウィンドウハンドル
	//---------------------------------------
	HWND Window::GetWindowHandle() const
	{
		return m_pImpl->m_hWindow;
	}

	//------------------------------------------------------------
	//!@brief   ウィンドウハンドルの取得
	//
	//!@param　なし
	//
	//!@retval 終了コード
	//
	//!@memo    WM_QUITを受け取ったときに正常終了するために必要
	//------------------------------------------------------------
	int Window::GetExitCode() const
	{
		return m_pImpl->m_msg.wParam;
	}



	//------------------------------------------------------------------------------------------------------------------
	//!@brief	ウィンドウプロシージャ													 
	//																													
	//																													
	//!@param[in]  hWnd          ウィンドウハンドル(アプリを表す値が入る)												
	//!@param[in]  message       16bit時代の名残。今は使われておらずNULLが入っている									
	//!@param[in]  wParam        文字列へのポインタ。コマンドライン引数として渡されたNULLで終わる文字列へのポインタ		
	//!@param[in]  lParam        ウィンドウをどのように表示するかを指定した値											
	//																													
	//!@retval  メッセージ処理結果																									
	//------------------------------------------------------------------------------------------------------------------
	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
		}

		return 0;

	}



	//-----------------------------------------------
	//!@brief	オブジェクトを生成				 
	//												 
	//!@param[in]    width    ウィンドウ幅		 
	//!@param[in]    height   ウィンドウ高さ	 
	//!@param[in]	 name     ウィンドウの名前　 
	//												 
	//!@retval   ウィンドウオブジェクト
	//-----------------------------------------------
	std::unique_ptr<Window> Window::Create(int width, int height, LPCWSTR name)
	{
		auto pWindow = std::make_unique<Window>();

		if (!pWindow)
			return nullptr;


		//初期化
		if (FAILED(pWindow->m_pImpl->InitWindow(width, height, name))) {
			
			return nullptr;
		}


		//生成したウィンドウのオブジェクトを返す
		return pWindow;
	}

}