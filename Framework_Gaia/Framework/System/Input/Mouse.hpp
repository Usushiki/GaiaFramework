//----------------------------------------------------------------//
//							 Mouse.hpp							�@//		
//																  //
//			About 		�}�E�X���͌��m�N���X�̃w�b�_�[�@�@		�@//
//     	    Last Update  2016/05/21	22:45						�@//
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
#include<memory>

//-----------------------------
//�}�E�X�N���X
//-----------------------------
namespace Gaia
{
	class Mouse
	{
	public:

		//���z�{�^���R�[�h
		enum  Button : BYTE
		{
			LEFT = VK_LBUTTON,
			RIGHT = VK_RBUTTON,
			WHEEL  = VK_MBUTTON, 
		};

	
	public:
		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		explicit Mouse(HWND hWindow);

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~Mouse();


	public:
		// �w�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
		bool GetIsButtonDown(Button button) const;

		// �w�肳�ꂽ�{�^����������Ă��Ȃ����ǂ����𔻒f
		bool GetIsButtonUp(Button button) const;

		// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
		bool GetIsButtonPressed(Button button) const;

		// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
		bool GetIsButtonReleased(Button button) const;


		// �z�C�[���̉�]�ʂ̎擾
		int GetWheelDelta() const;


		// �}�E�X�|�C���^�̍��W�̎擾
		POINT GetPointerPosition() const;

		// �}�E�X�|�C���^��X���W�̎擾
		LONG GetPointerPositionX() const;

		// �}�E�X�|�C���^��Y���W�̎擾
		LONG GetPointerPositionY() const;


	public:
		// �}�E�X�̏�Ԃ̍X�V
		void Update();

	private:

		//pimpl�C�f�B�I��
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;


	};
}