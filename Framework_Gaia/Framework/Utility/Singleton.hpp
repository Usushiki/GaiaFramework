//----------------------------------------------------------------//
//					      Singleton.h							　//		
//																  //
//			About 	シングルトンパターンのヘッダー			　　　//
//     	    Last Update  2016/05/10								　//
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//

//-----------------------------
//多重インクルード防止
//-----------------------------
#pragma once

#include"CopyForbidObject.hpp"
#include<memory>


//-----------------------------
//Singletonクラス
//-----------------------------
namespace Gaia
{

	namespace Utility
	{
		template<typename T>
		class Singleton : private CopyForbidObject<T>
		{
		private:

			static std::unique_ptr<T> s_Instance;	//インスタンス



		protected:
			//-----------------------------
			//!@brief コンストラクタ
			//-----------------------------
			Singleton() = default;

			//-----------------------------
			//!@brief デストラクタ
			//-----------------------------
			~Singleton() = default;

		public:

			//インスタンスの取得
			static std::unique_ptr<T>& Get()
			{
				if (!s_Instance)
				{
					s_Instance.reset(new T());
				}

				return s_Instance;
			}

			//インスタンス破棄
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
		//静的メンバ変数の実体
		template<typename T>
		std::unique_ptr<T>	Singleton<T>::s_Instance = nullptr;
	}
}