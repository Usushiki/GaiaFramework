#pragma once

//-----------------------------
//�X�N���[�����[�h
//-----------------------------
namespace Gaia {

	enum ScreenMode
	{
		FULL_SCREEN,
		WINDOW,
	};


	//�X�N���[�����[�h�̃`�F�b�N
	inline bool isBool(ScreenMode sc)
	{
		return sc == ScreenMode::FULL_SCREEN;
	}

}
