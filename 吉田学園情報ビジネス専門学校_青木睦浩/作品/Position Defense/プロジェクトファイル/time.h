//=============================================================================
//
// タイム処理 [time.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TIME (3)

//*****************************************************************************
// タイムクラス
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime(int nPriority = 5);					// デフォルトコンストラクタ
	~CTime();									// デストラクタ

	// メンバ関数
	static CTime *Create(D3DXVECTOR3 pos);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);				// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	void SetTime(int nScore);					// スコアの設定処理
	void AddTime(int nValue);					// スコアの加算処理
	int GetTime(void);							// スコアの取得処理

private:
	// メンバ変数
	CNumber *m_apNumber[MAX_TIME];				// スコアのポインタ配列
	int m_nTime;								// タイム
	int m_nCntTimer;							// タイマーのカウント
	D3DXVECTOR2 m_size;							// サイズ
	bool m_bUse;								// 使用
};

#endif // !_SCORE_H_