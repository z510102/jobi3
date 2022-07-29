//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "item.h"
#include "manager.h"
#include "bullet_total.h"
#include "time.h"
#include "game.h"
#include "g_possession.h"
#include "f_g_possession.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_type = TYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CItem::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/item_AR.png",			// 読み込むファイル名
							  &m_apTexture[TYPE_AR]);				// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/item_SG.png",			// 読み込むファイル名
							  &m_apTexture[TYPE_SG]);				// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/item_SR.png",			// 読み込むファイル名
							  &m_apTexture[TYPE_SR]);				// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/item_RL.png",			// 読み込むファイル名
							  &m_apTexture[TYPE_RL]);				// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/item_G.png",			// 読み込むファイル名
							  &m_apTexture[TYPE_G]);				// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/item_FG.png",			// 読み込むファイル名
							  &m_apTexture[TYPE_FG]);				// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/item_TIME.png",			// 読み込むファイル名
							  &m_apTexture[TYPE_TIME]);				// 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 2Dポリゴンのテクスチャ破棄
//=============================================================================
void CItem::Unload(void)
{
	// TYPE_MAXの数分
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 2Dポリゴンの生成処理
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ITEM_TYPE type)
{
	// ポインタ
	CItem *pItem;

	// メモリを確保
	pItem = new CItem (PRIORITY_ITEM);

	if (pItem != NULL)
	{
		// 処理へ
		pItem->Init(pos, move);
		pItem->SetSize(11, 11);
		pItem->BindTexture(m_apTexture[type]);

		// メンバへ情報を渡す
		pItem->m_type = type;
	}

	// ポインタを戻り値へ返す
	return pItem;
}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_ITEM);

	// 引数をメンバへ渡す
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CItem::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CItem::Update(void)
{
	// 位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// メンバへ情報を渡す
	m_pos = pos;

	// posとmoveを足してposへ渡す
	m_pos.y += m_move.y;

	// Scene2Dの更新処理へ
	CScene2D::Update();

	// 位置の設定処理へ
	SetPosition(m_pos);

	//アイテムとプレイヤーの当たり判定
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

				if (objType == OBJTYPE_PLAYER)
				{
					// キャスト（型変換して2Dポリゴンクラスにある位置情報を取得）
					D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
					D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

					if (m_pos.x >= pos.x - size.x &&
						m_pos.x <  pos.x + size.x &&
						m_pos.y >= pos.y - size.y &&
						m_pos.y <  pos.y + size.y)
					{
						// タイムを取得
						CTime *pTime;
						pTime = CGame::GetTime();

						// 総弾数を取得
						CBulletTotal *pBulletTotal;
						pBulletTotal = CGame::GetBulletTotal();

						// グレネード所持数を取得
						CG_Possession *pG_Possession;
						pG_Possession = CGame::GetG_Possession();

						// フラッシュグレネード所持数を取得
						CF_G_Possession *pF_G_Possession;
						pF_G_Possession = CGame::GetF_G_Possession();

						// アイテムの種類によって総弾数・時間を加算する
						switch (m_type)
						{
						case TYPE_AR:
							pBulletTotal->AddBulletTotalAR(30);
							break;

						case TYPE_SG:
							pBulletTotal->AddBulletTotalSG(8);
							break;

						case TYPE_SR:
							pBulletTotal->AddBulletTotalSR(6);
							break;

						case TYPE_RL:
							pBulletTotal->AddBulletTotalRL(1);
							break;

						case TYPE_G:
							pG_Possession->AddG_Ppssession(1);
							break;

						case TYPE_FG:
							pF_G_Possession->AddF_G_Ppssession(1);
							break;

						case TYPE_TIME:
							pTime->AddTime(30);
							break;

						default:
							break;
						}


						// 終了処理へ
						Uninit();
					}
				}
			}
		}
	}

	// 位置が座標の数値を超えたら
	if (m_pos.y >= SCREEN_HEIGHT)
	{
		// 終了処理へ
		Uninit();
	}
}

//=============================================================================
// 2Dポリゴンの描画処理
//=============================================================================
void CItem::Draw(void)
{
	// Scene2Dの描画処理へ
	CScene2D::Draw();
}