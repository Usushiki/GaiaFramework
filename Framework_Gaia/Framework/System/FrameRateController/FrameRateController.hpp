//----------------------------------------------------------------//
//					  FrameRateController.h						  //		
//																  //
//			About 	�t���[�����[�g�Ǘ��N���X�̃w�b�_�[�@�@�@	�@//
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
#include<memory>
#include<Windows.h>
#include"../../Utility/Timer.hpp"


//-----------------------------
//FrameRateController�N���X
//-----------------------------
namespace Gaia
{
	
		class FrameRateController
		{
			//�����ݒ�t���[�����[�g
			static const UINT S_FRAME_RATE_DEFAULT = 60;	
	
		public:

			//-----------------------------
			//!@brief �R���X�g���N�^
			//-----------------------------
			FrameRateController(UINT FrameRate = S_FRAME_RATE_DEFAULT);

			//-----------------------------
			//!@brief �f�X�g���N�^
			//-----------------------------
			~FrameRateController();

			//--------�A�N�Z�b�T-------//
			void SetFrameRate(UINT);
			double GetFrameRate() const;
			bool GetIsSkip() const;



			//�v���̊J�n
			void Start();

			//�t���[�����[�g�̒���
			void Regulate();


		private:

			//pImpl�C�f�B�I��
			class pImpl;
			std::unique_ptr<pImpl> m_pImpl;
		};
	
}