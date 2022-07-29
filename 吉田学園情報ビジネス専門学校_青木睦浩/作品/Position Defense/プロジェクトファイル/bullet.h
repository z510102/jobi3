//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// バレットクラス
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	// 弾の種類
	typedef enum
	{
		TYPE_HG = 0,	// ハンドガン
		TYPE_AR,		// アサルトライフル
		TYPE_SG,		// ショットガン
		TYPE_SR,		// スナイパーライフル
		TYPE_RL,		// ロケットランチャー
		TYPE_MAX,
	} BULLET_TYPE;

	CBullet(int nPriority = 3);																			// デフォルトコンストラクタ
	~CBullet();																							// デストラクタ

	// メンバ関数
	static HRESULT Load(void);																			// テクスチャ読み込み
	static void Unload(void);																			// テクスチャの破棄
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fAngle, BULLET_TYPE bullettype);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);													// 初期化処理
	void Uninit(void);																					// 終了処理
	void Update(void);																					// 更新処理
	void Draw(void);																					// 描画処理

	void Delete(void);																					// 消去処理

private:
	// メンバ変数
	D3DXVECTOR3 m_move;																					// ポリゴンの移動量
	D3DXVECTOR3 m_pos;																					// ポリゴンの位置
	static LPDIRECT3DTEXTURE9 m_pTexture;																// テクスチャへのポインタ
	BULLET_TYPE m_type;																					// 弾の種類
	float m_fAngle;																						// 角度
	int m_nDamage;																						// ダメージ
	int m_nLife;																						// ライフ
	bool m_bUse;																						// 使用
	int m_nPassHG;																						// ハンドガン
	int m_nPassAR;																						// アサルトライフル
	int m_nPassSG;																						// ショットガン
	int m_nPassSR;																						// スナイパーライフル
	int m_nPassRL;																						// ロケットランチャー
	int m_nType;																						// 弾の種類（数値）
};

#endif // !_SCENE2D_H_