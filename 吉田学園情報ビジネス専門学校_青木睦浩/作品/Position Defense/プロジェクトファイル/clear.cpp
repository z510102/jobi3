//=============================================================================
//
// クリア処理 [clear.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "clear.h"
#include "input_keyboard.h"
#include "fade.h"
#include "input_gamepad.h"
#include "UI.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CClear::m_pTexture = NULL;

//=============================================================================
// クリアの読み込み
//=============================================================================
HRESULT CClear::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						 // デバイスへのポインタ
							  "data/TEXTURE/clear_bg.png",	 // 読み込むファイル名
							  &m_pTexture);					 // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// クリアの破棄
//=============================================================================
void CClear::Unload(void)
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
CClear *CClear::Create(void)
{
	// ポインタ
	CClear *pClear;

	// メモリを確保
	pClear = new CClear;

	if (pClear != NULL)
	{
		// Initへ
		pClear->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	// ポインタを戻り値へ返す
	return pClear;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CClear::CClear()
{
	// 変数をクリア
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// デストラクタ
//=============================================================================
CClear::~CClear()
{

}

//=============================================================================
// クリアの初期化処理
//=============================================================================
HRESULT CClear::Init(D3DXVECTOR3 pos)
{
	// UIのテクスチャ読み込みへ
	CUI::Load();

	//生成
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
	pUI = CUI::Create(D3DXVECTOR3(640, 200, 0), D3DXVECTOR2(400, 100), CUI::TYPE_GAME_CLEAR);

	// 音を鳴らす
	pSound->PlaySound(pSound->SOUND_LABEL_CLEAR_BGM);

	// 音量を調整
	pSound->SoundVolume(CSound::SOUND_LABEL_CLEAR_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// クリアの終了処理
//=============================================================================
void CClear::Uninit(void)
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

	// オブジェクトの破棄へ
	Release();
}

//=============================================================================
// クリアの更新処理
//=============================================================================
void CClear::Update(void)
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

		/*CManager::SetMode(CManager::MODE_TITLE);*/
	}
}

//=============================================================================
// クリアの描画処理
//=============================================================================
void CClear::Draw(void)
{

}