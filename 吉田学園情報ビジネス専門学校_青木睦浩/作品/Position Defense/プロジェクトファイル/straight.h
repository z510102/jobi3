//=============================================================================
//
// エフェクトの軌跡処理 [straight.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _STRAIGHT_H_
#define _STRAIGHT_H_

#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_STRAIGHT (128)

//*****************************************************************************
// エフェクト軌跡クラス
//*****************************************************************************
class CStraight : public CEffect
{
public:
	CStraight(int nPriority = 4);																// デフォルトコンストラクタ
	~CStraight();																				// デストラクタ

	// メンバ関数
	static HRESULT Load(void);																	// テクスチャ読み込み
	static void Unload(void);																	// テクスチャの破棄
	static CStraight *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,
		                     int nColorR, int nColorG, int nColorB, int nColorA,
		                     int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
		                     int nLife);														// 生成処理

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size,
		                 int nColorR, int nColorG, int nColorB, int nColorA,
		                 int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
		                 int nLife);															// 初期化処理
	virtual void Uninit(void);																	// 終了処理
	virtual void Update(void);																	// 更新処理
	virtual void Draw(void);																	// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;														// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;																			// ポリゴンの位置
	D3DXVECTOR2 m_size;																			// ポリゴンのサイズ
	D3DXCOLOR   m_color;																		// ポリゴンのカラー
	int m_nLife;																				// 寿命
	int m_nColorR;																				// 色（赤）
	int m_nColorG;																				// 色（緑）
	int m_nColorB;																				// 色（青）
	int m_nColorA;																				// 色（透明度）
	int m_nColorSubR;																			// サブ色（赤）
	int m_nColorSubG;																			// サブ色（緑）
	int m_nColorSubB;																			// サブ色（青）
	int m_nColorSubA;																			// サブ色（透明度）
};

#endif // !_STRAIGHT_H_