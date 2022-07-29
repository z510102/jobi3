//=============================================================================
//
// ライトクラス [light.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//	ライトクラス
//*****************************************************************************
class CLight
{
public:
	typedef enum
	{
		LIGHT_0 = 0,
		LIGHT_1,
		LIGHT_2,
		LIGHT_MAX
	} LIGHT_TYPE;

	CLight();			// コンストラクタ
	~CLight();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理

	static CLight *Create(void);	// 生成処理

private:
	D3DLIGHT9 m_light[3];	// ライト情報
	D3DXVECTOR3 m_vecDir;			// 設定用方向ベクトル
	D3DXVECTOR3 m_vecDirection;
	D3DLIGHTTYPE m_type;
	D3DXCOLOR m_color;

};
#endif //!_LIGHT_H_