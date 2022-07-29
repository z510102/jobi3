//=============================================================================
//
// マガジン処理 [bullet_magazine.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _bullet_magazine_H_
#define _bullet_magazine_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLET_MAGAZINE (2)
#define MAX_BULLET_HG_MAGAZINE (10)
#define MAX_BULLET_AR_MAGAZINE (30)
#define MAX_BULLET_SG_MAGAZINE (8)
#define MAX_BULLET_SR_MAGAZINE (6)
#define MAX_BULLET_RL_MAGAZINE (1)

//*****************************************************************************
// マガジンクラス
//*****************************************************************************
class CBulletMagazine : public CScene
{
public:
	CBulletMagazine(int nPriority = 5);												// デフォルトコンストラクタ
	~CBulletMagazine();																// デストラクタ

	// メンバ関数
	static CBulletMagazine *Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type);		// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);													// 初期化処理
	void Uninit(void);																// 終了処理
	void Update(void);																// 更新処理
	void Draw(void);																// 描画処理

	void SubBulletMagazine(int nValue);												// 弾数の減算処理
	int GetBulletMagazineHG(void);													// ハンドガン弾数の取得処理
	int GetBulletMagazineAR(void);													// アサルトライフル弾数の取得処理
	int GetBulletMagazineSG(void);													// ショットガン弾数の取得処理
	int GetBulletMagazineSR(void);													// スナイパーライフル弾数の取得処理
	int GetBulletMagazineRL(void);													// ロケットランチャー弾数の取得処理
	int GetBulletType(void);														// 弾の種類の取得処理

private:
	// メンバ変数
	CNumber *m_apNumber[MAX_BULLET_MAGAZINE];										// スコアのポインタ配列
	int m_nBulletNumber_HG_magazine;												// ハンドガンのマガジンの弾数
	int m_nBulletNumber_AR_magazine;												// アサルトライフルのマガジンの弾数
	int m_nBulletNumber_SG_magazine;												// ショットガンのマガジンの弾数
	int m_nBulletNumber_SR_magazine;												// スナイパーライフルのマガジンの弾数
	int m_nBulletNumber_RL_magazine;												// ロケットランチャーのマガジンの弾数
	D3DXVECTOR2 m_size;																// サイズ
	CBullet::BULLET_TYPE m_type_magajine;											// マガジンの種類
	int m_nMagazineType;															// マガジンの種類（数値）
	int m_nMagazine;																// 弾の最大数から現在の弾数を引いた弾の数
	int m_nTotal_Magazine;															// 総弾数の情報をもらう
};

#endif // !_BULLET_MAGAZINE_H_