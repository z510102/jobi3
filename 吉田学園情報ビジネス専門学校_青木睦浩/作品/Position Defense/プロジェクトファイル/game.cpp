//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "game.h"
#include "player.h"
#include "input_keyboard.h"
#include "enemy.h"
#include "score.h"
#include "high_score.h"
#include "position.h"
#include "straight.h"
#include "UI.h"
#include "fade.h"
#include "time.h"
#include "life.h"
#include "grenade.h"
#include "flash_grenade.h"
#include "g_possession.h"
#include "f_g_possession.h"
#include "bullet_magazine.h"
#include "bullet_total.h"
#include "explosion.h"
#include "item.h"
#include "sound.h"
#include "flash.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CPlayer *CGame::m_pPlayer = NULL;
CBg *CGame::m_pBg = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CScore *CGame::m_pScore = NULL;
CPosition *CGame::m_pPosition = NULL;
CHighScore *CGame::m_pHighScore = NULL;
CUI *CGame::m_pUI = NULL;
CTime *CGame::m_pTime = NULL;
CLife *CGame::m_pLife = NULL;
CG_Possession *CGame::m_pG_Possession = NULL;
CF_G_Possession *CGame::m_pF_G_Possession = NULL;
CBulletMagazine *CGame::m_pBulletMagazine = NULL;
CBulletTotal *CGame::m_pBulletTotal = NULL;
CExplosion *CGame::m_pExplosion = NULL;
CFlash *CGame::m_pFlash = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	// 変数をクリア
	m_nSpawn = 0;
	m_nSpawn2 = 0;
	m_nSpawn3 = 0;
	m_nSpawn4 = 0;
	m_nSpawn5 = 0;
	m_nSpawn6 = 0;
	m_nSpawn7 = 0;
	m_nCntSpawn = 0;
	m_nCntLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// テクスチャ読み込みへ
	Load();

	// 背景を生成
	m_pBg = CBg::Create();

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(458, 685, 0));

#if 0
	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(125, 80, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);*/

	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(130, 130, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(130, 180, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);*/

	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 80, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 130, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 180, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 80, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 130, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 180, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);*/

	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 80, 0),  D3DXVECTOR3(0, 1, 0),    CEnemy::TYPE_1);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 80, 0),  D3DXVECTOR3(0, 1.5f, 0), CEnemy::TYPE_2);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(220, 80, 0),  D3DXVECTOR3(0, 2, 0),    CEnemy::TYPE_3);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(250, 80, 0),  D3DXVECTOR3(0, 2.5f, 0), CEnemy::TYPE_4);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(280, 80, 0),  D3DXVECTOR3(0, 3, 0),    CEnemy::TYPE_5);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(20, 30, 0),   D3DXVECTOR3(2, 0, 0),    CEnemy::TYPE_6);*/
#endif

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(1130, 100, 0), D3DXVECTOR2(30, 40));

	// ハイスコアの生成
	m_pHighScore = CHighScore::Create(D3DXVECTOR3(1130, 50, 0));

	// ポジションの生成
	m_pPosition = CPosition::Create(D3DXVECTOR3(457, 685, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	// UIの生成
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 50, 0),  D3DXVECTOR2(70, 20),  CUI::TYPE_HIGH_SCORE);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 100, 0), D3DXVECTOR2(70, 20),  CUI::TYPE_SCORE);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 170, 0), D3DXVECTOR2(70, 20),  CUI::TYPE_TIME);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 240, 0), D3DXVECTOR2(70, 20),  CUI::TYPE_LIFE);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 330, 0), D3DXVECTOR2(70, 40),  CUI::TYPE_GRENADE);
	m_pUI = CUI::Create(D3DXVECTOR3(1190, 330, 0), D3DXVECTOR2(70, 40),  CUI::TYPE_FLASH_GRENADE);
	m_pUI = CUI::Create(D3DXVECTOR3(1100, 480, 0), D3DXVECTOR2(170, 80), CUI::TYPE_WEAPON);
	m_pUI = CUI::Create(D3DXVECTOR3(1100, 630, 0), D3DXVECTOR2(200, 30), CUI::TYPE_RELOAD);
	m_pUI = CUI::Create(D3DXVECTOR3(1235, 515, 0), D3DXVECTOR2(25, 20),  CUI::TYPE_INFINITE);

	// タイムの生成
	m_pTime = CTime::Create(D3DXVECTOR3(1130, 170, 0));

	// ライフの生成
	m_pLife = CLife::Create(D3DXVECTOR3(1100, 240, 0));

	// グレネード所持数の生成
	m_pG_Possession = CG_Possession::Create(D3DXVECTOR3(1000, 310, 0));

	// フラッシュグレネード所持数の生成
	m_pF_G_Possession = CF_G_Possession::Create(D3DXVECTOR3(1190, 310, 0));

	// マガジンの生成
	m_pBulletMagazine = CBulletMagazine::Create(D3DXVECTOR3(1140, 510, 0), CBullet::TYPE_HG);

	// 総弾数の生成
	m_pBulletTotal = CBulletTotal::Create(D3DXVECTOR3(1220, 515, 0), CBullet::TYPE_HG);

	// 音を鳴らす
	pSound->PlaySound(pSound->SOUND_LABEL_GAME_BGM);

	// 音量を調整
	pSound->SoundVolume(CSound::SOUND_LABEL_GAME_BGM, 3.0f);

	return S_OK;
}

