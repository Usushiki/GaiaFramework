//----------------------------------------------------------------//
//					      Keyboard.hpp							�@//		
//																  //
//			About 		�L�[�{�[�h���͌��m�N���X�̃w�b�_�[�@�@�@�@//
//     	    Last Update  2016/05/13	09:21						�@//
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
#include<memory>

//-----------------------------
//Keyboard�N���X
//-----------------------------
namespace Gaia 
{

	class Keyboard 
	{
		
	public:
		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		Keyboard();

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~Keyboard();


		//�X�V
		void Update();


		//�w�肵���L�[��������Ă��邩
		bool GetIsKeyDown(BYTE) const;

		//�w�肳�ꂽ�L�[��������Ă��Ȃ���
		bool GetIskeyUp(BYTE) const;

		//�w�肳�ꂽ�L�[�������ꂽ��
		bool GetIsKeyPress(BYTE) const;

		//�w�肳�ꂽ�L�[�������ꂽ��
		bool GetIsKeyRelease(BYTE) const;

		//�w�肳�ꂽ�L�[��1�t���[���O�ɉ�����Ă�����
		bool GetIsKeyDownLastFrame(BYTE) const;

		//�L�[���ǂꂩ1�ł�������Ă��邩
		bool GetIsKeyInputAll();

	private:

		//pimpl�C�f�B�I��
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;


	};
}
