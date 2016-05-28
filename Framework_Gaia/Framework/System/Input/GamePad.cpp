//------------------------------------------------//
//				�Q�[���p�b�h�N���X				  //
//												  //
//												  //
//			2016. 5.19(Thu)19:43				  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//


//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include"GamePad.hpp"


//-----------------------------
//���C�u���������N
//-----------------------------
#pragma comment(lib, "Xinput9_1_0.lib")    // Xinput�p���C�u����


namespace Gaia
{

	//----------------------------------------
	//!@brief GamePad�N���X�̎����̏ڍ�
	//----------------------------------------
	class GamePad :: pImpl
	{
	public:
	
		//�Q�[���p�b�h��ԃN���X
		struct GamePadState
		{
			bool         isConnected;    //!< �ڑ��̗L��
			XINPUT_STATE state;          //!< �Q�[���p�b�h�̏��
		};


		//�����o�ϐ�
		DWORD m_userIndex;				//!< ���[�U�[�̃Q�[���p�b�h�̃C���f�b�N�X
		GamePadState m_lastState;       //!< �O��̃Q�[���p�b�h�̏��
		GamePadState m_currentState;    //!< ���݂̃Q�[���p�b�h�̏��


		static const int TRIGGER_MAX = 255;    //!< �g���K�[�̍ő�l
		static const int THUMB_LIMIT = 32767;    //!< �X�e�B�b�N�̏㉺��(�})


	public:

		//--------------------------------------------------
		//!@brief �R���X�g���N�^
		//
		//!@param[in] userIndex �Q�[���p�b�h�̃C���f�b�N�X
		//--------------------------------------------------
		pImpl(DWORD _userIndex)
			:m_userIndex(_userIndex)
			, m_lastState({ false,{0} })
			, m_currentState({ false,{0} })
		{
		}

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~pImpl() = default;


	public:
		
		//----------------------------------------------------------------
		//!@brief  �����Ԃɂ����Ďw�肳�ꂽ�{�^����������Ă��邩�ǂ����𔻒f
		//
		//!@param[in] state ��������������
		//!@brief[in] button �@�{�^���R�[�h
		//----------------------------------------------------------------
		inline bool IsButtonDown(const GamePadState& state, Button button)const
		{
			return (state.state.Gamepad.wButtons & button) ? true : false;
		}


		//-----------------------------
		//!@brief �X�e�B�b�N�l�̒���
		//
		//!@param[in] �Ȃ�
		//
		//!@retval    �Ȃ�
		//-----------------------------
		void AdjustThumb()
		{
			// ���X�e�B�b�N�̒l�̒���
			AdjustThumb(&m_currentState.state.Gamepad.sThumbLX);
			AdjustThumb(&m_currentState.state.Gamepad.sThumbLY);


			// �E�X�e�B�b�N�̒l�̒���
			AdjustThumb(&m_currentState.state.Gamepad.sThumbRX);
			AdjustThumb(&m_currentState.state.Gamepad.sThumbRY);
		}

		//------------------------------------
		//!@brief �X�e�B�b�N�e���̒l����
		//
		//!@param[in] *thumb ���̒l
		//
		//!@retval    �Ȃ�
		//------------------------------------
		void AdjustThumb(SHORT* _thumb)
		{
			// ���X�e�B�b�N��X���̒l�̒���
			if (*_thumb <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				*_thumb > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				*_thumb = 0;
			}
			else if (*_thumb < -THUMB_LIMIT)
			{
				*_thumb = -THUMB_LIMIT;
			}
		}

		//------------------------------------------------
		//!@brief �X�e�B�b�N�l�̐��K��
		//
		//!@param[in] thumb �X�e�B�b�N�l
		//
		//!@retval   ���K�����ꂽ�X�e�B�b�N�l(0.0�`1.0)
		//------------------------------------------------
		float NormalizeThumb(SHORT thumb) const
		{
			return thumb / static_cast<float>(THUMB_LIMIT);
		}

		//-----------------------------
		//!@brief �g���K�[�l�̒���
		//
		//!@param[in] �Ȃ�
		//
		//!@retval    �Ȃ�
		//-----------------------------
		void AdjustTrigger()
		{
			// ���g���K�[�̒l�̒���
			if (m_currentState.state.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				m_currentState.state.Gamepad.bLeftTrigger = 0;
			}


			// �E�g���K�[�̒l�̒���
			if (m_currentState.state.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				m_currentState.state.Gamepad.bRightTrigger = 0;
			}
		}

		//------------------------------------------------
		//!@brief �g���K�[�l�̐��K��
		//
		//!@param[in] trigger �g���K�[�l
		//
		//!@retval   ���K�����ꂽ�g���K�[�l(0.0�`1.0)
		//------------------------------------------------
		float NormalizeTrigger(BYTE trigger) const
		{
			return trigger / static_cast<float>(TRIGGER_MAX);
		}
	};

}

namespace Gaia
{

	//-----------------------------
	//!@brief �R���X�g���N�^
	//-----------------------------
	GamePad::GamePad(DWORD userIndex)
		:m_pImpl(std::make_unique<pImpl>(userIndex))
	{

	}

	//-----------------------------
	//!@brief �f�X�g���N�^
	//-----------------------------
	GamePad::~GamePad() = default;


	//----------------------------------------------
	//!@brief �Q�[���p�b�h���ڑ�����Ă��邩
	//
	//!@param[in]  �Ȃ�
	//
	//!@retval true �ڑ�����Ă���
	//!@retval false �ڑ�����Ă��Ȃ�
	//----------------------------------------------
	bool GamePad::IsConnected() const
	{
		return m_pImpl->m_currentState.isConnected;
	}

