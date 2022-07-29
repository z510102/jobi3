//=============================================================================
//
// 2Dポリゴンクラス [scene2D.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene2D.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pVtxBuff = NULL;
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_scale, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
	m_nColor_r = 0;
	m_nColor_g = 0;
	m_nColor_b = 0;
	m_nColor_a = 0;
	m_nType = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,										// 頂点バッファの使用法
		FVF_VERTEX_2D,											// 使用する頂点フォーマット
		D3DPOOL_MANAGED,										// リソースのバッファを保持するメモリ
		&m_pVtxBuff,											// 頂点バッファへのポインタ
		NULL);													// NULLに設定

	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// 2Dポリゴンの生成
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nType)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->m_scale = scale;
		pScene2D->m_pos = pos;
		pScene2D->m_nType = nType;
		pScene2D->Init();
	}

	return pScene2D;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void CScene2D::SetVtxTexture(int nPatteernAnimU, float fAnimU, int nPatteernAnimV, float fAnimV, float fTexU, float fTexV)
{
	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + fTexV);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 位置を取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
// 位置情報を設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_pos = pos;
	m_scale = scale;

	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
void CScene2D::SetTexPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float fPos)
{
	m_pos = pos;
	m_scale = scale;

	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fPos, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fPos, m_pos.y + m_scale.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// サイズを取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_scale;
}
//=============================================================================
// サイズを設定
//=============================================================================
void CScene2D::SetSize(D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//=============================================================================
// 頂点カラーを設定
//=============================================================================
void CScene2D::SetColor(int nColr, int nColg, int nColb, int nCola)
{
	m_nColor_r = nColr;
	m_nColor_g = nColg;
	m_nColor_b = nColb;
	m_nColor_a = nCola;

	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);
	pVtx[1].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);
	pVtx[2].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);
	pVtx[3].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点カラーを設定
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}