//=============================================================================
//
// ステージ管理クラス [stage.h]
// Author : 小笠原　彪我
// Author : 青木睦浩
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "stage.h"
#include "model.h"
#include "camera.h"
#include "keyboard.h"
#include "stage_data.h"
#include "game.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CStageData *CStage::m_pStageData = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CStage::CStage(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(m_pos, 0, sizeof(D3DXVECTOR3));			// 位置
	memset(m_move, 0, sizeof(D3DXVECTOR3));			// 移動量
	m_bUninit = false;								// 破棄
	m_nNumModel = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CStage::~CStage()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage::Init(void)
{
	SetObjType(CScene::OBJTYPE_MODEL);
#if 1
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	char aFile[256];	// 文字列読み込み
	D3DXVECTOR3 pos;	// 位置保存
	D3DXVECTOR3 rot;	// 向き保存
	D3DXVECTOR3 scale;	// 大きさ保存
	int nCntModel = 0;	// モデル数カウント
	int nModelType = 0;	// モデルの種類
	bool bModelSet = false;		// モデルセット
	bool bStageSet = false;		// ステージセット

	// モデルの配置情報読み込み
	FILE *pFile = fopen(MODEL_FILENAME, "r");

	if (pFile != NULL)
	{
		while (true)
		{
			// 文字列読み込み開始
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{
				// モデルの種類数
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nModelType);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)
			{
				// モデルのパス
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				CStageData::LoadXFile(&aFile[0], nModelType);
				nModelType++;
			}
			if (strcmp(&aFile[0], "STAGESET") == 0)
			{
				// ステージセット
				m_nNumModel = 0;
				bStageSet = true;
			}
			if (strcmp(&aFile[0], "END_STAGESET") == 0)
			{
				// ステージセットの終了
				bStageSet = false;
			}
			// ステージセット
			if (bStageSet == true)
			{
				if (strcmp(&aFile[0], "MODELSET") == 0)
				{
					// モデルセット
					bModelSet = true;
				}
				if (strcmp(&aFile[0], "END_MODELSET") == 0)
				{
					// モデルセットの終了
					bModelSet = false;

					// モデルの情報を設定
					m_pStageData = CStageData::Create(pos, rot, scale, nModelType);
					// モデルの数を増やす
					m_nNumModel++;
				}
				// モデルセット
				if (bModelSet == true)
				{
					// モデルの種類
					if (strcmp(&aFile[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nModelType);
					}
					// 位置
					if (strcmp(&aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					}
					// 向き
					if (strcmp(&aFile[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					}
					// 大きさ
					if (strcmp(&aFile[0], "SCALE") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &scale.x, &scale.y, &scale.z);
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

#if 0
	m_nNumModel = 2;
	m_pModel[0] = CModel::Create("data/MODEL/building00.x");
	m_pModel[0]->SetPosition(D3DXVECTOR3(-120, 0, -100));
	m_pModel[0]->SetRotation(D3DXVECTOR3(0, 0, 0));

	m_pModel[1] = CModel::Create("data/MODEL/building01.x");
	m_pModel[1]->SetPosition(D3DXVECTOR3(120, 0, 100));
	m_pModel[1]->SetRotation(D3DXVECTOR3(0, 0, 0));

#endif

	// 位置の設定
	m_pos = D3DXVECTOR3(0, 0, 0);

	// 向きの設定
	m_rot = D3DXVECTOR3(0, 0, 0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStage::Uninit(void)
{
	// モデルの破棄
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Uninit();
		}
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStage::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CStage::Draw(void)
{
}

//=============================================================================
// 通常の当たり判定
//=============================================================================
bool CStage::Collision(CStageData *pStage, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	//モデル情報を取得
	CModel *pModel = pStage->GetModel();

	// pModelがNULLじゃなかったら
	if (pModel != NULL)
	{
		// 情報を渡す
		D3DXVECTOR3 pos = pStage->GetPosition();
		D3DXVECTOR3 scale = pModel->GetScale();

		// pPos.yの値がpos.yの値以下かつpPosOld.yの値がpos.yの値以上の場合
		if (pPos->y <= pos.y && pPosOld->y >= pos.y)
		{
			// pPos.xの値が計算した値以上かつ pPos.zの値が計算した値以下かつ pPos.xの値が計算した値以下かつ pPos.zの値が計算した値以上の場合
			if (pPos->x >= pos.x - scale.x + 15.0f  && pPos->z <= pos.z + scale.z + 15.0f &&
				pPos->x <= pos.x + scale.x + 15.0f  && pPos->z >= pos.z - scale.z + 15.0f)
			{
				// 情報を渡す
				pPos->y = pos.y;
				BackPos = pos.y;

				// trueを返す
				return true;
			}
			
		}

	}

	// falseを返す
	return false;
}

//=============================================================================
// ステージの生成
//=============================================================================
CStage *CStage::Create(void)
{
	// ポインタ
	CStage *pStage;

	// メモリを確保
	pStage = new CStage;

	if (pStage != NULL)
	{
		// 処理へ
		pStage->Init();
	}

	// ポインタを戻り値へ返す
	return pStage;
}

//=============================================================================
// ステージデータの取得
//=============================================================================
CStageData *CStage::GetStageData(void)
{
	// メンバを戻り値へ返す
	return m_pStageData;
}
