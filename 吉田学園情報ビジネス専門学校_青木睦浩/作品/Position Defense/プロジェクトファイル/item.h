//=============================================================================
//
// アイテム処理 [item.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// アイテムクラス
//*****************************************************************************
class CItem : public CScene2D
{
public:
	// アイテムの種類
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_AR,		//　アサルトライフルの弾
		TYPE_SG,		//　ショットガンの弾
		TYPE_SR,		//　スナイパーライフルの弾
		TYPE_RL,		//　ロケットランチャーの弾
		TYPE_G,			//　グレネード
		TYPE_FG,		//　フラッシュグレネード
		TYPE_TIME,		//　タイム
		TYPE_MAX,
	} ITEM_TYPE;

	CItem(int nPriority = 4);													// デフォルトコンストラクタ
	~CItem();																	// デストラクタ

	// メンバ関数
	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャの破棄
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ITEM_TYPE type);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);							// 初期化処理
	void Uninit(void);															// 終了処理
	void Update(void);															// 更新処理
	void Draw(void);															// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];							// テクスチャへのポインタ
	D3DXVECTOR3 m_move;															// ポリゴンの移動量
	ITEM_TYPE m_type;															// アイテムの種類
	D3DXVECTOR3 m_pos;															// ポリゴンの位置
};

#endif // !_ITEM_H_