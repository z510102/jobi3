//=============================================================================
//
// UI処理 [UI.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "UI.h"
#include "manager.h"
#include "input_keyboard.h"
#include "title.h"
#include "input_gamepad.h"
#include "bullet_magazine.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CUI::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// 背景の読み込み
//=============================================================================
HRESULT CUI::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/high score.png",			 // 読み込むファイル名
		&m_apTexture[TYPE_HIGH_SCORE]);          // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/score.png",				 // 読み込むファイル名
		&m_apTexture[TYPE_SCORE]);				 // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/time.png",				 // 読み込むファイル名
		&m_apTexture[TYPE_TIME]);				 // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/life.png",				 // 読み込むファイル名
		&m_apTexture[TYPE_LIFE]);				 // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/grenade.png",				 // 読み込むファイル名
		&m_apTexture[TYPE_GRENADE]);			 // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/flash_grenade.png",		 // 読み込むファイル名
		&m_apTexture[TYPE_FLASH_GRENADE]);       // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/weapon.png",				 // 読み込むファイル名
		&m_apTexture[TYPE_WEAPON]);              // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/tutorial_animation.png",	 // 読み込むファイル名
		&m_apTexture[TYPE_TUTORIAL_ANIMATION]);  // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/switching.png",			 // 読み込むファイル名
		&m_apTexture[TYPE_SWITCHING]);           // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/title_logo.png",			 // 読み込むファイル名
		&m_apTexture[TYPE_TITLE]);				 // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/reload_logo.png",			 // 読み込むファイル名
		&m_apTexture[TYPE_RELOAD]);				 // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/infinite.png",			 // 読み込むファイル名
		&m_apTexture[TYPE_INFINITE]);			 // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/ranking_rank.png",		 // 読み込むファイル名
		&m_apTexture[TYPE_RANKING_RANK]);        // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/clear_logo.png",			 // 読み込むファイル名
		&m_apTexture[TYPE_GAME_CLEAR]);          // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/over_logo.png",			 // 読み込むファイル名
		&m_apTexture[TYPE_GAME_OVER]);           // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/start game_logo.png",		 // 読み込むファイル名
		&m_apTexture[TYPE_START_GAME]);          // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/tutorial_logo.png",		 // 読み込むファイル名
		&m_apTexture[TYPE_TUTORIAL]);            // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,	         // デバイスへのポインタ
		"data/TEXTURE/ranking_logo.png",		 // 読み込むファイル名
		&m_apTexture[TYPE_RANKING]);             // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 背景の破棄
