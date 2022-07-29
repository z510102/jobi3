//=============================================================================
//
// スコア処理 [score.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCORE (5)

//*****************************************************************************
// スコアクラス
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = 5);									// デフォルトコンストラクタ
	~CScore();													// デストラクタ

	// メンバ関数
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);								// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void SetScore(int nScore);									// スコアの設定処理
	void AddScore(int nValue);									// スコアの加算処理
	int GetScore(void);											// スコアの取得処理

private:
	// メンバ変数
	CNumber *m_apNumber[MAX_SCORE];								// スコアのポインタ配列
	int m_nScore;												// スコア
	D3DXVECTOR2 m_size;											// サイズ
};

#endif // !_SCORE_H_