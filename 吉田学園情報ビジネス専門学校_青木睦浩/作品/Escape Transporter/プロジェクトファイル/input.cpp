//=============================================================================
//
// インプットクラス [input.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "input.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL; // DirectInputオブジェクトのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;	// 入力デバイスへのポインタ
}
//=============================================================================
// デストラクタ
//=============================================================================
CInput::~CInput()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{

	// DirectInputオブジェクトの生成
	if (DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))
	{
		return E_FAIL;
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CInput::Uninit(void)
{
	// デバイスオブジェクトの開放
	if (m_pDevice != NULL)
	{
		// アクセス権の破棄
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}