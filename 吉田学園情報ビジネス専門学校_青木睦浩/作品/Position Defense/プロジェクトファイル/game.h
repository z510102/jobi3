//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "bg.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CSound;
class CEnemy;
class CScore;
class CEffect;
class CPosition;
class CHighScore;
class CUI;
class CTime;
class CLife;
class CG_Possession;
class CF_G_Possession;
class CBulletMagazine;
class CBulletTotal;
class CExplosion;
class CItem;
class CFlash;

//*****************************************************************************
// ゲームクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();											// デフォルトコンストラクタ
	~CGame();											// デストラクタ

	// メンバ関数
	static CGame *Create(void);							// 生成処理
	void Clear(void);									// ゲームクリア処理
	void Over(void);									// ゲームオーバー処理

	HRESULT Init(D3DXVECTOR3 pos);						// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CEnemy *GetEnemy(void);						// エネミーの取得処理
	static CScore *GetScore(void);						// スコアの取得処理
	static CPosition *GetPosition(void);				// ポジションの取得処理
	static CUI *GetUI(void);							// UIの取得処理
	static CTime *GetTime(void);						// タイムの取得処理
	static CLife *GetLife(void);						// ライフの取得処理
	static CG_Possession *GetG_Possession(void);		// グレネード所持数の取得処理
	static CF_G_Possession *GetF_G_Possession(void);	// フラッシュグレネード所持数の取得処理
	static CBulletMagazine *GetBulletMagazine(void);	// マガジンの弾数の取得処理
	static CBulletTotal *GetBulletTotal(void);			// 総弾数の取得処理
	static CExplosion *GetExplosion(void);				// 爆発の取得処理
	static CFlash *GetFlash(void);						// 閃光の取得処理

private:
	HRESULT Load(void);									// テクスチャ読み込み
	void Unload(void);									// テクスチャ破棄

	// メンバ変数
	static CBg *m_pBg;									// 背景へのポインタ
	static CPlayer *m_pPlayer;							// プレイヤーへのポインタ
	static CEnemy *m_pEnemy;							// エネミーへのポインタ
	static CScore *m_pScore;							// スコアへのポインタ
	static CPosition *m_pPosition;						// ポジションへのポインタ
	static CHighScore *m_pHighScore;					// ハイスコアへのポインタ
	static CUI *m_pUI;									// UIへのポインタ
	static CTime *m_pTime;								// タイムへのポインタ
	static CLife *m_pLife;								// ライフへのポインタ
	static CG_Possession *m_pG_Possession;				// グレネード所持数へのポインタ
	static CF_G_Possession *m_pF_G_Possession;			// フラッシュグレネード所持数へのポインタ
	static CBulletMagazine *m_pBulletMagazine;			// マガジンの弾数へのポインタ
	static CBulletTotal *m_pBulletTotal;				// 総弾数へのポインタ
	static CExplosion *m_pExplosion;					// 爆発へのポインタ
	static CItem *m_pItem;								// アイテムへのポインタ
	static CFlash *m_pFlash;							// 閃光へのポインタ
	int m_nSpawn;										// 敵のスポーン値
	int m_nSpawn2;										// 敵のスポーン値２
	int m_nSpawn3;										// 敵のスポーン値３
	int m_nSpawn4;										// 敵のスポーン値４
	int m_nSpawn5;										// 敵のスポーン値５
	int m_nSpawn6;										// 敵のスポーン値６
	int m_nSpawn7;										// 敵のスポーン値７
	int m_nCntSpawn;									// 敵7の出現間隔を調整する
	int m_nCntLife;										// ライフ増加カウント
};

#endif // !_GAME_H_