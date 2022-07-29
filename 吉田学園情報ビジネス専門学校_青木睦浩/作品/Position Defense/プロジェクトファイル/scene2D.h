//=============================================================================
//
// 2Dポリゴン処理 [scene2D.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)  //頂点フォーマット

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;  // 頂点座標
	float       rhw;  // 1.0fで固定
	D3DCOLOR    col;  // 頂点カラー
	D3DXVECTOR2 tex;  // テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// 2Dポリゴンクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);																							// デフォルトコンストラクタ
	~CScene2D();																											// デストラクタ

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);																							// 初期化処理
	void Uninit(void);																										// 終了処理
	void Update(void);																										// 更新処理
	void Draw(void);																										// 描画処理

	static CScene2D *Create(D3DXVECTOR3 pos);																				// 生成処理

	void SetPosition(D3DXVECTOR3 pos);																						// 設定処理
	D3DXVECTOR3 GetPosition(void);																							// 取得処理
	void SetSize(float fWidth, float fHeight);																				// サイズの設定
	D3DXVECTOR2 GetSize(void);																								// サイズの取得
	void SetColor(D3DXCOLOR col);																							// 頂点カラーの設定
	void SetColor(int nColR, int nColG, int nColB, int nColA);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);																			// テクスチャを割り当てる
	void SetVertexTexture(int nPatternAnimU, float fAnimU, int nPatternAnimV, float fAnimV, float fTexU, float fTexV);		// テクスチャ座標の設定

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9      m_pTexture;																						// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;																						// 頂点バッファへのポインタ
	D3DXVECTOR3             m_pos;																							// ポリゴンの位置
	D3DXVECTOR2             m_size;																							// ポリゴンのサイズ
	float m_fTexU;																											// テクスチャのU座標
	float m_fTexV;																											// テクスチャのV座標
	D3DXCOLOR m_color;																										// 頂点カラー
	int m_nColorR;																											// カラー（赤）
	int m_nColorG;																											// カラー（緑）
	int m_nColorB;																											// カラー（青）
	int m_nColorA;																											// カラー（透明度）
};

#endif // !_SCENE2D_H_