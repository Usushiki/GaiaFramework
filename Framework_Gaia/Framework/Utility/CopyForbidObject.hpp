//----------------------------------------------------------------//
//					      CopyFrobidObject.hpp					�@//		
//																  //
//			About 		�R�s�[�֎~�I�u�W�F�N�g�N���X�̃w�b�_�[�@�@//
//     	    Last Update  2016/05/09								�@//
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//

//-----------------------------
//���d�C���N���[�h�h�~
//-----------------------------
#pragma once


namespace Gaia
{
	namespace Utility
	{

		//-----------------------------------------------
		//	 �R�s�[�֎~�N���X
		//	 �R�s�[���������Ȃ��N���X�Ɍp�����Ďg��
		//-----------------------------------------------
		template<typename T>
		class CopyForbidObject
		{
		protected:

			//�R���X�g���N�^
			CopyForbidObject() = default;

		protected:

			//�f�X�g���N�^
			~CopyForbidObject() = default;

		private:
			//������Z�q�̋֎~
			CopyForbidObject& operator=(const T&) = delete;

			//�R�s�[�R���X�g���N�^�̋֎~
			CopyForbidObject(const CopyForbidObject&) = delete;
		};

	} //namespace Utility

} //namespace Gaia