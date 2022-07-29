//=============================================================================
//
// プレイヤークラス [player.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"
#include "model.h"
#include "keyboard.h"
#include "xinput_gamepad.h"
#include "camera.h"
#include "motion.h"
#include "stage.h"
#include "stage_data.h"
#include "billeffect.h"
#include "effect_straight.h"
#include "effect_speed.h"
#include "game.h"
#include "goal.h"
#include "fade.h"
#include "bullet.h"
#include "meshfield.h"
#include"time.h"
#include"sound.h"
#define RAND_POS (float(rand() % 200)- 100)

#define PI_QUARTER	(D3DX_PI / 4.0f)	// 3.14fの1/4の値	斜め移動の向き　45°
#define PI_HALF		(D3DX_PI / 2.0f)	// 3.14fの1/2の値	斜め移動の向き　90°
#define PLAYER_MOVESPEED		(5.5f)		// スピード

#define CYCLE (float(rand() % 324) / 90.0f - float(rand() % 324) / 90.0f)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(m_pos, 0, sizeof(D3DXVECTOR3));			// 位置
	memset(m_move, 0, sizeof(D3DXVECTOR3));			// 移動量
	m_nNumModel = 0;
	m_bJump = false;
	m_bLand = false;
	m_bGoal = false;
	m_bFade = false;
	m_bHitBullet = false;
	m_bDeathFrag = false;
	m_bMeshField = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	m_bJump = true;
	
	SetObjType(OBJTYPE_PLAYER);

	LoadPlayerFile(FILENAME_PLAYER);

	// 位置の設定
	m_pos = D3DXVECTOR3(0, 0, 0);

	// 向きの設定
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_fGravitySpeed = GRAVITYSPEED;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
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
void CPlayer::Update(void)
{
	//ゲームパッドの情報を取得
	CXinputPad *pXinputPad = CManager::GetXinputPad();

	// キーボードの情報を取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラの向きを取得
	D3DXVECTOR3 cameraRot = pCamera->GetRot();

	//サウンド取得
	CSound *pSound = CManager::GetSound();


	// スピードアップ	エフェクト
#if 0
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		float fAngle = CYCLE;
		CEffectSpeed::Create(D3DXVECTOR3(m_pos.x + sinf(fAngle) * 100, m_pos.y, m_pos.z + cosf(fAngle) * 100), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 180, 27);
	}