//=============================================================================
// ゲームの終了処理
//=============================================================================
void CGame::Uninit(void)
{
	// テクスチャ破棄へ
	Unload();

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// サウンドの停止
	pSound->StopSound();

	// オブジェクトの破棄へ
	Release();
}

//=============================================================================
// ゲームの更新処理
//=============================================================================
void CGame::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ライフの取得
	CLife *pLife;
	pLife = CGame::GetLife();

	// スコアをメンバへ渡す
	int nScore = m_pScore->GetScore();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	//Enterキーを押したら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//クリア画面へ
		pFade->SetFade(CManager::MODE_CLEAR);
	}

	// スポーン値を加算
	m_nSpawn++;
	m_nSpawn7++;

	// ランダムで出現位置を決める
	float fPosX = (float)(rand() % 666 + 125);

	// m_nSpawnが350以上になった場合
	if (m_nSpawn >= 350)
	{
		//敵の生成
		m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.2f, 0), CEnemy::TYPE_0);

		// 0にする
		m_nSpawn = 0;
	}

	// m_nSpawn7が1050以上かつm_nCntSpawnが0の場合
	if (m_nSpawn7 >= 1050 && m_nCntSpawn == 0)
	{
		// 1か2を決めて値を入れる
		int nSpawn = (int)(rand() % 2 + 1);

		switch (nSpawn)
		{
		// 1の場合
		case 1:
			// 爆発と敵を生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR3(1.0f, 0, 0), CEnemy::TYPE_6);
			break;

		// 2の場合
		case 2:
			// 爆発と敵を生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR3(-1.0f, 0, 0), CEnemy::TYPE_6);
			break;
		}

		// m_nSpawn7を0にする
		m_nSpawn7 = 0;

		// m_nCntSpawnを加算する
		m_nCntSpawn++;
	}

	// m_nSpawn7が2100以上かつm_nCntSpawnが1以上の場合
	else if (m_nSpawn7 >= 2100 && m_nCntSpawn >= 1)
	{
		// 1か2を決めてnSpawnに入れる
		int nSpawn = (int)(rand() % 2 + 1);

		switch (nSpawn)
		{
		// 1の場合
		case 1:
			// 爆発と敵を生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR3(1.0f, 0, 0), CEnemy::TYPE_6);
			break;

		// 2の場合
		case 2:
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR3(-1.0f, 0, 0), CEnemy::TYPE_6);
			break;
		}

		// m_nSpawn7の0にする
		m_nSpawn7 = 0;

		// m_nCntSpawnを加算する
		m_nCntSpawn++;
	}

	// nScoreが50以上になった場合
	if (nScore >= 50)
	{
		// m_nSpawn2を加算する
		m_nSpawn2++;

		// m_nSpawn2が455になった場合
		if (m_nSpawn2 >= 455)
		{
			//敵と爆発の生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.3f, 0), CEnemy::TYPE_1);

			// m_nSpawn2を0にする
			m_nSpawn2 = 0;
		}
	}

	// m_nScoreが150以上になった場合
	else if (nScore >= 150)
	{
		// m_nSpawn3を加算する
		m_nSpawn3++;

		// m_nSpawn3が525になった場合
		if (m_nSpawn3 >= 525)
		{
			//敵と爆発の生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.4f, 0), CEnemy::TYPE_2);

			// m_nSpawn3を0にする
			m_nSpawn3 = 0;
		}
	}

	// m_nScoreが300以上になった場合
	else if (nScore >= 300)
	{
		// m_nSpawn4を加算する
		m_nSpawn4++;

		// m_nSpawn4が595になった場合
		if (m_nSpawn4 >= 595)
		{
			//敵と爆発の生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.5f, 0), CEnemy::TYPE_3);

			// m_nSpawn4を0にする
			m_nSpawn4 = 0;
		}
	}

	// m_nScoreが500以上になった場合
	else if (nScore >= 500)
	{
		// m_nSpawn5を加算する
		m_nSpawn5++;

		// m_nSpawn5が665になった場合
		if (m_nSpawn5 >= 665)
		{
			//敵と爆発の生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.6f, 0), CEnemy::TYPE_4);

			// m_nSpawn5を0にする
			m_nSpawn5 = 0;
		}
	}

	// m_nScoreが750以上になった場合
	else if (nScore >= 750)
	{
		// m_nSpawn6を加算する
		m_nSpawn6++;

		// m_nSpawn6が725になった場合
		if (m_nSpawn6 >= 725)
		{
			//敵と爆発の生成
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.7f, 0), CEnemy::TYPE_5);

			// m_nSpawn6を0にする
			m_nSpawn6 = 0;
		}
	}

	// スコアが1000以上かつm_nCntLifeが0の場合
	if (nScore >= 1000 && m_nCntLife == 0)
	{
		// ライフを加算する
		pLife->AddLife(1);

		// m_nCntLifeを加算する
		m_nCntLife++;
	}

	// スコアが2000以上かつm_nCntLifeが1の場合
	else if (nScore >= 2000 && m_nCntLife == 1)
	{
		// ライフを加算する
		pLife->AddLife(1);

		// m_nCntLifeを加算する
		m_nCntLife++;
	}

	// スコアが3000以上かつm_nCntLifeが2の場合
	else if (nScore >= 3000 && m_nCntLife == 2)
	{
		// ライフを加算する
		pLife->AddLife(1);

		// m_nCntLifeを加算する
		m_nCntLife++;
	}

	// スコアが4000以上かつm_nCntLifeが3の場合
	else if (nScore >= 4000 && m_nCntLife == 3)
	{
		// ライフを加算する
		pLife->AddLife(1);

		// m_nCntLifeを加算する
		m_nCntLife++;
	}

	// スコアが5000以上かつm_nCntLifeが4の場合
	else if (nScore >= 5000 && m_nCntLife == 4)
	{
		// ライフを加算する
		pLife->AddLife(1);

		// m_nCntLifeを加算する
		m_nCntLife++;
	}
}

