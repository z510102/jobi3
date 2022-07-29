//=============================================================================
//
// 背景のクラス [bg.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_X (SCREEN_CENTER_X)		// 背景のX座標
#define BG_Y (SCREEN_CENTER_Y)		// 背景のY座標
#define BG_WIDTH (SCREEN_WIDTH / 2)	// 背景の幅
#define BG_HEIGHT (SCREEN_HEIGHT / 2)// 背景の高さ

//*****************************************************************************
// 背景のクラスの定義
//*****************************************************************************
class CBg : public CScene2D
{
public:
	CBg(int nPriority = PRIORITY_BG);	// コンストラクタ
	~CBg();					// デストラクタ

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	static HRESULT	Load(void);		//弾のテクスチャロード
	static void		Unload(void);	//弾のテクスチャアンロード

	//背景の生成
	static CBg	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

private:
	D3DXVECTOR3					m_pos;			//移動量
	float						m_fPosV;		//テクスチャ座標
	int							m_nPriority;	//優先順位
	int							m_nType;		//種類

};

#endif // !_BG_H_
