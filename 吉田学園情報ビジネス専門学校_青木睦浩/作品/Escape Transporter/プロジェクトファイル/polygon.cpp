//=============================================================================
//
// ポリゴンクラス [polygon.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "polygon.h"
#include "keyboard.h"
#include "game.h"
#include "texture.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = NULL;	// テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon::CPolygon()
{


	// メンバ変数のクリア
	memset(m_pos, 0, sizeof(D3DXVECTOR3));			// 位置
	memset(m_move, 0, sizeof(D3DXVECTOR3));			// 移動量
	memset(m_scale, 0, sizeof(D3DXVECTOR2));			// 大きさ
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	m_bUninit = false;								// 破棄

}
//=============================================================================
// デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPolygon::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CPolygon::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scall, int nType)
{
	CPolygon *pPlayer;
	pPlayer = new CPolygon;

	if (pPlayer != NULL)
	{
		pPlayer->m_pos = pos;
		pPlayer->m_scale = scall;
		pPlayer->Init();
		pPlayer->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		pPlayer->SetPosition(pos, scall);
		//pPlayer->BindTexture(m_pTexture);
	}

	return pPlayer;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CPolygon::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ".png", &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CPolygon::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
