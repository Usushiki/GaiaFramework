//------------------------------------------------//
//				Window�̍쐬�A�\��				  //
//												  //
//					�Q�lHP�@�@�@�@�@�@�@�@�@�@ �@ //�@�@�@
//			�L�ł��킩��Windows�v���O���~���O	  //
//	http://www.kumei.ne.jp/c_lang/index_sdk.html  //
//												  //
//												  //
//			2016 .5.12(Thu)11:28				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//


//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------

#include<Windows.h>
#include<wchar.h>

#include<d3d11.h>
#include<DirectXColors.h>
#include<memory>

#include"Framework\System\Debug\DebugLog.hpp"

#include"Framework\System\Window\Window.hpp"
#include"Framework\System\Direct3D\Direct3D.hpp"


// ���O��� ===================================================
using namespace Gaia;


//---------------------------------------------------------------------------------------------------------------------------//
//													���C���֐�																 //
//																															 //	
//									
//
//		HINSTANCE hInstance       �C���X�^���X�n���h��(�A�v����\���l������)												 //
//      HINSTANCE hPrevInstance   16bit����̖��c�B���͎g���Ă��炸NULL�������Ă���										 //
//		LPWSTR     lpCmdLine       ������ւ̃|�C���^�B�R�}���h���C�������Ƃ��ēn���ꂽNULL�ŏI��镶����ւ̃|�C���^		 //
//      int       nCmdShow        �E�B���h�E���ǂ̂悤�ɕ\�����邩���w�肵���l												 //
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
	
		
		//�o�b�N�o�b�t�@�̃N���A
		pDeviceConText->ClearRenderTargetView(pDirect3D->GetRenderTargetView(), DirectX::Colors::MidnightBlue);

		//�[�x�o�b�t�@�̃N���A
		pDeviceConText->ClearDepthStencilView(pDirect3D->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


		//�o�b�N�o�b�t�@�̕\��
		pSwapChain->Present(0, 0);

	}

	

//	DebugLogFileLine(LOG_TYPE::TYPE_NORMAL, "Test", i);


	return pWindow->GetExitCode();
}