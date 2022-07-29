//=============================================================================
//
// 3Dポリゴンクラス [scene3D.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene3D.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CScene3D::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D(int nPriority) : CScene(nPriority)
{
	m_pVtxBuff = NULL;
	memset(&m_pos, 0, sizeof(m_pos));
	memset(&m_rot, 0, sizeof(m_rot));
	memset(&m_scale, 0, sizeof(m_scale));
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx; //頂点バッファへのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);

	//rhwの設定
	pVtx[0].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
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
void CScene3D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{	
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;		// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,							//開始する始点のインデックス
		2);							//描画するプリミティブ数
}
//=============================================================================
// 3Dポリゴンの生成
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nType)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;

	if (pScene3D != NULL)
	{
		pScene3D->m_pos = pos;
		pScene3D->m_rot = rot;
		pScene3D->m_scale = scale;
		pScene3D->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		pScene3D->Init();
	}

	return pScene3D;
}
//=============================================================================
// 3Dポリゴンの位置を設定
//=============================================================================
void CScene3D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_pos = pos;
	m_scale = scale;

	VERTEX_3D *pVtx; //頂点バッファへのポインタ

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
//=============================================================================
// 3Dポリゴンの位置を取得
//=============================================================================
D3DXVECTOR3 CScene3D::GetPosition(void)
{
	return m_pos;
}
