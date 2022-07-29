//=============================================================================
//
// グレネード所持数処理 [g_possession.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _G_POSSESSION_H_
#define _G_POSSESSION_H_

#include "scene2D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// グレネード所持数クラス
//*****************************************************************************
class CG_Possession : public CScene
{
public:
	CG_Possession(int nPriority = 5);					// デフォルトコンストラクタ
	~CG_Possession();									// デストラクタ

	// メンバ関数
	static CG_Possession *Create(D3DXVECTOR3 pos);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);						// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	void SetG_Ppssession(int nG_Ppssession);			// グレネード所持数の設定処理
	void SubG_Ppssession(int nValue);					// グレネード所持数の減算処理
	int GetG_Ppssession(void);							// グレネード所持数の取得処理
	void AddG_Ppssession(int nValue);					// グレネード所持数の加算処理

private:
	// メンバ変数
	CNumber *m_pNumber;									// グレネード所持数のポインタ
	int m_nG_Possession;								// 所持数
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR2 m_size;									// サイズ
};

#endif // !_G_POSSESSION_H_