//=============================================================================
//
// エフェクト [effect.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect()
{
	// メンバ変数のクリア
	memset(m_pos, 0, sizeof(D3DXVECTOR3));		// 位置
	memset(m_move, 0, sizeof(D3DXVECTOR3));		// 移動量
	memset(m_size, 0, sizeof(D3DXVECTOR2));		// 大きさ
	m_nColorR = 0;								// 赤色
	m_nColorG = 0;								// 緑色
	m_nColorB = 0;								// 青色
	m_nColorA = 0;								// 透明度
	m_nSubColorR = 0;							// 赤色：減少値
	m_nSubColorG = 0;							// 緑色：減少値
	m_nSubColorB = 0;							// 青色：減少値
	m_nSubColorA = 0;							// 透明度：減少値
	m_nLife = 0;								// 寿命
}
//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int nColr, int nColg, int nColb, int nCola, int nSubColr, int nSubColg, int nSubColb, int nSubCola,
	int nLife)
{
	CBillboard::Init();
	SetObjType(OBJTYPE_EFFECT);
	m_pos = pos;
	m_move = move;
	m_size = size;
	m_nColorR = nColr;
	m_nColorG = nColg;
	m_nColorB = nColb;
	m_nColorA = nCola;
	m_nSubColorR = nSubColr;
	m_nSubColorG = nSubColg;
	m_nSubColorB = nSubColb;
	m_nSubColorA = nSubCola;

	m_nLife = nLife;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	// 頂点カラーを減算
	m_nColorR -= m_nSubColorR;
	m_nColorG -= m_nSubColorG;
	m_nColorB -= m_nSubColorB;
	m_nColorA -= m_nSubColorA;

	if (m_nColorR < 0)
	{
		m_nColorR = 0;
	}
	if (m_nColorG < 0)
	{
		m_nColorG = 0;
	}
	if (m_nColorB < 0)
	{
		m_nColorB = 0;
	}
	if (m_nColorA < 0)
	{
		m_nColorA = 0;
	}


	// 色を更新
	//SetColor(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	// αブレンディングを加算合成に設定
	CManager::GetRenderer()->SetAddSynthesis(true);

	// ビルボードの描画
	CBillboard::Draw();

	// αブレンディングを通常合成に設定
	CManager::GetRenderer()->SetAddSynthesis(false);
}
