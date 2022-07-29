//=============================================================================
//
// マネージャ [manager.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"
#include "keyboard.h"
#include "xinput_gamepad.h"
#include "sound.h"
#include "texture.h"

#include "title.h"
#include "menu.h"
#include "tutorial.h"
//#include "select.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "ranking2.h"
#include "fade.h"

#include "light.h"
#include "camera.h"
#include "scene3D.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CRenderer		*CManager::m_pRenderer = NULL;
CInputKeyboard	*CManager::m_pInputKeyboard = NULL;
CXinputPad		*CManager::m_pXinputPad = NULL;
CSound			*CManager::m_pSound = NULL;

CTitle			*CManager::m_pTitle = NULL;
CMenu			*CManager::m_pMenu = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CSelect			*CManager::m_pSelect = NULL;
CGame			*CManager::m_pGame = NULL;
CResult			*CManager::m_pResult = NULL;
CRanking		*CManager::m_pRanking = NULL;
CRanking2		*CManager::m_pRanking2 = NULL;

CFade			*CManager::m_pFade = NULL;
CTexture		*CManager::m_pTexture = NULL;
CModel			*CManager::m_pModel = NULL;

CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_pLight = NULL;
CManager::MODE	CManager::m_mode = MODE_TITLE;

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
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;

		// レンダラーの初期化処理
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}
	// キーボードの生成
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;

		// キーボードの初期化処理
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}
	// ゲームパッドの生成
	if (m_pXinputPad == NULL)
	{
		m_pXinputPad = new CXinputPad;

		// ゲームパッドの初期化処理
		if (m_pXinputPad != NULL)
		{
			m_pXinputPad->Init(hInstance, hWnd);
		}
	}
	// サウンド生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}
	

	// テクスチャクラス生成
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;

		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}


	//SetMode(m_mode);


	m_pCamera = CCamera::Create();
	m_pLight = CLight::Create();

	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	// Xinputゲームパッドの破棄
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Uninit();
		delete m_pXinputPad;
		m_pXinputPad = NULL;
	}
	//// サウンドの破棄
	//if (m_pSound != NULL)
	//{
	//	m_pSound->Uninit();
	//	delete m_pSound;
	//	m_pSound = NULL;
	//}
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// 全てのオブジェクトクラスを破棄
	CScene::ReleaseAll();

}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	// キーボードの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	// ゲームパッドの更新処理
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Update();
	}
	if (m_mode == MODE_GAME)
	{
		if (m_pCamera != NULL)
		{
			m_pCamera->Update();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();	// レンダラーの描画処理
	}
	if (m_mode == MODE_GAME)
	{
		m_pCamera->SetCamera();

	}


}
//=============================================================================
// モードの設定
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_MENU:
		if (m_pMenu != NULL)
		{
			m_pMenu->Uninit();
			m_pMenu = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;
		//case MODE_SELECT:
		//	if (m_pSelect != NULL)
		//	{
		//		m_pSelect->Uninit();
		//		m_pSelect = NULL;
		//	}
		//	break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}
		break;
	case MODE_RANKING2:
		if (m_pRanking2 != NULL)
		{
			m_pRanking2->Uninit();
			m_pRanking2 = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	default:
		break;
	}

	// 全てのオブジェクトクラスを破棄
	CScene::ReleaseAll();

	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_MENU:
		m_pMenu = CMenu::Create();
		break;
	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create();
		break;
		//case MODE_SELECT:
		//	m_pSelect = CSelect::Create();
		//	break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RANKING:
		m_pRanking = CRanking::Create();
		break;
	case MODE_RANKING2:
		m_pRanking2 = CRanking2::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	default:
		break;
	}

	m_mode = mode;
}
#if 1
//=============================================================================
// モードを取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}
//=============================================================================
// レンダラーを取得
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//=============================================================================
// キーボードを取得
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//=============================================================================
// ゲームパッドの取得
//=============================================================================
CXinputPad *CManager::GetXinputPad(void)
{
	return m_pXinputPad;
}
//=============================================================================
// サウンド取得
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}
//=============================================================================
// タイトル取得
//=============================================================================
CTitle *CManager::GetTitle(void)
{
	return m_pTitle;
}
//=============================================================================
// メニュー取得
//=============================================================================
CMenu *CManager::GetMenu(void)
{
	return m_pMenu;
}
CTutorial * CManager::GetTutorial(void)
{
	return m_pTutorial;
}
//=============================================================================
// セレクト取得
//=============================================================================
CSelect *CManager::GetSelect(void)
{
	return m_pSelect;
}
//=============================================================================
// ゲーム取得
//=============================================================================
CGame *CManager::GetGame(void)
{
	return m_pGame;
}
//=============================================================================
// リザルト取得
//=============================================================================
CResult *CManager::GetResult(void)
{
	return m_pResult;
}
CRanking * CManager::GetRanking(void)
{
	return m_pRanking;
}
CRanking2 * CManager::GetRanking2(void)
{
	return m_pRanking2;
}
//=============================================================================
// フェード取得
//=============================================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}
//=============================================================================
// フェード取得
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}
//=============================================================================
// ライト取得
//=============================================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}
//=============================================================================
// カメラ取得
//=============================================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}
#endif