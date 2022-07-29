//=============================================================================
//
// 2Dポリゴンクラス [scene2D.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "texture.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 頂点フォーマット
#define NUM_VERTEX		4											// 頂点数
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float		rhw; //1.0fで固定
	D3DCOLOR    col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
//	2Dポリゴンクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);			// コンストラクタ
	~CScene2D();		// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nType);		// 2Dポリゴンの生成

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; } // テクスチャの割り当て
	void SetVtxTexture(int nPatteernAnimU, float fAnimU, int nPatteernAnimV, float fAnimV, float fTexU, float fTexV);	// テクスチャ座標の設定
	D3DXVECTOR3 GetPosition(void);								// 位置を取得
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// 位置を設定
	void SetTexPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float fPos);		// 位置を設定
	D3DXVECTOR3 GetSize(void);									// サイズを取得
	void SetSize(D3DXVECTOR3 scale);							// サイズを設定
	void SetColor(int nColr, int nColg, int nColb, int nCola);	// 頂点カラーの設定
	void SetColor(D3DXCOLOR col);								// 頂点カラーの設定

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;					// 位置
	D3DXVECTOR3				m_scale;				// サイズ
	D3DXCOLOR				m_color;				// 頂点カラー
	int						m_nColor_r;				// 頂点カラーR
	int						m_nColor_g;				// 頂点カラーG
	int						m_nColor_b;				// 頂点カラーB
	int						m_nColor_a;				// 頂点カラーA

	int m_nNumTexture;
	//TEXTURE_TYPE m_type;
	int m_nType;
};
#endif //!_SCENE2D_H_