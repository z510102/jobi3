//=============================================================================
//
// フラッシュグレネード所持数処理 [f_g_possession.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _F_G_POSSESSION_H_
#define _F_G_POSSESSION_H_

#include "scene2D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// フラッシュグレネード所持数クラス
//*****************************************************************************
class CF_G_Possession : public CScene
{
public:
	CF_G_Possession(int nPriority = 5);					// デフォルトコンストラクタ
	~CF_G_Possession();									// デストラクタ

	// メンバ関数
	static CF_G_Possession *Create(D3DXVECTOR3 pos);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);						// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	void SetF_G_Ppssession(int nG_Ppssession);			// フラッシュグレネード所持数の設定処理
	void SubF_G_Ppssession(int nValue);					// フラッシュグレネード所持数の減算処理
	int GetF_G_Ppssession(void);						// フラッシュグレネード所持数の取得処理
	void AddF_G_Ppssession(int nValue);					// フラッシュグレネード所持数の加算処理

private:
	// メンバ変数
	CNumber *m_pNumber;									// ナンバーのポインタ
	int m_nF_G_Possession;								// フラッシュグレネード所持数
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR2 m_size;									// サイズ
};

#endif // !_F_G_POSSESSION_H_