//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_EFFECT (128)

//*****************************************************************************
// エフェクトクラス
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority);																	// デフォルトコンストラクタ
	~CEffect();																				// デストラクタ

	// メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos,
		                 int nColorR, int nColorG, int nColorB, int nColorA,
		                 int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA);	// 初期化処理
	virtual void Uninit(void);																// 終了処理
	virtual void Update(void);																// 更新処理
	virtual void Draw(void);																// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;													// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;																		// ポリゴンの位置
	D3DXVECTOR2 m_size;																		// ポリゴンのサイズ
	D3DXCOLOR   m_color;																	// ポリゴンのカラー
	int m_nColorR;																			// カラー（赤）
	int m_nColorG;																			// カラー（緑）
	int m_nColorB;																			// カラー（青）
	int m_nColorA;																			// カラー（透明度）
	int m_nColorSubR;																		// サブカラー（赤）
	int m_nColorSubG;																		// サブカラー（緑）
	int m_nColorSubB;																		// サブカラー（青）
	int m_nColorSubA;																		// サブカラー（透明度）
};

#endif // !_EFFECT_H_