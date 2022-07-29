//=============================================================================
//
// 敵クラス [enemy.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"
#include "model.h"
#include "keyboard.h"
#include "camera.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(m_pos, 0, sizeof(D3DXVECTOR3));			// 位置
	memset(m_move, 0, sizeof(D3DXVECTOR3));			// 移動量
	m_nNumModel = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
#if 1
	char aFile[256];	// 文字列読み込み
	D3DXVECTOR3 pos;	// 位置保存
	D3DXVECTOR3 rot;	// 向き保存
	int nCntModel = 0;	// モデル数
	int nParent = 0;	// 親モデル
	bool bCharacterSet = false;	// キャラクターセット
	bool bPartsSet = false;		// パーツセット

								// プレイヤーのモデル/オフセット読み込み
	FILE *pFile = fopen(FILENAME_LEG, "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{
				// モデル数
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)
			{
				// モデルのパス
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				m_pModel[nCntModel] = CModel::Create(&aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)
			{
				// キャラクターセット
				nCntModel = 0;
				bCharacterSet = true;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)
			{
				// キャラクターセット終了
				bCharacterSet = false;
			}
			if (bCharacterSet == true)
			{
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{
					// パーツセット
					bPartsSet = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{
					// パーツセット終了
					bPartsSet = false;
					nCntModel++;
				}
				if (bPartsSet == true)
				{
					// 親子関係設定
					if (strcmp(&aFile[0], "PARENT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);

						// 親子関係が-1の場合、親モデルを設定
						if (nParent != -1)
						{
							m_pModel[nCntModel]->SetParent(m_pModel[nParent]);
						}
					}
					// 位置
					if (strcmp(&aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntModel]->SetPosition(pos);
					}
					// 向き
					if (strcmp(&aFile[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntModel]->SetRotation(rot);
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// 読み込み終了
				break;
			}
		}
		fclose(pFile);
	}
#endif
	// 位置の設定
	m_pos = D3DXVECTOR3(0, 0, 0);

	// 向きの設定
	m_rot = D3DXVECTOR3(0, 0, 0);

#if 0
	//頂点座標の取得
	int nNumVtx;  //頂点数
	DWORD sizeFVF;  //頂点フォーマットのサイズ
	BYTE *pVtxBuff;  //頂点へのポインタ

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

		//全ての頂点を比較してモデルの最小値、最大値を抜き出す
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

		//g_aBuilding[g_nCntBuilding].fWidth = g_aBuilding[g_nCntBuilding].vtxMax.x - g_aBuilding[g_nCntBuilding].vtxMin.x;
		//g_aBuilding[g_nCntBuilding].fHeight = g_aBuilding[g_nCntBuilding].vtxMax.y - g_aBuilding[g_nCntBuilding].vtxMin.y;
		//g_aBuilding[g_nCntBuilding].fDepth = g_aBuilding[g_nCntBuilding].vtxMax.z - g_aBuilding[g_nCntBuilding].vtxMin.z;

		pVtxBuff += sizeFVF;
	}
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Uninit();
		}
	}


	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX	mtxRot, mtxTrans;

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

	// モデルの描画
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		pEnemy->Init();
		pEnemy->m_pos = pos;
		pEnemy->m_rot = rot;
	}

	return pEnemy;
}
//=============================================================================
// 通常の当たり判定
//=============================================================================
void CEnemy::Collision(void)
{
	// オブジェクト情報を取得
	CScene *pScene = CScene::GetScene(0);

	bool bLand = false;

	// 先オブジェクトから順に探す
	while (pScene)
	{
		// オブジェクトの種類を取得
		OBJTYPE objtype = CScene::GetobjType();

		// オブジェクトの種類が配置モデルの場合
		if (objtype == CScene::OBJTYPE_MODEL)
		{
			// オブジェクトの位置と大きさを取得
			D3DXVECTOR3 pos = ((CModel*)pScene)->GetPosition();
			D3DXVECTOR3 scale = ((CModel*)pScene)->GetScale();

			if (m_pos.x < pos.x + scale.x && m_pos.x > pos.x - scale.x &&
				m_pos.y < pos.y + scale.y && m_posOld.y <= pos.y)
			{
				m_pos.y = pos.y;
				bLand = true;
			}
			else if (m_pos.x < pos.x + scale.x && m_pos.x > pos.x - scale.x &&
				m_pos.y < pos.y + scale.y && m_posOld.y >= pos.y + scale.y)
			{
				m_pos.y = pos.y + scale.y;
			}
			if (m_pos.y < pos.y + scale.y && m_pos.y > pos.y &&
				m_pos.x < pos.x - scale.x && m_posOld.x <= pos.x)
			{
				m_pos.x = pos.x - scale.x;
			}
			else if (m_pos.y < pos.y + scale.y && m_pos.y > pos.y &&
				m_pos.x < pos.x && m_posOld.x >= pos.x + scale.x)
			{
				m_pos.x = pos.x + scale.x;
			}

		}
	}
}
