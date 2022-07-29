//=============================================================================
//
// リザルト画面の処理 [result.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_BG (24)							 // 背景のテクスチャ番号
#define NOWSCORE_X (100.0f)						 // 今のスコアのX座標
#define NOWSCORE_Y (200.0f)						 // 今のスコアのY座標
#define NOWSCORE_WIDTH (45.0f)					 // 今のスコアの幅
#define NOWSCORE_HEIGHT (47.0f)					 // 今のスコアの高さ
#define NOWTIME_X (SCREEN_CENTER_X - 100.0f)	 // 今の時間のX座標
#define NOWTIME_Y (250.0f)						 // 今の時間のY座標
#define NOWTIME_WIDTH (35.0f)					 // 今の時間の幅
#define NOWTIME_HEIGHT (47.0f)					 // 今の時間の高さ
#define RANK_X (SCREEN_CENTER_X)				 // ランクのX座標
#define RANK_Y (600.0f)							 // ランクのY座標
#define RANK_WIDTH (100.0f)						 // ランクの幅
#define RANK_HEIGHT (100.0f)					 // ランクの高さ
#define PLUS_X (SCREEN_CENTER_X + 65.0f)		 // プラス表示のX座標
#define PLUS_Y (550.0f)							 // プラス表示のY座標
#define PLUS_WIDTH (30.0f)						 // プラス表示の幅
#define PLUS_HEIGHT (30.0f)						 // プラス表示の高さ
#define FILE_TIME ("data/SAVEDATA/newtime.txt")	 // タイム読み込み用ファイル
#define FILE_SCORE ("data/SAVEDATA/newscore.txt")// スコア読み込み用ファイル

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;
class CTime;
class CScore;

//*****************************************************************************
// リザルトのクラス
//*****************************************************************************
class CResult : public CScene
{
public:
	CResult();			// コンストラクタ
	~CResult();		// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	static CResult *Create(void);	// 生成処理

private:
	bool			m_fade;		 // フェードイン判定
	bool			m_bflag1;	 // フェードイン判定
	bool			m_bflag2;	 // フェードイン判定
	bool			m_bflag3;	 // フェードイン判定
	static CScore	*m_pScore;	 // スコアのインスタンス
	static CTime	*m_pTime;	 // タイムのインスタンス
	CScore			*m_pNowScore;// 今のスコア
	int				m_nNewdata;
	int				m_nTime;
	DWORD		m_dwCurrentTime;	  // 経過時間
	DWORD		m_dwExecLastTime;	  // 現在の時間

};

#endif // !_RESULT_H_
