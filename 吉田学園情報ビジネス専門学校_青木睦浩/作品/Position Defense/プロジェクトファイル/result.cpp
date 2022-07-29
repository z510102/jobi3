//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "result.h"
#include "input_keyboard.h"
#include "fade.h"
#include "ranking.h"
#include "number.h"
#include "input_gamepad.h"
#include "sound.h"
#include "UI.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;

//=============================================================================
// タイトルの読み込み
//=============================================================================
HRESULT CResult::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,							 // デバイスへのポインタ
							  "data/TEXTURE/ranking_bg.png",	 // 読み込むファイル名
							  &m_pTexture);						 // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// タイトルの破棄
//=============================================================================
void CResult::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// タイトルの生成
//=============================================================================
CResult *CResult::Create(void)
{
	// ポインタ
	CResult *pResult;

	// メモリを確保
	pResult = new CResult;

	if (pResult != NULL)
	{
		// Initへ
		pResult->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	// ポインタを戻り値へ返す
	return pResult;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	// 変数をクリア
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos)
{
	// UIのテクスチャ読み込みへ
	CUI::Load();

	// 生成
	m_pScene2D = new CScene2D (PRIORITY_SCREEN);

	if (m_pScene2D != NULL)
	{
		// それぞれの処理へ
		m_pScene2D->Init(pos);
		m_pScene2D->SetSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_pScene2D->BindTexture(m_pTexture);
	}

	// UIの取得
	CUI *pUI = CGame::GetUI();

	// UIの生成
	pUI = CUI::Create(D3DXVECTOR3(480, 400, 0), D3DXVECTOR2(100, 200), CUI::TYPE_RANKING_RANK);

	// ナンバーのテクスチャ読み込みへ
	CNumber::Load();

	// ランキングの生成
	CRanking::Create(D3DXVECTOR3(650, 230, 0), D3DXVECTOR2(60, 80));

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// 音を鳴らす
	pSound->PlaySound(pSound->SOUND_LABEL_RANKING_BGM);

	// 音量を調整
	pSound->SoundVolume(CSound::SOUND_LABEL_RANKING_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	// UIのテクスチャ破棄へ
	CUI::Unload();

	//背景の破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();

		m_pScene2D = NULL;
	}

	// ナンバーのテクスチャ破棄へ
	CNumber::Unload();

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// サウンドの停止
	pSound->StopSound();

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// タイトルの更新処理
//=============================================================================
void CResult::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// Enterキーを押したら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
	{
		// ゲーム画面へ
		pFade->SetFade(CManager::MODE_TITLE);

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);
	}
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CResult::Draw(void)
{

}