//=============================================================================
//
// UIの処理 [ui.cpp]
// Author : 川村優斗
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "ui.h"
#include"fade.h"
#include"keyboard.h"
#include"time.h"
#include"game.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CUI::CUI(int nPriority) : CScene2D(nPriority)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Lifesize = D3DXVECTOR3(LIFE_WIDTH, LIFE_HEIGHT, 0.0f);
	m_type = CTexture::TEXTURETYPE_NAME;
	m_fPosU = 0.0f;
	m_fPosV = 0.0f;
	m_bBrinkFlag = false;
	m_bBrinkFlag2 = false;
	m_fade = false;
	m_bDisplay = false;

	// ライフの初期設定
	m_nLife = LIFE_MAX;
	m_dwCurrentTime = 0;
	m_dwExecLastTime = timeGetTime();
}

//=============================================================================
// デストラクタ
//=============================================================================
CUI::~CUI()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUI::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUI::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUI::Update(void)
{
	//UIの大きさを設定
	D3DXVECTOR3 pPos = GetPosition();

	// UIのサイズを設定
	D3DXVECTOR3 pSize = GetSize();

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//フェードの取得
	CFade *pFade = CManager::GetFade();

	// 時間切れのときはスコア増えないように
	CTime *pTime = CGame::GetTime();

	if (m_mode == CManager::MODE_GAME)
	{
		int nTime = pTime->GetTime();
	}

	CScene2D::Update();

	//タイプごとに動きを指定
	switch (m_type)
	{
	case CTexture::TEXTURETYPE_NAME:
		if (m_bBrinkFlag2 == false)
		{
			m_col.a = 0.0f;
		}
		m_col.a += 0.01f;
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			pPos.y = STOP_PUSH;
			m_col.a = 0.9f;
		}
		m_bBrinkFlag2 = true;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_bDisplay = true;
		}

		//色設定
		SetColor(m_col);

		//徐々に降りてく
		pPos.y += MOVE_PUSH;
		if (pPos.y >= STOP_PUSH)
		{
			//真ん中で止まる
			pPos.y -= MOVE_PUSH;
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				if (m_fade == false)
				{
					if (m_bDisplay == true)
					{
						//ゲーム行き
						pFade->SetFade(CManager::MODE_MENU);
						m_fade = true;
					}
				}
			}
		}
		break;
	case CTexture::TEXTURETYPE_PUSH:
		//点滅させる
		if (m_bBrinkFlag == false)
		{
			m_col.a -= 0.01f;
			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_bBrinkFlag = true;
			}
		}
		else
		{
			m_col.a += 0.01f;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_bBrinkFlag = false;
			}
		}

		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_WITCH:
		//上をウロウロさせとく
		pPos.x += MOVE_PICT;

		//端まで行ったらワープ
		if (pPos.x >= 1400.0f)
		{
			pPos.x = -70.0f;
		}
		break;
	case CTexture::TEXTURETYPE_HPHONTAI:

		if (pInputKeyboard->GetTrigger(DIK_L) == true)
		{
			AddLife(-10);
			m_Lifesize.x -= LIFE_DAMAGE;
			pPos.x += LIFE_DAMAGE;
		}
		if (m_nLife <= 0)
		{
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RESULT);
				m_fade = true;
				m_nLife = 0;
			}
		}
		break;

	default:
		break;
	}
	// HPゲージだけ特殊な処理
	if (m_type == CTexture::TEXTURETYPE_HPHONTAI)
	{
		SetTexPos(m_pos, m_size, m_Lifesize.x);
	}
	else
	{
		//プレイヤーの位置設定
		SetPosition(pPos, pSize);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ライフの加算
//=============================================================================
void CUI::AddLife(int nValue)
{
	m_nLife += nValue;
}

//=============================================================================
// ライフの取得
//=============================================================================
int CUI::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// UIの生成
//=============================================================================
CUI * CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, CTexture::TEXTURETYPE type)
{
	// UIのインスタンス生成
	CUI *pUI = new CUI(PRIORITY_UI);

	// UIの準備
	if (pUI != NULL)
	{
		pUI->m_type = type;
		pUI->m_pos = pos;
		pUI->m_size = size;
		pUI->Init();
		pUI->SetPosition(pos, size);
		pUI->SetSize(size);
		pUI->BindTexture(CManager::GetTexture()->SetTextureType(type));
	}
	return pUI;
}


