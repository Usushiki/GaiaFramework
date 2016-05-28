
//------------------------------------------------//
//				Window�̍쐬�A�\��				  //
//												  //
//					�Q�lHP�@�@�@�@�@�@�@�@�@�@ �@ //�@�@�@
//			�L�ł��킩��Windows�v���O���~���O	  //
//	http://www.kumei.ne.jp/c_lang/index_sdk.html  //
//												  //
//												  //
//			2015.6.30(Tue)14:20					  //
//			coded by Y.Takada					  //
//												  //
//------------------------------------------------//

//-----------------------------
//���d�C���N���[�h�h�~
//-----------------------------
#pragma once



//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include<Windows.h>
#include<memory>

namespace Gaia {

	//-----------------------------
	//�E�B���h�E�N���X
	//-----------------------------

	class Window 
	{
		

	public:

		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		Window();

	
	public:
		

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~Window();

		//--------�A�N�Z�b�T-------//

		//�E�B���h�E�n���h���̎擾
		HWND GetWindowHandle() const;

		//�I���R�[�h�̎擾
		int  GetExitCode()	   const;


		//���b�Z�[�W����
		bool HandleMessage();

	private:
		//pimpl�C�f�B�I��
		class pImpl;
		std::unique_ptr<pImpl> m_pImpl;

	public:

		//�E�B���h�E�v���V�[�W��	
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

		//�t�@�N�g��
		static std::unique_ptr<Window> Create(int, int, LPCWSTR name);

	

	};

}