//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputGamepad;
class CSound;
class CTitle;
class CTutorial;
class CGame;
class CClear;
class COver;
class CResult;
class CFade;

//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:

	// 画面のモードの種類
	typedef enum
	{
		MODE_TITLE = 0,		// タイトル
		MODE_TUTORIAL,		// チュートリアル
		MODE_GAME,			// ゲーム
		MODE_CLEAR,			// クリア
		MODE_OVER,			// オーバー
		MODE_RESULT,		// リザルト
		MODE_MAX,
	} MODE;

	CManager();														// デフォルトコンストラクタ
	~CManager();													// デストラクタ

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	static void SetMode(MODE mode);									// モードの設定処理
	static MODE GetMode(void);										// モードの取得処理

	static CRenderer *GetRenderer(void);							// レンダリングクラスの取得
	static CInputKeyboard *GetInputKeyboard(void);					// キーボードクラスの取得
	static CInputGamepad *GetInputGamepad(void);					// ゲームパッドクラスの取得
	static CFade *GetFade(void);									// フェードクラスの取得
	static CSound *GetSound(void);									// サウンドクラスの取得

private:
	// メンバ変数
	static CTitle *m_pTitle;										// タイトルのインスタンス
	static CTutorial *m_pTutorial;									// チュートリアルのインスタンス
	static CGame *m_pGame;											// ゲームのインスタンス
	static CClear *m_pClear;										// クリアのインスタンス
	static COver *m_pOver;											// オーバーのインスタンス
	static CResult *m_pResult;										// リザルトのインスタンス
	static MODE m_mode;												// モードのインスタンス
	static CSound *m_pSound;										// サウンドのインスタンス
	static CRenderer *m_pRenderer;									// レンダリングクラスのインスタンス
	static CInputKeyboard *m_pInputKeyboard;						// キーボードクラスのインスタンス
	static CInputGamepad *m_pInputGamepad;							// ゲームパッドクラスのインスタンス
	static CFade *m_pFade;											// フェードクラスのインスタンス
};

#endif // !_MANAGER_H_