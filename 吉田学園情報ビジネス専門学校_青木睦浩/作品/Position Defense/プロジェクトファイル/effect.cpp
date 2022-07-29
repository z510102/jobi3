//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "effect.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリアする
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
	m_nColorR = 0;
	m_nColorG = 0;
	m_nColorB = 0;
	m_nColorA = 0;
	m_nColorSubR = 0;
	m_nColorSubG = 0;
	m_nColorSubB = 0;
	m_nColorSubA = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos,
	int nColorR, int nColorG, int nColorB, int nColorA,
	int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_EFFECT);

	//メンバに情報を渡す
	m_pos = pos;
	m_nColorR = nColorR;
	m_nColorG = nColorG;
	m_nColorB = nColorB;
	m_nColorA = nColorA;
	m_nColorSubR = nColorSubR;
	m_nColorSubG = nColorSubG;
	m_nColorSubB = nColorSubB;
	m_nColorSubA = nColorSubA;

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CEffect::Update(void)
{
	//頂点カラーのRGB値を減算
	m_nColorR -= m_nColorSubR;
	m_nColorG -= m_nColorSubG;
	m_nColorB -= m_nColorSubB;
	m_nColorA -= m_nColorSubA;

	//RGBAがそれぞれ0以下になったとき
	if (m_nColorR <= 0)
	{
		//0に戻す
		m_nColorR = 0;
	}

	if (m_nColorG <= 0)
	{
		//0に戻す
		m_nColorG = 0;
	}

	if (m_nColorB <= 0)
	{
		//0に戻す
		m_nColorB = 0;
	}

	if (m_nColorA <= 0)
	{
		//0に戻す
		m_nColorA = 0;
	}

	//色を更新
	SetColor(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
}

//=============================================================================
// 2Dポリゴンの描画処理
//=============================================================================
void CEffect::Draw(void)
{
	//アルファブレンディングを加算合成に設定
	CManager::GetRenderer()->SetAddSynthesis(true);

	// Scene2Dの描画処理へ
	CScene2D::Draw();

	//アルファブレンディングを通常合成に設定
	CManager::GetRenderer()->SetAddSynthesis(false);
}