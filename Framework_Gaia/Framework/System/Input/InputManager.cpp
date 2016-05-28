//------------------------------------------------//
//			�C���v�b�g�}�l�[�W���[�N���X		  //
//												  //
//												  //
//			2016. 5.22(Sun)10:38				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//

//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include"InputManager.hpp"


//-----------------------------
//���C�u���������N
//-----------------------------
#pragma comment(lib, "Xinput9_1_0.lib")    // Xinput�p���C�u����



namespace Gaia
{

	//-----------------------------
	//!@brief �R���X�g���N�^
	//-----------------------------
	InputManager::InputManager()
		:Singleton()
	{

	}

	//------------------------------------------------------------
	//!@brief	�@	�L�[�{�[�h�I�u�W�F�N�g���擾	
	//															
	//!@param[in] �@�Ȃ�		
	//
	//!@retval     �L�[�{�[�h�I�u�W�F�N�g�̃|�C���^				
	//------------------------------------------------------------
	Keyboard* InputManager::GetKeyboard() const
	{
		return m_pKeyboard.get();		
	}

	//------------------------------------------------------------
	//!@brief	�@	�Q�[���p�b�h�I�u�W�F�N�g���擾	
	//															
	//!@param[in] �@�Ȃ�		
	//
	//!@retval     �Q�[���p�b�h�I�u�W�F�N�g�̃|�C���^				
	//------------------------------------------------------------
	GamePad* InputManager::GetGamePad(int _index) const
	{
		return &m_pGamePad[_index];
	}

	//------------------------------------------------------------
	//!@brief	�@	�}�E�X�I�u�W�F�N�g���擾	
	//															
	//!@param[in] �@�Ȃ�		
	//
	//!@retval     �}�E�X�I�u�W�F�N�g�̃|�C���^				
	//------------------------------------------------------------
	Mouse* InputManager::GetMouse() const
	{
		return m_pMouse.get();
	}


	//------------------------------------------------------------
	//!@brief	�@	�X�V	
	//															
	//!@param[in] �@�Ȃ�		
	//
	//!@retval     �Ȃ�				
	//------------------------------------------------------------
	void InputManager::Update()
	{
		//�L�[�{�[�h�̍X�V
		if (m_InputDevice & InputDevice::KEYBOARD)
		{
			m_pKeyboard->Update();
		}

		//�Q�[���p�b�h�̍X�V
		if (m_InputDevice & InputDevice::GAMEPAD)
		{
			for (int i = 0; i < XUSER_MAX_COUNT; i++)
			{
				m_pGamePad[i].Update();
			}
		}

		//�}�E�X�̍X�V
		if (m_InputDevice & InputDevice::MOUSE)
		{
			m_pMouse->Update();
		}
	}

	//-----------------------------------------------
	//!@brief	����������				 
	//												 
	//!@param[in]    _hWindow      �E�B���h�E�n���h��		 
	//!@param[in]    _inputDevice  �g�p����C���v�b�g�f�o�C�X	  
	//												 
	//!@retval   S_OK     ����
	//!@retval   E_FAIL   ���s
	//-----------------------------------------------
	HRESULT InputManager::Initialize(HWND _hWindow, BYTE _inputDevice)
	{
		m_InputDevice = (InputDevice)_inputDevice;

		//�L�[�{�[�h�I�u�W�F�N�g�𐶐�
		if (_inputDevice & InputDevice::KEYBOARD)
		{
			m_pKeyboard = std::make_unique<Keyboard>();
		}

		//�}�E�X�I�u�W�F�N�g�𐶐�
		if (_inputDevice & InputDevice::MOUSE)
		{
			m_pMouse = std::make_unique<Mouse>(_hWindow);

			if (!m_pMouse)
			{
				return E_FAIL;
			}
		}

		//�Q�[���p�b�h�I�u�W�F�N�g�𐶐�
		if (_inputDevice & InputDevice::GAMEPAD)
		{
			m_pGamePad.reset(new GamePad[XUSER_MAX_COUNT]);

			if (!m_pGamePad) 
			{
				return E_FAIL;
			}
		}

		return S_OK;
	}

}