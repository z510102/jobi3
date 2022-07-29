//=============================================================================
//
// 総弾数処理 [bullet_total.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _bullet_total_H_
#define _bullet_total_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLET_TOTAL (2)

//*****************************************************************************
// 総弾数クラス
//*****************************************************************************
class CBulletTotal : public CScene
{
public:
	CBulletTotal(int nPriority = 5);											// デフォルトコンストラクタ
	~CBulletTotal();															// デストラクタ

	// メンバ関数
	static CBulletTotal *Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);												// 初期化処理
	void Uninit(void);															// 終了処理
	void Update(void);															// 更新処理
	void Draw(void);															// 描画処理

	void SetBulletTotal(int nBulletNumber);										// 総弾数の設定処理
	void SubBulletTotal(int nValue);											// 総弾数の減算処理
	int GetBulletTotal(void);													// 総弾数の取得処理
	void AddBulletTotalHG(int nValue);											// ハンドガンの総弾数の加算処理
	void AddBulletTotalAR(int nValue);											// アサルトライフルの総弾数の加算処理
	void AddBulletTotalSG(int nValue);											// ショットガンの総弾数の加算処理
	void AddBulletTotalSR(int nValue);											// スナイパーライフルの総弾数の加算処理
	void AddBulletTotalRL(int nValue);											// ロケットランチャーの総弾数の加算処理

private:
	// メンバ変数
	CNumber *m_apNumber[MAX_BULLET_TOTAL];										// スコアのポインタ配列
	int m_nBulletNumber_HG_total;												// ハンドガンの総弾数
	int m_nBulletNumber_AR_total;												// アサルトライフルの総弾数
	int m_nBulletNumber_SG_total;												// ショットガンの総弾数
	int m_nBulletNumber_SR_total;												// スナイパーライフルの総弾数
	int m_nBulletNumber_RL_total;												// ロケットランチャーの総弾数
	D3DXVECTOR2 m_size;															// サイズ
	CBullet::BULLET_TYPE m_type_total;											// 総弾数の種類
	int m_nTotalType;															// 総弾数の種類（数値）
	int m_nRemainingTotal;														// 残りの総弾数
	int m_nTotal;																// 現在の総弾数
	int m_nPass;																// マガジンの情報を渡す
};

#endif // !_BULLET_TOTAL_H_