//=============================================================================
void CUI::Unload(void)
{
	// TYPE_MAXの数分
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// スコアの生成
//=============================================================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, UI_TYPE type)
{
	// ポインタ
	CUI *pUI;

	// メモリを確保とプライオリティ
	pUI = new CUI (PRIORITY_UI);

	if (pUI != NULL)
	{
		// 処理へ
		pUI->Init(pos);
		pUI->SetSize(size.x, size.y);
		pUI->BindTexture(m_apTexture[type]);

		// メンバへ情報を渡す
		pUI->m_Type = type;

		// 種類がTYPE_WEAPONの場合
		if (type == TYPE_WEAPON)
		{
			// テクスチャ座標を設定
			pUI->SetVertexTexture(0, 0.2f, 0, 0, 0.2f, 1.0f);
		}

		// 種類がTYPE_TUTORIAL_ANIMATIONの場合
		else if (type == TYPE_TUTORIAL_ANIMATION)
		{
			// テクスチャ座標を設定
			pUI->SetVertexTexture(0, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// ポインタを戻り値へ返す
	return pUI;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CUI::CUI(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_Type = TYPE_NONE;
	m_nPatternAnimU = 0;
	m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nType = 0;
	m_nReloadHG = 0;
	m_nReloadAR = 0;
	m_nReloadSG = 0;
	m_nReloadSR = 0;
	m_nReloadRL = 0;
	m_nBulletType = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CUI::~CUI()
{

}

//=============================================================================
// スコアの初期化処理
//=============================================================================
HRESULT CUI::Init(D3DXVECTOR3 pos)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を設定
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//=============================================================================
// スコアの終了処理
//=============================================================================
void CUI::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CUI::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// マガジンの取得
	CBulletMagazine *pBulletMagazine;
	pBulletMagazine = CGame::GetBulletMagazine();

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//=============================================================================
	// 武器の種類変更
	//=============================================================================

	// 十字キー右
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_RIGHT))
	{
		// m_nPatternAnimUを加算
		m_nPatternAnimU++;

		// 種類がTYPE_WEAPONの場合
		if (m_Type == TYPE_WEAPON)
		{
			// テクスチャ座標を設定
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.2f, 0, 0, 0.2f, 1.0f);
		}

		// 種類がTYPE_TUTORIAL_ANIMATIONの場合
		else if (m_Type == TYPE_TUTORIAL_ANIMATION)
		{
			// 音を鳴らす
			pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

			// 音量を調整
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

			// テクスチャ座標を設定
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);

			// m_nPatternAnimUが4以上の場合
			if (m_nPatternAnimU >= 3 + 1)
			{
				// 音量を調整
				pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

				// m_nPatternAnimUを3にする
				m_nPatternAnimU = 3;

				// テクスチャ座標を設定
				CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
			}
		}
	}

	// 十字キー左
	else if (pInputKeyboard->GetKeyboardTrigger(DIK_LEFT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_LEFT))
	{
		// m_nPatternAnimUを減算
		m_nPatternAnimU--;

		// 種類がTYPE_WEAPONの場合
		if (m_Type == TYPE_WEAPON)
		{
			// テクスチャ座標を設定
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.2f, 0, 0, 0.2f, 1.0f);
		}

		// 種類がTYPE_TUTORIAL_ANIMATIONの場合
		else if (m_Type == TYPE_TUTORIAL_ANIMATION)
		{
			// 音を鳴らす
			pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

			// 音量を調整
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

			// テクスチャ座標を設定
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);

			// m_nPatternAnimUが-1以下の場合
			if (m_nPatternAnimU <= 0 - 1)
			{
				// 音量を調整
				pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

				// m_nPatternAnimUを0にする
				m_nPatternAnimU = 0;

				// テクスチャ座標を設定
				CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
			}
		}
	}

	// 選択項目の取得
	int nSelect = CTitle::GetSelect();

	// UIの種類
	switch (m_Type)
	{
	// TYPE_START_GAMEの場合
	case TYPE_START_GAME:

		// 選択項目がTYPE_START_GAMEの場合
		if (nSelect == CTitle::TYPE_START_GAME)
		{
			// 色を設定
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			// 頂点カラーの設定へ
			SetColor(m_Color);
		}

		// それ以外の場合
		else
		{
			// 色を設定
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

			// 頂点カラーの設定へ
			SetColor(m_Color);
		}

		break;



	// TYPE_TUTORIALの場合
	case TYPE_TUTORIAL:

		// 選択項目がTYPE_TUTORIALの場合
		if (nSelect == CTitle::TYPE_TUTORIAL)
		{
			// 色を設定
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			// 頂点カラーの設定へ
			SetColor(m_Color);
		}

		// それ以外の場合
		else
		{
			// 色を設定
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

			// 頂点カラーの設定へ
			SetColor(m_Color);
		}

		break;



	// TYPE_RANKINGの場合
	case TYPE_RANKING:

		// 選択項目がTYPE_RANKINGの場合
		if (nSelect == CTitle::TYPE_RANKING)
		{
			// 色を設定
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			// 頂点カラーの設定へ
			SetColor(m_Color);
		}

		// それ以外の場合
		else
		{
			// 色を設定
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

			// 頂点カラーの設定へ
			SetColor(m_Color);
		}

		break;



	// TYPE_RELOADの場合
	case TYPE_RELOAD:

		// それぞれのマガジンの弾数を取得
		m_nReloadHG = pBulletMagazine->GetBulletMagazineHG();
		m_nReloadAR = pBulletMagazine->GetBulletMagazineAR();
		m_nReloadSG = pBulletMagazine->GetBulletMagazineSG();
		m_nReloadSR = pBulletMagazine->GetBulletMagazineSR();
		m_nReloadRL = pBulletMagazine->GetBulletMagazineRL();

		// 弾の種類を取得
		m_nBulletType = pBulletMagazine->GetBulletType();

		// それぞれのマガジンの弾数が0かつ弾の種類
		if (m_nReloadHG == 0 && m_nBulletType == 0 || m_nReloadAR == 0 && m_nBulletType == 1 || m_nReloadSG == 0 && m_nBulletType == 2 || m_nReloadSR == 0 && m_nBulletType == 3 || m_nReloadRL == 0 && m_nBulletType == 4)
		{
			// 色を設定
			SetColor(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}

		// それ以外
		else
		{
			// 色を設定
			SetColor(D3DXCOLOR(0.0, 0.0, 0.0, 0.0));
		}
		break;

	// TYPE_INFINITEの場合
	case TYPE_INFINITE:

		// 弾の種類を取得
		m_nBulletType = pBulletMagazine->GetBulletType();

		// 弾の種類が0（HG）の場合
		if (m_nBulletType == 0)
		{
			// 色を設定
			SetColor(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}

		else
		{
			// 色を設定
			SetColor(D3DXCOLOR(0.0, 0.0, 0.0, 0.0));
		}
		break;
	}

	// Scene2Dの更新処理へ
	CScene2D::Update();
}

//=============================================================================
// スコアの描画処理
//=============================================================================
void CUI::Draw(void)
{
	// Scene2Dの描画処理へ
	CScene2D::Draw();
}