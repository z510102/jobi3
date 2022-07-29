//=============================================================================
//
// タイトルクラスの処理 [title.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PUSH_X (SCREEN_CENTER_X)			// PUSHSTARTのX座標
#define PUSH_Y (200.0f + SCREEN_CENTER_Y)	// PUSHSTARTのY座標
#define PUSH_WIDTH (350.0f)					// PUSHSTARTの幅
#define PUSH_HEIGHT (100.0f)				// PUSHSTARTの高さ
#define TITLE_X (SCREEN_CENTER_X)			// ロゴのX座標
#define TITLE_Y (100.0f)					// ロゴのY座標
#define TITLE_WIDTH (550.0f)				// ロゴの幅
#define TITLE_HEIGHT (80.0f)				// ロゴの高さ
#define HUMAN_X (0.0f)						// 上のアレのX座標
#define HUMAN_Y (50.0f)						// 上のアレのY座標
#define HUMAN_WIDTH (60.0f)					// 上のアレの幅
#define HUMAN_HEIGHT (50.0f)				// 上のアレの高さ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// タイトルのクラス
//*****************************************************************************
class CTitle : public CScene
{
public:
	CTitle();	// コンストラクタ
	~CTitle();	// デストラクタ

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	static CTitle *Create(void);// 生成処理

private:
	bool m_fade;			//フェードイン判定
	DWORD m_dwCurrentTime;	//起動時の時間
	DWORD m_dwExecLastTime;	//経過時間

};

#endif // !_TITLE_H_
