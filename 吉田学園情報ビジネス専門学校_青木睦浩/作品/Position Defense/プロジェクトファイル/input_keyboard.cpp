//=============================================================================
//
// 入力処理 [input_keyboard.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "input_keyboard.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyStatePress[0], 0, sizeof(m_aKeyStatePress));      //プレス
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));  //トリガー
}

//=============================================================================
// デストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// マウスとかはここに増やしていく


	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CInputKeyboard::Update(void)
{
	// キーボードの入力情報
	BYTE aKeyState[NUM_KEY_MAX];

	// カウント用の変数
	int nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		// キーボードの入力情報保存
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//トリガーキー
			m_aKeyStateTrigger[nCntKey] = (m_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			m_aKeyStatePress[nCntKey] = aKeyState[nCntKey];
		}
	}

	else
	{
		// キーボードへのアクセス権を獲得
		m_pDevice->Acquire();
	}
}

//=============================================================================
//キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//=============================================================================
//キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}