//----------------------------------------------------------------//
//					      Keyboard.cpp							　//		
//																  //
//					 About キーボード入力検知クラスのソース		　//
//     	  		    Last Update  2016/05/13 09:21				  //
//					Place Valencienne France					  //
//																  //
//                    Coded by Y.Takada							  //
//																　//
//----------------------------------------------------------------//


//-----------------------------
//ヘッダファイルのインクルード
//-----------------------------
#include"Keyboard.hpp"




namespace Gaia
{
	
	//----------------------------------------
	//!@brief Keyboardクラスの実装の詳細
	//----------------------------------------
	class Keyboard::pImpl
	{
	public:
		//キー情報構造体
		struct KeyState
		{
			BYTE key[256];
		};

		KeyState m_CurrentKeyState;				//現在のキーの入力状態
		KeyState m_LastKeyState;				//1フレーム前のキーの入力状態


		//-----------------------------------------------------
		//無視キーコードリスト
		//-----------------------------------------------------
		const int NonCheckKeyList[10] = { 1, 2, 8, 13, 16, 17, 28, 160, 161, 162 };
		
		//キーコード数
		static const int KEY_NUM = 240;

	public:

		//-----------------------------
		//!@brief コンストラクタ
		//-----------------------------
		pImpl()
			:m_LastKeyState({ { 0 } })
			, m_CurrentKeyState({ { 0 } })
		{

		}

		//-----------------------------
		//!@brief デストラクタ
		//-----------------------------
		~pImpl() = default;

	public:
		//-------------------------------------------------------------
		//!@brief  	指定されたキーがある状況下に押されているかを判定
		//
		//!@param[in] _state　キーボードの状態
		//!@param[in] _ key   検知したいキーのコード
		//
		//!@retval true  押されている
		//		   false 押されていない 
		//-------------------------------------------------------------
		inline bool GetIsKeyDown(const KeyState& _state, BYTE _key) const
		{
			return (_state.key[_key] & 0x80) ? true : false;
		}

		//---------------------------------------------------------------
		//!@brief 現在参照しているキーが無視リストに入っているかを判定
		//
		//!@param[in] _key キーコード
		//
		//!@retval  true   入っている
		//			false  入っていない
		//---------------------------------------------------------------
		bool IsFindNonCheckKey(int _key) const
		{
			for (int i : NonCheckKeyList) {
				if (NonCheckKeyList[i] == _key)
					return true;
			}

			return false;
		}

	};
}


namespace Gaia
{

	//-----------------------------
	//!@brief コンストラクタ
	//-----------------------------
	Keyboard::Keyboard()
		:m_pImpl(std::make_unique<pImpl>())
	{

	}

	//-----------------------------
	//!@brief デストラクタ
	//-----------------------------
	Keyboard::~Keyboard() = default;

	//------------------------------------------------------------
	//!@brief			キーボードの状態の更新					
	//															
	//!@param[in] なし												
	//															
	//!@retvl なし												
	//------------------------------------------------------------
	void Keyboard::Update()
	{
		//状態の履歴を保存
		m_pImpl->m_LastKeyState = m_pImpl->m_CurrentKeyState;

		//現在のキーボードの状態を取得
		GetKeyboardState(m_pImpl->m_CurrentKeyState.key);
	}


	//------------------------------------------------------------
	//!@brief	  	 指定されたキーが押されているかを判定		
	//															
	//															
	//!@param[in] _key			判定したいキーのコード			
	//															
	//!@retval  true  キーが押されている						
	//          false それ以外									
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyDown(BYTE _key)const
	{
		return m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key);
	}

	//------------------------------------------------------------
	//!@brief   指定されたキーが押されていないかを判定			
	//																
	//																
	//!@param[in] _key			判定したいキーのコード			
	//																
	//!@retval    true  キーが押されていない						
	//            false それ以外									
	//------------------------------------------------------------
	bool Keyboard::GetIskeyUp(BYTE _key)const
	{
		return !m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key);
	}


	//------------------------------------------------------------
	//!@brief   指定されたキーが押されたかを判定			
	//															
	//															
	//!@param[in]  _key			判定したいキーのコード		
	//															
	//!@retval     true  キーが押された						
	//             false それ以外								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyPress(BYTE _key)const
	{
		return m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key) &&
			  !m_pImpl->GetIsKeyDown(m_pImpl->m_LastKeyState, _key);
	}


	//------------------------------------------------------------
	//!@brief	    指定されたキーが離されたかを判定			
	//															
	//															
	//!@param[in]  _key			判定したいキーのコード		
	//															
	//!@retval true  キーが離された						
	//              false それ以外								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyRelease(BYTE _key)const
	{
		return !m_pImpl->GetIsKeyDown(m_pImpl->m_CurrentKeyState, _key) &&
				m_pImpl->GetIsKeyDown(m_pImpl->m_LastKeyState, _key);
	}

	//------------------------------------------------------------
	//!@brief 指定されたキーが1フレーム前に押されていたかを判定	
	//															
	//															
	//!@param[in]  _key			判定したいキーのコード		
	//															
	//!@retval     true  キーが押されていた					
	//             false それ以外								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyDownLastFrame(BYTE _key)const
	{
		return m_pImpl->GetIsKeyDown(m_pImpl->m_LastKeyState, _key);
	}



	//------------------------------------------------------------
	//!@brief	　	 キーどれか一つでもが押されているかを判定	
	//															
	//!@param[in] 　なし		
	//
	//!@retval     true  キーが押されていた						
	//             false それ以外								
	//------------------------------------------------------------
	bool Keyboard::GetIsKeyInputAll()
	{
		for (int i = 0; i < m_pImpl->KEY_NUM; i++) {
			if ((m_pImpl->m_CurrentKeyState.key[i] & 0x80) && !m_pImpl->IsFindNonCheckKey(i)) {
				return true;
			}
		}

		return false;
	}


	
}