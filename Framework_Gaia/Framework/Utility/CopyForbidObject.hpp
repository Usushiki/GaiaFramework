//----------------------------------------------------------------//
//					      CopyFrobidObject.hpp					　//		
//																  //
//			About 		コピー禁止オブジェクトクラスのヘッダー　　//
//     	    Last Update  2016/05/09								　//
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//

//-----------------------------
//多重インクルード防止
//-----------------------------
#pragma once


namespace Gaia
{
	namespace Utility
	{

		//-----------------------------------------------
		//	 コピー禁止クラス
		//	 コピーをしたくないクラスに継承して使う
		//-----------------------------------------------
		template<typename T>
		class CopyForbidObject
		{
		protected:

			//コンストラクタ
			CopyForbidObject() = default;

		protected:

			//デストラクタ
			~CopyForbidObject() = default;

		private:
			//代入演算子の禁止
			CopyForbidObject& operator=(const T&) = delete;

			//コピーコンストラクタの禁止
			CopyForbidObject(const CopyForbidObject&) = delete;
		};

	} //namespace Utility

} //namespace Gaia