//=============================================================================
//
// キーボード処理 [input_keyboard.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256)

//*****************************************************************************
// キーボードクラス
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// デフォルトコンストラクタ
	~CInputKeyboard();								// デストラクタ

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理

	bool GetKeyboardPress(int nKey);				// プレス情報
	bool GetKeyboardTrigger(int nKey);				// トリガー情報

private:
	// メンバ変数
	BYTE m_aKeyStatePress[NUM_KEY_MAX];				// プレス
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// トリガー
};

#endif // !_INPUT_KEYBOARD_H_