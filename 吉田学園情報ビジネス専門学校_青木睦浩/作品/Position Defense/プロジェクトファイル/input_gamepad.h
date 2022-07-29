//=============================================================================
//
// ゲームパッド処理 [input_gamepad.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _INPUT_GAMEPAD_H_
#define _INPUT_GAMEPAD_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_BUTTON_MAX (256)

//*****************************************************************************
// ゲームパッドクラス
//*****************************************************************************
class CInputGamepad : public CInput
{
public:
	typedef enum
	{
		STICK_TYPE_NONE = 0,
		STICK_TYPE_UP,
		STICK_TYPE_DOWN,
		STICK_TYPE_RIGHT,
		STICK_TYPE_LEFT,
		STICK_TYPE_MAX
	} STICK_TYPE;

	typedef enum
	{
		SHOULDER_TYPE_NONE = 0,
		SHOULDER_TYPE_RIGHT,
		SHOULDER_TYPE_LEFT,
		SHOULDER_TYPE_MAX
	} SHOULDER_TYPE;

	CInputGamepad();   //デフォルトコンストラクタ
	~CInputGamepad();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetButtonPress(int nButton);    //プレス情報
	bool GetButtonTrigger(int nButton);	//トリガー情報
	bool GetButtonRelease(int nButton);	//トリガー情報

	bool GetLeftStick(int nStick);
	bool GetLeftStickTrigger(int nStick);
	bool GetLeftStickRelease(int nStick);

	bool GetLeftShoulder(int nShoulder);
	bool GetLeftShoulderTrigger(int nShoulder);
	bool GetLeftShoulderRelease(int nShoulder);

	void SetVibe(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond);

private:
	XINPUT_STATE m_State;
	XINPUT_STATE m_StateLast;
	bool m_bConect;
	XINPUT_VIBRATION m_Vibration;
	bool m_bVibration;
	int m_nVibCount;
};

#endif // !_INPUT_GAMEPAD_H_