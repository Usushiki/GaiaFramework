//----------------------------------------------------------------//
//					      Direct3D.h							�@//		
//																  //
//					  About 	DirectX�N���X�̃w�b�_�[			�@//
//     	  		    Last Update  2016/05/12 12:07				  //
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//


//-----------------------------
//���d�C���N���[�h�h�~
//-----------------------------
#pragma once


//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include<Windows.h>
#include<d3d11.h>
#include<wrl.h>
#include<memory>




//-----------------------------
//DirectX�N���X
//-----------------------------

namespace Gaia {

	class Direct3D final
	{

		template<typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

	private:
		//--------�R���X�g���N�^-------//
		Direct3D();

	public:
		//--------�f�X�g���N�^-------//
		~Direct3D();

		//--------�A�N�Z�b�T-------//
		ID3D11Device*			GetDevice()const;			//�f�o�C�X�̎擾
		ID3D11DeviceContext*	GetDeviceContext()const;	//�f�o�C�X�R���e�L�X�g�̎擾
		IDXGISwapChain*			GetSwapChain()const;		//�X���b�v�`�F�[���̎擾
		ID3D11RenderTargetView*	GetRenderTargetView()const;	//�����_�[�^�[�Q�b�g�r���[�̎擾
		ID3D11DepthStencilView*	GetDepthStencilView()const;	//�[�x�X�e���V���r���[�̎擾

		HRESULT SetScreenMode(bool);						//�X�N���[�����[�h��ݒ�

		//--------�t�@�N�g��-------//
		static Direct3D* Create(HWND);

	private:
		//pImpl�C�f�B�I��
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;

	};
}

