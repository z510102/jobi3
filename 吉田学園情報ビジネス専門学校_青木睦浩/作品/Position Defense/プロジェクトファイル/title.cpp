//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "title.h"
#include "input_keyboard.h"
#include "fade.h"
#include "UI.h"
#include "game.h"
#include "input_gamepad.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;
int CTitle::m_nSelect = TYPE_START_GAME;

//=============================================================================
// タイトルの読み込み
//=============================================================================
HRESULT CTitle::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					 // デバイスへのポインタ
							  "data/TEXTURE/bg.png",	 // 読み込むファイル名
							  &m_pTexture);				 // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// タイトルの破棄
//=============================================================================
void CTitle::Unload(void)
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
CTitle *CTitle::Create(void)
{
	// ポインタ
	CTitle *pTitle;

	// メモリを確保
	pTitle = new CTitle;

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
CTitle::CTitle()
{
	// 変数をクリア
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos)
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

	// 選択項目をTYPE_START_GAMEに
	m_nSelect = TYPE_START_GAME;

	// UIを取得
	CUI *pUI = CGame::GetUI();

	// UIの生成
	pUI = CUI::Create(D3DXVECTOR3(640, 200, 0), D3DXVECTOR2(380, 80), CUI::TYPE_TITLE);

	// TYPE_MAXの数分
	for (int nCnt = CUI::TYPE_START_GAME; nCnt < CUI::TYPE_MAX; nCnt++)
	{
		// UIの生成
		pUI = CUI::Create(D3DXVECTOR3(640, (float)(90 * nCnt - 1000), 0), D3DXVECTOR2(140, 40), (CUI::UI_TYPE)nCnt);
	}

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// 音を鳴らす
	pSound->PlaySound(pSound->SOUND_LABEL_TITLE_BGM);

	// 音量を調整
	pSound->SoundVolume(CSound::SOUND_LABEL_TITLE_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CTitle::Uninit(void)
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
void CTitle::Update(void)
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

	// 十字キー下
	if (pInputKeyboard->GetKeyboardTrigger(DIK_DOWN) == true || pInputGamepad->GetLeftStickTrigger(CInputGamepad::STICK_TYPE_DOWN))
	{
		// 選択項目の数値を加算
		m_nSelect++;

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

		// 選択項目がTYPE_RANKING + 1の場合
		if (m_nSelect >= TYPE_RANKING + 1)
		{
			// 音量を調整
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

			// 選択項目をTYPE_RANKINGに調整
			m_nSelect = TYPE_RANKING;
		}
	}

	//十字キー上
	else if (pInputKeyboard->GetKeyboardTrigger(DIK_UP) == true || pInputGamepad->GetLeftStickTrigger(CInputGamepad::STICK_TYPE_UP))
	{
		// 選択項目の数値を減算
		m_nSelect--;

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

		// 選択項目がTYPE_START_GAME - 1の場合
		if (m_nSelect <= TYPE_START_GAME - 1)
		{
			// 音量を調整
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

			// 選択項目をTYPE_START_GAMEに調整
			m_nSelect = TYPE_START_GAME;
		}
	}

	// Enterキーを押したら
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
	{
		// 選択項目の種類
		switch (m_nSelect)
		{

		// TYPE_START_GAMEの場合
		case TYPE_START_GAME:

			// 音を鳴らす
			pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);

			// 音量を調整
			pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);

			// GAME画面へ
			pFade->SetFade(CManager::MODE_GAME);
			break;



		// TYPE_TUTORIALの場合
		case TYPE_TUTORIAL:

			// 音を鳴らす
			pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

			// 音量を調整
			pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);

			// チュートリアル画面へ
			pFade->SetFade(CManager::MODE_TUTORIAL);
			break;



		// TYPE_RANKINGの場合
		case TYPE_RANKING:

			// 音を鳴らす
			pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

			// 音量を調整
			pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);

			// リザルト画面へ
			pFade->SetFade(CManager::MODE_RESULT);
			break;



		// 例外処理
		default:
			break;
		}
	}
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CTitle::Draw(void)
{
	
}

int CTitle::GetSelect(void)
{
	// メンバを戻り値へ返す
	return m_nSelect;
}
