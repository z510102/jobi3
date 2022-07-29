//=============================================================================
//
// メニューの処理 [menu.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_UI (12)							// UIの最大数
#define UITEXT_X (250.0f)					// アレのX座標
#define UITEXT_WIDTH (250.0f)				// アレの幅
#define UITEXT_HEIGHT (50.0f)				// アレの高さ
#define UIICON_X (SCREEN_CENTER_X + 250.0f)	// アイコンのX座標
#define UIICON_Y (SCREEN_CENTER_Y - 50.0f)	// アイコンのY座標
#define UIICON_WIDTH (250.0f)				// アイコンの幅
#define UIICON_HEIGHT (250.0f)				// アイコンの高さ
#define UIINFO_Y (SCREEN_CENTER_Y + 250.0f)	// 説明文のX座標
#define UIINFO_WIDTH (350.0f)				// 説明文の幅
#define UIINFO_HEIGHT (80.0f)				// 説明文の高さ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;
class CUI;

//*****************************************************************************
// リザルトのクラス
//*****************************************************************************
class CMenu : public CScene
{
public:
	// 選択肢の列挙
	typedef enum
	{
		SELECT_PLAY = 0,		// 選択（プレイ）
		SELECT_TUTORIAL,		// 選択（チュートリアル）
		SELECT_RANKING,			// 選択（ランキング）
		SELECT_QUIT,			// 選択（戻る）
		SELECT_MAX
	} SELECTTYPE;

	CMenu();		// コンストラクタ
	~CMenu();		// デストラクタ

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	static CMenu *Create(void);	// 生成処理

private:
	bool		m_fade;			// フェードイン判定
	static CUI	*m_pUI[12];		// UIのインスタンス
	int			m_nCntSelect;	// どこを選んでるかのやつ

};

#endif // !_RESULT_H_
