//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "explosion.h"
#include "manager.h"
#include "enemy.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,								// デバイスへのポインタ
							  "data/TEXTURE/explosion000.png",		// 読み込むファイル名
							  &m_pTexture);							// 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 2Dポリゴンのテクスチャ破棄
//=============================================================================
void CExplosion::Unload(void)
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR color, EXPLOSION_TYPE type)
{
	// ポインタ
	CExplosion *pExplosion = NULL;

	// メモリを確保
	pExplosion = new CExplosion (PRIORITY_ANIM_EFFECT);

	if (pExplosion != NULL)
	{
		// それぞれの処理へ
		pExplosion->Init(pos);
		pExplosion->BindTexture(m_pTexture);

		// メンバへ情報を渡す
		pExplosion->m_color = color;
		pExplosion->m_size = size;
		pExplosion->m_Type = type;
	}

	// ポインタを戻り値へ返す
	return pExplosion;
}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_EXPLOSION);

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CExplosion::Update(void)
{
	// 位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// メンバへ情報を渡す
	m_pos = pos;

	// 頂点カラーを設定
	SetColor(m_color);

	// サイズを設定
	SetSize(m_size.x, m_size.y);

	// m_nCounterAnimを加算
	m_nCounterAnim++;

	if (m_nCounterAnim % 2)
	{
		// m_nPatternAnim加算
		m_nPatternAnim++;

		// Scene2Dの更新処理へ
		CScene2D::Update();

		// テクスチャ座標更新
		SetVertexTexture(m_nPatternAnim, 0.125f, 0, 0, 0.125f, 1.0f);

		// m_nPatternAnimが8になった場合
		if (m_nPatternAnim == 8)
		{
			// 終了処理へ
			Uninit();
			return;
		}
	}

	//敵と自陣の当たり判定
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// オブジェクトを取得
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			// 敵を取得
			CEnemy *pEnemy;
			pEnemy = CGame::GetEnemy();

			if (pScene != NULL)
			{
				// オブジェクトの種類を取得
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				// オブジェクトの種類がエネミーの場合
				if (objType == OBJTYPE_ENEMY)
				{
					// 爆発の種類がTYPE_Gの場合
					if (m_Type == TYPE_G)
					{
						//キャスト（型変換して2Dポリゴンクラスにある位置情報を取得）
						D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
						D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

						if (m_pos.x + 30 >= pos.x - size.x &&
							m_pos.x - 30 <  pos.x + size.x &&
							m_pos.y + 30 >= pos.y - size.y &&
							m_pos.y - 30 <  pos.y + size.y)
						{
							// 敵の終了処理へ
							pScene->Uninit();

							// 敵を倒したときの処理へ
							pEnemy->KnockDown();
						}
					}

					// 爆発の種類がTYPE_RLの場合
					if (m_Type == TYPE_RL)
					{
						//キャスト（型変換して2Dポリゴンクラスにある位置情報を取得）
						D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
						D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

						if (m_pos.x + 90 >= pos.x - size.x &&
							m_pos.x - 90 <  pos.x + size.x &&
							m_pos.y + 90 >= pos.y - size.y &&
							m_pos.y - 90 <  pos.y + size.y)
						{
							// 音を鳴らす
							pSound->PlaySound(pSound->SOUND_LABEL_BOMB);

							// 音量を調整
							pSound->SoundVolume(CSound::SOUND_LABEL_BOMB, 1.0f);

							// 敵の終了処理へ
							pScene->Uninit();

							// 敵を倒したときの処理へ
							pEnemy->KnockDown();
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// 2Dポリゴンの描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	// Scene2Dの描画処理へ
	CScene2D::Draw();
}