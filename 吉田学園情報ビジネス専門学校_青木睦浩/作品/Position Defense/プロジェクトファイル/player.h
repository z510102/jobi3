//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"
#include "bullet.h"

//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer(int nPriority = 2);					// デフォルトコンストラクタ
	~CPlayer();									// デストラクタ

	// メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);				// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	static HRESULT Load(void);					// テクスチャ読み込み
	static void Unload(void);					// テクスチャの破棄
	static int GetBulletType(void);				// 弾の種類情報取得処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;							// 位置
	CBullet::BULLET_TYPE m_type;				// 弾の種類
	static int m_nBullet;						// 弾の種類の情報をもらう（数値）
	int m_nPatternAnimU;						// アニメーションパターン（U）
	int m_nCounterAnim;							// アニメーションカウンター
	int m_nBulletNumber_HG_magazine;			// ハンドガンのマガジンの弾数
	int m_nBulletNumber_AR_magazine;			// アサルトライフルのマガジンの弾数
	int m_nBulletNumber_SG_magazine;			// ショットガンのマガジンの弾数
	int m_nBulletNumber_SR_magazine;			// スナイパーライフルのマガジンの弾数
	int m_nBulletNumber_RL_magazine;			// ロケットランチャーのマガジンの弾数
	int m_nRapidSpeedHG;						// ハンドガンの弾の発射間隔
	int m_nRapidSpeedAR;						// アサルトライフルの弾の発射間隔
	int m_nRapidSpeedSG;						// ショットガンの弾の発射間隔
	int m_nRapidSpeedSR;						// スナイパーライフルの弾の発射間隔
	int m_nRapidSpeedRL;						// ロケットランチャーの弾の発射間隔
};

#endif // !_PLAYER_H_