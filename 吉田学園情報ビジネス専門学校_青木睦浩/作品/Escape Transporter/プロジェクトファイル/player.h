//=============================================================================
//
// プレイヤークラス [player.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "motion.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define FILENAME_PLAYER "data/SCRIPT/PLAYER/motion.txt"
#define MAX_PLAYER_MODEL 20
#define MAX_PARTS 20
#define GRAVITYSPEED (0.5)
//=============================================================================
// 前方宣言
//=============================================================================
class CModel;
//*****************************************************************************
//	プレイヤークラス
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = PRIORITY_PLAYER);	// コンストラクタ
	~CPlayer();					// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// 生成処理

	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3	GetPos(void);		//
	//void SetDeath(bool bDeath) {m_bDeathFrag = bDeath;}
	//bool GetDeath(void) { return m_bDeathFrag; }
	void SetbHitBullet(bool bHitBullet) { m_bHitBullet = bHitBullet; }
	void LoadPlayerFile(const char *pFileName);

private:
	CModel								*m_pModel[MAX_PLAYER_MODEL];	// モデルへのポインタ
	D3DXMATRIX							m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3							m_pos;						// 位置
	D3DXVECTOR3							m_posOld;					// 前の位置
	D3DXVECTOR3							m_rot;						// 向き
	D3DXVECTOR3							m_scale;						// 大きさ
	D3DXVECTOR3							m_move;						// 移動量

	int									m_nNumModel;				// モデルの総数
	float								m_fGravitySpeed;			//重力加速度
	float								m_fBackPos;					//プレイヤーが着地する位置
	bool								m_bJump;
	bool								m_bLand;
	bool								m_bGoal;
	bool								m_bFade;	//フェード
	bool								m_bHitBullet;  //弾の当たり判定用
	bool								m_bDeathFrag;
	bool								m_bMeshField;

};
#endif //!_PLAYER_H_