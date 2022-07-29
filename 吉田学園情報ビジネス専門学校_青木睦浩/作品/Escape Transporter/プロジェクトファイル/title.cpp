//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "title.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"sound.h"
#include"ui.h"
#include"bg.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_dwCurrentTime = 0;
	// 現在の時刻を取得
	m_dwExecLastTime = timeGetTime();
	m_fade = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{

	//サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_TITLE);
	pSound->SetVolume(pSound->SOUND_LABEL_TITLE, 0.5f);

	// 背景作る
	CBg::Create(D3DXVECTOR3(BG_X, BG_Y, 0.0f), D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f), CTexture::TEXTURETYPE_TITLEBG);

	// UI出す
	CUI::Create(D3DXVECTOR3(PUSH_X, PUSH_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(PUSH_WIDTH, PUSH_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PUSH);
	CUI::Create(D3DXVECTOR3(TITLE_X, TITLE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f), CTexture::TEXTURETYPE_NAME);
	CUI::Create(D3DXVECTOR3(HUMAN_X, HUMAN_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(HUMAN_WIDTH, HUMAN_HEIGHT, 0.0f), CTexture::TEXTURETYPE_WITCH);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_TITLE);
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// 現在の時間を取得
	m_dwCurrentTime = timeGetTime();

	//// 十秒経過で
	//if ((m_dwCurrentTime - m_dwExecLastTime) >= 10000)
	//{
	//	if (m_fade == false)
	//	{
	//		// ランキング画面へ
	//		pFade->SetFade(CManager::MODE_RANKING);
	//		m_fade = true;
	//		// ランキングも十秒で戻るようにしたいんだけど苦戦中
	//	}
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// タイトルの生成
//=============================================================================
CTitle * CTitle::Create(void)
{
	// タイトルのインスタンス生成
	CTitle *pTitle = new CTitle;

	// タイトルの準備
	if (pTitle != NULL)
	{
		pTitle->Init();
	}
	return pTitle;
}
