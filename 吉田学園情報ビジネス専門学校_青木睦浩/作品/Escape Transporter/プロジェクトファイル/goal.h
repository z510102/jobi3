//=============================================================================
//
// ステージ管理クラス [goal.h]
// Author : 土居大輝
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_FILENAME "data/SCRIPT/model.txt"
#define MODELTYPE_MAX 5
#define MODEL_MAX 20
#define MAX_TEX 20
//=============================================================================
// 前方宣言
//=============================================================================
class CModel;
class CStageData;
//*****************************************************************************
//	ステージクラス
//*****************************************************************************
class CGoal : public CScene
{
public:

	CGoal(int nPriority = 0);	// コンストラクタ
	~CGoal();					// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CGoal *Create(void);		// 生成処理
	int GetNumModel(void) { return m_nNumModel; }
	CModel *GetModel(void);
	D3DXVECTOR3 GetPosition(void);

	bool Collision(CGoal *pGoal,D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);		// 通常の当たり判定

private:
	static CModel				*m_apModel[MODEL_MAX];
	D3DXMATRIX					m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3					m_pos;			// 位置
	D3DXVECTOR3					m_rot;			// 向き
	D3DXVECTOR3					m_move;			// 移動量
	CModel						*m_pModel;	// モデルへのポインタ
	D3DXCOLOR					m_color;		// 色
	bool						m_bUninit;		// 破棄
	int							m_nNumModel;
	int							m_nModelType;
	LPD3DXMESH					m_pMesh[20];	// メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER				m_pBuffMat[20];	// マテリアル（材質情報）へのポインタ
	DWORD						m_nNumMat[20];	// マトリックス数

	static CStageData			*m_pStageData;
};
#endif //!_STAGE_H_
