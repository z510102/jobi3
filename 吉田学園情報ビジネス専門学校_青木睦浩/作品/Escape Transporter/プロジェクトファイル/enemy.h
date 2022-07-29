//=============================================================================
//
// 敵クラス [enemy.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "motion.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define FILENAME_HUMAN "data/SCRIPT/ENEMY/motion_human.txt"
#define FILENAME_LEG "data/SCRIPT/ENEMY/motion_leg.txt"
#define MAX_ENEMY_MODEL 20
#define MAX_ENEMY_PARTS 20
//=============================================================================
// 前方宣言
//=============================================================================
class CModel;
//*****************************************************************************
//	敵クラス
//*****************************************************************************
class CEnemy : public CScene
{
public:

	CEnemy(int nPriority = PRIORITY_ENEMY);	// コンストラクタ
	~CEnemy();					// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// 生成処理

	void LoadXFile(const char *pFileName);		// 読み込むファイルを設定
	void Collision(void);						// 通常の当たり判定
	void VectorCollision(void);					// ベクトルの当たり判定

private:
	D3DXMATRIX							m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3							m_pos;						// 位置
	D3DXVECTOR3							m_posOld;					// 前の位置
	D3DXVECTOR3							m_rot;						// 向き
	D3DXVECTOR3							m_move;						// 移動量
	CModel								*m_pModel[MAX_ENEMY_MODEL];	// モデルへのポインタ
	LPD3DXMESH							m_pMesh[MAX_ENEMY_PARTS];	// メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER						m_pBuffMa[MAX_ENEMY_PARTS];	// マテリアル（材質情報）へのポインタ
	DWORD								m_nNumMat[MAX_ENEMY_PARTS];	// マトリックス数
	D3DXVECTOR3							m_vtxMin[8];				// モデルの最小値
	D3DXVECTOR3							m_vtxMax[8];				// モデルの最大値
	int									m_nNumModel;				// モデルの総数

};
#endif //!_ENEMY_H_