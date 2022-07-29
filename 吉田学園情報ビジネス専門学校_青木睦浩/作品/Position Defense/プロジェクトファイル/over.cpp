//=============================================================================
//
// ゲームオーバー処理 [over.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "over.h"
#include "input_keyboard.h"
#include "fade.h"
#include "input_gamepad.h"
#include "UI.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 COver::m_pTexture = NULL;

//=============================================================================
// クリアの読み込み
//=============================================================================
HRESULT COver::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						 // デバイスへのポインタ
							  "data/TEXTURE/over_bg.png",	 // 読み込むファイル名
							  &m_pTexture);					 // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// クリアの破棄
//=============================================================================
void COver::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// クリアの生成
//=============================================================================
COver *COver::Create(void)
{
	// ポインタ
	COver *pOver;

	// メモリを確保
	pOver = new COver;

	if (pOver != NULL)
	{
		// Initへ
		pOver->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	// ポインタを戻り値へ返す
	return pOver;
}

//=============================================================================
// コンストラクタ
//=============================================================================
COver::COver()
{
	// 変数をクリア
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// デストラクタ
//=============================================================================
COver::~COver()
{

}

//=============================================================================
// クリアの初期化処理
//=============================================================================
HRESULT COver::Init(D3DXVECTOR3 pos)
{
	// UIのテクスチャ読み込みへ
	CUI::Load();

	// 生成
	m_pScene2D = new CScene2D(PRIORITY_SCREEN);

	if (m_pScene2D != NULL)
	{
		m_pScene2D->Init(pos);
		m_pScene2D->SetSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_pScene2D->BindTexture(m_pTexture);
	}

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// UIの取得
	CUI *pUI = CGame::GetUI();

	// UIの生成
	pUI = CUI::Create(D3DXVECTOR3(640, 200, 0), D3DXVECTOR2(400, 100), CUI::TYPE_GAME_OVER);

	// 音を鳴らす
	pSound->PlaySound(pSound->SOUND_LABEL_CLEAR_BGM);

	// 音量を調整
	pSound->SoundVolume(CSound::SOUND_LABEL_CLEAR_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// クリアの終了処理
//=============================================================================
void COver::Uninit(void)
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
// クリアの更新処理
//=============================================================================
void COver::Update(void)
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
		//タイトル画面へ
		pFade->SetFade(CManager::MODE_RESULT);

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);
	}
}

//=============================================================================
// クリアの描画処理
//=============================================================================
void COver::Draw(void)
{

}