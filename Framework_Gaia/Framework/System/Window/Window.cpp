//------------------------------------------------//
//				Window�̍쐬�A�\��				  //
//												  //
//					�Q�lHP�@�@�@�@�@�@�@�@�@�@ �@ //�@�@�@
//			�L�ł��킩��Windows�v���O���~���O	  //
//	http://www.kumei.ne.jp/c_lang/index_sdk.html  //
//												  //
//												  //
//			2016. 5.12(Thu)11:55				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//


//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include "Window.hpp"


namespace Gaia 
{

	//----------------------------------------
	//!@brief Window�N���X�̎����̏ڍ�
	//----------------------------------------
	class Window::pImpl
	{
	public:

		//�����o�ϐ�
		HWND m_hWindow = nullptr;	//�E�B���h�E�n���h��													
		MSG  m_msg = { 0 };		//���b�Z�[�W�L���[		

	public:

		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		pImpl() = default;

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~pImpl() = default;

		//---------------------------------------------
		//!@brief ������
		//
		//!@param[in]  _width �E�B���h�E�̕�
		//!@param[in]  _width �E�B���h�E�̍���
		//!@param[in]  _name  �E�B���h�E���^�C�g��
		//
		//!@retval  S_OK		����					 
		//!@retval  E_FAIL		���s			
		//---------------------------------------------
		HRESULT InitWindow(int _width, int _height, LPCWSTR _name)
		{
			HINSTANCE hInstance = GetModuleHandle(nullptr);

			WNDCLASSEX wcex;		//�E�B���h�E�N���X
			ZeroMemory(&wcex, sizeof(wcex));



			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;		//�E�B���h�E�̃X�^�C�����w��
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

			//���������s
			if (!RegisterClassEx(&wcex))
				return E_FAIL;


			//�E�B���h�E�X�^�C���̐ݒ�
			DWORD windowStyle = WS_OVERLAPPEDWINDOW	//��{�X�^�C��
				& ~WS_MAXIMIZEBOX					//�ő剻�{�^���̖�����
				& ~WS_THICKFRAME;					//�E�B���h�E�T�C�Y�ύX�̖�����


													//�T�C�Y�̎Z�o
			RECT rect{ 0, 0, _width, _height };

			AdjustWindowRect(&rect, windowStyle, FALSE);


			int windowWidth = rect.right - rect.left;
			int windowHeight = rect.bottom - rect.top;




			//�E�B���h�E�𐶐�
			m_hWindow = CreateWindow(wcex.lpszClassName,
				_name,										//�E�B���h�E�̃^�C�g��
				windowStyle,								//�E�B���h�E�̃X�^�C��
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				windowWidth,								//�E�B���h�E��
				windowHeight,								//�E�B���h�E����
				nullptr,
				nullptr,
				wcex.hInstance,
				nullptr
			);


			if (!m_hWindow)
				//���������s
				return E_FAIL;

			//�E�B���h�E��\��
			ShowWindow(m_hWindow, SW_SHOWNORMAL);


			//����������
			return S_OK;
		}



	};

}

namespace Gaia
{


	//-----------------------------
	//!@brief �R���X�g���N�^
	//-----------------------------
	Window::Window()
		:m_pImpl(std::make_unique<pImpl>())
	{
		ZeroMemory(&m_pImpl->m_msg, sizeof(m_pImpl->m_msg));	//���b�Z�[�W�L���[��������

	}

	//-----------------------------
	//!@brief �f�X�g���N�^
	//-----------------------------
	Window::~Window() = default;

	//----------------------------------------------
	//!@brief	���b�Z�[�W����舵��	
	//										
	//!@param	�Ȃ�			
	//
	//!@retval  true	WM_QUIT�ȊO���󂯎�����Ƃ�
	//!@retval  false   WM_QUIT���󂯎�����Ƃ�
	//-----------------------------------------------
	bool Window::HandleMessage()
	{
		//�|�X�g�ς݃��b�Z�[�W�̏���
		while (PeekMessage(&m_pImpl->m_msg, nullptr, 0, 0, PM_REMOVE)) {

			//WM_QUIT�̎��̏���
			if (m_pImpl->m_msg.message == WM_QUIT)
				return false;

			//WM_QUIT�ȊO�̏���
			TranslateMessage(&m_pImpl->m_msg);
			DispatchMessage(&m_pImpl->m_msg);
		}

		return true;
	}

	//---------------------------------------
	//!@brief   �E�B���h�E�n���h���̎擾
	//
	//!@param�@�Ȃ�
	//
	//!@retval �E�B���h�E�n���h��
	//---------------------------------------
	HWND Window::GetWindowHandle() const
	{
		return m_pImpl->m_hWindow;
	}

	//------------------------------------------------------------
	//!@brief   �E�B���h�E�n���h���̎擾
	//
	//!@param�@�Ȃ�
	//
	//!@retval �I���R�[�h
	//
	//!@memo    WM_QUIT���󂯎�����Ƃ��ɐ���I�����邽�߂ɕK�v
	//------------------------------------------------------------
	int Window::GetExitCode() const
	{
		return m_pImpl->m_msg.wParam;
	}



	//------------------------------------------------------------------------------------------------------------------
	//!@brief	�E�B���h�E�v���V�[�W��													 
	//																													
	//																													
	//!@param[in]  hWnd          �E�B���h�E�n���h��(�A�v����\���l������)												
	//!@param[in]  message       16bit����̖��c�B���͎g���Ă��炸NULL�������Ă���									
	//!@param[in]  wParam        ������ւ̃|�C���^�B�R�}���h���C�������Ƃ��ēn���ꂽNULL�ŏI��镶����ւ̃|�C���^		
	//!@param[in]  lParam        �E�B���h�E���ǂ̂悤�ɕ\�����邩���w�肵���l											
	//																													
	//!@retval  ���b�Z�[�W��������																									
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
	//!@brief	�I�u�W�F�N�g�𐶐�				 
	//												 
	//!@param[in]    width    �E�B���h�E��		 
	//!@param[in]    height   �E�B���h�E����	 
	//!@param[in]	 name     �E�B���h�E�̖��O�@ 
	//												 
	//!@retval   �E�B���h�E�I�u�W�F�N�g
	//-----------------------------------------------
	std::unique_ptr<Window> Window::Create(int width, int height, LPCWSTR name)
	{
		auto pWindow = std::make_unique<Window>();

		if (!pWindow)
			return nullptr;


		//������
		if (FAILED(pWindow->m_pImpl->InitWindow(width, height, name))) {
			
			return nullptr;
		}


		//���������E�B���h�E�̃I�u�W�F�N�g��Ԃ�
		return pWindow;
	}

}