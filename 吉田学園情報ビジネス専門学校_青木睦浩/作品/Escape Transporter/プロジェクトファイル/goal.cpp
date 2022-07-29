//=============================================================================
//
// ステージ管理クラス [goal.h]
// Author : 土居　大輝
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "goal.h"
#include "model.h"
#include "camera.h"
#include "keyboard.h"
#include "stage_data.h"
#include "game.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CModel *CGoal::m_apModel[MODEL_MAX] = {};
CStageData *CGoal::m_pStageData = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal(int nPriority) : CScene(nPriority)
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
CGoal::~CGoal()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGoal::Init(void)
{
	SetObjType(CScene::OBJTYPE_MODEL);

#if 1
	//m_nNumModel = 2;
	m_pModel = CModel::Create("data/MODEL/FLOOR/Floor_Green.x");
	m_pModel->SetPosition(D3DXVECTOR3(-30.0f, 20.0f, 6500.0f));
	m_pModel->SetRotation(D3DXVECTOR3(0, 0, 0));

	//m_pModel[1] = CModel::Create("data/MODEL/building01.x");
	//m_pModel[1]->SetPosition(D3DXVECTOR3(120, 0, 100));
	//m_pModel[1]->SetRotation(D3DXVECTOR3(0, 0, 0));

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
void CGoal::Uninit(void)
{
	// モデルの破棄
		if (m_pModel != NULL)
		{
			m_pModel->Uninit();
		}


	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGoal::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CGoal::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// 計算用マトリックス

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
		if (m_pModel != NULL)
		{
			m_pModel->Draw();
		}

}
//=============================================================================
// 通常の当たり判定
//=============================================================================
bool CGoal::Collision(CGoal *pGoal,D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	//モデル情報を取得
	CModel *pModel = pGoal->GetModel();

	if (pModel != NULL)
	{
		D3DXVECTOR3 pos = pModel->GetPosition();
		D3DXVECTOR3 scale = pModel->GetScale();

		if (pPos->y <= pos.y&&pPosOld->y >= pos.y)
		{
			if (pPos->x >= pos.x - scale.x + 10.0f && pPos->z <= pos.z + scale.z + 10.0f&&
				pPos->x <= pos.x + scale.x + 10.0f  && pPos->z >= pos.z - scale.z + 10.0f)
			{
				pPos->y = pos.y;
				BackPos = pos.y;
				return true;
			}
		}

	}

	return false;
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CGoal *CGoal::Create(void)
{
	CGoal *pGoal;
	pGoal = new CGoal;

	if (pGoal != NULL)
	{
		pGoal->Init();
	}

	return pGoal;
}


CModel *CGoal::GetModel(void)
{
	return m_pModel;
}

D3DXVECTOR3 CGoal::GetPosition(void)
{
	return m_pos;
}

