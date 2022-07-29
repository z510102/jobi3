//=============================================================================
//
//	キーボードクラス [keyboard.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "keyboard.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyStatePress[0], 0, sizeof(m_aKeyStatePress));		// プレス
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));	// トリガー
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));	// リリース
}
//=============================================================================
// デストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードの設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// アクセス権の取得
	m_pDevice->Acquire();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	//入力デバイスからデータ取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < NUM_KEY_MAX; nKey++)
		{
			// トリガー情報
			m_aKeyStateTrigger[nKey] = (m_aKeyStatePress[nKey] & aKeyState[nKey]) ^ aKeyState[nKey];

			// リリース情報
			m_aKeyStateRelease[nKey] = (m_aKeyStatePress[nKey] | aKeyState[nKey]) ^ aKeyState[nKey];

			// プレス情報
			m_aKeyStatePress[nKey] = aKeyState[nKey];
		}
	}
	else
	{	// アクセス権の取得
		m_pDevice->Acquire();
	}
}
//=============================================================================
// プレス情報
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
}
//=============================================================================
// トリガー情報
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// リリース情報
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
