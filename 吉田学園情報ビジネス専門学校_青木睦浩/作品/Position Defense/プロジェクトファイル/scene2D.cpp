//=============================================================================
//
// 2Dポリゴン処理 [scene2D.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "scene2D.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	// 値をクリア（初期設定）
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXVECTOR2));
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nColorR = 0;
	m_nColorG = 0;
	m_nColorB = 0;
	m_nColorA = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定（引数から）
	m_pos = pos;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,  //確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,          //頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,            //頂点バッファへのポインタ
		NULL);

	// 頂点バッファへのポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{
	// 頂点バッファへのポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし頂点座標へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2Dポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  //プリミティブの種類
						   0,                    //開始する頂点のインデックス
						   2);                   //描画するプリミティブ数
}

//=============================================================================
// 2Dポリゴンの生成
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos)
{
	// ポインタ
	CScene2D *pScene2D;

	// メモリを確保
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		// Initへ
		pScene2D->Init(pos);
	}

	// ポインタを戻り値へ返す
	return pScene2D;
}

//=============================================================================
// 2Dポリゴンの設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	// 引数をメンバへ渡す
	m_pos = pos;
}

//=============================================================================
// 2Dポリゴンの取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	// メンバを戻り値へ返す
	return m_pos;
}

//=============================================================================
// 2Dポリゴンのサイズの設定
//=============================================================================
void CScene2D::SetSize(float fWidth, float fHeight)
{
	// 引数をメンバへ渡す
	m_size = D3DXVECTOR2(fWidth, fHeight);
}

//=============================================================================
// 2Dポリゴンのサイズの取得
//=============================================================================
D3DXVECTOR2 CScene2D::GetSize(void)
{
	// メンバを戻り値へ返す
	return m_size;
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	//メンバに情報を渡す
	m_color = col;

	//頂点バッファへのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void CScene2D::SetColor(int nColR, int nColG, int nColB, int nColA)
{
	// 引数をメンバへ渡す
	m_nColorR = nColR;
	m_nColorG = nColG;
	m_nColorB = nColB;
	m_nColorA = nColA;

	//頂点バッファへのポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
	pVtx[1].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
	pVtx[2].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
	pVtx[3].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2Dポリゴンのテクスチャ割り当て
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	// 引数をメンバへ渡す
	m_pTexture = pTexture;
}

//=============================================================================
// 2Dポリゴンのテクスチャ座標の設定
//=============================================================================
void CScene2D::SetVertexTexture(int nPatternAnimU, float fAnimU, int nPatternAnimV, float fAnimV, float fTexU, float fTexV)
{
	// 引数をメンバへ渡す
	m_fTexU = fTexU;
	m_fTexV = fTexV;

	// 頂点バッファへのポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + 0.0f, (nPatternAnimV * fAnimV) + 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + m_fTexU, (nPatternAnimV * fAnimV) + 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + 0.0f, (nPatternAnimV * fAnimV) + m_fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + m_fTexU, (nPatternAnimV * fAnimV) + m_fTexV);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}