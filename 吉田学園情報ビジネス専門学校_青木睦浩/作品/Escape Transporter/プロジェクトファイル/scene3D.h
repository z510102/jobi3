//=============================================================================
//
// 3Dポリゴンクラス [scene3D.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 3D 頂点フォーマット
#define NUM_VERTEX		4					// 頂点数
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; // 頂点座標
	D3DXVECTOR3 nor; // 法線ベクトル
	D3DCOLOR    col; // 頂点カラー
	D3DXVECTOR2 tex; // テクスチャ座標
} VERTEX_3D;

//*****************************************************************************
//	3Dポリゴンクラス
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 3);		// コンストラクタ
	~CScene3D();		// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nType);		// 2Dポリゴンの生成

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; } // テクスチャの割り当て
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// 位置を設定
	D3DXVECTOR3 GetPosition(void);								// 位置を取得

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;				// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3				m_pos;					// 位置
	D3DXVECTOR3				m_rot;					// 向き
	D3DXVECTOR3				m_scale;				// サイズ
	int m_nType;

};
#endif //!_SCENE3D_H_