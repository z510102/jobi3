//=============================================================================
//
// フラッシュグレネード処理 [flash_grenade.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _FLASH_GRENADE_H_
#define _FLASH_GRENADE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// フラッシュグレネードクラス
//*****************************************************************************
class CFlashGrenade : public CScene2D
{
public:
	CFlashGrenade(int nPriority = 3);									// デフォルトコンストラクタ
	~CFlashGrenade();													// デストラクタ

	// メンバ関数
	static CFlashGrenade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);					// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理

	static HRESULT Load(void);											// テクスチャ読み込み
	static void Unload(void);											// テクスチャの破棄

private:
	// メンバ変数
	D3DXVECTOR3 m_move;													// ポリゴンの移動量
	D3DXVECTOR3 m_pos;													// ポリゴンの位置
	static LPDIRECT3DTEXTURE9 m_pTexture;								// テクスチャへのポインタ
	bool m_bUse;														// 使用
};

#endif // !_FLASH_GRENADE_H_