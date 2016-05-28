//----------------------------------------------------------------//
//					      Singleton.h							�@//		
//																  //
//			About 	�V���O���g���p�^�[���̃w�b�_�[			�@�@�@//
//     	    Last Update  2016/05/10								�@//
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//

//-----------------------------
//���d�C���N���[�h�h�~
//-----------------------------
#pragma once

#include"CopyForbidObject.hpp"
#include<memory>


//-----------------------------
//Singleton�N���X
//-----------------------------
namespace Gaia
{

	namespace Utility
	{
		template<typename T>
		class Singleton : private CopyForbidObject<T>
		{
		private:

			static std::unique_ptr<T> s_Instance;	//�C���X�^���X



		protected:
			//-----------------------------
			//!@brief �R���X�g���N�^
			//-----------------------------
			Singleton() = default;

			//-----------------------------
			//!@brief �f�X�g���N�^
			//-----------------------------
			~Singleton() = default;

		public:

			//�C���X�^���X�̎擾
			static std::unique_ptr<T>& Get()
			{
				if (!s_Instance)
				{
					s_Instance.reset(new T());
				}

				return s_Instance;
			}

			//�C���X�^���X�j��
			static void Reset()
			{
				s_Instance.reset();
			}

		};

	} //namespace Utility

} //namespae Gaia

namespace Gaia
{
	namespace Utility
	{
		//�ÓI�����o�ϐ��̎���
		template<typename T>
		std::unique_ptr<T>	Singleton<T>::s_Instance = nullptr;
	}
}