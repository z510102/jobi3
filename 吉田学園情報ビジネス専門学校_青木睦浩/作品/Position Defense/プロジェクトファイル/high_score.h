//=============================================================================
//
// ハイスコア処理 [high_score.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _HIGH_SCORE_H_
#define _HIGH_SCORE_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_HIGH_SCORE (5)

//*****************************************************************************
// ハイスコアクラス
//*****************************************************************************
class CHighScore : public CScene
{
public:
	CHighScore(int nPriority = 5);					// デフォルトコンストラクタ
	~CHighScore();									// デストラクタ

	// メンバ関数
	static CHighScore *Create(D3DXVECTOR3 pos);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);					// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理

	void SetScore(int nScore);						// スコアの設定処理
	void AddScore(int nValue);						// スコアの加算処理
	int GetScore(void);								// スコアの取得処理

private:
	// メンバ変数
	CNumber *m_apNumber[MAX_HIGH_SCORE];			// スコアのポインタ配列
	int m_nScore;									// スコア
	D3DXVECTOR2 m_size;								// サイズ
	int m_nHighScore;								// ハイスコア
};

#endif // !_HIGH_SCORE_H_