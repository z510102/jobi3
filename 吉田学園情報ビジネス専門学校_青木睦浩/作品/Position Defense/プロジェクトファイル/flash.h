//=============================================================================
//
// 閃光処理 [flash.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _FLASH_H_
#define _FLASH_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// 閃光クラス
//*****************************************************************************
class CFlash : public CScene2D
{
public:
	CFlash(int nPriority = 3);									// デフォルトコンストラクタ
	~CFlash();													// デストラクタ

	//メンバ関数
	static HRESULT Load(void);                                  // テクスチャ読み込み
	static void Unload(void);                                   // テクスチャの破棄
	static CFlash *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);								// 初期化処理
	void Uninit(void);                                          // 終了処理
	void Update(void);                                          // 更新処理
	void Draw(void);                                            // 描画処理

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;						// テクスチャへのポインタ
	int m_nCounterAnim;											// アニメーションカウンター
	int m_nPatternAnim;											// アニメーションパターン
	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR2 m_size;											// サイズ
};

#endif // !_EXPLOSION_H_