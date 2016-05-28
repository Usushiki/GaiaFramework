#pragma once

//-----------------------------
//スクリーンモード
//-----------------------------
namespace Gaia {

	enum ScreenMode
	{
		FULL_SCREEN,
		WINDOW,
	};


	//スクリーンモードのチェック
	inline bool isBool(ScreenMode sc)
	{
		return sc == ScreenMode::FULL_SCREEN;
	}

}
