//
// メッシュフィールドクラス [meshfield.h]
// Author : 青木　睦浩
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//=============================================================================
// マクロ定義
//=============================================================================

//*****************************************************************************
//	メッシュフィールドクラス
//*****************************************************************************
class CMeshField : public CScene3D
{
public:
	CMeshField(int nPriority = PRIORITY_MODEL);																				// コンストラクタ
	~CMeshField();																											// デストラクタ

	HRESULT Init(void);																										// 初期化処理
	void Uninit(void);																										// 終了処理
	void Update(void);																										// 更新処理
	void Draw(void);																										// 描画処理

	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nType);												// 生成処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }												// テクスチャの割り当て

	D3DXVECTOR3 GetPosition(void);																							// 位置の取得
	D3DXVECTOR3 GetScale(void);																								// 大きさの取得
	bool Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);	// 当たり判定

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;																					// メッシュフィールドの頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff;																					// メッシュフィールドのインデックスへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;																					// 共有テクスチャのポインタ
	D3DXMATRIX					m_mtxWorld;																					//	ワールドマトリックス
	D3DXVECTOR3					m_move;																						// 移動量
	D3DXVECTOR3					m_pos;																						// 位置
	D3DXVECTOR3					m_rot;																						// 向き
	D3DXVECTOR3					m_scale;																					// 大きさ
	D3DXCOLOR					m_color;																					// 色
	bool						m_bUninit;																					// 破棄
	int m_nType;
};
#endif //!_MESHFIELD_H_