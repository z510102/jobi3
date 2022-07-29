//=============================================================================
//
// ゲームクラス [game.h]
// Author : 小笠原　彪我
// Author : 川村　優斗
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "scene2D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CPlayer;
class CScore;
class CTime;
class CStage;
class CGoal;
class CBullet;
class CMeshField;
//*****************************************************************************
//	ゲームクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();			// コンストラクタ
	~CGame();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	static CGame	*Create(void);	// 生成処理

	static CPlayer	*GetPlayer(void); 	// プレイヤー情報の取得
	static CScore	*GetScore(void);//スコア情報の取得
	static CTime	*GetTime(void);	//タイム情報の取得
	static CStage	*GetStage(void);	//タイム情報の取得
	static CGoal	*GetGoal(void);		//ゴール情報の取得
	static CBullet	*GetBullet(void);	//弾情報の取得
	static CMeshField *GetMeshField(void);

private:
	static CPlayer	*m_pPlayer;	// プレイヤーのインスタンス
	static CScore	*m_pScore;	// スコアのインスタンス
	static CTime	*m_pTime;	// タイムのインスタンス

	bool			m_bFade;	// フェード判定
	D3DCOLORVALUE m_colval;
	static CStage  *m_pStage;
	static CMeshField	*m_pMeshField;
	static CGoal	*m_pGoal;
	static CBullet	*m_pBullet;
};
#endif //!_GAME_H_