//=============================================================================
// ゲームの描画処理
//=============================================================================
void CGame::Draw(void)
{
	
}

//=============================================================================
// ゲームの生成
//=============================================================================
CGame *CGame::Create(void)
{
	// ポインタ
	CGame *pGame;

	// メモリを確保
	pGame = new CGame;

	if (pGame != NULL)
	{
		// Init処理へ
		pGame->Init(D3DXVECTOR3(0, 0, 0));
	}

	// ポインタを戻り値へ返す
	return pGame;
}

//=============================================================================
// ゲームクリア
//=============================================================================
void CGame::Clear(void)
{
	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// クリア画面へ
	pFade->SetFade(CManager::MODE_CLEAR);
}

//=============================================================================
// ゲームオーバー
//=============================================================================
void CGame::Over(void)
{
	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// オーバー画面へ
	pFade->SetFade(CManager::MODE_OVER);
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CGame::Load(void)
{
	// それぞれのテクスチャ読み込み処理へ
	CBg::Load();
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	CNumber::Load();
	CStraight::Load();
	CPosition::Load();
	CUI::Load();
	CGrenade::Load();
	CFlashGrenade::Load();
	CItem::Load();
	CFlash::Load();

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CGame::Unload(void)
{
	// それぞれのテクスチャ破棄処理へ
	CBg::Unload();
	CPlayer::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CNumber::Unload();
	CStraight::Unload();
	CPosition::Unload();
	CUI::Unload();
	CGrenade::Unload();
	CFlashGrenade::Unload();
	CItem::Unload();
	CFlash::Unload();
}





//=============================================================================
// エネミークラスを取得
//=============================================================================
CEnemy * CGame::GetEnemy(void)
{
	// メンバを戻り値へ返す
	return m_pEnemy;
}

//=============================================================================
// スコアクラスを取得
//=============================================================================
CScore * CGame::GetScore(void)
{
	// メンバを戻り値へ返す
	return m_pScore;
}

//=============================================================================
// ポジションクラスを取得
//=============================================================================
CPosition * CGame::GetPosition(void)
{
	// メンバを戻り値へ返す
	return m_pPosition;
}

//=============================================================================
// UIクラスを取得
//=============================================================================
CUI * CGame::GetUI(void)
{
	// メンバを戻り値へ返す
	return m_pUI;
}

//=============================================================================
// タイムクラスを取得
//=============================================================================
CTime * CGame::GetTime(void)
{
	// メンバを戻り値へ返す
	return m_pTime;
}

//=============================================================================
// ライフクラスを取得
//=============================================================================
CLife * CGame::GetLife(void)
{
	// メンバを戻り値へ返す
	return m_pLife;
}

//=============================================================================
// グレネード所持数クラスを取得
//=============================================================================
CG_Possession * CGame::GetG_Possession(void)
{
	// メンバを戻り値へ返す
	return m_pG_Possession;
}

//=============================================================================
// フラッシュグレネード所持数クラスを取得
//=============================================================================
CF_G_Possession * CGame::GetF_G_Possession(void)
{
	// メンバを戻り値へ返す
	return m_pF_G_Possession;
}

//=============================================================================
// マガジンクラスを取得
//=============================================================================
CBulletMagazine * CGame::GetBulletMagazine(void)
{
	// メンバを戻り値へ返す
	return m_pBulletMagazine;
}

//=============================================================================
// 総弾数クラスを取得
//=============================================================================
CBulletTotal * CGame::GetBulletTotal(void)
{
	// メンバを戻り値へ返す
	return m_pBulletTotal;
}

//=============================================================================
// 爆発クラスを取得
//=============================================================================
CExplosion * CGame::GetExplosion(void)
{
	// メンバを戻り値へ返す
	return m_pExplosion;
}

//=============================================================================
// 閃光クラスを取得
//=============================================================================
CFlash * CGame::GetFlash(void)
{
	// メンバを戻り値へ返す
	return m_pFlash;
}
