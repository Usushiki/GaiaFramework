//----------------------------------------------------------------//
//					       FrameRateController.cpp				�@//		
//																  //
//				  About 	�t���[�����[�g�Ǘ��N���X�̃\�[�X	�@//
//     	  		    Last Update  2015/07/25						  //
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
#include"FrameRateController.hpp"

namespace Gaia
{
	//----------------------------------------
	//!@brief FrameRateController�N���X�̎����̏ڍ�
	//----------------------------------------
	class FrameRateController::pImpl
	{
		//�����o�ϐ�
	public:
		std::unique_ptr<Utility::Timer> m_pTimer;		//�^�C�}�[
		double m_FrameRate;								//�t���[����
		UINT m_StartTime;								//�v���J�n����[ns]
		UINT m_FrameTime;								//1�t���[�������莞��[ns]
		UINT m_ElapsedTime;								//�o�ߎ���[ns]
		UINT m_ElapsedTime_Total;						//���o�ߎ���[ns]

		int m_FrameCount;								//�t���[���J�E���^�[

		bool m_IsSkip;

	public:

		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		pImpl(UINT _FrameRate = S_FRAME_RATE_DEFAULT)
			:m_FrameRate(0)
			,m_StartTime(0)
			,m_FrameTime(0)
			, m_FrameCount(0)
			, m_ElapsedTime(0)
			, m_ElapsedTime_Total(0)
			, m_IsSkip(false)
			, m_pTimer(nullptr)
		{
			SetFrameRate(_FrameRate);
			m_pTimer = std::make_unique<Utility::Timer>();
		}

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~pImpl() = default;

	private:
		//-----------------------------
		//!@brief �X�V
		//
		//!@param[in] �Ȃ�
		//
		//!@retval �Ȃ�
		//-----------------------------
		void Update()
		{
			//�J�E���g�A�b�v
			m_FrameCount++;

			//1�t���[���̌o�ߎ��Ԃ𑍌o�ߎ��Ԃɉ��Z
			m_ElapsedTime_Total += m_ElapsedTime;

			//���o�ߎ��Ԃ�1�b�𒴂���Ȃ�
			if (m_ElapsedTime_Total >= m_pTimer->SECOND) {

				//1�b�o�߂���܂ł̃t���[�������Z�o
				m_FrameRate = static_cast<double>(m_FrameRate*m_pTimer->SECOND) / m_ElapsedTime_Total;

				//�J�E���^�Ƒ��o�ߎ��Ԃ����Z�b�g
				m_FrameCount = 0;
				m_ElapsedTime_Total = 0;
			}

		}

	public:

		//-----------------------------
		//!@brief �v���J�n
		//
		//!@param[in] �Ȃ�
		//
		//!@retval �Ȃ�
		//-----------------------------
		void Start()
		{
			m_pTimer->Reset();
			m_StartTime = m_pTimer->GetTime();

		}

		
		//-----------------------------
		//!@brief �t���[�����[�g�̒���
		//
		//!@param[in] �Ȃ�
		//
		//!@retval �Ȃ�
		//-----------------------------
		void Regulate()
		{
			//1�t���[���̌o�ߎ��Ԃ��Z�o
			m_ElapsedTime = m_pTimer->GetTime() - m_StartTime;


			//�t���[�����[�g�̒���
			if (m_ElapsedTime < m_FrameTime)
			{
				m_IsSkip = false;

				//�L���[�⍂��������Ԃ̃��b�N�̊m�F�̖h�~
				//���X���b�h��荂���D��x�����X���b�h�����s�\���A�c��̃^�C���X���C�X��j��
				Sleep(0);

				//�X���[�v���[�v
				while (m_ElapsedTime < m_FrameTime)
				{
					//���̖��߂�x�点��(�v���Z�b�T�[�ŗL����)
					_mm_pause();

					//�o�ߎ��Ԃ̍X�V
					m_ElapsedTime = m_pTimer->GetTime() - m_StartTime;
				}

			}
			else
				m_IsSkip = true;


			//�X�V
			Update();

			//�t���[���J�n���Ԃ̍X�V
			m_StartTime = m_pTimer->GetTime();

		}

		//-----------------------------
		//!@brief �t���[�����[�g�̐ݒ�
		//
		//!@param[in] �Ȃ�
		//
		//!@retval �Ȃ�
		//-----------------------------
		void SetFrameRate(UINT _frameRate)
		{
			//1�t���[��������̎��Ԃ��v�Z
			m_FrameTime = m_pTimer->SECOND / _frameRate;
		}

	};
}

namespace Gaia
{
	using namespace Utility;

		//----------------------------------------------------------
		//!@brief		�R���X�g���N�^								
		//															
		//!@param[in] framerate		�����t���[�����[�g				
		//	
		//!@note   �w�肪�Ȃ��ꍇ�̓f�t�H���g�l��60���Z�b�g			
		//----------------------------------------------------------
		FrameRateController::FrameRateController(UINT framerate)
			:m_pImpl(std::make_unique<pImpl>(framerate))
		{
			
		}

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		FrameRateController::~FrameRateController()
		{

		}


		//---------------------------------------------------
		//!@brief		�t���[�����[�g�̌v���J�n			
		//													
		//!@param[in]	�Ȃ�								
		//													
		//!@retval  �@ �Ȃ�									
		//---------------------------------------------------
		void FrameRateController::Start()
		{
			m_pImpl->Start();
		}


		//---------------------------------------------------
		//!@brief		�t���[�����[�g�̒���				
		//													
		//!@param[in]	�Ȃ�								
		//													
		//!@retval  �@  �Ȃ�								
		//---------------------------------------------------
		void FrameRateController::Regulate()
		{
			m_pImpl->Regulate();
		}


		//---------------------------------------------------
		//!@brief			�t���[�����[�g�̐ݒ�			
		//													
		//!@param[in]	 framerate  �t���[�����[�g			
		//													
		//!@retval  �@�@ �Ȃ�								
		//---------------------------------------------------
		void FrameRateController::SetFrameRate(UINT framerate)
		{
			m_pImpl->SetFrameRate(framerate);
		}


		//---------------------------------------------------
		//!@brief		�t���[�����[�g�̎擾				
		//													
		//!@param[in]	�Ȃ�								
		//													
		//!@retval   �t���[�����[�g							
		//---------------------------------------------------
		double FrameRateController::GetFrameRate() const
		{
			return m_pImpl->m_FrameRate;
		}


		//---------------------------------------------------
		//!@brief			�X�L�b�v�t���O�̎擾			
		//													
		//!@param[in]	�Ȃ�								
		//													
		//!@retval  �@�t���[�����X�L�b�v���邩�̃t���O		
		//---------------------------------------------------
		bool FrameRateController::GetIsSkip() const
		{
			return m_pImpl->m_IsSkip;
		}



	
}
