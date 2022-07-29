//=============================================================================
//
// フェード処理 [fade.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//	フェードクラス
//*****************************************************************************
class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// フェードなし
		FADE_IN,		// フェードイン
		FADE_OUT,		// フェードアウト
		FADE_DIM,
		FADE_MAX
	} FADE;

	CFade(int nPriority = PRIORITY_FADE);	// コンストラクタ
	~CFade();							// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE mode);		// 生成処理
	FADE GetFade(void);						// フェード取得
	void SetFade(CManager::MODE modenext);	// フェードの設定
	
private:
	CManager::MODE			m_mode;			// モードの種類
	D3DXCOLOR				m_color;		// フェードの透明度
	FADE					m_fade;			// フェードの種類
};
#endif