#endif


	m_posOld = m_pos;


	//***********************************************************
	//	移動処理
	//***********************************************************
	
	// 後ろ移動
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_move.x = sinf(0.75f) * -PLAYER_MOVESPEED;
			m_move.z = cosf(0.75f) * PLAYER_MOVESPEED;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			//まだ
			m_rot.y = (-D3DX_PI *3) /4;
			m_move.x = sinf(-0.75f) * -PLAYER_MOVESPEED;
			m_move.z = cosf(-0.75f) * PLAYER_MOVESPEED;
		}
		else
		{
			m_rot.y = D3DX_PI;
			m_move.x = sinf(m_rot.y) * PLAYER_MOVESPEED;
			m_move.z = cosf(m_rot.y) * -PLAYER_MOVESPEED;
		}
	}
	// 前移動
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_move.x = sinf(0.50f) * PLAYER_MOVESPEED;
			m_move.z = cosf(0.50f) * -PLAYER_MOVESPEED;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = -(D3DX_PI * 7) / 4;
			m_move.x = sinf(-0.50f) * PLAYER_MOVESPEED;
			m_move.z = cosf(-0.50f) * -PLAYER_MOVESPEED;
		}
		else
		{
			m_rot.y = 0;
			m_move.x = sinf(m_rot.y) * PLAYER_MOVESPEED;
			m_move.z = cosf(m_rot.y) * -PLAYER_MOVESPEED;
		}
	}
	// 左移動
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_rot.y = -D3DX_PI / 2;
		m_move.x = sinf(m_rot.y) * -PLAYER_MOVESPEED;
		m_move.z = cosf(m_rot.y) * PLAYER_MOVESPEED;
	}
	// 右移動
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_move.x = sinf(m_rot.y) * -PLAYER_MOVESPEED;
		m_move.z = cosf(m_rot.y) * PLAYER_MOVESPEED;
	}
	else
	{
		m_move = D3DXVECTOR3(0, m_move.y, 0);
	}
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{
		m_bJump = true;
		m_move.y = 15.0f;
		pSound->Play(pSound->SOUND_LABEL_JUMP);
		pSound->SetVolume(pSound->SOUND_LABEL_JUMP, 0.8f);
	}
	if (m_bJump = true)
	{
		m_bLand = false;
		m_bJump = true;
	}


	if (m_fGravitySpeed > 0.0f)
	{
		m_move.y -= m_fGravitySpeed;
		m_pos.y += m_move.y;
	}

	//浮く状態
	//if (m_pos.y <= 0.0f)
	//{
	//	m_pos.y = 0.0f;
	//	m_move.y = 0.0f;
	//	m_bJump = false;
	//}

	//当たり判定
	CStage *pStage = CManager::GetGame()->GetStage();
	CGoal * pGoal = CManager::GetGame()->GetGoal();
	CMeshField *pMeshField = CManager::GetGame()->GetMeshField();

	//シーンからステージデータを取得
	CScene *pScene = CScene::GetScene(PRIORITY_MODEL);
	//各モデル数分回す
	while (pScene != NULL)
	{
		//シーンからとってきたステージデータをCStageDataにキャスト
		CStageData *pStageData = (CStageData*)pScene;

		//シーンの次の情報の確保
		CScene *pSceneNext = CScene::GetNextScene(pScene);
		if (pStageData != NULL)
		{
			m_bLand = pStage->Collision(pStageData, &m_pos, &m_posOld, &m_move, m_fBackPos);
			m_bGoal = pGoal->Collision(pGoal, &m_pos, &m_posOld, &m_move, m_fBackPos);
			m_bMeshField = pMeshField->Collision(pMeshField, &m_pos, &m_posOld, &m_move, m_fBackPos);

			// 床ブロックの位置を取得
			D3DXVECTOR3 blockpos = pStageData->GetPosition();

			//地面踏んだら
			if (m_bLand == true)
			{
				m_fGravitySpeed = blockpos.y;
				m_move.y = 0.0f;
				m_pos.y = m_fBackPos;
				m_bJump = false;
			}
			//ゴール踏んだら
			if (m_bGoal == true)
			{
				m_fGravitySpeed = 0.0f;
				m_move.y = 0.0f;
				m_pos.y = m_fBackPos;
				m_bGoal = false;
				// フェードの取得
				CFade *pFade = CManager::GetFade();
				if (m_bFade == false)
				{
					// 画面遷移 / フェード処理
					pFade->SetFade(CManager::MODE_RESULT);
					m_bFade = true;
				}

			}
			//メッシュフィールドの着地判定
			if (m_bMeshField == true)
			{
				m_bLand = true;
				m_fGravitySpeed = 0.0f;
				m_move.y = 0.0f;
				m_pos.y = m_fBackPos;
				m_bJump = false;
				m_bMeshField = false;
			}

			else
			{
				m_fGravitySpeed = GRAVITYSPEED;
			}

			//次の情報に置き換える
			pScene = pSceneNext;

		}

	}
	//弾あたったら
	if (m_bHitBullet == true&& m_bFade==false)
	{
		m_bGoal = false;
		// フェードの取得
		//CFade *pFade = CManager::GetFade();
		// 画面遷移 / フェード処理
		//pFade->SetFade(CManager::MODE_RESULT);
		//m_bFade = true;
		m_bHitBullet = false;
	}
	//死亡フラグがオンだったら
	if (m_bDeathFrag == true)
	{
		Uninit();
	}
	// ゲームオーバー判定
	if (m_pos.y <= -200.0f)
	{
		m_pos.y = -200.0f;

		// ファイル呼び出しのやつ
		FILE *pFile;
		CTime *pTime = CGame::GetTime();

		//時間のセーブ処理
		pFile = fopen("data/SAVEDATA/newtime.txt", "w");
		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", 0);
		}
		else
		{
			printf("ファイルが開けませんでした\n");
		}
		fclose(pFile);
		pTime->SetTime(0);

		// フェードの取得
		CFade *pFade = CManager::GetFade();
		if (m_bFade == false)
		{
			// 画面遷移 / フェード処理
			pFade->SetFade(CManager::MODE_RESULT);
			m_bFade = true;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
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
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
	}

	return pPlayer;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// モデルファイル読み込み
//=============================================================================
void CPlayer::LoadPlayerFile(const char * pFileName)
{	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 pos;	// 位置保存
	D3DXVECTOR3 rot;	// 向き保存
	int nIndex = 0;
	int nParent = 0;	// 親モデル
	int nCntModel = 0;	// モデル数
	char aFile[256];	// 文字列読み込み

	bool bCharacterSet = false;	// キャラクターセット
	bool bPartsSet = false;		// パーツセット

	// プレイヤーのモデル/オフセット読み込み
	FILE *pFile = fopen(pFileName, "r");

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
}


