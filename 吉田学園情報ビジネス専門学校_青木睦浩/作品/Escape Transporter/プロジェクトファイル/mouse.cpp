//=============================================================================
//
//	マウスクラス [mouse.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "mouse.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
DIMOUSESTATE CMouse::m_CurrentMouseState;		// マウスの現在の入力情報
DIMOUSESTATE CMouse::m_PrevMouseState;			// マウスの一フレーム前の入力情報
//=============================================================================
// コンストラクタ
//=============================================================================
CMouse::CMouse()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CMouse::~CMouse()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
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

	// ポーリングを開始
	m_pDevice->Poll();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CMouse::Update(void)
{
	// 更新前に最新マウス情報を保存する
	m_PrevMouseState = m_CurrentMouseState;

	//入力デバイスからデータ取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState)))
	{
		// アクセス権の取得
		m_pDevice->Acquire();

		// 最新のマウスの状態を更新
		m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);
	}
}

bool CMouse::ButtonDown(int nButton)
{
	if (!(m_PrevMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX) &&
		m_CurrentMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX)
	{
		return true;
	}

	return false;
}

bool CMouse::ButtonUp(int nButton)
{
	if (m_PrevMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX &&
		!(m_CurrentMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX))
	{
		return true;
	}

	return false;
}
