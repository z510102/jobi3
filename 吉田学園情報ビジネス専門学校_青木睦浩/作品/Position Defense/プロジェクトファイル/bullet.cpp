//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "manager.h"
#include "game.h"
#include "straight.h"
#include "explosion.h"
#include "item.h"
#include "bullet_magazine.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリアする
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_type = TYPE_HG;
	m_fAngle = 0.0f;
	m_nDamage = 0;
	m_nLife = 0;
	m_bUse = true;
	m_nPassHG = 0;
	m_nPassAR = 0;
	m_nPassSG = 0;
	m_nPassSR = 0;
	m_nPassRL = 0;
	m_nType = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CBullet::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
							  "data/TEXTURE/bullet000.png",		// 読み込むファイル名
							  &m_pTexture);						// 読み込むメモリ

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CBullet::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 消去処理
//=============================================================================
void CBullet::Delete(void)
{
	// マガジンの弾数の情報を取得
	CBulletMagazine *pBulletMagazine;
	pBulletMagazine = CGame::GetBulletMagazine();

	// メンバ変数に情報を渡す
	m_nPassHG = pBulletMagazine->GetBulletMagazineHG();
	m_nPassAR = pBulletMagazine->GetBulletMagazineAR();
	m_nPassSG = pBulletMagazine->GetBulletMagazineSG();
	m_nPassSR = pBulletMagazine->GetBulletMagazineSR();
	m_nPassRL = pBulletMagazine->GetBulletMagazineRL();
	m_nType   = pBulletMagazine->GetBulletType();

	// 弾が-1でタイプが0(HG)だったら
	if (m_nPassHG <= -1 && m_nType == 0)
	{
		// 使用できなくする
		m_bUse = false;
	}

	// 弾が-1でタイプが1(AR)だったら
	else if (m_nPassAR <= -1 && m_nType == 1)
	{
		// 使用できなくする
		m_bUse = false;
	}

	// 弾が-1でタイプが2(SG)だったら
	else if (m_nPassSG <= -1 && m_nType == 2)
	{
		// 使用できなくする
		m_bUse = false;
	}

	// 弾が-1でタイプが3(SR)だったら
	else if (m_nPassSR <= -1 && m_nType == 3)
	{
		// 使用できなくする
		m_bUse = false;
	}

	// 弾が-1でタイプが4(RL)だったら
	else if (m_nPassRL <= -1 && m_nType == 4)
	{
		// 使用できなくする
		m_bUse = false;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fAngle, BULLET_TYPE bullettype)
{
	// ポインタ
	CBullet *pBullet = NULL;

	// メモリを確保
	pBullet = new CBullet(PRIORITY_BULLET);

	if (pBullet != NULL)
	{
		// それぞれの処理へ
		pBullet->Init(pos, move);
		pBullet->SetSize(6, 6);
		pBullet->BindTexture(m_pTexture);

		// メンバ変数へ情報を渡す
		pBullet->m_fAngle = fAngle;
		pBullet->m_type = bullettype;
	}

	// ポインタを戻り値へ返す
	return pBullet;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// 初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_BULLET);

	// 弾の初期化
	m_move = move;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	// 終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	// 更新処理へ
	CScene2D::Update();

	// キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// メンバ変数へ情報を渡す
	m_pos = pos;

	// 弾の移動（足し算をして左の変数へ渡す）
	m_pos.y += m_move.y;

	// 設定処理へ
	SetPosition(m_pos);

	// 消去処理へ
	Delete();

	// 使用していたら
	if (m_bUse == true)
	{
		//エフェクトを生成
		CStraight::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 8, m_pos.z), D3DXVECTOR2(8, 16), 255, 255, 0, 255, 0, 10, 0, 0, 10);
	}

	//画面外に行ったら消す　又は画面外に行っていて使用されていなかったら消す
	if (SCREEN_HEIGHT - SCREEN_HEIGHT >= m_pos.y && m_bUse == true || SCREEN_HEIGHT - SCREEN_HEIGHT >= m_pos.y && m_bUse == false)
	{
		// 終了処理へ
		Uninit();
	}

	//画面外に行っていなくて、使用されていなかったら
	else if (SCREEN_HEIGHT - SCREEN_HEIGHT <= m_pos.y && m_bUse == false)
	{
		//使用する
		m_bUse = true;
	}

	// 消去処理へ
	Delete();

	//発射位置より弾が移動していなくて使用されていなかったら消す
	if (SCREEN_HEIGHT - 100 <= m_pos.y && m_bUse == false)
	{
		// 終了処理へ
		Uninit();
	}

	//弾の位置判定
	if (MOVE_MAX <= m_pos.x || MOVE_MIN >= m_pos.x)
	{
		// 爆発を生成
		CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(20, 20), D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f), CExplosion::TYPE_SG);

		// 終了処理へ
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	// 描画処理へ
	CScene2D::Draw();
}