//=============================================================================
//
// ナンバー処理 [number.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "number.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
// 背景の読み込み
//=============================================================================
HRESULT CNumber::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	                     // デバイスへのポインタ
		                      "data/TEXTURE/number.png",	 // 読み込むファイル名
		                      &m_pTexture);                  // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 背景の破棄
//=============================================================================
void CNumber::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ナンバーの生成
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ポインタ
	CNumber *pNumber;

	// メモリを確保
	pNumber = new CNumber;

	if (pNumber != NULL)
	{
		// Initへ
		pNumber->Init(pos, fWidth, fHeight);
	}

	// ポインタを戻り値へ返す
	return pNumber;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	// 変数をクリアする
	m_pVtxBuff = NULL;
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// ナンバーの初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// メンバに情報を渡す
	m_pos = pos;
	m_size = D3DXVECTOR2(fWidth / 2, fHeight / 2);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,  // 確保するバッファのサイズ
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,          // 頂点フォーマット
		                        D3DPOOL_MANAGED,
		                        &m_pVtxBuff,            // 頂点バッファへのポインタ
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ナンバーの終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// ナンバーの更新処理
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
// ナンバーの描画処理
//=============================================================================
void CNumber::Draw(void)
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
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  // プリミティブの種類
		                   0,                    // 開始する頂点のインデックス
		                   2);                   // 描画するプリミティブ数
}

//=============================================================================
// ナンバーの設定処理
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	// 頂点バッファへのポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ナンバーの色設定処理
//=============================================================================
void CNumber::SetColor(int nColR, int nColG, int nColB, int nColA)
{
	// 頂点バッファへのポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);
	pVtx[1].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);
	pVtx[2].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);
	pVtx[3].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
