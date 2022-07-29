//=============================================================================
//
// ライフ処理 [life.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "scene2D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// ライフクラス
//*****************************************************************************
class CLife : public CScene
{
public:
	CLife(int nPriority = 0);					// デフォルトコンストラクタ
	~CLife();									// デストラクタ

	// メンバ関数
	static CLife *Create(D3DXVECTOR3 pos);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);				// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	void SetLife(int nLife);					// スコアの設定処理
	void AddLife(int nValue);					// スコアの加算処理
	void SubLife(int nValue);					// スコアの減算処理
	int GetLife(void);							// スコアの取得処理

private:
	// メンバ変数
	CNumber *m_pNumber;							// スコアのポインタ配列
	int m_nLife;								// ライフ
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR2 m_size;							// サイズ
	bool m_bUse;								// 使用
};

#endif // !_LIFE_H_