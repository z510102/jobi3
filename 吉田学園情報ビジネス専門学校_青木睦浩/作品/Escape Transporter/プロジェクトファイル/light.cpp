//=============================================================================
//
// ライトクラス [light.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "light.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{
	// メンバ変数のクリア
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

}
//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLight::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

#if 1
	// ライトをクリアする
	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの方向を設定
		// ライトの拡散光の設定
		m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		D3DXVec3Normalize(&m_vecDir, &m_vecDir);		// 正規化する
		m_light[0].Direction = m_vecDir;

		// ライトの拡散光の設定
		m_vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
		D3DXVec3Normalize(&m_vecDir, &m_vecDir);		// 正規化する
		m_light[1].Direction = m_vecDir;

		// ライトの拡散光の設定
		m_vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
		D3DXVec3Normalize(&m_vecDir, &m_vecDir);		// 正規化する
		m_light[2].Direction = m_vecDir;

		// ライトを設定
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
#endif
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CLight::Uninit(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void CLight::Update(void)
{
}
//=============================================================================
// 生成処理
//=============================================================================
CLight *CLight::Create(void)
{
	CLight *pLight;
	pLight = new CLight;

	if (pLight != NULL)
	{
		pLight->Init();
		//pLight->m_type = type;
		//pLight->m_vecDirection = vecDir;
		//pLight->m_color = color;
	}

	return pLight;
}
