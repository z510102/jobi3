//=============================================================================
//
// 爆発処理 [explosion.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// 爆発クラス
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	// 爆発の種類
	typedef enum
	{
		TYPE_SG = 0,		// ショットガン
		TYPE_G,				// グレネード
		TYPE_KNOCK,			// 敵を倒したとき
		TYPE_APPEARANCE,	// 敵の出現
		TYPE_RL,			// ロケットランチャー
		TYPE_MAX,
	} EXPLOSION_TYPE;

	CExplosion(int nPriority = 3);																			// デフォルトコンストラクタ
	~CExplosion();																							// デストラクタ

	// メンバ関数
	static HRESULT Load(void);																				// テクスチャ読み込み
	static void Unload(void);																				// テクスチャの破棄
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR color, EXPLOSION_TYPE type);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);																			// 初期化処理
	void Uninit(void);																						// 終了処理
	void Update(void);																						// 更新処理
	void Draw(void);																						// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;																	// テクスチャへのポインタ
	int m_nCounterAnim;																						// アニメーションカウンター
	int m_nPatternAnim;																						// アニメーションパターン
	D3DXVECTOR3 m_pos;																						// 位置
	D3DXCOLOR   m_color;																					// 色
	D3DXVECTOR2 m_size;																						// サイズ
	EXPLOSION_TYPE m_Type;																					// 爆発の種類
};

#endif // !_EXPLOSION_H_