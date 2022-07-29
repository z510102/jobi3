//=============================================================================
//
// エフェクトの軌跡処理 [straight.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "straight.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CStraight::m_pTexture = NULL;

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CStraight::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
		                      "data/TEXTURE/effect000.jpg",		// 読み込むファイル名
		                      &m_pTexture);						// 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 2Dポリゴンのテクスチャ破棄
//=============================================================================
void CStraight::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 2Dポリゴンの生成処理
//=============================================================================
CStraight *CStraight::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,
	int nColorR, int nColorG, int nColorB, int nColorA,
	int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
	int nLife)
{
	// ポインタ
	CStraight *pEffect = NULL;

	// メモリを確保
	pEffect = new CStraight (PRIORITY_EFFECT);

	if (pEffect != NULL)
	{
		// Initへ
		pEffect->Init(pos, size, nColorR, nColorG, nColorB, nColorA, nColorSubR, nColorSubG, nColorSubB, nColorSubA, nLife);

		// BindTextureへ
		pEffect->BindTexture(m_pTexture);
	}

	// ポインタを戻り値へ返す
	return pEffect;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CStraight::CStraight(int nPriority) : CEffect(nPriority)
{
	// 変数をクリア
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
	m_nLife = 0;
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
CStraight::~CStraight()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStraight::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size,
	int nColorR, int nColorG, int nColorB, int nColorA,
	int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
	int nLife)
{
	// 初期化処理
	CEffect::Init(pos, nColorR, nColorG, nColorB, nColorA, nColorSubR, nColorSubG, nColorSubB, nColorSubA);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_EFFECT);

	//メンバに情報を渡す
	m_pos = pos;
	m_size = size;
	m_nLife = nLife;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStraight::Uninit(void)
{
	// 終了処理
	CEffect::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStraight::Update(void)
{
	//寿命を減らす
	m_nLife--;

	//サイズを小さくする
	m_size -= D3DXVECTOR2(1.0f, 0.1f);

	//サイズを更新
	SetSize(m_size.x, m_size.y);

	//位置を更新
	SetPosition(m_pos);

	// 更新処理
	CEffect::Update();
	CScene2D::Update();

	//寿命が0になったら
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CStraight::Draw(void)
{
	// 描画処理
	CEffect::Draw();
}