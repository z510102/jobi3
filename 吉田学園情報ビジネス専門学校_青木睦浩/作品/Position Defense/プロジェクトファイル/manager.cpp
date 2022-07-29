//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "manager.h"
#include "sound.h"
#include "input_keyboard.h"
#include "input_gamepad.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "clear.h"
#include "over.h"
#include "result.h"
#include "fade.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputGamepad *CManager::m_pInputGamepad = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CClear *CManager::m_pClear = NULL;
COver *CManager::m_pOver = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == NULL)
	{
		// メモリを確保
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL)
		{
			// レンダラーの初期化処理へ
			m_pRenderer->Init(hWnd, TRUE);
		}
	}

	if (m_pInputKeyboard == NULL)
	{
		// メモリを確保
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != NULL)
		{
			// キーボードの初期化処理へ
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	if (m_pInputGamepad == NULL)
	{
		// メモリを確保
		m_pInputGamepad = new CInputGamepad;

		if (m_pInputGamepad != NULL)
		{
			// ゲームパッドの初期化処理へ
			m_pInputGamepad->Init(hInstance, hWnd);
		}
	}

	if (m_pSound == NULL)
	{
		// メモリを確保
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			// サウンドの初期化処理へ
			m_pSound->Init(hWnd);
		}
	}

	// フェードの生成処理へ
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CManager::MODE_TITLE);

	// それぞれの画面の読み込みへ
	CTitle::Load();
	CTutorial::Load();
	CClear::Load();
	COver::Load();
	CResult::Load();

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CManager::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CScene::ReleaseAll();

	// それぞれの画面の破棄へ
	CTitle::Unload();
	CTutorial::Unload();
	CClear::Unload();
	COver::Unload();
	CResult::Unload();

	// レンダリングクラスの破棄
	if (m_pRenderer != NULL)
	{
		// レンダラーの終了処理へ
		m_pRenderer->Uninit();

		// メモリを解放
		delete m_pRenderer;

		// NULLにする
		m_pRenderer = NULL;
	}

	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの終了処理へ
		m_pInputKeyboard->Uninit();

		// メモリを解放
		delete m_pInputKeyboard;

		// NULLにする
		m_pInputKeyboard = NULL;
	}

	// ゲームパッドの破棄
	if (m_pInputGamepad != NULL)
	{
		// ゲームパッドの終了処理へ
		m_pInputGamepad->Uninit();

		// メモリを解放
		delete m_pInputGamepad;

		// NULLにする
		m_pInputGamepad = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		// サウンドの終了処理へ
		m_pSound->Uninit();

		// メモリを解放
		delete m_pSound;

		// NULLにする
		m_pSound = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの更新処理
		m_pInputKeyboard->Update();
	}

	if (m_pInputGamepad != NULL)
	{
		// ゲームパッドの更新処理
		m_pInputGamepad->Update();
	}

	if (m_pRenderer != NULL)
	{
		// レンダリングの更新処理
		m_pRenderer->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// レンダリングの描画処理
		m_pRenderer->Draw();
	}
}

//=============================================================================
// モードの設定
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	// モードの種類
	switch (m_mode)
	{
	// タイトルの場合
	case MODE_TITLE:

		if (m_pTitle != NULL)
		{
			// タイトルの終了へ
			m_pTitle->Uninit();

			// メンバをNULLにする
			m_pTitle = NULL;
		}

		break;



	// チュートリアルの場合
	case MODE_TUTORIAL:

		if (m_pTutorial != NULL)
		{
			// チュートリアルの終了へ
			m_pTutorial->Uninit();

			// メンバをNULLにする
			m_pTutorial = NULL;
		}

		break;



	// ゲームの場合
	case MODE_GAME:
		
		if (m_pGame != NULL)
		{
			// ゲームの終了へ
			m_pGame->Uninit();

			// メンバをNULLにする
			m_pGame = NULL;
		}

		break;



	// クリアの場合
	case MODE_CLEAR:
		
		if (m_pClear != NULL)
		{
			// クリアの終了へ
			m_pClear->Uninit();

			// メンバをNULLにする
			m_pClear = NULL;
		}

		break;



	// オーバーの場合
	case MODE_OVER:

		if (m_pOver != NULL)
		{
			// オーバーの終了へ
			m_pOver->Uninit();

			// メンバをNULLにする
			m_pOver = NULL;
		}

		break;



	// リザルトの場合
	case MODE_RESULT:

		if (m_pResult != NULL)
		{
			// リザルトの終了へ
			m_pResult->Uninit();

			// メンバをNULLにする
			m_pResult = NULL;
		}

		break;
	}

	// 全てのオブジェクトの破棄へ
	CScene::ReleaseAll();

	// モードの破棄
	switch (mode)
	{
	// タイトルの場合
	case MODE_TITLE:

		// タイトルの生成
		m_pTitle = CTitle::Create();
		break;



	// チュートリアルの場合
	case MODE_TUTORIAL:

		// チュートリアルの生成
		m_pTutorial = CTutorial::Create();
		break;



	// ゲームの場合
	case MODE_GAME:

		// ゲームの生成
		m_pGame = CGame::Create();
		break;



	// クリアの場合
	case MODE_CLEAR:

		// クリアの場合
		m_pClear = CClear::Create();
		break;



	// オーバーの場合
	case MODE_OVER:

		// オーバーの場合
		m_pOver = COver::Create();
		break;



	// リザルトの場合
	case MODE_RESULT:

		// リザルトの場合
		m_pResult = CResult::Create();
		break;
	}

	// 情報を渡す
	m_mode = mode;
}

//=============================================================================
// モードの取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	// メンバを戻り値へ返す
	return m_mode;
}

//=============================================================================
// レンダリングクラスを取得
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	// メンバを戻り値へ返す
	return m_pRenderer;
}

//=============================================================================
// キーボードクラスを取得
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	// メンバを戻り値へ返す
	return m_pInputKeyboard;
}

//=============================================================================
// ゲームパッドクラスを取得
//=============================================================================
CInputGamepad * CManager::GetInputGamepad(void)
{
	// メンバを戻り値へ返す
	return m_pInputGamepad;
}

//=============================================================================
// フェードクラスを取得
//=============================================================================
CFade * CManager::GetFade(void)
{
	// メンバを戻り値へ返す
	return m_pFade;
}

//=============================================================================
// サウンドクラスを取得
//=============================================================================
CSound * CManager::GetSound(void)
{
	// メンバを戻り値へ返す
	return m_pSound;
}
