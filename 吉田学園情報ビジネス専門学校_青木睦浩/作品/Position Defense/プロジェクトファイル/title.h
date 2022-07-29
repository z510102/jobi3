//=============================================================================
//
// タイトル処理 [title.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// タイトルクラス
//*****************************************************************************
class CTitle : public CScene
{
public:

	//選択項目の種類
	typedef enum
	{
		TYPE_START_GAME = 0,	// スタートゲーム
		TYPE_TUTORIAL,			// チュートリアル
		TYPE_RANKING,			// ランキング
		TYPE_MAX
	} SELECT_TYPE;

	CTitle();									// デフォルトコンストラクタ
	~CTitle();									// デストラクタ

	// メンバ関数
	static HRESULT Load(void);					// テクスチャ読み込み
	static void Unload(void);					// テクスチャの破棄
	static CTitle *Create(void);				// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);				// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	static int GetSelect(void);					// 選択項目の取得処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	CScene2D *m_pScene2D;						// Scene2Dへのポインタ
	D3DXVECTOR3 m_Pos;							// 位置
	static int m_nSelect;						// 選択項目
};

#endif // !_TITLE_H_