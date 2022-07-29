//=============================================================================
//
// 弾数処理 [bullet_number.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "bullet_magazine.h"
#include "input_keyboard.h"
#include "input_gamepad.h"
#include "manager.h"
#include "player.h"
#include "bullet_total.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// 生成処理
//=============================================================================
CBulletMagazine *CBulletMagazine::Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type)
{
	// ポインタ
	CBulletMagazine *pNumber;

	// メモリを確保
	pNumber = new CBulletMagazine (PRIORITY_NUMBER);

	if (pNumber != NULL)
	{
		// メンバ変数へ情報を渡す
		pNumber->m_size = D3DXVECTOR2(30, 40);
		pNumber->m_nMagazineType = type;

		// 初期化処理へ
		pNumber->Init(pos);
	}

	// ポインタを戻り値へ返す
	return pNumber;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletMagazine::CBulletMagazine(int nPriority) : CScene(nPriority)
{
	// 変数をクリアする
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nBulletNumber_HG_magazine = 0;
	m_nBulletNumber_AR_magazine = 0;
	m_nBulletNumber_SG_magazine = 0;
	m_nBulletNumber_SR_magazine = 0;
	m_nBulletNumber_RL_magazine = 0;
	m_nMagazineType = 0;
	m_nMagazine = 0;
	m_nTotal_Magazine = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletMagazine::~CBulletMagazine()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBulletMagazine::Init(D3DXVECTOR3 pos)
{
	// 弾の種類の情報を渡す
	m_nMagazineType = CPlayer::GetBulletType();

	// MAX_BULLET_MAGAZINEの数分
	for (int nCnt = 0; nCnt < MAX_BULLET_MAGAZINE; nCnt++)
	{
		// 生成
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}
	
	// マガジンの数値を決める
	m_nBulletNumber_HG_magazine = 10;
	m_nBulletNumber_AR_magazine = 30;
	m_nBulletNumber_SG_magazine = 8;
	m_nBulletNumber_SR_magazine = 6;
	m_nBulletNumber_RL_magazine = 1;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBulletMagazine::Uninit(void)
{
	// MAX_BULLET_MAGAZINEの数分
	for (int nCnt = 0; nCnt < MAX_BULLET_MAGAZINE; nCnt++)
	{
		//頂点バッファの破棄
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;

			delete m_apNumber[nCnt];
		}
	}

	// オブジェクトを破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBulletMagazine::Update(void)
{
	// 弾の種類の情報を渡す
	m_nMagazineType = CPlayer::GetBulletType();

	// キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// 総弾数の取得
	CBulletTotal *pBulletTotal;
	pBulletTotal = CGame::GetBulletTotal();

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// 弾の種類がHGだった場合
	if (m_nMagazineType == CBullet::TYPE_HG)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_HG_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_HG_magazine % (int)pow(10, 1));

		// 10以上だったら
		if (m_nBulletNumber_HG_magazine >= 10)
		{
			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 9以下かつ1以上だったら
		if (m_nBulletNumber_HG_magazine <= 9 && m_nBulletNumber_HG_magazine >= 1)
		{
			// 色を白にする
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// 所持数が０以下になったら
		if (m_nBulletNumber_HG_magazine <= 0)
		{
			// ０で停止する
			m_nBulletNumber_HG_magazine = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// Rキー・Xボタンを押したら
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SEを流す
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// 弾数が9以下又は1以上だったら
			if (m_nBulletNumber_HG_magazine <= 9 || m_nBulletNumber_HG_magazine >= 1)
			{
				// 弾数が9以下かつ1以上だったら
				if (m_nBulletNumber_HG_magazine <= 9 && m_nBulletNumber_HG_magazine >= 1)
				{
					// 音を出す
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// 弾数が10以上だったら
				if (m_nBulletNumber_HG_magazine >= 10)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// 弾の最大数から現在の弾数を引く
				m_nMagazine = MAX_BULLET_HG_MAGAZINE - m_nBulletNumber_HG_magazine;

				// 引いた数を総弾数から引く
				pBulletTotal->SubBulletTotal(m_nMagazine);

				// トータルの情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// トータルの情報をマガジンに加算
				m_nBulletNumber_HG_magazine += m_nTotal_Magazine;

				// マガジンがマックスの値を超えたら
				if (m_nBulletNumber_HG_magazine >= MAX_BULLET_HG_MAGAZINE)
				{
					// 初期化する
					m_nBulletNumber_HG_magazine = 0;

					// マガジンに10を入れる
					m_nBulletNumber_HG_magazine = 10;
				}
			}

			// 所持数が０以下になったら
			if (m_nBulletNumber_HG_magazine <= 0)
			{
				// トータルの情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// トータルの情報をマガジンに加算
				m_nBulletNumber_HG_magazine += m_nTotal_Magazine;
			}
		}
	}



	// 弾の種類がARだった場合
	else if (m_nMagazineType == CBullet::TYPE_AR)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_AR_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_AR_magazine % (int)pow(10, 1));

		// 弾数が30以上だったら
		if (m_nBulletNumber_AR_magazine >= 30)
		{
			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 弾数が29以下かつ1以上だったら
		if (m_nBulletNumber_AR_magazine <= 29 && m_nBulletNumber_AR_magazine >= 1)
		{
			// 色を白にする
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// 所持数が０以下になったら
		if (m_nBulletNumber_AR_magazine <= 0)
		{
			// 0で停止する
			m_nBulletNumber_AR_magazine = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// Rキー・Xボタンを押したら
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SEを流す
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);
			
			// 弾数が29以下又は1以上だったら
			if (m_nBulletNumber_AR_magazine <= 29 || m_nBulletNumber_AR_magazine >= 1)
			{
				// 弾数が29以下かつ1以上だったら
				if (m_nBulletNumber_AR_magazine <= 29 && m_nBulletNumber_AR_magazine >= 1)
				{
					// 音を出す
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// 弾数が30以上だったら
				if (m_nBulletNumber_AR_magazine >= 30)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// 弾の最大数から現在の弾数を引く
				m_nMagazine = MAX_BULLET_AR_MAGAZINE - m_nBulletNumber_AR_magazine;

				// 引いた数を総弾数から引く
				pBulletTotal->SubBulletTotal(m_nMagazine);

				// 総弾数の情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// 総弾数が0だったら
				if (m_nTotal_Magazine <= 0)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// 総弾数の情報をマガジンに加算
				m_nBulletNumber_AR_magazine += m_nTotal_Magazine;

				// マガジンがマックスの値を超えたら
				if (m_nBulletNumber_AR_magazine >= MAX_BULLET_AR_MAGAZINE)
				{
					// 初期化する
					m_nBulletNumber_AR_magazine = 0;

					// マガジンに30を入れる
					m_nBulletNumber_AR_magazine = 30;
				}
			}

			// 所持数が０以下になったら
			if (m_nBulletNumber_AR_magazine <= 0)
			{
				// 総弾数の情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// 総弾数の情報をマガジンに加算
				m_nBulletNumber_AR_magazine += m_nTotal_Magazine;
			}
		}
	}



	// 弾の種類がSGだった場合
	else if (m_nMagazineType == CBullet::TYPE_SG)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_SG_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SG_magazine % (int)pow(10, 1));

		// 所持弾数が8以上だったら
		if (m_nBulletNumber_SG_magazine >= 8)
		{
			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 所持弾数が7以下かつ1以上だったら
		if (m_nBulletNumber_SG_magazine <= 7 && m_nBulletNumber_SG_magazine >= 1)
		{
			// 色を白にする
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// 所持数が０以下になったら
		if (m_nBulletNumber_SG_magazine <= 0)
		{
			// 0で停止する
			m_nBulletNumber_SG_magazine = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// Rキー・Xボタンを押したら
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SEを流す
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// 弾数が7以下又は1以上だったら
			if (m_nBulletNumber_SG_magazine <= 7 || m_nBulletNumber_SG_magazine >= 1)
			{
				// 弾数が7以下かつ1以上だったら
				if (m_nBulletNumber_SG_magazine <= 7 && m_nBulletNumber_SG_magazine >= 1)
				{
					// 音を出す
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// 弾数が8以上だったら
				if (m_nBulletNumber_SG_magazine >= 8)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				//弾の最大数から現在の弾数を引く
				m_nMagazine = MAX_BULLET_SG_MAGAZINE - m_nBulletNumber_SG_magazine;

				//引いた数を総弾数から引く
				pBulletTotal->SubBulletTotal(m_nMagazine);

				//トータルの情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// 総弾数が0だったら
				if (m_nTotal_Magazine <= 0)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// トータルの情報をマガジンに加算
				m_nBulletNumber_SG_magazine += m_nTotal_Magazine;

				// マガジンがマックスの値を超えたら
				if (m_nBulletNumber_SG_magazine >= MAX_BULLET_SG_MAGAZINE)
				{
					// 初期化する
					m_nBulletNumber_SG_magazine = 0;

					// マガジンに10を入れる
					m_nBulletNumber_SG_magazine = 8;
				}
			}

			// 所持数が０以下になったら
			if (m_nBulletNumber_SG_magazine <= 0)
			{
				// トータルの情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// トータルの情報をマガジンに加算
				m_nBulletNumber_SG_magazine += m_nTotal_Magazine;
			}
		}
	}



	// 弾の種類がSRだった場合
	else if (m_nMagazineType == CBullet::TYPE_SR)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_SR_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SR_magazine % (int)pow(10, 1));

		// 所持弾数が6以上だったら
		if (m_nBulletNumber_SR_magazine >= 6)
		{
			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 所持弾数が5以下かつ1以上だったら
		if (m_nBulletNumber_SR_magazine <= 5 && m_nBulletNumber_SR_magazine >= 1)
		{
			// 色を白にする
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		//所持数が0以下になったら
		if (m_nBulletNumber_SR_magazine <= 0)
		{
			//0で停止する
			m_nBulletNumber_SR_magazine = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// Rキー・Xボタンを押したら
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SEを流す
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// 弾数が5以下又は1以上だったら
			if (m_nBulletNumber_SR_magazine <= 5 || m_nBulletNumber_SR_magazine >= 1)
			{
				// 弾数が5以下かつ1以上だったら
				if (m_nBulletNumber_SR_magazine <= 5 && m_nBulletNumber_SR_magazine >= 1)
				{
					// 音を出す
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// 弾数が6以上だったら
				if (m_nBulletNumber_SR_magazine >= 6)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				//　弾の最大数から現在の弾数を引く
				m_nMagazine = MAX_BULLET_SR_MAGAZINE - m_nBulletNumber_SR_magazine;

				//　引いた数を総弾数から引く
				pBulletTotal->SubBulletTotal(m_nMagazine);

				//　トータルの情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// 総弾数が0以下だったら
				if (m_nTotal_Magazine <= 0)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// トータルの情報をマガジンに加算
				m_nBulletNumber_SR_magazine += m_nTotal_Magazine;

				// マガジンがマックスの値を超えたら
				if (m_nBulletNumber_SR_magazine >= MAX_BULLET_SR_MAGAZINE)
				{
					// 初期化する
					m_nBulletNumber_SR_magazine = 0;

					// マガジンに10を入れる
					m_nBulletNumber_SR_magazine = 6;
				}
			}

			// 所持数が０以下になったら
			if (m_nBulletNumber_SR_magazine <= 0)
			{
				// トータルの情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// トータルの情報をマガジンに加算
				m_nBulletNumber_SR_magazine += m_nTotal_Magazine;
			}
		}
	}



	// 弾の種類がRLだった場合
	else if (m_nMagazineType == CBullet::TYPE_RL)
	{
		//桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_RL_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_RL_magazine % (int)pow(10, 1));

		// 弾数が1以上だったら
		if (m_nBulletNumber_HG_magazine >= 1)
		{
			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		//所持数が０以下になったら
		if (m_nBulletNumber_RL_magazine <= 0)
		{
			//０で停止する
			m_nBulletNumber_RL_magazine = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// Rキー・Xボタンを押したら
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SEを流す
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// 弾数が0以下になったら
			if (m_nBulletNumber_RL_magazine <= 0)
			{
				// 音を出す
				pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);

				// 弾の最大数から現在の弾数を引く
				m_nMagazine = MAX_BULLET_RL_MAGAZINE - m_nBulletNumber_RL_magazine;

				// 引いた数を総弾数から引く
				pBulletTotal->SubBulletTotal(m_nMagazine);

				// 総弾数の情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// 総弾数が0以下だったら
				if (m_nTotal_Magazine <= 0)
				{
					// 音を出さない
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				//トータルの情報をマガジンに加算
				m_nBulletNumber_RL_magazine += m_nTotal_Magazine;

				//マガジンがマックスの値を超えたら
				if (m_nBulletNumber_RL_magazine >= MAX_BULLET_RL_MAGAZINE)
				{
					//初期化する
					m_nBulletNumber_RL_magazine = 0;

					//マガジンに1を入れる
					m_nBulletNumber_RL_magazine = 1;
				}
			}

			// 弾数が1以上だったら
			else
			{
				// 音を出さない
				pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
			}

			//所持数が０以下になったら
			if (m_nBulletNumber_RL_magazine <= 0)
			{
				//トータルの情報を渡す
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				//トータルの情報をマガジンに加算
				m_nBulletNumber_RL_magazine += m_nTotal_Magazine;
			}
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CBulletMagazine::Draw(void)
{
	// MAX_BULLET_MAGAZINEの数分
	for (int nCnt = 0; nCnt < MAX_BULLET_MAGAZINE; nCnt++)
	{
		// 描画処理
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// 減算処理
//=============================================================================
void CBulletMagazine::SubBulletMagazine(int nValue)
{
	// ポインタ
	CPlayer *pPlayer = NULL;

	// 弾の種類の情報を渡す
	m_nMagazineType = CPlayer::GetBulletType();

	// 弾の種類がHGだった場合
	if (m_nMagazineType == CBullet::TYPE_HG)
	{
		// nValueの数分引く
		m_nBulletNumber_HG_magazine -= nValue;
	}

	// 弾の種類がARだった場合
	else if (m_nMagazineType == CBullet::TYPE_AR)
	{
		// nValueの数分引く
		m_nBulletNumber_AR_magazine -= nValue;
	}
	
	// 弾の種類がSGだった場合
	else if (m_nMagazineType == CBullet::TYPE_SG)
	{
		// nValueの数分引く
		m_nBulletNumber_SG_magazine -= nValue;
	}

	// 弾の種類がSRだった場合
	else if (m_nMagazineType == CBullet::TYPE_SR)
	{
		// nValueの数分引く
		m_nBulletNumber_SR_magazine -= nValue;
	}

	// 弾の種類がRLだった場合
	else if (m_nMagazineType == CBullet::TYPE_RL)
	{
		// nValueの数分引く
		m_nBulletNumber_RL_magazine -= nValue;
	}
}

//=============================================================================
// ハンドガン弾数の取得処理
//=============================================================================
int CBulletMagazine::GetBulletMagazineHG(void)
{
	// メンバを戻り値へ返す
	return m_nBulletNumber_HG_magazine;
}

//=============================================================================
// アサルトライフル弾数の取得処理
//=============================================================================
int CBulletMagazine::GetBulletMagazineAR(void)
{
	// メンバを戻り値へ返す
	return m_nBulletNumber_AR_magazine;
}

//=============================================================================
// ショットガン弾数の取得処理
//=============================================================================
int CBulletMagazine::GetBulletMagazineSG(void)
{
	// メンバを戻り値へ返す
	return m_nBulletNumber_SG_magazine;
}

//=============================================================================
// スナイパーライフル弾数の取得処理
//=============================================================================
int CBulletMagazine::GetBulletMagazineSR(void)
{
	// メンバを戻り値へ返す
	return m_nBulletNumber_SR_magazine;
}

//=============================================================================
// ロケットランチャー弾数の取得処理
//=============================================================================
int CBulletMagazine::GetBulletMagazineRL(void)
{
	// メンバを戻り値へ返す
	return m_nBulletNumber_RL_magazine;
}

//=============================================================================
// 弾の種類の取得処理
//=============================================================================
int CBulletMagazine::GetBulletType(void)
{
	// メンバを戻り値へ返す
	return m_nMagazineType;
}
