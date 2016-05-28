//----------------------------------------------------------------//
//					      GamePad.hpp							�@//		
//																  //
//			About 		�Q�[���p�b�h�N���X�̃w�b�_�[�@		�@�@�@//
//     	    Last Update  2016/05/21	22:42						�@//
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
#include<Xinput.h>
#include<memory>


//-----------------------------
//�Q�[���p�b�h�N���X
//-----------------------------
namespace Gaia
{
	
	class GamePad
	{
	
	public:
		//! @brief ���z�{�^���R�[�h
		enum Button : WORD
		{
			UP = XINPUT_GAMEPAD_DPAD_UP,
			DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
			LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
			RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
			START = XINPUT_GAMEPAD_START,
			BACK = XINPUT_GAMEPAD_BACK,
			L_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,
			R_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
			L_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,
			R_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			A = XINPUT_GAMEPAD_A,
			B = XINPUT_GAMEPAD_B,
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y,
		};


	private:

		//pimpl�C�f�B�I��
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;

		
	public:

		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		explicit GamePad(DWORD userIndex = 0);

	public:

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~GamePad();

		
	public:
		// �Q�[���p�b�h���ڑ�����Ă��邩�ǂ����𔻒f
		bool IsConnected() const;


		// �w�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
		bool IsButtonDown(Button button) const;

		// �w�肳�ꂽ�{�^����������Ă��Ȃ����ǂ����𔻒f
		bool IsButtonUp(Button button) const;

		// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
		bool IsButtonPressed(Button button) const;

		// �w�肳�ꂽ�{�^���������ꂽ���ǂ����𔻒f
		bool IsButtonReleased(Button button) const;


		// ���X�e�B�b�N��X���̒l�̎擾
		float GetLeftThumbX() const;

		// ���X�e�B�b�N��Y���̒l�̎擾
		float GetLeftThumbY() const;

		// �E�X�e�B�b�N��X���̒l�̎擾
		float GetRightThumbX() const;

		// �E�X�e�B�b�N��Y���̒l�̎擾
		float GetRightThumbY() const;


		// ���g���K�[�̒l�̎擾
		float GetLeftTrigger() const;

		// �E�g���K�[�̒l�̎擾
		float GetRightTrigger() const;
		
	public:
		// �Q�[���p�b�h�̏�Ԃ̍X�V
		void Update();
	
	};
}
