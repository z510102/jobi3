//=============================================================================
//
// UI処理 [UI.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// UIクラス
//*****************************************************************************
class CUI : public CScene2D
{
public:
	// UIの種類
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_HIGH_SCORE,			// ハイスコア
		TYPE_SCORE,					// スコア
		TYPE_TIME,					// タイム
		TYPE_LIFE,					// ライフ
		TYPE_GRENADE,				// グレネード
		TYPE_FLASH_GRENADE,			// フラッシュグレネード
		TYPE_WEAPON,				// 武器
		TYPE_TUTORIAL_ANIMATION,	// チュートリアルアニメーション
		TYPE_SWITCHING,				// ページ切り替え
		TYPE_TITLE,					// タイトル
		TYPE_RELOAD,				// リロード
		TYPE_INFINITE,				// ∞
		TYPE_RANKING_RANK,			// ランキング順位
		TYPE_GAME_CLEAR,			// ゲームクリア
		TYPE_GAME_OVER,				// ゲームオーバー
		TYPE_START_GAME,			// ゲームスタート
		TYPE_TUTORIAL,				// チュートリアル
		TYPE_RANKING,				// ランキング
		TYPE_MAX,
	} UI_TYPE;

	CUI(int nPriority = 4);													// デフォルトコンストラクタ
	~CUI();																	// デストラクタ

	// メンバ関数
	static HRESULT Load(void);                                              // テクスチャ読み込み
	static void Unload(void);                                               // テクスチャの破棄
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, UI_TYPE type);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);											// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];						// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;														// 位置
	D3DXVECTOR2 m_size;														// サイズ
	UI_TYPE m_Type;															// UIの種類
	int m_nPatternAnimU;													// アニメーションパターン（U）
	D3DXCOLOR m_Color;														// 色
	int m_nType;															// 種類（数値）
	int m_nReloadHG;														// ハンドガンのリロードするときの数値
	int m_nReloadAR;														// アサルトライフルのリロードするときの数値
	int m_nReloadSG;														// ショットガンのリロードするときの数値
	int m_nReloadSR;														// スナイパーライフルのリロードするときの数値
	int m_nReloadRL;														// ロケットランチャーのリロードするときの数値
	int m_nBulletType;														// 弾の種類
};

#endif // !_SCORE_H_