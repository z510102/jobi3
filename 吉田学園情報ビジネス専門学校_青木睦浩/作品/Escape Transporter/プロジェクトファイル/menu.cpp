//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "menu.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"ui.h"
#include"bg.h"
#include"sound.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CUI *CMenu::m_pUI[12] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CMenu::CMenu()
{
	m_fade = false;
	// 初期状態（Startを選んでいる状態）
	m_nCntSelect = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMenu::~CMenu()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMenu::Init(void)
{
	// 背景作る
	CBg::Create(D3DXVECTOR3(BG_X, BG_Y, 0.0f), D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f), CTexture::TEXTURETYPE_MENUBG);

	// UI出す
	m_pUI[0] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y - 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PLAY);
	m_pUI[1] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y + 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_HELP);
	m_pUI[2] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y + 120.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_RANK);
	m_pUI[3] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y + 240.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_BACK);
	m_pUI[4] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH, UIICON_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PLAYICON);
	m_pUI[5] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH, UIICON_HEIGHT, 0.0f), CTexture::TEXTURETYPE_HELPICON);
	m_pUI[6] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH, UIICON_HEIGHT, 0.0f), CTexture::TEXTURETYPE_RANKICON);
	m_pUI[7] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH - 50.0f, UIICON_HEIGHT - 100.0f, 0.0f), CTexture::TEXTURETYPE_BACKICON);
	m_pUI[8] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PLAYTEXT);
	m_pUI[9] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_HELPTEXT);
	m_pUI[10] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_RANKTEXT);
	m_pUI[11] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_BACKTEXT);


	//サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_MENU);
	pSound->SetVolume(pSound->SOUND_LABEL_MENU, 0.5f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMenu::Uninit(void)
{
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_MENU);
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMenu::Update(void)
{
	// フェードの取得
	CFade *pFade = CManager::GetFade();

	//サウンド取得
	CSound *pSound = CManager::GetSound();

	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// UIの色々処理（Startのときにこれを出す、Tutorialのときにこれを出す…）
	switch (m_nCntSelect)
	{
	case 0:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case 1:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case 2:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case 3:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}

	// メニュー移動（↓）
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true || pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_MOVE);
		pSound->SetVolume(pSound->SOUND_LABEL_MOVE, 0.5f);

		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_RANKING;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_PLAY;
			break;
		}
	}

	// メニュー移動（↑）
	if (pInputKeyboard->GetTrigger(DIK_UP) == true || pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_MOVE);
		pSound->SetVolume(pSound->SOUND_LABEL_MOVE, 0.5f);
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_PLAY;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_RANKING;
			break;
		}
	}

	// 決定
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_KETTEI);
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_GAME);
				m_fade = true;
			}
			break;
		case SELECT_TUTORIAL:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_TUTORIAL);
				m_fade = true;
			}
			break;
		case SELECT_RANKING:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RANKING2);
				m_fade = true;
			}
			break;
		case SELECT_QUIT:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_TITLE);
				m_fade = true;
			}
			break;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CMenu::Draw(void)
{
}

//=============================================================================
// タイトルの生成
//=============================================================================
CMenu * CMenu::Create(void)
{
	//メニューのインスタンス生成
	CMenu *pMenu = new CMenu;

	//メニューの準備
	if (pMenu != NULL)
	{
		pMenu->Init();
	}
	return pMenu;
}

