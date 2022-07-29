//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// チュートリアルクラス
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial();								// デフォルトコンストラクタ
	~CTutorial();								// デストラクタ

	// メンバ関数
	static HRESULT Load(void);					// テクスチャ読み込み
	static void Unload(void);					// テクスチャの破棄
	static CTutorial *Create(void);				// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);				// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	CScene2D *m_pScene2D;						// Scene2Dへのポインタ
	D3DXVECTOR3 m_Pos;							// 位置
};

#endif // !_TUTORIAL_H_