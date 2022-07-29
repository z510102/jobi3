//=============================================================================
//
// グレネード処理 [grenade.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// グレネードクラス
//*****************************************************************************
class CGrenade : public CScene2D
{
public:
	CGrenade(int nPriority = 3);									// デフォルトコンストラクタ
	~CGrenade();													// デストラクタ

	// メンバ関数
	static CGrenade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	static HRESULT Load(void);										// テクスチャ読み込み
	static void Unload(void);										// テクスチャの破棄
	void NotUse(void);												// グレネードを使用無効処理

private:
	// メンバ変数
	D3DXVECTOR3 m_move;												// 移動量
	D3DXVECTOR3 m_pos;												// 位置
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャへのポインタ
	bool m_bUse;													// 使用
	int m_nPassG;													// グレネード所持数の情報をもらう
};

#endif // !_GRENADE_H_