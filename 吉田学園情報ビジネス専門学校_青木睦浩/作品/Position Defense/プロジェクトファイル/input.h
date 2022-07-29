//=============================================================================
//
// 入力処理 [input.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// インプットクラス
//*****************************************************************************
class CInput
{
public:
	CInput();												// デフォルトコンストラクタ
	virtual ~CInput();										// デストラクタ

	// メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	virtual void Uninit(void);								// 終了処理

protected:
	//メンバ変数
	LPDIRECTINPUTDEVICE8 m_pDevice;							// 入力デバイスへのポインタ
	static LPDIRECTINPUT8 m_pInput;							// DirectInputオブジェクトへのポインタ
};

#endif // !_INPUT_H_