//----------------------------------------------------------------//
//							GameTimer.h							  //		
//																  //
//			About 	�^�C�}�[�N���X�̃w�b�_�[�@			�@�@	�@//
//     	    Last Update  2015/07/25								�@//
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




//-----------------------------
//GameTimer�N���X
//-----------------------------
namespace Gaia
{
	namespace Utility
	{

		class Timer
		{
		public:
			static const UINT SECOND = 1000000;		//1�b�P��

		private:
			static LARGE_INTEGER s_Frequency;	//�^�C�}�\���g��

			LARGE_INTEGER m_Count;				//�J�E���^


		public:

			//--------�R���X�g���N�^-------//
			Timer();

			//--------�f�X�g���N�^-------//
			~Timer() = default;

			//���Ԃ̃��Z�b�g
			void Reset();


			//--------�A�N�Z�b�T-------//

			//���Ԃ̎擾
			UINT GetTime() const;	
		};
	}//namespace Utility
}//namespace Gaia
