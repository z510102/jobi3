//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	レンダリングクラス
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();							// コンストラクタ
	~CRenderer();							// デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(void);						// 更新処理
	void Draw(void);						// 描画処理

											// デバイスを取得
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

	void SetAddSynthesis(bool bUse);		// 加算合成の設定
	void SetSubSynthesis(bool bUse);		// 減算合成の設定
	void SetZTest(bool bUse);				// Zテストの設定

private:
#ifdef _DEBUG
	void DrawFPS(void);						// FPSの描画処理
	void DrawTXT(void);
#endif

	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
};
#endif //!_RENDERER_H_