//=============================================================================
//
// エフェクト [effect.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	エフェクトクラス
//*****************************************************************************
class CEffect : public CBillboard
{
public:
	CEffect();							// コンストラクタ
	virtual~CEffect();								// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int nColr, int nColg, int nColb, int nCola,
		int nSubColr, int nSubColg, int nSubColb, int nSubCola, int nLife);			// 初期化処理
	virtual void Uninit(void);						// 終了処理
	virtual void Update(void);						// 更新処理
	virtual void Draw(void);						// 描画処理

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;	// 共有テクスチャのポインタ
	D3DXVECTOR3	m_pos;						// 位置
	D3DXVECTOR3	m_rot;						// 向き
	D3DXVECTOR3	m_move;						// 移動量
	D3DXVECTOR2 m_size;						// サイズ
	int			m_nColorR;					// 赤
	int			m_nColorG;					// 緑
	int			m_nColorB;					// 青
	int			m_nColorA;					// 透明度
	int			m_nSubColorR;				// 赤の減少値
	int			m_nSubColorG;				// 緑の減少値
	int			m_nSubColorB;				// 青の減少値
	int			m_nSubColorA;				// 透明度の減少値

	int			m_nLife;					// 寿命
	float		m_fAlpha;					// α値
	float		m_fRemove;					// 移動量の減少値
};
#endif //!_EFFECT_H_