//=============================================================================
//
// ポリゴンクラス [polygon.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================

//*****************************************************************************
//	プレイヤークラス
//*****************************************************************************
class CPolygon : public CScene2D
{
public:
	CPolygon();			// コンストラクタ
	~CPolygon();			// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);		// 生成処理

	static HRESULT Load(void);				// テクスチャの読み込み
	static void Unload(void);				// テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// 共有テクスチャのポインタ
	D3DXVECTOR3					m_pos;			// 位置
	D3DXVECTOR3					m_rot;			// 向き
	D3DXVECTOR3					m_scale;		// 大きさ
	D3DXVECTOR3					m_move;			// 移動量
	D3DXCOLOR					m_color;		// 色
	bool						m_bUninit;		// 破棄
};
#endif //!_POLYGON_H_