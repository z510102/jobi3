//=============================================================================
//
// ナンバー処理 [number.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//*****************************************************************************
// ナンバークラス
//*****************************************************************************
class CNumber
{
public:
	CNumber();																// デフォルトコンストラクタ
	~CNumber();																// デストラクタ

	// メンバ関数
	static HRESULT Load(void);                                              // テクスチャ読み込み
	static void Unload(void);                                               // テクスチャの破棄
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);				// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理

	void SetNumber(int nNumber);											// ナンバーの設定処理
	void SetColor(int nColR, int nColG, int nColB, int nColA);				// 色設定処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;									// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;									// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;														// 位置
	D3DXVECTOR2 m_size;														// サイズ
};

#endif // !_NUMBER_H_