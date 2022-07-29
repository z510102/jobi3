//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "player.h"
#include "input_keyboard.h"
#include "manager.h"
#include "input_gamepad.h"
#include "sound.h"
#include "grenade.h"
#include "flash_grenade.h"
#include "g_possession.h"
#include "f_g_possession.h"
#include "game.h"
#include "bullet_magazine.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
int CPlayer::m_nBullet = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	// 変数をクリア
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_nPatternAnimU = 0;
	m_nCounterAnim = 0;
	m_nBulletNumber_HG_magazine = 0;
	m_nBulletNumber_AR_magazine = 0;
	m_nBulletNumber_SG_magazine = 0;
	m_nBulletNumber_SR_magazine = 0;
	m_nBulletNumber_RL_magazine = 0;
	m_nRapidSpeedHG = 0;
	m_nRapidSpeedAR = 0;
	m_nRapidSpeedSG = 0;
	m_nRapidSpeedSR = 0;
	m_nRapidSpeedRL = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 2Dポリゴンのテクスチャ読み込み
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,								 // デバイスへのポインタ
							  "data/TEXTURE/player_animation.png",	 // 読み込むファイル名
							  &m_pTexture);							 // 読み込むメモリ

	return S_OK;
}

//=============================================================================
// 2Dポリゴンのテクスチャ破棄
//=============================================================================
void CPlayer::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//int CPlayer::GetBulletRemainig(void)
//{
//	return m_nRemaining;
//}

//=============================================================================
// 2Dポリゴンの生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	// ポインタ
	CPlayer *pPlayer;

	// メモリを確保
	pPlayer = new CPlayer (PRIORITY_CHARA);

	if (pPlayer != NULL)
	{
		// 処理へ
		pPlayer->Init(pos);
		pPlayer->SetSize(11, 22);
		pPlayer->BindTexture(m_pTexture);
		pPlayer->SetVertexTexture(4, 0.25f, 0, 0, 0.25f, 1.0f);
	}

	// ポインタを戻り値へ返す
	return pPlayer;
}

//=============================================================================
// 2Dポリゴンの初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	// Scene2Dの初期化処理へ
	CScene2D::Init(pos);

	// オブジェクトの種類を決める
	SetObjType(OBJTYPE_PLAYER);

	// 弾の種類をメンバへ渡す
	m_nBullet = CBullet::TYPE_HG;

	// マガジンの弾数を設定
	m_nBulletNumber_HG_magazine = 10;
	m_nBulletNumber_AR_magazine = 30;
	m_nBulletNumber_SG_magazine = 8;
	m_nBulletNumber_SR_magazine = 6;
	m_nBulletNumber_RL_magazine = 1;


	return S_OK;
}

//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// Scene2Dの終了処理へ
	CScene2D::Uninit();
}

//=============================================================================
// 2Dポリゴンの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// 位置を取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// メンバへ情報を渡す
	m_pos = pos;

	//=============================================================================
	// プレイヤーの移動と移動制限
	//=============================================================================

	//上下
	/*if (pInputKeyboard->GetKeyboardPress(DIK_W) == true && SCREEN_HEIGHT - SCREEN_HEIGHT <= pos.y - 30)
	{
		pos.y -= 3.0f;
	}

	if (pInputKeyboard->GetKeyboardPress(DIK_S) == true && pos.y + 30 <= SCREEN_HEIGHT)
	{
		pos.y += 3.0f;
	}*/

	// 左への移動と移動制限
	if (pInputKeyboard->GetKeyboardPress(DIK_A) == true && MOVE_MIN <= m_pos.x - 15 || pInputGamepad->GetLeftStick(CInputGamepad::STICK_TYPE_LEFT) && MOVE_MIN <= m_pos.x - 15)
	{
		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが10より大きくなった場合
		if (m_nCounterAnim > 10)
		{
			// 0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを減算
			m_nPatternAnimU--;

			// テクスチャ座標を設定
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}

		// 移動（posと数値を引いてposへ渡す）
		m_pos.x -= 2.2f;
	}

	// 右への移動と移動制限
	if (pInputKeyboard->GetKeyboardPress(DIK_D) == true && m_pos.x + 15 <= MOVE_MAX || pInputGamepad->GetLeftStick(CInputGamepad::STICK_TYPE_RIGHT) && m_pos.x + 15 <= MOVE_MAX)
	{
		// m_nCounterAnimを加算
		m_nCounterAnim++;

		// m_nCounterAnimが10より大きくなった場合
		if (m_nCounterAnim > 10)
		{
			// 0にする
			m_nCounterAnim = 0;

			// m_nPatternAnimUを加算
			m_nPatternAnimU++;

			// テクスチャ座標を設定
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}

		// 移動（posと数値を足してposへ渡す）
		m_pos.x += 2.2f;
	}

	// 総弾数を取得
	CBulletTotal *pBulletTotal;
	pBulletTotal = CGame::GetBulletTotal();

	//=============================================================================
	// 弾発射
	//=============================================================================

	// 発射間隔を加算
	m_nRapidSpeedHG++;
	m_nRapidSpeedAR++;
	m_nRapidSpeedSG++;
	m_nRapidSpeedSR++;
	m_nRapidSpeedRL++;

	// サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_nRapidSpeedHG >= 50)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//弾数を取得
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//ハンドガン
			if (m_nBullet == CBullet::TYPE_HG)
			{
				//弾の生成
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_HG);

				//弾数減算
				pBulletMagazine->SubBulletMagazine(1);

				int nHG = pBulletMagazine->GetBulletMagazineHG();

				if (nHG <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nHG >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedHG = 0;
		}
	}

	if (m_nRapidSpeedAR >= 12)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonPress(XINPUT_GAMEPAD_A))
		{
			//弾数を取得
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//アサルトライフル
			if (m_nBullet == CBullet::TYPE_AR)
			{
				//弾の生成
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_AR);

				//弾数減算
				pBulletMagazine->SubBulletMagazine(1);

				int nAR = pBulletMagazine->GetBulletMagazineAR();

				if (nAR <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nAR >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedAR = 0;
		}
	}

	if (m_nRapidSpeedSG >= 100)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//弾数を取得
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//ショットガン
		    if (m_nBullet == CBullet::TYPE_SG)
		    {
		    	//弾の生成
		    	CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SG);
		    	CBullet::Create(D3DXVECTOR3(m_pos.x + 30, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SG);
		    	CBullet::Create(D3DXVECTOR3(m_pos.x - 30, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SG);
		    
		    	//弾数減算
		    	pBulletMagazine->SubBulletMagazine(1);

				int nSG = pBulletMagazine->GetBulletMagazineSG();

				if (nSG <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nSG >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SG_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_SG_SHOT, 1.0f);
				}
		    }

			m_nRapidSpeedSG = 0;
		}
	}

	if (m_nRapidSpeedSR >= 170)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//弾数を取得
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//スナイパーライフル
			if (m_nBullet == CBullet::TYPE_SR)
			{
				//弾の生成
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SR);

				//弾数減算
				pBulletMagazine->SubBulletMagazine(1);

				int nSR = pBulletMagazine->GetBulletMagazineSR();

				if (nSR <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nSR >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SR_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_SR_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedSR = 0;
		}
	}

	if (m_nRapidSpeedRL >= 70)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//弾数を取得
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//ロケットランチャー
			if (m_nBullet == CBullet::TYPE_RL)
			{
				//弾の生成
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_RL);

				//弾数減算
				pBulletMagazine->SubBulletMagazine(1);

				int nRL = pBulletMagazine->GetBulletMagazineRL();

				if (nRL <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nRL >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_RL_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_RL_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedRL = 0;
		}
	}

	//=============================================================================
	// リロード
	//=============================================================================
