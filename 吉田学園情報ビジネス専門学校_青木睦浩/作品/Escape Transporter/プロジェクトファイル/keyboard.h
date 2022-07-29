//=============================================================================
//
//	キーボードクラス [inputkeyboard.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256) //キーの最大数

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//	キーボードクラス
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// コンストラクタ
	~CInputKeyboard();								// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理

	bool GetPress(int nKey);						// プレス情報
	bool GetTrigger(int nKey);						// トリガー情報
	bool GetRelease(int nKey);						// リリース情報

private:
	BYTE m_aKeyStatePress[NUM_KEY_MAX];				// プレス
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// トリガー
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			// リリース

};
#endif //!_INPUT_KEYBOARD_H_