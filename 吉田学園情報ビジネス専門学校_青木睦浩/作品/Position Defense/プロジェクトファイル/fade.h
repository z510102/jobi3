//=============================================================================
//
// フェード処理 [fade.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

//*****************************************************************************
// フェードクラス
//*****************************************************************************
class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// フェードなし
		FADE_IN,		// フェードイン
		FADE_OUT,		// フェードアウト
		FADE_MAX,
	} FADE;

	CFade(int nPriority = 9);														// デフォルトコンストラクタ
	~CFade();																		// デストラクタ

	// メンバ関数
	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CManager::MODE mode);	// 生成処理

	HRESULT Init(D3DXVECTOR3 pos);													// 初期化処理
	void Uninit(void);																// 終了処理
	void Update(void);																// 更新処理
	void Draw(void);																// 描画処理

	void SetFade(CManager::MODE modenext);											// 設定処理
	FADE GetFade(void);																// 取得処理

private:
	// メンバ変数
	FADE m_Fade;																	// フェードの種類
	CManager::MODE m_Mode;															// 画面のモード
	D3DXCOLOR m_Color;																// カラー
};

#endif // !_FADE_H_