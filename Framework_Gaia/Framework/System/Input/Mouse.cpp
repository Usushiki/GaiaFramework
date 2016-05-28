//----------------------------------------------------------------//
//							 Mouse.cpp							�@//		
//																  //
//			About 		�}�E�X���͌��m�N���X�̃\�[�X�@�@		�@//
//     	    Last Update  2016/05/21	22:45						�@//
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//

//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include"Mouse.hpp"
#include<CommCtrl.h>

//-----------------------------
//���C�u���������N
//-----------------------------
#pragma comment(lib, "comctl32.lib")    //�R�����R���g���[�����C�u����


namespace Gaia
{
	//----------------------------------------
	//!@brief Mouse�N���X�̎����̏ڍ�
	//----------------------------------------
	class Mouse::pImpl
	{
	public:

		//�}�E�X���
		struct MouseState
		{
			BYTE buttonState;		//�{�^�����
			int wheelDelta;			//�z�C�[���̉�]��
			POINT pointerPosition;	//�}�E�X�|�C���^�[�̍��W
		};

		MouseState m_lastState;		//�O��̃}�E�X�̏��
		MouseState m_currentState;	//���݂̃}�E�X�̏��

		int m_wheelDelta;			//�z�C�[���̉�]��

		HWND m_hWindow;				//�E�B���h�E�n���h��


	public:
		//------------------------------------------
		//!@brief �R���X�g���N�^
		//
		//!@param[in] _hWindow �E�B���h�E�n���h��
		//------------------------------------------
		pImpl(HWND _hWindow)
			:m_hWindow(_hWindow)
			, m_currentState({ 0,0,{0,0} })
			, m_lastState({ 0,0,{0,0} })
		{
			//�E�B���h�E�̃T�u�N���X��
			UINT_PTR subclassID		= reinterpret_cast<DWORD_PTR>(this);
			DWORD_PTR referenceData = reinterpret_cast<DWORD_PTR>(this);
			SetWindowSubclass(_hWindow, Procedure, subclassID, referenceData);
		}

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~pImpl()
		{
			//�T�u�N���X���̉���
			UINT_PTR subclassID = reinterpret_cast<DWORD_PTR>(this);
			RemoveWindowSubclass(m_hWindow, Procedure, subclassID);
		}

		//----------------------------------------------
		//!@brief	�z�C�[����ԍX�V
		//
		//!@param[in] _delta �z�C�[���̉�]�� 
		//
		//!@retval �Ȃ�
		//----------------------------------------------
		void UpdateWheel(int _delta)
		{
			m_wheelDelta += _delta;
		}

		//-------------------------------------------------------------
		//!@brief  	�w�肳�ꂽ�{�^��������󋵉��ɉ�����Ă��邩�𔻒�
		//
		//!@param[in] _state�@  �}�E�X�̏��
		//!@param[in] _button   ���m�������{�^���̃R�[�h
		//
		//!@retval true  ������Ă���
		//		   false ������Ă��Ȃ� 
		//-------------------------------------------------------------
		inline bool IsButtonDown(const MouseState& _state, Button _button)
		{
			return (_state.buttonState & _button) ? true : false;
		}

	public:
		//------------------------------------------------------------------
		//! @brief �}�E�X�E�v���V�[�W��
		//!
		//! @param[in] hWindow     �E�B���h�E�n���h��
		//! @param[in] uMessage    ���b�Z�[�W�̎��ʎq
		//! @param[in] wParam      ���b�Z�[�W��1�Ԗڂ̃p�����[�^
		//! @param[in] lParam      ���b�Z�[�W��2�Ԗڂ̃p�����[�^
		//! @param[in] uIdSubclass �T�u�N���XID
		//! @param[in] dwRefData   �Q�ƃf�[�^
		//!
		//! @retval ���b�Z�[�W�����̌���(���M���ꂽ���b�Z�[�W�ɂ���ĈقȂ�)
		//------------------------------------------------------------------
		static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage,
			WPARAM wParam, LPARAM lParam,
			UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
		{
			// ���b�Z�[�W�̏���
			switch (uMessage)
			{
			case WM_MOUSEWHEEL:

				Mouse* mouse = reinterpret_cast<Mouse*>(dwRefData);
				if (mouse)
				{
					mouse->m_pImpl->UpdateWheel(GET_WHEEL_DELTA_WPARAM(wParam));
					return 0;
				}
				break;

			}
			// �����ŏ������Ȃ����b�Z�[�W��Windows�ɔC����
			return DefSubclassProc(hWindow, uMessage, wParam, lParam);
		}
	};
}



