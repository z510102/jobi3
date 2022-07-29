#ifndef _BULLET_H_
#define _BULLET_H_
#include "billboard.h"

#define BULLET_SCALE_X 50.0f
#define BULLET_SCALE_Y 50.0f
#define BULLET_SCALE_Z 50.0f

class CModel;

class CBullet : public CBillboard
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_WHITE,
		TYPE_RED,
		TYPE_BLUE,
		TYPE_YELLOW,
		TYPE_MAX
	} TYPE_SMOKECOLOR;

	CBullet(int nPriority = CScene::PRIORITY_BULLET);
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life, int nType);		//エフェクトの生成
	bool Collision(CBullet *pBullet, D3DXVECTOR3 *pPos);		// 通常の当たり判定


private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;  //移動
	D3DXVECTOR3 m_scale;  //移動
	D3DXVECTOR3	m_rot;  // 向き
	CModel	*m_pModel;
	int m_nType;
	int m_nLife;		//寿命
	D3DCOLORVALUE m_colval;
	bool m_bUninit;		//削除フラグ
	TYPE_SMOKECOLOR m_smokecol;
	int m_nFrameSmoke = 0;  //煙のフレーム
};
#endif
