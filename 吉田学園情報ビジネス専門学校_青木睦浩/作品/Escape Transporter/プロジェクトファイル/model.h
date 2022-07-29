//=============================================================================
//
// モデルクラス [model.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//	プレイヤークラス
//*****************************************************************************
class CModel
{
public:
	CModel();	// コンストラクタ
	~CModel();					// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理
	void DrawObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);		// ステージセットのオブジェクト描画処理

	static CModel *Create(const char *pModelFileName);	// 生成処理

	void SetParent(CModel *pModel);						// 親モデルを設定
	D3DXMATRIX GetMtxWorld(void);						// ワールドマトリックスを取得
	void LoadXFile(const char *pModelFileName);			// Xファイル読み込み
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// パーツの位置を設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// パーツの位置を取得
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }			// パーツの向きを設定
	D3DXVECTOR3 GetRotation(void) { return m_pos; }			// パーツの向きを取得
	D3DXVECTOR3 GetMove(void);			// 移動量を取得
	D3DXVECTOR3 GetScale(void);


private:
	LPDIRECT3DTEXTURE9	m_pTexture[5];	// テクスチャのポインタ
	LPD3DXMESH					m_pMesh;		// メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER				m_pBuffMat;		// マテリアル（材質情報）へのポインタ
	DWORD						m_nNumMat;		// マトリックス数
	CModel						*m_pParent;		// 親モデルへのポインタ
	int							m_nIdxParent;	// 親モデルのインデックス
	D3DXMATRIX					m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3					m_pos;			// 位置
	D3DXVECTOR3					m_rot;			// 向き
	D3DXVECTOR3					m_scale;		// 大きさの倍率
	D3DXVECTOR3					m_size;			// 大きさ
	D3DXVECTOR3					m_move;			// 移動量
	D3DXVECTOR3					m_vtxMin;		// 頂点の最小値
	D3DXVECTOR3					m_vtxMax;		// 頂点の最大値
};
#endif //!_MODEL_H_