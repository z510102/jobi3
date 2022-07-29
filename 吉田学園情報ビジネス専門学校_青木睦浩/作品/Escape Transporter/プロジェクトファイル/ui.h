//=============================================================================
//
// UIクラスの処理 [UI.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_SCORE (5)		// スコアのケタ数
#define MAX_TIME (3)		// 時間のケタ数
#define LIFE_WIDTH (150.0f)	// ライフバーの幅
#define LIFE_HEIGHT (40.0f)	// ライフバーの高さ
#define LIFE_MAX (260)		// ライフの上限
#define LIFE_DAMAGE (10.0f)	// ライフバーの減る量
#define STOP_PUSH (300.0f)	// PUSHSTARTが止まる位置
#define MOVE_PUSH (2.0f)	// PUSHSTARTの速度
#define MOVE_PICT (5.0f)	// 上の人の移動速度

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
//UIのクラス
//*****************************************************************************
class CUI : public CScene2D
{
public:

	CUI(int nPriority = PRIORITY_UI);	// コンストラクタ
	~CUI();					// デストラクタ

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void AddLife(int nValue);	// ライフ加算
	int GetLife(void);			// ライフ取得

								// 生成処理
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, CTexture::TEXTURETYPE type);

private:
	CNumber						*m_apTime[MAX_TIME];	// 数字のインスタンス（時間）
	CNumber						*m_apScore[MAX_SCORE];	// 数字のインスタンス（スコア）
	D3DXCOLOR					m_col;					// 色
	D3DXVECTOR3					m_size;					// 大きさ
	D3DXVECTOR3					m_Lifesize;				// ライフゲージの大きさ
	D3DXVECTOR3					m_pos;					// 位置
	float						m_fPosV;				// テクスチャ座標V
	float						m_fPosU;				// テクスチャ座標U
	CTexture::TEXTURETYPE		m_type;					// UIのタイプ
	bool						m_bBrinkFlag;			// PUSHSPACEの点滅判定
	bool						m_bBrinkFlag2;			// タイトルの字の薄さ判定
	bool						m_fade;					// フェードイン判定
	bool						m_bDisplay;				// ロゴが下まで降りたか判定					
	int							m_nLife;				// 残りライフ
	DWORD						m_dwCurrentTime;		// 経過時間
	DWORD						m_dwExecLastTime;		// 現在の時間
	CManager::MODE				m_mode;					// モード

};

#endif // !_TYTLEUI_H_