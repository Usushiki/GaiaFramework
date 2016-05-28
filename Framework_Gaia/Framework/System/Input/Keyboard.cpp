//----------------------------------------------------------------//
//					      Keyboard.cpp							�@//		
//																  //
//					 About �L�[�{�[�h���͌��m�N���X�̃\�[�X		�@//
//     	  		    Last Update  2016/05/13 09:21				  //
//					Place Valencienne France					  //
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//


//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include"Keyboard.hpp"




namespace Gaia
{
	
	//----------------------------------------
	//!@brief Keyboard�N���X�̎����̏ڍ�
	//----------------------------------------
	class Keyboard::pImpl
	{
	public:
		//�L�[���\����
		struct KeyState
		{
			BYTE key[256];
		};

		KeyState m_CurrentKeyState;				//���݂̃L�[�̓��͏��
		KeyState m_LastKeyState;				//1�t���[���O�̃L�[�̓��͏��


		//-----------------------------------------------------
		//�����L�[�R�[�h���X�g
		//-----------------------------------------------------
		const int NonCheckKeyList[10] = { 1, 2, 8, 13, 16, 17, 28, 160, 161, 162 };
		
		//�L�[�R�[�h��
		static const int KEY_NUM = 240;

	public:

		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		pImpl()
			:m_LastKeyState({ { 0 } })
			, m_CurrentKeyState({ { 0 } })
		{

		}

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~pImpl() = default;

	public:
		//-------------------------------------------------------------
		//!@brief  	�w�肳�ꂽ�L�[������󋵉��ɉ�����Ă��邩�𔻒�
		//
		//!@param[in] _state�@�L�[�{�[�h�̏��
		//!@param[in] _ key   ���m�������L�[�̃R�[�h
		//
		//!@retval true  ������Ă���
		//		   false ������Ă��Ȃ� 
		//-------------------------------------------------------------
		inline bool GetIsKeyDown(const KeyState& _state, BYTE _key) const
		{
			return (_state.key[_key] & 0x80) ? true : false;
		}

		//---------------------------------------------------------------
		//!@brief ���ݎQ�Ƃ��Ă���L�[���������X�g�ɓ����Ă��邩�𔻒�
		//
		//!@param[in] _key �L�[�R�[�h
		//
		//!@retval  true   �����Ă���
		//			false  �����Ă��Ȃ�
		//---------------------------------------------------------------
		bool IsFindNonCheckKey(int _key) const
		{
			for (int i : NonCheckKeyList) {
				if (NonCheckKeyList[i] == _key)
					return true;
			}

			return false;
		}

	};
}


namespace Gaia
{

	//-----------------------------
	//!@brief �R���X�g���N�^
	//-----------------------------
	Keyboard::Keyboard()
		:m_pImpl(std::make_unique<pImpl>())
	{

	}

	//-----------------------------
	//!@brief �f�X�g���N�^
	//-----------------------------
	Keyboard::~Keyboard() = default;

	//------------------------------------------------------------
	//!@brief			�L�[�{�[�h�̏�Ԃ̍X�V					
	//															
	//!@param[in] �Ȃ�												
	//															
	//!@retvl �Ȃ�												
	//------------------------------------------------------------
	void Keyboard::Update()
	{
		//��Ԃ̗�����ۑ�
		m_pImpl->m_LastKeyState = m_pImpl->m_CurrentKeyState;

		//���݂̃L�[�{�[�h�̏�Ԃ��擾
		GetKeyboardState(m_pImpl->m_CurrentKeyState.key);
	}


	//------------------------------------------------------------
	//!@brief	  	 �w�肳�ꂽ�L�[��������Ă��邩�𔻒�		
	//															
	//															
	//!@param[in] _key			���肵�����L�[�̃R�[�h			
	//															
	//!@retval  true  �L�[��������Ă���						
	//          false ����ȊO									
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyDown(BYTE _key)const
	{
		return m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key);
	}

	//------------------------------------------------------------
	//!@brief   �w�肳�ꂽ�L�[��������Ă��Ȃ����𔻒�			
	//																
	//																
	//!@param[in] _key			���肵�����L�[�̃R�[�h			
	//																
	//!@retval    true  �L�[��������Ă��Ȃ�						
	//            false ����ȊO									
	//------------------------------------------------------------
	bool Keyboard::GetIskeyUp(BYTE _key)const
	{
		return !m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key);
	}


	//------------------------------------------------------------
	//!@brief   �w�肳�ꂽ�L�[�������ꂽ���𔻒�			
	//															
	//															
	//!@param[in]  _key			���肵�����L�[�̃R�[�h		
	//															
	//!@retval     true  �L�[�������ꂽ						
	//             false ����ȊO								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyPress(BYTE _key)const
	{
		return m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key) &&
			  !m_pImpl->GetIsKeyDown(m_pImpl->m_LastKeyState, _key);
	}


	//------------------------------------------------------------
	//!@brief	    �w�肳�ꂽ�L�[�������ꂽ���𔻒�			
	//															
	//															
	//!@param[in]  _key			���肵�����L�[�̃R�[�h		
	//															
	//!@retval true  �L�[�������ꂽ						
	//              false ����ȊO								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyRelease(BYTE _key)const
	{
		return !m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key) &&
				m_pImpl->GetIsKeyDown(m_pImpl->m_LastKeyState, _key);
	}

	//------------------------------------------------------------
	//!@brief �w�肳�ꂽ�L�[��1�t���[���O�ɉ�����Ă������𔻒�	
	//															
	//															
	//!@param[in]  _key			���肵�����L�[�̃R�[�h		
	//															
	//!@retval     true  �L�[��������Ă���					
	//             false ����ȊO								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyDownLastFrame(BYTE _key)const
	{
		return m_pImpl->GetIsKeyDown(m_pImpl->m_LastKeyState, _key);
	}



	//------------------------------------------------------------
	//!@brief	�@	 �L�[�ǂꂩ��ł���������Ă��邩�𔻒�	
	//															
	//!@param[in] �@�Ȃ�		
	//
	//!@retval     true  �L�[��������Ă���						
	//             false ����ȊO								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyInputAll()
	{
		for (int i = 0; i < m_pImpl->KEY_NUM; i++) {
			if ((m_pImpl->m_CurrentKeyState.key[i] & 0x80) && !m_pImpl->IsFindNonCheckKey(i)) {
				return true;
			}
		}

		return false;
	}


	
}