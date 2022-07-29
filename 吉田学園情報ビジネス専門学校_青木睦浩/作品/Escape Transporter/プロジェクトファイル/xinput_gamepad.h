//=============================================================================
//
//	ゲームパッドクラス [xinput_gamepad.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _XINPUT_GAMEPAD_H_
#define _XINPUT_GAMEPAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256) //キーの最大数

//*****************************************************************************
//	ゲームパッドクラス
//*****************************************************************************
class CXinputPad : public CInput
{
public:
	// ショルダートリガーの列挙
	typedef enum
	{
		SHOULDERTYPE_RIGHT = 0,
		SHOULDERTYPE_LEFT,
		SHOULDERTYPE_MAX
	} SHOULDER_TRIGGER;

	// スティックの方向列挙
	typedef enum
	{
		STICKTYPE_UP = 0,
		STICKTYPE_RIGHT,
		STICKTYPE_LEFT,
		STICKTYPE_DOWN,
		STICKTYPE_MAX
	} STICKTYPE;

	CXinputPad();			//コンストラクタ
	~CXinputPad();			//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理

	bool GetButtonPress(int nButton);				// ボタンのプレス処理
	bool GetButtonTrigger(int nButton);				// ボタンのトリガー処理
	bool GetButtonRelease(int nButton);				// ボタンのリリース処理

	bool GetShoulder(int nShoulderTrigger);			// ショルダートリガーのプレス処理
	bool GetShoulderTrigger(int nShoulderTrigger);	// ショルダートリガーのトリガー処理
	bool GetShoulderRelease(int nShoulderTrigger);	// ショルダートリガーのリリース処理

	bool GetLeftStick(int nLstick);							// 左スティックの基本処理
	bool GetLeftStickTrigger(int nLstick);					// 左スティックのトリガー処理
	bool GetLeftStickRelease(int nLstick);					// 左スティックのリリース処理

	bool GetRightStick(int nRstick);						// 右スティックの基本処理
	void SetVibration(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond);	// コントローラの振動機能設定(バイブレーション機能)

private:
	XINPUT_STATE		m_state;			// コントローラーの状態
	XINPUT_STATE		m_stateLast;		// コントローラーの状態保存
	XINPUT_VIBRATION	m_vibration;		// コントローラの振動機能(バイブレーション機能)
	bool				m_bConnect;			// コントローラーの接続判定
	bool				m_bVibration;		// コントローラの振動機能(バイブレーション機能)の使用判定
	int					m_nCntVibration;	// コントローラの振動機能(バイブレーションカウンター)
};
#endif //!_GAMEPAD_H_