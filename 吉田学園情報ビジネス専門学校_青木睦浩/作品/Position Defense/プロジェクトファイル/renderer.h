//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*****************************************************************************
// レンダリングクラス
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();													// デフォルトコンストラクタ
	~CRenderer();													// デストラクタ

	// メンバ関数
	HRESULT Init(HWND hWnd, bool bWindow);							// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }		// デバイスを取得する
	void SetAddSynthesis(bool bUse);								// 加算合成の設定

private:
	// メンバ関数
#ifdef _DEBUG
	void DrawFPS(void);												//FPSの表示処理
#endif

	LPDIRECT3D9		   m_pD3D;										// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9  m_pD3DDevice;								// Deviceオブジェクト(描画に必要)
	LPD3DXFONT		   m_pFont;										// フォントへのポインタ
};

#endif // !_RENDERER_H_