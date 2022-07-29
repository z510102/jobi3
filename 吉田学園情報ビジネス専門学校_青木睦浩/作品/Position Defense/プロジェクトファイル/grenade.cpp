//=============================================================================
//
// グレネード処理 [grenade.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "grenade.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "straight.h"
#include "g_possession.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CGrenade::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGrenade::CGrenade(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_bUse = true;
	m_nPassG = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGrenade::~CGrenade()
{

}

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CGrenade::Load(void)
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
void CGrenade::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// グレネードの使用無効処理
//=============================================================================
void CGrenade::NotUse(void)
{
	// グレネード所持数を取得
	CG_Possession *pG_Possession;
	pG_Possession = CGame::GetG_Possession();

	// メンバへ情報を渡す
	m_nPassG = pG_Possession->GetG_Ppssession();

	// グレネード所持数が-1以下になったら
	if (m_nPassG <= -1)
	{
		// 使用できなくする
		m_bUse = false;
	}
}

//=============================================================================
// 2Dポリゴンの生成
//=============================================================================
CGrenade *CGrenade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ポインタ
	CGrenade *pGrenade = NULL;

	// メモリを確保
	pGrenade = new CGrenade(PRIORITY_GRENADE);

	if (pGrenade != NULL)
	{
		// 処理へ
		pGrenade->Init(pos, move);
		pGrenade->SetSize(6, 6);
		pGrenade->BindTexture(m_pTexture);
	}

	// ポインタを戻り値へ返す
	return pGrenade;
}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CGrenade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_GRENADE);

	// メンバへ情報を渡す
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CGrenade::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CGrenade::Update(void)
{
	// グレネード所持数を取得
	CG_Possession *pG_Possession;
	pG_Possession = CGame::GetG_Possession();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	/*int nPassG = 0;
	nPassG = pG_Possession->GetG_Ppssession();*/

	// 位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// メンバへ情報を渡す
	m_pos = pos;

	// グレネードの移動
	m_pos.y += m_move.y;

	// Scene2Dの更新処理へ
	CScene2D::Update();

	// 位置の設定処理
	SetPosition(m_pos);

	// エフェクトを生成
	CStraight::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 8, m_pos.z), D3DXVECTOR2(8, 16), 0, 128, 0, 255, 0, 10, 0, 0, 10);

	// グレネード使用無効処理へ
	NotUse();

	// 位置が指定した座標の数値以上にあって使用されているか又は位置が指定した数値の数値以上にあって使用されていない場合
	if (SCREEN_HEIGHT - 400 >= m_pos.y && m_bUse == true || SCREEN_HEIGHT - 400 >= m_pos.y && m_bUse == false)
	{
		// 爆発を取得
		CExplosion *pExplosion;
		pExplosion = CGame::GetExplosion();

		// 音を鳴らす
		pSound->PlaySound(pSound->SOUND_LABEL_BOMB);

		// 音量を調整
		pSound->SoundVolume(CSound::SOUND_LABEL_BOMB, 1.0f);

		// 爆発の生成
		pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(100, 100), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CExplosion::TYPE_G);

		// 終了処理へ
		Uninit();
	}

	// 位置が指定した座標の数値以下で使用されていない場合
	else if (SCREEN_HEIGHT - 400 <= m_pos.y && m_bUse == false)
	{
		// 使用する
		m_bUse = true;
	}

	// グレネード使用無効処理へ
	NotUse();

	// 発射位置より弾が移動していなくて使用されていなかった場合
	if (SCREEN_HEIGHT - 100 <= m_pos.y && m_bUse == false)
	{
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

						CExplosion *pExplosion;
						pExplosion = CGame::GetExplosion();

						//スコア加算
						pScore->AddScore(10);

						//爆発の生成
						pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(88, 88), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

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
void CGrenade::Draw(void)
{
	// Scene2Dの描画処理へ
	CScene2D::Draw();
}