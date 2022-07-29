//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// エネミークラス
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	// 敵の種類
	typedef enum
	{
		TYPE_0 = 0,		// タイプ0
		TYPE_1,			// タイプ1
		TYPE_2,			// タイプ2
		TYPE_3,			// タイプ3
		TYPE_4,			// タイプ4
		TYPE_5,			// タイプ5
		TYPE_6,			// タイプ6
		TYPE_MAX,
	} ENEMY_TYPE;

	CEnemy(int nPriority = 2);													// デフォルトコンストラクタ
	~CEnemy();																	// デストラクタ

	// メンバ関数
	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャの破棄
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY_TYPE type);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);							// 初期化処理
	void Uninit(void);															// 終了処理
	void Update(void);															// 更新処理
	void Draw(void);															// 描画処理

	void KnockDown(void);														// 敵を倒した時の処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];							// テクスチャへのポインタ
	D3DXVECTOR3 m_move;															// ポリゴンの移動量
	ENEMY_TYPE m_Type;															// 敵の種類
	D3DXVECTOR3 m_pos;															// ポリゴンの位置
	int m_nPatternAnimU;														// アニメーションパターン（U）
	int m_nCounterAnim;															// アニメーションカウンター
	int m_nStop;																// 移動停止
	bool m_bStop;																// 停止しているかどうか
};

#endif // !_ENEMY_H_