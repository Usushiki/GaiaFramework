//----------------------------------------------------------------//
//					      GameBase.h							�@//		
//																  //
//			About 	�Q�[���̃x�[�X�ƂȂ���N���X�̃w�b�_�[�@�@�@//
//     	    Last Update  2015/07/20								�@//
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//

//-----------------------------
//���d�C���N���[�h�h�~
//-----------------------------
#pragma once




//-----------------------------
//�N���X�O���錾
//-----------------------------
namespace Gaia
{
	class Window;
	class Direct3D;
	class FrameRateController;
	
}



//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include<memory>

#include<string>
#include<Windows.h>

#include<d3d11.h>


#include"../Window/ScreenMode.hpp"


//-----------------------------
//GameBase�N���X
//-----------------------------
namespace Gaia
{

	class GameBase
	{
	private:
		

		std::unique_ptr<Window>			  	 m_pWindow;					//�E�B���h�E
		std::unique_ptr<Direct3D>			 m_pDirect3D;				//DirectX�I�u�W�F�N�g
		std::unique_ptr<FrameRateController> m_pFrameRateController;	//�t���[�����[�g�Ǘ��I�u�W�F�N�g

		std::wstring	m_GameTitle;				//�Q�[���^�C�g��
		int				m_ScreenWidth;				//��ʕ�
		int				m_ScreenHeight;				//��ʂ̍���


	public:
		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		GameBase(LPCWSTR, int, int);

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		virtual ~GameBase();


		//--------�A�N�Z�b�T-------//
		HWND GetWindowHandle()const;						//�E�B���h�E�n���h���̎擾

		ID3D11Device*			GetDevice()const;			//�f�o�C�X�̎擾
		ID3D11DeviceContext*	GetDeviceContext()const;	//�f�o�C�X�R���e�L�X�g�̎擾
		IDXGISwapChain*			GetSwapChain()const;		//�X���b�v�`�F�[���̎擾
		ID3D11RenderTargetView*	GetRenderTargetView()const;	//�����_�[�^�[�Q�b�g�r���[�̎擾
		ID3D11DepthStencilView*	GetDepthStencilView()const;	//�[�x�X�e���V���r���[�̎擾
		double GetFrameRate()const;							//�t���[�����[�g�̎擾
		void SetFrameRate(int);								//�t���[�����[�g�̐ݒ�


		//--------���s�֐�-------//
		int Run(ScreenMode);

		//--------------------------���������֐�--------------------------//
	private:

		//�V�X�e��������
		bool InitializeBaseSystem();

		//������
		virtual bool Initialize() = 0;

		//�X�V
		virtual void Update() = 0;

		//�`��
		virtual void Render() = 0;

		//��n��
		virtual void Finalize() = 0;

	};


}

