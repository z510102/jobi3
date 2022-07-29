//=============================================================================
//
// ポジション処理 [position.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _POSITION_H_
#define _POSITION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// ポジションクラス
//*****************************************************************************
class CPosition : public CScene2D
{
public:
	CPosition(int nPriority = 1);									// デフォルトコンストラクタ
	~CPosition();													// デストラクタ

	// メンバ関数
	static HRESULT Load(void);										// テクスチャ読み込み
	static void Unload(void);										// テクスチャの破棄
	static CPosition *Create(D3DXVECTOR3 pos, D3DXCOLOR color);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);									// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャへのポインタ
	D3DXCOLOR   m_color;											// ポリゴンのカラー
};

#endif // !_POSITION_H_