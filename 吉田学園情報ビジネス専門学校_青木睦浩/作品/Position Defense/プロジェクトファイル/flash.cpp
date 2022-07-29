//=============================================================================
//
// 閃光処理 [flash.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "flash.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CFlash::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CFlash::CFlash(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFlash::~CFlash()
{

}

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CFlash::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
							  "data/TEXTURE/flash.png",		// 読み込むファイル名
							  &m_pTexture);					// 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 2Dポリゴンのテクスチャ破棄
//=============================================================================
void CFlash::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 2Dポリゴンの生成
//=============================================================================
CFlash *CFlash::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ポインタ
	CFlash *pFlash = NULL;

	// メモリを確保
	pFlash = new CFlash(PRIORITY_ANIM_EFFECT);

	if (pFlash != NULL)
	{
		// それぞれの処理へへ
		pFlash->Init(pos);
		pFlash->BindTexture(m_pTexture);

		// メンバへ情報を渡す
		pFlash->m_size = size;
	}

	// ポインタを戻り値へ返す
	return pFlash;
}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CFlash::Init(D3DXVECTOR3 pos)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_FLASH);

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CFlash::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CFlash::Update(void)
{
	//位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// メンバへ情報を渡す
	m_pos = pos;

	// サイズを設定する
	SetSize(m_size.x, m_size.y);

	// m_nCounterAnimを加算
	m_nCounterAnim++;

	if (m_nCounterAnim % 2)
	{
		// m_nPatternAnimを加算
		m_nPatternAnim++;

		// 頂点情報更新
		CScene2D::Update();

		// テクスチャ座標設定
		SetVertexTexture(m_nPatternAnim, 0.125f, 0, 0, 0.125f, 1.0f);

		// m_nPatternAnimが8になった場合
		if (m_nPatternAnim == 8)
		{
			// 終了処理へ
			Uninit();
			return;
		}
	}

#if 0
	//敵と自陣の当たり判定
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == OBJTYPE_ENEMY)
				{
					//キャスト（型変換して2Dポリゴンクラスにある位置情報を取得）
					D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
					D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

					if (m_pos.x + 50 >= pos.x - size.x &&
						m_pos.x - 50 <  pos.x + size.x &&
						m_pos.y + 50 >= pos.y - size.y &&
						m_pos.y - 50 <  pos.y + size.y)
					{
						CEnemy *pEnemy;
						pEnemy = CGame::GetEnemy();

						pEnemy->Stop();
					}
				}
			}
		}
	}
#endif
}

//=============================================================================
// 2Dポリゴンの描画処理
//=============================================================================
void CFlash::Draw(void)
{
	// Scene2Dの描画処理へ
	CScene2D::Draw();
}