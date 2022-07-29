//=============================================================================
//
// マネージャ [manager.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CXinputPad;
class CSound;

class CTitle;
class CMenu;
class CTutorial;
class CSelect;
class CGame;
class CResult;
class CRanking;
class CRanking2;
class CFade;
class CLight;
class CCamera;
class CTexture;
class CModel;
//*****************************************************************************
//	マネージャクラス
//*****************************************************************************
class CManager
{
public:
	// モードの種類
	typedef enum
	{
		MODE_TITLE = 0,	// タイトル
		MODE_MENU,		// 選択
		MODE_TUTORIAL,	// チュートリアル
		MODE_SELECT,	// 武器セレクト
		MODE_GAME,		// ゲーム
		MODE_RESULT,	//リザルト
		MODE_RANKING,
		MODE_RANKING2,
		MODE_MAX		// 最大数
	} MODE;

	CManager();										// コンストラクタ
	~CManager();									// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	static CRenderer		*GetRenderer(void);		// レンダラーを取得
	static CInputKeyboard	*GetInputKeyboard(void);// キーボードを取得
	static CXinputPad		*GetXinputPad(void);	// ゲームパッド取得
	static CSound			*GetSound(void);		// サウンドを取得
	static CTitle			*GetTitle(void); 		// タイトルのインスタンス
	static CMenu			*GetMenu(void); 		// メニューのインスタンス
	static CTutorial		*GetTutorial(void);		// チュートリアルのインスタンス
	static CSelect			*GetSelect(void);		// セレクトのインスタンス
	static CGame			*GetGame(void);			// ゲームのインスタンス
	static CResult			*GetResult(void);		// リザルトのインスタンス
	static CRanking			*GetRanking(void);		// ランキングのインスタンス
	static CRanking2		*GetRanking2(void);		// ランキングのインスタンス
	static CFade			*GetFade(void);			// フェードを取得
	static CLight			*GetLight(void); 		// ライトを取得
	static CCamera			*GetCamera(void);		// カメラを取得
	static CTexture			*GetTexture(void);		// テクスチャを取得
	static CModel			*GetModel(void); 		// モデルを取得


	static void SetMode(MODE mode);	// モードの設定
	static MODE GetMode(void);		// モードを取得


private:
	static CRenderer		*m_pRenderer;			// レンダラーのインスタンス
	static CInputKeyboard	*m_pInputKeyboard;		// キーボードのインスタンス
	static CXinputPad		*m_pXinputPad;			// ゲームパッドのインスタンス
	static CSound			*m_pSound;				// サウンドのインスタンス
	static CTitle			*m_pTitle;				// タイトルのインスタンス
	static CMenu			*m_pMenu;				// メニューのインスタンス
	static CTutorial		*m_pTutorial;			// チュートリアルのインスタンス
	static CSelect			*m_pSelect;				// セレクトのインスタンス
	static CGame			*m_pGame;				// ゲームのインスタンス
	static CResult			*m_pResult;				// リザルトのインスタンス
	static CRanking			*m_pRanking;			// ランキングのインスタンス
	static CRanking2			*m_pRanking2;			// ランキング2のインスタンス
	static CFade			*m_pFade;				// フェードのインスタンス
	static CLight			*m_pLight;				// ライトのインスタンス
	static CCamera			*m_pCamera;				// カメラのインスタンス
	static CTexture			*m_pTexture;			// テクスチャのインスタンス
	static CModel			*m_pModel;			// モデルのインスタンス

	static MODE				m_mode;					// 画面のモード

};
#endif //!_MANAGER_H_