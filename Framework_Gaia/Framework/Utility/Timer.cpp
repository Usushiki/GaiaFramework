//----------------------------------------------------------------//
//							Timer.cpp							�@//		
//																  //
//			  About 	�^�C�}�[�N���X�̃\�[�X					�@//
//     	  		    Last Update  2016/05/12 22:33				  //
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//

// ���d�C���N���[�h�h�~ ===================================================
#pragma once



//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include"Timer.hpp"


namespace Gaia
{
	namespace Utility
	{

		//�ÓI�����o�ϐ��̎���
		LARGE_INTEGER Timer::s_Frequency = { 0 };



		//-----------------------------
		//!@brief�@�R���X�g���N�^
		//-----------------------------
		Timer::Timer()
		{

			if (s_Frequency.QuadPart == 0)
			{
				//CPU���g���̎擾
				QueryPerformanceFrequency(&s_Frequency);
			}

			//�v���J�n�J�E���g��ݒ�
			QueryPerformanceCounter(&m_Count);

		}


		//--------------------------------------------------------------
		//!@brief				����[ns]�̎擾							
		//																
		//!@param[in]	�Ȃ�											
		//																
		//!@retval 		�v���J�n���_����̂��Ƃ߂����ݎ���[ns]			
		//--------------------------------------------------------------
		UINT Timer::GetTime()const
		{
			LARGE_INTEGER currentTime;

			//���݂̃p�t�H�[�}���X�J�E���^���擾
			QueryPerformanceCounter(&currentTime);


			//�J�E���^�̍��������߂�
			LONGLONG calcTime = currentTime.QuadPart - m_Count.QuadPart;


			//���������g���Ŋ��菈�����Ԃ��Z�o
			return static_cast<UINT>(calcTime*SECOND / s_Frequency.QuadPart);
		}


		//----------------------------------------------------------
		//!@brief	    �J�E���^�̃��Z�b�g							
		//															
		//!@param[in]	�Ȃ�										
		//															
		//!@retval		�Ȃ�										
		//----------------------------------------------------------
		void Timer::Reset()
		{
			QueryPerformanceCounter(&m_Count);
		}
	
	}//namespace Utility
}//namespace Gaia