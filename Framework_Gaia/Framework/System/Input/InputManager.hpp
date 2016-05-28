//----------------------------------------------------------------//
//					      InputManager.hpp						�@//		
//																  //
//			About 		���̓}�l�[�W���[�N���X�̃w�b�_�[�@	�@�@�@//
//     	    Last Update  2016/05/22	00:19						�@//
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
#include"Keyboard.hpp"
#include"GamePad.hpp"
#include"Mouse.hpp"

#include"../../Utility/Singleton.hpp"

namespace Gaia
{
	//���̓f�o�C�X
	enum InputDevice : BYTE
	{
		KEYBOARD = 0x01,
		GAMEPAD = 0x02,
		MOUSE = 0x04,
	};

	class InputManager :public  Utility::Singleton<InputManager>
	{
		//�t�����h�N���X
		friend class Utility::Singleton<InputManager>;


	private:
		std::unique_ptr<Keyboard>   m_pKeyboard = nullptr;	//�L�[�{�[�h
		std::unique_ptr<GamePad[]>  m_pGamePad = nullptr;	//�Q�[���p�b�h
		std::unique_ptr<Mouse>      m_pMouse = nullptr;		//�}�E�X
	
		InputDevice m_InputDevice;

	private:

		
		//-----------------------------
		//!@brief �R���X�g���N�^
		//----------------------------
		InputManager();
	
	public:

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~InputManager() = default;

	public:
		Keyboard* GetKeyboard()			const;	//�L�[�{�[�h�I�u�W�F�N�g�̎擾
		GamePad*  GetGamePad(int)		const;	//�Q�[���p�b�h�I�u�W�F�N�g�̎擾
		Mouse*	  GetMouse()			const;	//�}�E�X�I�u�W�F�N�g�̎擾


		//�X�V
		void Update();

		HRESULT Initialize(HWND,BYTE);

	};
}
