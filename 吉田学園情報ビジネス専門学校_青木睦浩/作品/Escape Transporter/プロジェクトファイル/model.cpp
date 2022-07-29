//=============================================================================
//
// モデルクラス [model.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"
#include "keyboard.h"
#include "game.h"
#include "stage.h"
#include "stage_data.h"

#define PLAYER_SIZE 10.0f
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel()
{
	// メンバ変数のクリア
	memset(m_pos, 0, sizeof(D3DXVECTOR3));	// 位置
	memset(m_rot, 0, sizeof(D3DXVECTOR3));	// 位置
	memset(m_scale, 0, sizeof(D3DXVECTOR2));// 大きさ
	m_pMesh = NULL;							// メッシュ（頂点情報）へのポインタ
	m_pBuffMat = NULL;						// マテリアル（材質情報）へのポインタ
	m_pParent = NULL;						// 親モデルへのポインタ
	m_nNumMat = 0;							// マテリアル数
	m_pTexture[5] = {};
}
//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9		matDef;		// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;		// マテリアルデータへのポインタ

	
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 親のマトリックスと掛け合わせる
	D3DXMATRIX	mtxParent;

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();				//親のマトリックスを取得
	}
	else
	{
		// 一番最初のマトリックス(基本になるマトリックス)を掛け合わせる
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// 各パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		int nCntTex = 0;

		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat->pTextureFilename)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntTex]);
			nCntTex++;
		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}

		// モデル（パーツ）の描画	
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}
//=============================================================================
// ステージセット　オブジェクト描画処理
//=============================================================================
void CModel::DrawObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9		matDef;		// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;		// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// スケールを反映
	D3DXMatrixScaling(&mtxTrans, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 各パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		int nCntTex = 0;

		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat->pTextureFilename)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntTex]);
			nCntTex++;
		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}

		// モデル（パーツ）の描画	
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}
//=============================================================================
// モデルの生成
//=============================================================================
CModel *CModel::Create(const char *pModelFileName)
{
	CModel *pModel;
	pModel = new CModel;

	if (pModel != NULL)
	{
		pModel->LoadXFile(pModelFileName);
		pModel->Init();
	}

	return pModel;
}
//=============================================================================
// 親モデルの設定
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}
//=============================================================================
// ワールドマトリックスを取得
//=============================================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//=============================================================================
// モデルの大きさを取得
//=============================================================================
D3DXVECTOR3 CModel::GetScale(void)
{ 
	return m_size;
}
//=============================================================================
// 移動量を取得
//=============================================================================
D3DXVECTOR3 CModel::GetMove(void) 
{ 
	return m_move; 
}			
//=============================================================================
// モデルの情報を設定
//=============================================================================
void CModel::LoadXFile(const char *pModelFileName)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(pModelFileName, D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	D3DXMATERIAL	*pMat;		// マテリアルデータへのポインタ
	int nCntTex = 0;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntTex]);
			nCntTex++;
		}
	}

	//頂点情報の取得
	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	//頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//全ての頂点を比較して最大値と最小値を抜き出す
		//最大値
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		//最小値
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}


		// 頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}
	// 最大値と最小値を引いた値がモデルの大きさ
	m_size.x = m_vtxMax.x;
	m_size.y = m_vtxMax.y;
	m_size.z = m_vtxMax.z;

}
