//=============================================================================
//
// オブジェクトクラス [scene.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE		(40)		// テクスチャの最大数

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	オブジェクトクラス
//*****************************************************************************
class CScene
{
public:
	// オブジェクトの種類
	typedef enum
	{
		OBJTYPE_NONE = 0,	// なし
		OBJTYPE_BG,			// 背景
		OBJTYPE_MODEL,
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_ENEMY,		// 敵
		OBJTYPE_BOSS,
		OBJTYPE_ITEM,		// アイテム
		OBJTYPE_BULLET,		// 弾
		OBJTYPE_SPECIAL,
		OBJTYPE_ENEMYBULLET,// 敵弾
		OBJTYPE_EXPLOSION,	// 爆発
		OBJTYPE_EFFECT,		// エフェクト
		OBJTYPE_UI,			// 残機
		OBJTYPE_FADE,		// フェード
		OBJTYPE_MAX			// 最大数
	} OBJTYPE;

	// 描画の優先順位
	typedef enum
	{
		PRIORITY_BG = 0,		// 背景
		PRIORITY_MODEL,
		PRIORITY_ENEMY,			// 敵
		PRIORITY_BOSS,			// ボス
		PRIORITY_PLAYER,		// プレイヤー
		PRIORITY_ITEM,			// アイテム
		PRIORITY_BGBOARD,		// サイドボード
		PRIORITY_BULLET,		// 弾
		PRIORITY_EFFECT,		// エフェクト
		PRIORITY_EXPLOSION,		// 爆発
		PRIORITY_UI,			// UI
		PRIORITY_FADE,			// フェード
		PRIORITY_MAX			// 最大数
	} PRIORITY_TYPE;

	CScene(int nPriority = OBJTYPE_NONE);				// コンストラクタ
	virtual ~CScene();						// デストラクタ

	virtual HRESULT Init(void) = 0;				// 初期化処理
	virtual void Uninit(void) = 0;				// 終了処理
	virtual void Update(void) = 0;				// 更新処理
	virtual void Draw(void) = 0;				// 描画処理

	static void ReleaseAll(void);				// 全てのオブジェクトの破棄
	static void UpdateAll(void);				// 全てのオブジェクトの更新処理
	static void DrawAll(void);					// 全てのオブジェクトの描画処理

	void SetObjType(OBJTYPE objType);			// オブジェクトの種類を設定
	OBJTYPE GetobjType(void);					// オブジェクトの種類を取得
	static CScene *GetScene(int nPriority);		// 列挙型と一致するオブジェクトを取得
	static CScene *GetNextScene(CScene *pScene) { return pScene->m_pNext; };

protected:
	void Release(void);							// オブジェクトの破棄

private:
	OBJTYPE			m_objType;					// オブジェクトの種類

												// リスト構造
	static CScene *m_apTop[PRIORITY_MAX];		// 先頭オブジェクトのポインタ
	static CScene *m_apCur[PRIORITY_MAX];		// 現在(一番後ろ)のオブジェクトのポインタ
	CScene *m_pPrev;			// 前のオブジェクトへのポインタ
	CScene *m_pNext;			// 次のオブジェクトへのポインタ
	bool m_bDeath;				// 死亡フラグ
	int m_nPriority;

};
#endif //!_SCENE_H_