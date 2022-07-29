//=============================================================================
//
// ゲーム画面 [game.cpp]
// Author : 小笠原　彪我
// Author : 川村　優斗
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "game.h"
#include "keyboard.h"
//#include "xinput_gamepad.h"
#include "fade.h"

#include "scene2D.h"
#include "scene3D.h"
#include "stage.h"

#include "meshfield.h"
#include "texture.h"

#include "light.h"
#include "camera.h"
#include "model.h"
#include "player.h"
//#include "bg.h"
//#include "bg_board.h"
//#include "player.h"
#include "enemy.h"
#include "score.h"
#include "time.h"
#include "ui.h"
//#include "move.h"
//#include "select.h"
//#include "ui_select.h"
#include "sound.h"
#include "billboard.h"
#include "billeffect.h"
#include "effect_straight.h"
#include "effect_smoke.h"
#include "effect_dust.h"
#include "goal.h"
#include "bullet.h"

#define CYCLE (float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f)
#define SPEED 2

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPlayer	*CGame::m_pPlayer = NULL;
CScore *CGame::m_pScore = NULL;
CTime *CGame::m_pTime = NULL;
CStage *CGame::m_pStage = NULL;
CGoal *CGame::m_pGoal = NULL;
CBullet *CGame::m_pBullet = NULL;
CMeshField *CGame::m_pMeshField = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_bFade = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{

	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetPositionR(D3DXVECTOR3(0.0f, GAZE_Y, -GAZE_Z));	// 注視点
	pCamera->SetPositionV(D3DXVECTOR3(0.0f, VIEW_Y, -VIEW_Z));	// 視点

	// メッシュフィールド
	//m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, -200.0f, 500.0f), D3DXVECTOR3(7000.0f, 0.0f, 7000.0f), CTexture::TEXTURETYPE_MAX);
	
	// プレーヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_GAME);
	pSound->SetVolume(pSound->SOUND_LABEL_GAME, 0.5f);

	// UIの生成
	CUI::Create(D3DXVECTOR3(150.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 40.0f, 0.0f), CTexture::TEXTURETYPE_HPBG);
	CUI::Create(D3DXVECTOR3(132.0f, 658.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(112.0f, 15.0f, 0.0f), CTexture::TEXTURETYPE_HPHONTAI);

	// ステージの生成
	m_pStage = CStage::Create();
	//ゴールの生成
	m_pGoal = CGoal::Create();

	// 敵の生成
	//CEnemy::Create(D3DXVECTOR3(0, 0, 300), D3DXVECTOR3(0, 0, 0));

	// UI タイマーとスコア　仮設置
	m_pTime = CTime::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(35.0f, 47.0f, 0.0f), 60, false);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	// ファイル呼び出しのやつ
	FILE *pFile;

	// 終わった時の時間を記録
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	//サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_GAME);

	//時間のセーブ処理
	pFile = fopen("data/SAVEDATA/newtime.txt", "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", nTime);
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	//// 終わったときのスコアもセーブ
	//CScore *pScore = CGame::GetScore();
	//int nScore = pScore->GetScore();
	////セーブ処理
	//pFile = fopen("data/SAVEDATA/newscore.txt", "w");
	//if (pFile != NULL)
	//{
	//	fprintf(pFile, "%d\n", nScore);
	//}
	//else
	//{
	//	printf("ファイルが開けませんでした\n");
	//}
	//fclose(pFile);

	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// フェードの取得
	CFade *pFade = CManager::GetFade();

	//// リザルト行き
	//if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true )
	//{
	//	if (m_bFade == false)
	//	{
	//		// 画面遷移 / フェード処理
	//		pFade->SetFade(CManager::MODE_RESULT);
	//		m_bFade = true;
	//	}
	//}

	//// とりあえず今はスペースおしっぱでスコア増えるように
	//CScore *pScore = CGame::GetScore();
	//if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
	//{
 //		pScore->AddScore(1);
	//}

	// エフェクト/パーティクル
#if 1
	//煙
	if (CManager::GetInputKeyboard()->GetPress(DIK_K) == true)
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			CEffectSmoke::Create(D3DXVECTOR3(0, 50, 0),
				D3DXVECTOR3(10.0f, 10.0f, 0.0f),
				D3DXVECTOR3(0, 0, 0),
				60, 26);
		}
	}

	//砂埃
	if (CManager::GetInputKeyboard()->GetPress(DIK_L) == true)
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			CEffectDust::Create(D3DXVECTOR3(0, 70, 0),
				D3DXVECTOR3(10.0f, 10.0f, 0.0f),
				D3DXVECTOR3(sinf(CYCLE) * SPEED, 1.0f, cosf(CYCLE) * SPEED),
				120, 26);
		}
	}


//ビーム
	if (CManager::GetInputKeyboard()->GetPress(DIK_J) == true)
	{
		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			CEffectDust::Create(D3DXVECTOR3(0, 70, 0),
				D3DXVECTOR3(10.0f, 10.0f, 0.0f),
				D3DXVECTOR3(sinf(CYCLE) * 5, cosf(CYCLE) * 5, 1.5f),
				420, 26);
		}
		CEffectStr::Create(D3DXVECTOR3(0, 70, 0),
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(0.0f, 0.0f, 5.0f),
			120, 26,
			m_colval);
	}
		//test
	if (CManager::GetInputKeyboard()->GetPress(DIK_O) == true)
	{
		CBullet::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(BULLET_SCALE_X, BULLET_SCALE_Y, BULLET_SCALE_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 240, 28);	// ビルボードの初期化
	}

	CScene *pSceneBullet = CScene::GetScene(PRIORITY_BULLET);

	//弾の当たり判定
	while (pSceneBullet != NULL)
	{
		//シーンを弾のクラスにキャスト
		CBullet *pBullet = (CBullet*)pSceneBullet;
		//シーンの次のオブジェクトを格納
		CScene *pNext = CScene::GetNextScene(pSceneBullet);
		if (pBullet != NULL)
		{
			pBullet->Collision(pBullet, &m_pPlayer->GetPos());
		}
		//シーンを次にする
		pSceneBullet = pNext;
	}

#endif

}
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}
//=============================================================================
// ゲーム画面の生成
//=============================================================================
CGame *CGame::Create(void)
{
	// タイトルのインスタンス生成
	CGame *pGame = new CGame;
	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}

//=============================================================================
// スコアの取得
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// タイムの取得
//=============================================================================
CTime * CGame::GetTime(void)
{
	return m_pTime;
}

CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}
CStage *CGame::GetStage(void)
{
	return m_pStage;
}

CGoal *CGame::GetGoal(void)
{
	return m_pGoal;
}

CBullet *CGame::GetBullet(void)
{
	return m_pBullet;
}

CMeshField *CGame::GetMeshField(void)
{
	return m_pMeshField;
}