#if 0
	if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true)
	{
		//トータルの数値を渡す
		m_nRemainingTotal = pBulletTotal->GetBulletTotal();

		if (m_nBullet == CBullet::TYPE_HG)
		{
			//弾数が９以下になったら
			if (m_nBulletNumber_HG_magazine <= 9)
			{
				//弾の最大数から現在の弾数を引く
				m_nRemaining = MAX_BULLET_HG - m_nBulletNumber_HG_magazine;

				//引いた数を総弾数から引く
				pBulletTotal->SubBulletTotal(m_nRemaining);

				m_nBulletNumber_HG_magazine += m_nRemaining;

				m_bRemaiing = true;

			}

			if (m_nRemainingTotal <= 9)
			{
				m_nRemaining = m_nRemainingTotal - m_nBulletNumber_HG_magazine;

				m_bRemaiing = false;
			}
			
		}
	
	}
#endif

	//=============================================================================
	// グレネード発射
	//=============================================================================
	if (pInputKeyboard->GetKeyboardTrigger(DIK_G) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_B))
	{
		//グレネードの生成
		CGrenade::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0));

		//グレネード所持数を取得
		CG_Possession *pG_Possession;
		pG_Possession = CGame::GetG_Possession();

		//グレネード所持数減算
		pG_Possession->SubG_Ppssession(1);

		int nG = pG_Possession->GetG_Ppssession();

		if (nG <= -1)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 0.0f);
		}

		if (nG >= 0)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 1.0f);
		}
	}

	//=============================================================================
	// フラッシュグレネード発射
	//=============================================================================
	if (pInputKeyboard->GetKeyboardTrigger(DIK_H) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_Y))
	{
		//フラッシュグレネードの生成
		CFlashGrenade::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0));

		//フラッシュグレネード所持数を取得
		CF_G_Possession *pF_G_Possession;
		pF_G_Possession = CGame::GetF_G_Possession();

		//フラッシュグレネード所持数減算
		pF_G_Possession->SubF_G_Ppssession(1);

		int nFG = pF_G_Possession->GetF_G_Ppssession();

		if (nFG <= -1)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 0.0f);
		}

		if (nFG >= 0)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 1.0f);
		}
	}

	//=============================================================================
	// 弾の種類変更
	//=============================================================================

	//十字キー右
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_RIGHT))
	{
		// 弾の種類を加算
		m_nBullet++;

		// 弾の種類がロケットランチャー+1以上になった場合
		if (m_nBullet >= CBullet::TYPE_RL + 1)
		{
			// 弾の種類をハンドガンにする
			m_nBullet = CBullet::TYPE_HG;
		}
	}

	//十字キー左
	if (pInputKeyboard->GetKeyboardTrigger(DIK_LEFT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_LEFT))
	{
		// 弾の種類を減算
		m_nBullet--;

		// 弾の種類がハンドガン-1以下になった場合
		if (m_nBullet <= CBullet::TYPE_HG - 1)
		{
			// 弾の種類をロケットランチャーにする
			m_nBullet = CBullet::TYPE_RL;
		}
	}

	// Scene2Dの更新処理へ
	CScene2D::Update();

	// 位置の設定処理へ
	SetPosition(m_pos);
}

//=============================================================================
// 2Dポリゴンの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// Scene2Dの描画処理へ
	CScene2D::Draw();
}

//=============================================================================
// 弾の種類の取得処理
//=============================================================================
int CPlayer::GetBulletType(void)
{
	// メンバを戻り値へ返す
	return m_nBullet;
}