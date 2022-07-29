//=============================================================================
//
// 背景処理 [bg.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "scene2D.h"

//*****************************************************************************
// 背景クラス
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);					// デフォルトコンストラクタ
	~CBg();									// デストラクタ

	// メンバ関数
	static HRESULT Load(void);				// テクスチャ読み込み
	static void Unload(void);				// テクスチャの破棄
	static CBg *Create(void);				// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);			// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(void);						// 更新処理
	void Draw(void);						// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
	CScene2D *m_pScene2D;					// Scene2Dへのポインタ
	D3DXVECTOR3 m_Pos;						// 位置
	int m_nPriority;						// 優先順位
};

#endif // !_BG_H_