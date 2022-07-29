//=============================================================================
//
// 2Dポリゴンクラス [billboard.h]
// Author : 土居　大輝
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

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

//*****************************************************************************
//	2Dポリゴンクラス
//*****************************************************************************
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = PRIORITY_EFFECT);			// コンストラクタ
	~CBillboard();		// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType);		// 2Dポリゴンの生成
																									//LPDIRECT3DTEXTURE9 SetTextureType(int nType);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	D3DXVECTOR3 GetPosition(void);
	void SetColVal(D3DCOLORVALUE colval);


	//void SetPosition(D3DXVECTOR3 pos,D3DXVECTOR3 scale);
	//D3DXVECTOR3 GetPosition(void);
	//void SetCol(D3DCOLORVALUE colval);


private:
	// 共有テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;					// 位置
	D3DXVECTOR3				m_scale;				// サイズ
	D3DXMATRIX				m_mtxWorld;
	D3DXCOLOR				m_color;				// 頂点カラー
	D3DCOLORVALUE		    m_colval;
	int m_nType;
};
#endif //!_SCENE2D_H_
