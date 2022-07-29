//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "enemy.h"
#include "manager.h"
#include "score.h"
#include "game.h"
#include "life.h"
#include "position.h"
#include "item.h"
#include "explosion.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_Type = TYPE_0;
	m_nPatternAnimU = 0;
	m_nCounterAnim = 0;
	m_nStop = 0;
	m_bStop = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/enemy_00.png",	    // 読み込むファイル名
							  &m_apTexture[TYPE_0]);            // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/enemy_01.png",	    // 読み込むファイル名
							  &m_apTexture[TYPE_1]);            // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/enemy_02.png",		// 読み込むファイル名
							  &m_apTexture[TYPE_2]);			// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/enemy_03.png",		// 読み込むファイル名
							  &m_apTexture[TYPE_3]);			// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/enemy_04.png",		// 読み込むファイル名
							  &m_apTexture[TYPE_4]);			// 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/enemy_05.png",		// 読み込むファイル名
							  &m_apTexture[TYPE_5]);            // 読み込むメモリ

	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/enemy_06.png",		// 読み込むファイル名
							  &m_apTexture[TYPE_6]);            // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 2Dポリゴンのテクスチャ破棄
//=============================================================================
void CEnemy::Unload(void)
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY_TYPE type)
{
	// ポインタ
	CEnemy *pEnemy;

	// メモリを確保
	pEnemy = new CEnemy (PRIORITY_CHARA);

	if (pEnemy != NULL)
	{
		// それぞれの処理へ
		pEnemy->Init(pos, move);
		pEnemy->SetSize(11, 22);
		pEnemy->BindTexture(m_apTexture[type]);
		pEnemy->SetVertexTexture(4, 0.25f, 0, 0, 0.25f, 1.0f);

		// メンバへ情報を渡す
		pEnemy->m_Type = type;
	}

	// ポインタを戻り値へ返す
	return pEnemy;
}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2Dの初期化へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_ENEMY);

	// メンバへ情報を渡す
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CEnemy::Update(void)
{
	// 位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// メンバへ情報を渡す
	m_pos = pos;

	// 種類がTYPE_0だったら
	if (m_Type == TYPE_0)
	{
		// posとmoveを足してposへ渡す
		m_pos.y += m_move.y;

		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが18よりも大きくなったら
		if (m_nCounterAnim > 18)
		{
			// m_nCounterAnimを0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算する
			m_nPatternAnimU++;

			// テクスチャ座標を設定する
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// 種類がTYPE_1だったら
	else if (m_Type == TYPE_1)
	{
		// posとmoveを足してposへ渡す
		m_pos.y += m_move.y;

		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが15よりも大きくなったら
		if (m_nCounterAnim > 15)
		{
			// m_nCounterAnimを0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算する
			m_nPatternAnimU++;

			// テクスチャ座標を設定する
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// 種類がTYPE_2だったら
	else if (m_Type == TYPE_2)
	{
		// posとmoveを足してposへ渡す
		m_pos.y += m_move.y;

		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが15よりも大きくなったら
		if (m_nCounterAnim > 12)
		{
			// m_nCounterAnimを0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算する
			m_nPatternAnimU++;

			// テクスチャ座標を設定する
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// 種類がTYPE_3だったら
	else if (m_Type == TYPE_3)
	{
		// posとmoveを足してposへ渡す
		m_pos.y += m_move.y;

		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが15よりも大きくなったら
		if (m_nCounterAnim > 9)
		{
			// m_nCounterAnimを0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算する
			m_nPatternAnimU++;

			// テクスチャ座標を設定する
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// 種類がTYPE_4だったら
	else if (m_Type == TYPE_4)
	{
		// posとmoveを足してposへ渡す
		m_pos.y += m_move.y;

		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが15よりも大きくなったら
		if (m_nCounterAnim > 6)
		{
			// m_nCounterAnimを0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算する
			m_nPatternAnimU++;

			// テクスチャ座標を設定する
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// 種類がTYPE_5だったら
	else if (m_Type == TYPE_5)
	{
		// posとmoveを足してposへ渡す
		m_pos.y += m_move.y;

		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが15よりも大きくなったら
		if (m_nCounterAnim > 3)
		{
			// m_nCounterAnimを0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算する
			m_nPatternAnimU++;

			// テクスチャ座標を設定する
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// 種類がTYPE_6だったら
	else if (m_Type == TYPE_6)
	{
		// posとmoveを足してposへ渡す
		m_pos.x += m_move.x;

		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが15よりも大きくなったら
		if (m_nCounterAnim > 9)
		{
			// m_nCounterAnimを0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算する
			m_nPatternAnimU++;

			// テクスチャ座標を設定する
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// m_bStopがtrueのとき
	if (m_bStop == true)
	{
		// moveを0にする（停止する）
		m_move.y = 0;

		// m_nStopを加算
		m_nStop++;

		// m_nStopが700以上だったら
		if (m_nStop >= 700)
		{
			// 種類がTYPE_0だったら
			if (m_Type == TYPE_0)
			{
				// 移動再開
				m_move.y = 0.2f;
			}

			// 種類がTYPE_1だったら
			else if (m_Type == TYPE_1)
			{
				// 移動再開
				m_move.y = 0.3f;
			}

			// 種類がTYPE_2だったら
			else if (m_Type == TYPE_2)
			{
				// 移動再開
				m_move.y = 0.4f;
			}

			// 種類がTYPE_3だったら
			else if (m_Type == TYPE_3)
			{
				// 移動再開
				m_move.y = 0.5f;
			}

			// 種類がTYPE_4だったら
			else if (m_Type == TYPE_4)
			{
				// 移動再開
				m_move.y = 0.6f;
			}

			// 種類がTYPE_5だったら
			else if (m_Type == TYPE_5)
			{
				// 移動再開
				m_move.y = 0.7f;
			}

			// m_nStopを0にする
			m_nStop = 0;
		}

		// m_nStopを0だったら
		if (m_nStop == 0)
		{
			// m_bStopをfalseにする
			m_bStop = false;
		}
	}

	// Scene2Dの更新処理へ
	CScene2D::Update();

	// 位置の設定処理へ
	SetPosition(m_pos);

	// ポジションを取得
	CPosition *pPosition;
	pPosition = CGame::GetPosition();

	// 爆発を取得
	CExplosion *pExplosion;
	pExplosion = CGame::GetExplosion();

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

				//キャスト（型変換して2Dポリゴンクラスにある位置情報を取得）
				D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
				D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

				// オブジェクトの種類がポジションだった場合
				if (objType == OBJTYPE_POSITION)
				{
					if (m_pos.x >= pos.x - size.x &&
						m_pos.x <  pos.x + size.x &&
						m_pos.y >= pos.y - size.y &&
						m_pos.y <  pos.y + size.y)
					{
						// ライフを取得
						CLife *pLife;
						pLife = CGame::GetLife();

						// ライフの減算
						pLife->SubLife(1);

						// 終了処理
						Uninit();

						// ポジションの頂点カラーの設定
						pPosition->SetColor(255, 0, 0, 255);
					}
				}

				// オブジェクトの種類が閃光だった場合
				else if (objType == OBJTYPE_FLASH)
				{
					if (m_pos.x >= pos.x - size.x &&
						m_pos.x <  pos.x + size.x &&
						m_pos.y >= pos.y - size.y &&
						m_pos.y <  pos.y + size.y)
					{
						m_bStop = true;
					}
				}

				// オブジェクトの種類が弾だった場合
				else if (objType == OBJTYPE_BULLET)
				{
					if (m_pos.x >= pos.x - size.x - 5 &&
						m_pos.x <  pos.x + size.x + 5 &&
						m_pos.y >= pos.y - size.y - 5 &&
						m_pos.y <  pos.y + size.y + 5)
					{
						// 弾の種類を取得
						int nBulletType = CPlayer::GetBulletType();

						// 弾の種類がショットガン以下（ハンドガン ～ ショットガン）又はロケットランチャーの場合
						if (nBulletType <= CBullet::TYPE_SG || nBulletType >= CBullet::TYPE_RL)
						{
							// 弾を終了
							pScene->Uninit();

							// 弾の種類がロケットランチャーの場合
							if (nBulletType == CBullet::TYPE_RL)
							{
								// 爆発を生成
								pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(200, 200), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CExplosion::TYPE_RL);
							}
						}

						// 敵を倒した処理へ
						KnockDown();

						// 爆発を生成
						pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CExplosion::TYPE_KNOCK);

						// 敵の種類がTYPE_5以下（TYPE_0 ～ TYPE_5）の場合
						if (m_Type <= TYPE_5)
						{
							// ランダムで数値を生成
							int nItemSpawn = (int)(rand() % 21 + 1);

#if 1
							// 数値によってアイテムを生成又は無し
							switch (nItemSpawn)
							{
							case 1:
								break;

							case 2:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_AR);
								break;

							case 3:
								break;

							case 4:
								break;

							case 5:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_SG);
								break;

							case 6:
								break;

							case 7:
								break;

							case 8:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_SR);
								break;

							case 9:
								break;

							case 10:
								break;

							case 11:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_RL);
								break;

							case 12:
								break;

							case 13:
								break;

							case 14:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_G);
								break;

							case 15:
								break;

							case 16:
								break;

							case 17:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_FG);
								break;

							case 18:
								break;

							case 19:
								break;

							case 20:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_TIME);
								break;

							case 21:
								break;
							}
#endif
						}

						// 終了処理へ
						Uninit();
					}
				}
			}
		}
	}

	// m_pos.xが指定した数値を下回る・超えた場合
	if (m_pos.x <= 25 || m_pos.x >= 890)
	{
		// 終了処理へ
		Uninit();
	}
}

//=============================================================================
// 2Dポリゴンの描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	// Scene2Dの描画処理へ
	CScene2D::Draw();
}

//=============================================================================
// 敵を倒した時の処理
//=============================================================================
void CEnemy::KnockDown(void)
{
	// スコアを取得
	CScore *pScore = CGame::GetScore();

	// 敵の種類がTYPE_0の場合
	if (m_Type == TYPE_0)
	{
		// スコアを加算
		pScore->AddScore(10);
	}

	// 敵の種類がTYPE_1の場合
	else if (m_Type == TYPE_1)
	{
		// スコアを加算
		pScore->AddScore(20);
	}

	// 敵の種類がTYPE_2の場合
	else if (m_Type == TYPE_2)
	{
		// スコアを加算
		pScore->AddScore(30);
	}

	// 敵の種類がTYPE_3の場合
	else if (m_Type == TYPE_3)
	{
		// スコアを加算
		pScore->AddScore(40);
	}

	// 敵の種類がTYPE_4の場合
	else if (m_Type == TYPE_4)
	{
		// スコアを加算
		pScore->AddScore(50);
	}

	// 敵の種類がTYPE_5の場合
	else if (m_Type == TYPE_5)
	{
		// スコアを加算
		pScore->AddScore(60);
	}

	// 敵の種類がTYPE_6の場合
	else if (m_Type == TYPE_6)
	{
		// スコアを加算
		pScore->AddScore(100);
	}
}