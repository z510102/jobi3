//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "tutorial.h"
#include "input_keyboard.h"
#include "fade.h"
#include "input_gamepad.h"
#include "sound.h"
#include "UI.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//=============================================================================
// タイトルの読み込み
//=============================================================================
HRESULT CTutorial::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,							 // デバイスへのポインタ
							  "data/TEXTURE/tutorial_bg.png",	 // 読み込むファイル名
							  &m_pTexture);						 // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// タイトルの破棄
//=============================================================================
void CTutorial::Unload(void)
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
CTutorial *CTutorial::Create(void)
{
	// ポインタ
	CTutorial *pTitle;

	// メモリを確保
	pTitle = new CTutorial;

	if (pTitle != NULL)
	{
		// Initへ
		pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	// ポインタを戻り値へ返す
	return pTitle;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	// 変数をクリア
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
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
	pUI = CUI::Create(D3DXVECTOR3(640, 50, 0),   D3DXVECTOR2(200, 50),  CUI::TYPE_TUTORIAL);
	pUI = CUI::Create(D3DXVECTOR3(640, 400, 0),  D3DXVECTOR2(420, 280), CUI::TYPE_TUTORIAL_ANIMATION);
	pUI = CUI::Create(D3DXVECTOR3(1180, 650, 0), D3DXVECTOR2(100, 50),  CUI::TYPE_SWITCHING);

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// 音を鳴らす
	pSound->PlaySound(pSound->SOUND_LABEL_TUTORIAL_BGM);

	// 音量を調整
	pSound->SoundVolume(CSound::SOUND_LABEL_TUTORIAL_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	// UIのテクスチャ破棄へ
	CUI::Unload();

	// 背景の破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();

		m_pScene2D = NULL;
	}

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
void CTutorial::Update(void)
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

	// Enterキー又はSTARTボタンを押したら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_START))
	{
		// ゲーム画面へ
		pFade->SetFade(CManager::MODE_GAME);

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);
	}

	// Aボタンを押したら
	if (pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
	{
		// タイトル画面へ
		pFade->SetFade(CManager::MODE_TITLE);

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_CANCEL);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_CANCEL, 1.0f);
	}
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}