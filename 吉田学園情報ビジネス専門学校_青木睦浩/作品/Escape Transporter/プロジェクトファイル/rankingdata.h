//=============================================================================
//
// ランキングクラス [rankingdata.h]
// Author : 川村　優斗
//
//=============================================================================

#ifndef _RANKINGDATA_H_
#define _RANKINGDATA_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_RANKING (6)
#define RANKING_TEXT ("data/SAVEDATA/ranking.txt")
#define SCORE_TEXT ("data/SAVEDATA/newtime.txt")
#define NUMBER_WIDTH (42.0f)
#define NUMBER_HEIGHT (47.0f)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CTime;

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CRankingData : public CScene
{
public:
	CRankingData(int nPriority = 4);// コンストラクタ
	~CRankingData();				// デストラクタ

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	static CRankingData *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bFlag);	// 生成処理

private:
	int	m_nTime[MAX_RANKING];				// スコア格納
	D3DXVECTOR3 m_size;						// 大きさ
	D3DXVECTOR3 m_pos;						// 位置
	static CTime	*m_pTime[MAX_RANKING];	// スコアのインスタンス
	CTime *m_pNowTime;					// 現在のスコア
	bool m_bFlag;							// メニューかゲームから飛んだかの判定

};

#endif //!_RANKINGDATA_H_