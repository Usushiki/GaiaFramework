//----------------------------------------------------------------//
//					      GameBase.cpp							�@//		
//																  //
//			  About 	�Q�[���̃x�[�X�ƂȂ���N���X�̃\�[�X	�@//
//     	  		    Last Update  2015/07/25						  //
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//

// ���d�C���N���[�h�h�~ ===================================================
#pragma once

//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
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
	//!@brief �R���X�g���N�^
	//
	//!@param[in] title  �E�B���h�E�̃^�C�g��
	//!@param[in] width  �E�B���h�E��
	//!@param[in] height �E�B���h�E�̍���
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
		// �������[���[�N���o�̂��߂̐ݒ�
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif 
	}


	//-----------------------------
	//!@brief �f�X�g���N�^
	//-----------------------------
	GameBase::~GameBase()
	{
	}


	//----------------------------------------------
	//!@brief		�V�X�e���̏�����				
	//												
	//!@param[in] �Ȃ�								
	//												
	//!@retval 	  true		����������				
	//		  	  false     ���s					
	//----------------------------------------------
	bool GameBase::InitializeBaseSystem()
	{
		//�E�B���h�E�̍쐬
		m_pWindow = Window::Create(m_ScreenWidth, m_ScreenHeight, m_GameTitle.c_str());
		if (!m_pWindow) {
			MessageBox(nullptr, L"�E�B���h�E�̍쐬�Ɏ��s���܂���", nullptr, MB_OK);
			return false;
		}

		//Direct3D�I�u�W�F�N�g���쐬
		m_pDirect3D.reset(Direct3D::Create(m_pWindow->GetWindowHandle()));
		if (!m_pDirect3D)
		{
			MessageBox(nullptr, L"Direct3D�̐ݒ�Ɏ��s���܂���", nullptr, MB_OK);
			return false;
		}

		m_pFrameRateController = std::make_unique<FrameRateController>(60);

		BYTE device = InputDevice::GAMEPAD | InputDevice::KEYBOARD | InputDevice::MOUSE;
		//InputManager::Get();


		//����������
		return true;
	}


	//----------------------------------------------
	//!@brief		�f�o�C�X�̎擾				 
	//											 
	//!@param[in]	�Ȃ�						 
	//											 
	//!@retval  	�f�o�C�X�̃|�C���^			 
	//----------------------------------------------
	ID3D11Device* GameBase::GetDevice() const
	{
		return m_pDirect3D->GetDevice();
	}


	//----------------------------------------------
	//!@brief		�f�o�C�X�R���e�L�X�g�̎擾		
	//												
	//!@param[in]	�Ȃ�							
	//												
	//!@retval  	�f�o�C�X�R���e�L�X�g�̃|�C���^	
	//----------------------------------------------
	ID3D11DeviceContext* GameBase::GetDeviceContext() const
	{
		return m_pDirect3D->GetDeviceContext();
	}


	//----------------------------------------------
	//!@brief		�X���b�v�`�F�[���̎擾			
	//												
	//!@param[in]	�Ȃ�							
	//												
	//!@retval  	�X���b�v�`�F�[���̃|�C���^		
	//----------------------------------------------
	IDXGISwapChain* GameBase::GetSwapChain() const
	{
		return m_pDirect3D->GetSwapChain();
	}


	//-------------------------------------------------
	//!@brief		�����_�[�^�[�Q�b�g�r���[�̎擾	
	//												
	//!@param[in]	�Ȃ�							
	//												
	//!@retval  	�����_�[�^�[�Q�b�g�r���[�̃|�C���^
	//-------------------------------------------------
	ID3D11RenderTargetView* GameBase::GetRenderTargetView() const
	{
		return m_pDirect3D->GetRenderTargetView();
	}


	//----------------------------------------------
	//!@brief		�����_�[�^�[�Q�b�g�r���[�̎擾	
	//												
	//!@param[in]	�Ȃ�							
	//												
	//!@retval  	�[�x�X�e���V���r���[�̃|�C���^	
	//----------------------------------------------
	ID3D11DepthStencilView* GameBase::GetDepthStencilView() const
	{
		return m_pDirect3D->GetDepthStencilView();
	}


	//----------------------------------------------
	//!@brief		�E�B���h�E�n���h���̎擾		
	//												
	//!@param[in]	�Ȃ�							
	//												
	//!@retval  	�E�B���h�E�n���h��				
	//----------------------------------------------
	HWND GameBase::GetWindowHandle() const
	{
		return m_pWindow->GetWindowHandle();
	}


	//----------------------------------------------
	//!@brief		�t���[�����[�g�̎擾			
	//												
	//!@param[in]	�Ȃ�							
	//												
	//!@retval  	�t���[�����[�g					
	//----------------------------------------------
	double GameBase::GetFrameRate() const
	{
		return m_pFrameRateController->GetFrameRate();
		
	}


	//----------------------------------------------
	//!@brief		�t���[�����[�g�̐ݒ�			
	//												
	//!@param[in]	framerate �t���[�����[�g		
	//												
	//!@retval  	�Ȃ�							
	//----------------------------------------------
	void GameBase::SetFrameRate(int framerate)
	{
		m_pFrameRateController->SetFrameRate(framerate);
	}


	//---------------------------------------------------------
	//!@brief		���s�֐�								
	//														
	//!@param[in]	�Ȃ�									
	//														
	//!@retval  	ExitCode �E�B���h�E���b�Z�[�W�̏I���R�[�h
	//!@retval		    0	 �ُ�I��						
	//---------------------------------------------------------
	int GameBase::Run(ScreenMode screenmode)
	{
		//�V�X�e����������
		if (!InitializeBaseSystem()) {
			return 0;
		}

		//�Q�[���̏�����
		if (!Initialize()) {
			Finalize();
			return 0;
		}



		//�E�B���h�E���[�h�̐ݒ�
		m_pDirect3D->SetScreenMode(isBool(screenmode));

		//�t���[�����[�g�̌v�����J�n
		m_pFrameRateController->Start();

		//���b�Z�[�W���[�v
		while (m_pWindow->HandleMessage()) {

			//�t���[�����[�g�̒���
			m_pFrameRateController->Regulate();

			//�Q�[���̍X�V
			Update();

			//1�t���[���Ɉ��
			if (!m_pFrameRateController->GetIsSkip())
				//�Q�[���̕`��
				Render();

		}

		//�Q�[���̌�n��
		Finalize();

		//�I���R�[�h��Ԃ�
		return m_pWindow->GetExitCode();

	}

}