	//----------------------------------------------
	//!@brief �w�肵���{�^����������Ă��邩
	//
	//!@param[in]  button�@���f�������{�^���̃R�[�h
	//
	//!@retval true ������Ă���
	//!@retval false ������Ă��Ȃ�
	//----------------------------------------------
	bool GamePad::IsButtonDown(Button _button)const
	{
		return m_pImpl->IsButtonDown(m_pImpl->m_currentState,_button);
	}

	//----------------------------------------------
	//!@brief �w�肵���{�^����������Ă��Ȃ���
	//
	//!@param[in]  button�@���f�������{�^���̃R�[�h
	//
	//!@retval true ������Ă��Ȃ�
	//!@retval false ������Ă���
	//----------------------------------------------
	bool GamePad::IsButtonUp(Button _button) const
	{
		return !m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button);
	}

	//----------------------------------------------
	//!@brief �w�肵���{�^����������Ă���
	//
	//!@param[in]  button�@���f�������{�^���̃R�[�h
	//
	//!@retval true ������Ă���
	//!@retval false ������Ă��Ȃ�
	//
	//!@note �����ꂽ�u�Ԃ����m
	//----------------------------------------------
	bool GamePad::IsButtonPressed(Button _button) const
	{
		return m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button) &&
			  !m_pImpl->IsButtonDown(m_pImpl->m_lastState, _button);
	}

	//----------------------------------------------
	//!@brief �w�肵���{�^���������ꂽ��
	//
	//!@param[in]  button�@���f�������{�^���̃R�[�h
	//
	//!@retval true ������Ă��Ȃ�
	//!@retval false ������Ă�
	//
	//!@note �����ꂽ�u�Ԃ����m
	//----------------------------------------------
	bool GamePad::IsButtonReleased(Button _button) const
	{
		return !m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button) &&
				m_pImpl->IsButtonDown(m_pImpl->m_lastState, _button);
	}

	//----------------------------------------------
	//!@brief ���X�e�B�b�N��X���̒l���擾
	//
	//!@param[in] �Ȃ�
	//
	//!@retval ���X�e�B�b�NX���̒l(0.0 �` 1.0)
	//----------------------------------------------
	float GamePad::GetLeftThumbX() const
	{
		return m_pImpl->NormalizeThumb( m_pImpl->m_currentState.state.Gamepad.sThumbLX);
	}

	//----------------------------------------------
	//!@brief ���X�e�B�b�N��Y���̒l���擾
	//
	//!@param[in] �Ȃ�
	//
	//!@retval ���X�e�B�b�NY���̒l(0.0 �` 1.0)
	//----------------------------------------------
	float GamePad::GetLeftThumbY() const
	{
		return m_pImpl->NormalizeThumb(m_pImpl->m_currentState.state.Gamepad.sThumbLY);
	}


	//----------------------------------------------
	//!@brief �E�X�e�B�b�N��X���̒l���擾
	//
	//!@param[in] �Ȃ�
	//
	//!@retval �E�X�e�B�b�NX���̒l(0.0 �` 1.0)
	//----------------------------------------------
	float GamePad::GetRightThumbX() const
	{
		return m_pImpl->NormalizeThumb(m_pImpl->m_currentState.state.Gamepad.sThumbRX);
	}

	//----------------------------------------------
	//!@brief �E�X�e�B�b�N��Y���̒l���擾
	//
	//!@param[in] �Ȃ�
	//
	//!@retval �E�X�e�B�b�NY���̒l(0.0 �` 1.0)
	//----------------------------------------------
	float GamePad::GetRightThumbY() const
	{
		return m_pImpl->NormalizeThumb(m_pImpl->m_currentState.state.Gamepad.sThumbRY);
	}

	//----------------------------------------------
	//!@brief ���g���K�[�̒l���擾
	//
	//!@param[in] �Ȃ�
	//
	//!@retval ���g���K�[�̒l(0.0 �` 1.0)
	//----------------------------------------------
	float GamePad::GetLeftTrigger() const
	{
		return m_pImpl->NormalizeTrigger(m_pImpl->m_currentState.state.Gamepad.bLeftTrigger);
	}

	//----------------------------------------------
	//!@brief �E�g���K�[�̒l���擾
	//
	//!@param[in] �Ȃ�
	//
	//!@retval �E�g���K�[�̒l(0.0 �` 1.0)
	//----------------------------------------------
	float GamePad::GetRightTrigger() const
	{
		return m_pImpl->NormalizeTrigger(m_pImpl->m_currentState.state.Gamepad.bRightTrigger);
	}

	//----------------------------------------------
	//!@brief �X�V
	//
	//!@param[in] �Ȃ�
	//
	//!@retval �Ȃ�
	//----------------------------------------------
	void GamePad::Update()
	{
		//���݂̏�Ԃ̕ۑ�
		m_pImpl->m_lastState = m_pImpl->m_currentState;

		
		//���݂̏�Ԃ��擾	
		DWORD result = XInputGetState(m_pImpl->m_userIndex, &m_pImpl->m_currentState.state);
		
		

		if (result == ERROR_SUCCESS)
		{
			m_pImpl->m_currentState.isConnected = true;

			m_pImpl->AdjustThumb();
			m_pImpl->AdjustTrigger();
		}
		else
		{
			m_pImpl->m_currentState.isConnected = false;
		}
		
	}

}