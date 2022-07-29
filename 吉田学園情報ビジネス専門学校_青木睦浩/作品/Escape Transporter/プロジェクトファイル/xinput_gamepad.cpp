//=============================================================================
//
//	ゲームパッドクラス [Xinput_gamepad.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "Xinput_gamepad.h"
#include "input.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CXinputPad::CXinputPad()
{
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));			// コントローラーの状態
	ZeroMemory(&m_stateLast, sizeof(XINPUT_STATE));		// コントローラーの状態保存
	ZeroMemory(&m_vibration, sizeof(XINPUT_VIBRATION));	// コントローラの振動機能のモーター速度レベル
	m_bVibration = false;								// コントローラの振動機能の使用判定
	m_nCntVibration = 0;								// コントローラの振動機能(バイブレーションカウンター)
}
//=============================================================================
// デストラクタ
//=============================================================================
CXinputPad::~CXinputPad()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CXinputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CXinputPad::Uninit(void)
{
	// 引数がfalseの場合：現在再生中のバイブレーションエフェクトを停止
	XInputEnable(false);

	CInput::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CXinputPad::Update(void)
{
	// コントローラーの状態
	XINPUT_STATE state;

	// XInputからコントローラーの状態を取得
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// コントローラーと接続している
		m_bConnect = true;
	}
	else
	{
		// コントローラーと接続していない
		m_bConnect = false;
	}

	// 左スティック入力
	// サムスティックがデッドゾーン内にある場合は値がゼロ
	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}

	// 右スティック入力
	// サムスティックがデッドゾーン内にある場合は値がゼロ
	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}

	// 振動機能(バイブレーション)のカウントダウン
	if (m_nCntVibration > 0)
	{
		m_nCntVibration--;
	}
	// カウントが終了すると振動機能(バイブレーション)が終了
	if (m_nCntVibration <= 0 && m_bVibration == true)
	{
		SetVibration(0, 0, 0);
		m_bVibration = false;
	}

	// コントローラーの入力状態を保存
	m_stateLast = m_state;
	m_state = state;
}
//=======================================================================
// ボタンのプレス処理
//=======================================================================
bool CXinputPad::GetButtonPress(int nButton)
{
	return m_state.Gamepad.wButtons & nButton ? true : false;
}
//=======================================================================
// ボタンのトリガー処理
//=======================================================================
bool CXinputPad::GetButtonTrigger(int nButton)
{
	return (((m_stateLast.Gamepad.wButtons & nButton) == false) && (m_state.Gamepad.wButtons & nButton)) ? true : false;
}
//=============================================================================
// リリース情報
//=============================================================================
bool CXinputPad::GetButtonRelease(int nButton)
{
	return (((m_stateLast.Gamepad.wButtons & nButton) == false) && (m_state.Gamepad.wButtons & nButton)) ? true : false;
}

//=======================================================================
// ショルダートリガーのプレス処理
//=======================================================================
bool CXinputPad::GetShoulder(int nShoulderTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nShoulderTrigger)
	{
	case SHOULDERTYPE_RIGHT:
		return m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case SHOULDERTYPE_LEFT:
		return m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}

}
//=======================================================================
// ショルダートリガーのトリガー処理
//=======================================================================
bool CXinputPad::GetShoulderTrigger(int nShoulderTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nShoulderTrigger)
	{
	case SHOULDERTYPE_RIGHT:
		return (((m_stateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case SHOULDERTYPE_LEFT:
		return (((m_stateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// ショルダートリガーのリリース処理
//=======================================================================
bool CXinputPad::GetShoulderRelease(int nShoulderTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nShoulderTrigger)
	{
	case SHOULDERTYPE_RIGHT:
		return (((m_stateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case SHOULDERTYPE_LEFT:
		return (((m_stateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=======================================================================
// 左スティックのプレス処理
//=======================================================================
bool CXinputPad::GetLeftStick(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// 左スティックのトリガー処理
//=======================================================================
bool CXinputPad::GetLeftStickTrigger(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return (((m_stateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return (((m_stateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_LEFT:
		return (((m_stateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_DOWN:
		return (((m_stateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// 左スティックのリリース処理
//=======================================================================
bool CXinputPad::GetLeftStickRelease(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return (((m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return (((m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_LEFT:
		return (((m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_DOWN:
		return (((m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// 右スティックのプレス処理
//=======================================================================
bool CXinputPad::GetRightStick(int nRstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nRstick)
	{
	case STICKTYPE_UP:
		return m_state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return m_state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return m_state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return m_state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
//バイブレーション設定
//=======================================================================
void CXinputPad::SetVibration(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond)
{
	m_vibration.wLeftMotorSpeed = nLeftMotorSpeed;		// 左モーターの速度：有効な値は0～65,535の範囲

	m_vibration.wRightMotorSpeed = nRightMotorSpeed;	// 右モーターの速度：有効な値は0～65,535の範囲

	XInputSetState(0, &m_vibration);			// 振動機能(バイブレーション)設定

	m_nCntVibration = nSecond;					// 振動機能(バイブレーション)の使用カウント

	m_bVibration = true;						// 振動機能(バイブレーション)を使用
}