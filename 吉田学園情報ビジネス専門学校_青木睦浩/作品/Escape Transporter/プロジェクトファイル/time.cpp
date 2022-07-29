//=============================================================================
//
// 時間経過の処理 [time.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "time.h"
#include "number.h"
#include"player.h"
#include"game.h"
#include"fade.h"
#include"ui.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CTime::CTime(int nPriority) : CScene(nPriority)
{
	m_bStop = false;
	m_dwCurrentTime = 0;
	// 現在の時間を取得
	m_dwExecLastTime = timeGetTime();
	m_fade = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CTime::~CTime()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	// 数字の生成
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apNumber[nCntTime] = CNumber::Create(D3DXVECTOR3(m_pos.x + m_size.x + SPACE_TIME * nCntTime, m_pos.y, 0.0f), D3DXVECTOR3(m_size.x, m_size.y, 0.0f), CTexture::TEXTURETYPE_TIME);
	}

	m_fade = false;
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->Uninit();
			delete m_apNumber[nCntTime];
			m_apNumber[nCntTime] = NULL;
		}
	}
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CTime::Update(void)
{
	m_dwCurrentTime = timeGetTime();	// 現在の時間を取得

										//フェードの取得
	CFade *pFade = CManager::GetFade();

	// 時間経過処理（1秒で減らす）
	if ((m_dwCurrentTime - m_dwExecLastTime) >= REDUCE_TIME && m_nTime != 0)
	{
		if (m_bStop == false)
		{
			AddTime(-1);
			m_dwCurrentTime = 0;
			m_dwExecLastTime = timeGetTime();
		}
	}

	// 数字
	m_apNumber[0]->SetNumber(m_nTime % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[1]->SetNumber(m_nTime % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[2]->SetNumber(m_nTime % (int)pow(10, 1));

	if (m_nTime <= 30)
	{
		// 残り時間少なくなると色を変える
		m_col.a = 1.0f;
		m_col.r = 1.0f;
		m_apNumber[0]->SetColor(m_col);
		m_apNumber[1]->SetColor(m_col);
		m_apNumber[2]->SetColor(m_col);
	}
	m_mode = CManager::GetMode();
	if (m_mode == CManager::MODE_GAME)
	{
		// 時間切れ
		if (m_nTime == 0)
		{
			if (m_bflag == false)
			{
				CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(TIMEUP_WIDTH, TIMEUP_HEIGHT, 0.0f), CTexture::TEXTURETYPE_TIMEUP);
				m_bflag = true;
			}
			m_IntervalTime++;
			if (m_IntervalTime >= INTERVAL_TIME)
			{
				// リザルト行き
				if (m_fade == false)
				{
					pFade->SetFade(CManager::MODE_RESULT);
					m_fade = true;
					m_bStop = true;
				}
			}
			m_nTime = 0;
		}
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apNumber[nCntTime]->Draw();
	}
}

//=============================================================================
//時間の加算
//=============================================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;
}
//=============================================================================
//時間の取得
//=============================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

void CTime::SetTime(int nTime)
{
	m_nTime = nTime;
}

//=============================================================================
//時間の生成
//=============================================================================
CTime * CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time, bool bStop)
{
	// 時間のインスタンス生成
	CTime *pTime = new CTime;

	// 時間の準備
	if (pTime != NULL)
	{
		pTime->m_bStop = bStop;
		pTime->m_nTime = time;
		pTime->m_pos = pos;
		pTime->m_size = size;
		pTime->Init();
	}
	return pTime;
}
