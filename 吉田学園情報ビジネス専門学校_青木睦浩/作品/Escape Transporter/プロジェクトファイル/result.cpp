//=============================================================================
//
// リザルトの処理 [result.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "result.h"
#include"keyboard.h"
#include"manager.h"
#include"score.h"
#include"fade.h"
#include"time.h"
#include"sound.h"
#include"game.h"
#include"bg.h"
#include"ranking.h"
#include "ui.h"
//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CScore *CResult::m_pScore = NULL;
CTime *CResult::m_pTime = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_dwCurrentTime = 0;
	// 現在の時間を取得
	m_dwExecLastTime = timeGetTime();
	m_fade = false;
	m_bflag1 = false;
	m_bflag2 = false;
	m_bflag3 = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	// 背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 24);


	// 今回の時間をロード
	FILE *pFile;
	//ロード処理
	pFile = fopen(FILE_TIME, "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%d\n", &m_nNewdata);
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_RESULT, 0.5f);
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	//フェードの取得
	CFade *pFade = CManager::GetFade();

	//サウンド取得
	CSound *pSound = CManager::GetSound();

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	m_dwCurrentTime = timeGetTime();	// 現在の時間を取得


	// 時間経過処理（1秒で減らす）
	if ((m_dwCurrentTime - m_dwExecLastTime) >= 400)
	{
		// 今回の時間を生成
		m_pTime = CTime::Create(D3DXVECTOR3(NOWTIME_X, NOWTIME_Y, 0.0f), D3DXVECTOR3(NOWTIME_WIDTH, NOWTIME_HEIGHT, 0.0f), m_nNewdata, true);
		if (m_bflag2 == false)
		{
			pSound->Play(pSound->SOUND_LABEL_TAIKODON);
			pSound->SetVolume(pSound->SOUND_LABEL_TAIKODON, 2.0f);
			m_bflag2 = true;
		}
	}

	if ((m_dwCurrentTime - m_dwExecLastTime) >= 1200)
	{
		if (m_nNewdata == 0)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_GRANK);
		}
		else if (m_nNewdata <= 5 && m_nNewdata > 0)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_FRANK);
		}
		else if (m_nNewdata <= 10 && m_nNewdata > 5)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_ERANK);
		}
		else if (m_nNewdata <= 15 && m_nNewdata > 10)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_DRANK);
		}
		else if (m_nNewdata <= 20 && m_nNewdata > 15)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_CRANK);

		}
		else if (m_nNewdata <= 25 && m_nNewdata > 20)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_BRANK);

		}
		else if (m_nNewdata <= 20 && m_nNewdata > 25)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_ARANK);
		}
		else if (m_nNewdata > 30)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_SRANK);
		}
		if (m_bflag3 == false)
		{
			pSound->Play(pSound->SOUND_LABEL_TADA);
			pSound->SetVolume(pSound->SOUND_LABEL_TADA, 1.0f);
			m_bflag3 = true;
		}
	}


	// ランキング行き
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (m_bflag3 == true)
		{
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RANKING);
				pSound->Stop(pSound->SOUND_LABEL_TADA);
				m_fade = true;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// リザルトの生成
//=============================================================================
CResult * CResult::Create(void)
{
	//リザルトのインスタンス生成
	CResult *pResult = new CResult;

	//リザルトの準備
	if (pResult != NULL)
	{
		pResult->Init();
	}
	return pResult;
}
