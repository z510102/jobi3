//=============================================================================
//
//	マウスクラス [mouse.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _INPUT_MOUSE_H_
#define _INPUT_MOUSE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_BUTTON_MAX (3) //ボタンの最大数

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//	キーボードクラス
//*****************************************************************************
class CMouse : public CInput
{
public:
	CMouse();								// コンストラクタ
	~CMouse();								// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理

	bool ButtonDown(int nButton);					// プレス情報
	bool ButtonUp(int nButton);						// トリガー情報
	bool GetRelease(int nKey);						// リリース情報

private:
	static DIMOUSESTATE m_CurrentMouseState;		// マウスの現在の入力情報
	static DIMOUSESTATE m_PrevMouseState;			// マウスの一フレーム前の入力情報
};
#endif //!_INPUT_MOUSE_H_