namespace Gaia
{
	//-----------------------------
	//!@brief �R���X�g���N�^
	//-----------------------------
	Mouse::Mouse(HWND _hWindow)
		:m_pImpl(std::make_unique<pImpl>(_hWindow))
	{

	}

	//-----------------------------
	//!@brief �f�X�g���N�^
	//-----------------------------
	Mouse::~Mouse() = default;


	//------------------------------------------------------------
	//!@brief	  	 �w�肳�ꂽ�{�^����������Ă��邩�𔻒�		
	//															
	//															
	//!@param[in] _button			���肵�����{�^���̃R�[�h			
	//															
	//!@retval  true  �{�^����������Ă���						
	//          false �{�^����������Ă��Ȃ�									
	//------------------------------------------------------------
	bool Mouse::GetIsButtonDown(Button _button) const
	{
		return m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button);
	}

	//------------------------------------------------------------
	//!@brief	  	 �w�肳�ꂽ�{�^����������Ă��Ȃ����𔻒�		
	//															
	//															
	//!@param[in] _button			���肵�����{�^���̃R�[�h			
	//															
	//!@retval  true  �{�^����������Ă��Ȃ�						
	//          false �{�^����������Ă���									
	//------------------------------------------------------------
	bool Mouse::GetIsButtonUp(Button _button) const
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
	bool Mouse::GetIsButtonPressed(Button _button) const
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
	bool Mouse::GetIsButtonReleased(Button _button) const
	{
		return !m_pImpl->IsButtonDown(m_pImpl->m_currentState, _button) &&
				m_pImpl->IsButtonDown(m_pImpl->m_lastState, _button);
	}

	//----------------------------------------------
	//! @brief �z�C�[���̉�]��(�m�b�`)�̎擾
	//
	//! @param �Ȃ�
	//
	//! @retval �z�C�[���̉�]��(�m�b�`)
	//----------------------------------------------
	int Mouse::GetWheelDelta() const
	{
		return m_pImpl->m_currentState.wheelDelta / WHEEL_DELTA;
	}

	//----------------------------------------------
	//! @brief �}�E�X�|�C���^�̍��W���擾
	//
	//! @param �Ȃ�
	//
	//! @retval �}�E�X�|�C���^�̍��W
	//----------------------------------------------
	POINT Mouse::GetPointerPosition() const
	{
		return m_pImpl->m_currentState.pointerPosition;
	}

	//----------------------------------------------
	//! @brief �}�E�X�|�C���^��X���W���擾
	//
	//! @param �Ȃ�
	//
	//! @retval �}�E�X�|�C���^��X���W
	//----------------------------------------------
	LONG Mouse::GetPointerPositionX() const
	{
		return m_pImpl->m_currentState.pointerPosition.x;
	}

	//----------------------------------------------
	//! @brief �}�E�X�|�C���^��Y���W���擾
	//
	//! @param �Ȃ�
	//
	//! @retval �}�E�X�|�C���^��Y���W
	//----------------------------------------------
	LONG Mouse::GetPointerPositionY() const
	{
		return m_pImpl->m_currentState.pointerPosition.y;
	}

	//----------------------------------------------
	//! @brief �}�E�X��Ԃ̍X�V
	//
	//! @param �Ȃ�
	//
	//! @retval �Ȃ�
	//----------------------------------------------
	void Mouse::Update()
	{
		//���݂̏�Ԃ̕ۑ�
		m_pImpl->m_lastState = m_pImpl->m_currentState;

		//�{�^���̌��݂̏�Ԃ��擾
		m_pImpl->m_currentState.buttonState = 0;

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			m_pImpl->m_currentState.buttonState |= Button::LEFT;
		}

		if (GetKeyState(VK_RBUTTON) & 0x8000)
		{
			m_pImpl->m_currentState.buttonState |= Button::RIGHT;
		}

		if (GetKeyState(VK_MBUTTON) & 0x8000)
		{
			m_pImpl->m_currentState.buttonState |= Button::WHEEL;
		}

		//�z�C�[����]�ʂ̎擾
		m_pImpl->m_currentState.wheelDelta = m_pImpl->m_wheelDelta;
		m_pImpl->m_wheelDelta = 0;

		//�}�E�X�|�C���^�[�̍��W���擾
		GetCursorPos(&m_pImpl->m_currentState.pointerPosition);
		ScreenToClient(m_pImpl->m_hWindow, &m_pImpl->m_currentState.pointerPosition);

	}
}

