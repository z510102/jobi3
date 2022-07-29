//=============================================================================
//
// 入力処理 [input_gamepad.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "input_gamepad.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInputGamepad::CInputGamepad()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	ZeroMemory(&m_StateLast, sizeof(XINPUT_STATE));
	m_bConect = false;
	ZeroMemory(&m_Vibration, sizeof(XINPUT_VIBRATION));
	m_nVibCount = 0;
	m_bVibration = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CInputGamepad::~CInputGamepad()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInputGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CInputGamepad::Uninit(void)
{
	XInputEnable(false);
	CInput::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CInputGamepad::Update(void)
{
	XINPUT_STATE state;

	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		m_bConect = true;
	}

	else
	{
		m_bConect = false;
	}

	// Zero value if thumbsticks are within the dead zone
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&
		 state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&
		 state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}

	// Zero value if thumbsticks are within the dead zone
	if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&
		 state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&
		 state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}

	if (m_nVibCount >= 0)
	{
		m_nVibCount--;
	}

	if (m_nVibCount <= 0 && m_bVibration == true)
	{
		SetVibe(0, 0, 0);
		m_bVibration = false;
	}

	m_StateLast = m_State;

	m_State = state;
}

//=============================================================================
//キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputGamepad::GetButtonPress(int nButton)
{
	return m_State.Gamepad.wButtons & nButton ? true : false;
}

//=============================================================================
//キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputGamepad::GetButtonTrigger(int nButton)
{
	return (((m_StateLast.Gamepad.wButtons & nButton) == false) && (m_State.Gamepad.wButtons & nButton)) ? true : false;
}

bool CInputGamepad::GetButtonRelease(int nButton)
{
	return (((m_StateLast.Gamepad.wButtons & nButton) == false) && (m_State.Gamepad.wButtons & nButton)) ? true : false;
}





bool CInputGamepad::GetLeftStick(int nStick)
{
	if (m_bConect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_LEFT:
		return m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	default:
		return false;
		break;
	}
}

bool CInputGamepad::GetLeftStickTrigger(int nStick)
{
	if (m_bConect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return (((m_StateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return (((m_StateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;;
		break;

	case STICK_TYPE_LEFT:
		return (((m_StateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}

bool CInputGamepad::GetLeftStickRelease(int nStick)
{
	if (m_bConect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return (((m_StateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return (((m_StateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;;
		break;

	case STICK_TYPE_LEFT:
		return (((m_StateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}





bool CInputGamepad::GetLeftShoulder(int nShoulder)
{
	if (m_bConect == false)
	{
		return false;
	}

	switch (nShoulder)
	{
	case SHOULDER_TYPE_RIGHT:
		return m_State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;

	case SHOULDER_TYPE_LEFT:
		return m_State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;

	default:
		return false;
		break;
	}
}

bool CInputGamepad::GetLeftShoulderTrigger(int nShoulder)
{
	if (m_bConect == false)
	{
		return false;
	}

	switch (nShoulder)
	{
	case SHOULDER_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;;
		break;

	case SHOULDER_TYPE_LEFT:
		return (((m_StateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}

bool CInputGamepad::GetLeftShoulderRelease(int nShoulder)
{
	if (m_bConect == false)
	{
		return false;
	}

	switch (nShoulder)
	{
	case SHOULDER_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;;
		break;

	case SHOULDER_TYPE_LEFT:
		return (((m_StateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}





void CInputGamepad::SetVibe(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond)
{
	m_Vibration.wLeftMotorSpeed = nLeftMotorSpeed;
	m_Vibration.wRightMotorSpeed = nRightMotorSpeed;
	XInputSetState(0, &m_Vibration);
	m_nVibCount = nSecond;

	m_bVibration = true;
}
