//=============================================================================
//
// フラッシュグレネード処理 [flash_grenade.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "flash_grenade.h"
#include "manager.h"
#include "game.h"
#include "flash.h"
#include "straight.h"
#include "f_g_possession.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CFlashGrenade::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CFlashGrenade::CFlashGrenade(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_bUse = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFlashGrenade::~CFlashGrenade()
{

}

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CFlashGrenade::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						 // デバイスへのポインタ
							  "data/TEXTURE/bullet000.png",	 // 読み込むファイル名
							  &m_pTexture);					 // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 2Dポリゴンのテクスチャ破棄
//=============================================================================
void CFlashGrenade::Unload(void)
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
CFlashGrenade *CFlashGrenade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ポインタ
	CFlashGrenade *pFlashGrenade = NULL;

	// メモリを確保
	pFlashGrenade = new CFlashGrenade(PRIORITY_GRENADE);

	if (pFlashGrenade != NULL)
	{
		// 処理へ
		pFlashGrenade->Init(pos, move);
		pFlashGrenade->SetSize(6, 6);
		pFlashGrenade->BindTexture(m_pTexture);
	}

	// ポインタを戻り値へ返す
	return pFlashGrenade;
}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CFlashGrenade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_FLASH_GRENADE);

	// メンバへ情報を渡す
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CFlashGrenade::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CFlashGrenade::Update(void)
{
	// フラッシュグレネード所持数を取得
	CF_G_Possession *pF_G_Possession;
	pF_G_Possession = CGame::GetF_G_Possession();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// フラッシュグレネード所持数の情報を渡す
	int nPassF_G = 0;
	nPassF_G = pF_G_Possession->GetF_G_Ppssession();

	// 位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// メンバへ情報を渡す
	m_pos = pos;

	// フラッシュグレネードの移動
	m_pos.y += m_move.y;

	// Scene2Dの更新処理へ
	CScene2D::Update();

	// 位置の設定処理へ
	SetPosition(m_pos);

	// エフェクトを生成
	CStraight::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 8, m_pos.z), D3DXVECTOR2(8, 16), 24, 235, 249, 255, 0, 10, 0, 0, 10);

	// フラッシュグレネード所持数が-1以下になった場合
	if (nPassF_G <= -1)
	{
		// 使用できなくする
		m_bUse = false;

		// 終了処理へ
		Uninit();
	}

	// 弾の位置が指定した位置を超えたとき
	if (SCREEN_HEIGHT - 400 >= m_pos.y)
	{
		// 閃光を取得
		CFlash *pFlash;
		pFlash = CGame::GetFlash();

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_FLASH_BOMB);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_FLASH_BOMB, 1.0f);

		// 爆発の生成
		pFlash->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(100, 100));

		// 終了処理へ
		Uninit();
	}

#if 0
	//弾と敵の当たり判定
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
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

					if (m_pos.x >= pos.x - size.x / 2 &&
						m_pos.x <  pos.x + size.x / 2 &&
						m_pos.y >= pos.y - size.y / 2 &&
						m_pos.y <  pos.y + size.y / 2)
					{
						//スコアを取得
						CScore *pScore;
						pScore = CGame::GetScore();

						//スコア加算
						pScore->AddScore(10);

						//爆発の生成
						/*CExplosion::Create(pos);*/

						//敵の破棄
						pScene->Uninit();

						//弾の破棄
						Uninit();
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
void CFlashGrenade::Draw(void)
{
	// Scene2Dの描画へ
	CScene2D::Draw();
}