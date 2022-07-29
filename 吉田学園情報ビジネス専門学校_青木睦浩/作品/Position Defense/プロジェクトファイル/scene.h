//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCENE (1280)
#define PRIORITY_MAX (15)
#define MOVE_MAX (800)
#define MOVE_MIN (115)

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CScene
{
public:
	// オブジェクトの種類
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,			// プレイヤー
		OBJTYPE_ENEMY,			// 敵
		OBJTYPE_BULLET,			// 弾
		OBJTYPE_GRENADE,		// 手榴弾
		OBJTYPE_FLASH_GRENADE,	// 閃光手榴弾
		OBJTYPE_EXPLOSION,		// 爆発
		OBJTYPE_LIFE,			// 体力
		OBJTYPE_EFFECT,			// エフェクト
		OBJTYPE_POSITION,		// ポジション
		OBJTYPE_UI,				// UI
		OBJTYPE_BG,				// 背景
		OBJTYPE_ITEM,			// アイテム
		OBJTYPE_FLASH,			// 閃光
		OBJTYPE_MAX
	} OBJTYPE;

	// プライオリティの種類
	typedef enum
	{
		PRIORITY_BG = 0,
		PRIORITY_POSITION,
		PRIORITY_CHARA,
		PRIORITY_ANIM_EFFECT,
		PRIORITY_SCREEN,
		PRIORITY_UI,
		PRIORITY_NUMBER,
		PRIORITY_BULLET,
		PRIORITY_GRENADE,
		PRIORITY_ITEM,
		PRIORITY_EFFECT,
		PRIORITY_FADE,
		PRIORITY,
	} PRIORITY_TYPE;

	CScene(int nPriority = 3);								// デフォルトコンストラクタ
	virtual ~CScene();										// デストラクタ

	// メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;				// 初期化処理
	virtual void Uninit(void) = 0;							// 終了処理
	virtual void Update(void) = 0;							// 更新処理
	virtual void Draw(void) = 0;							// 描画処理

	static void ReleaseAll(void);							// 全てのオブジェクトの破棄
	static void UpdateAll(void);							// 全てのオブジェクトの更新処理
	static void DrawAll(void);								// 全てのオブジェクトの描画処理

	void SetObjType(OBJTYPE objType);						// オブジェクトの設定処理
	OBJTYPE GetObjType(void);								// オブジェクトの種類の取得処理
	static CScene *GetScene(int nPriority, int nIndex);		// オブジェクトの取得処理

protected:
	void Release(void);										// オブジェクトの破棄

private:
	// メンバ変数
	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];		// オブジェクトのポインタ配列
	static int m_nNumAll;									// オブジェクトの総数
	int m_nID;												// 格納先の番号
	OBJTYPE m_objType;										// オブジェクトの種類
	int m_nPriority;										// 優先順位の番号
};

#endif // !_SCENE_H_