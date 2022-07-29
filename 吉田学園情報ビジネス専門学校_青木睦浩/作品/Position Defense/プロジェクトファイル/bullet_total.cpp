//=============================================================================
//
// 総弾数処理 [bullet_total.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "bullet_total.h"
#include "manager.h"
#include "player.h"
#include "bullet_magazine.h"
#include "game.h"

//=============================================================================
// 生成処理
//=============================================================================
CBulletTotal *CBulletTotal::Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type)
{
	// ポインタ
	CBulletTotal *pNumber;

	// メモリを確保
	pNumber = new CBulletTotal (PRIORITY_NUMBER);

	if (pNumber != NULL)
	{
		// メンバ変数へ情報を渡す
		pNumber->m_size = D3DXVECTOR2(30, 30);
		pNumber->m_type_total = type;

		// 処理へ
		pNumber->Init(pos);
	}

	// ポインタを戻り値へ返す
	return pNumber;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletTotal::CBulletTotal(int nPriority) : CScene(nPriority)
{
	// 変数をクリアする
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nBulletNumber_HG_total = 0;
	m_nBulletNumber_AR_total = 0;
	m_nBulletNumber_SG_total = 0;
	m_nBulletNumber_SR_total = 0;
	m_nBulletNumber_RL_total = 0;
	m_type_total = CBullet::TYPE_HG;
	m_nTotal = 0;
	m_nPass = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletTotal::~CBulletTotal()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBulletTotal::Init(D3DXVECTOR3 pos)
{
	// ポインタ
	CPlayer *pPlayer = NULL;

	// 弾の種類の情報を渡す
	m_nTotalType = CPlayer::GetBulletType();

	// MAX_BULLET_TOTALの数分
	for (int nCnt = 0; nCnt < MAX_BULLET_TOTAL; nCnt++)
	{
		// 生成
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}

	// 数値を入れる
	m_nBulletNumber_HG_total = 9999;
	m_nBulletNumber_AR_total = 90;
	m_nBulletNumber_SG_total = 16;
	m_nBulletNumber_SR_total = 12;
	m_nBulletNumber_RL_total = 1;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBulletTotal::Uninit(void)
{
	// MAX_BULLET_TOTALの数分
	for (int nCnt = 0; nCnt < MAX_BULLET_TOTAL; nCnt++)
	{
		//頂点バッファの破棄
		if (m_apNumber[nCnt] != NULL)
		{
			// ナンバーの終了処理へ
			m_apNumber[nCnt]->Uninit();

			// メンバをNULLにする
			m_apNumber[nCnt] = NULL;

			// メモリを解放
			delete m_apNumber[nCnt];
		}
	}

	// オブジェクトを破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBulletTotal::Update(void)
{
	// ポインタ
	CPlayer *pPlayer = NULL;

	// 弾の種類の情報を渡す
	m_nTotalType = CPlayer::GetBulletType();

	// マガジンの取得
	CBulletMagazine *pBulletMagazine;
	pBulletMagazine = CGame::GetBulletMagazine();

	// サウンドの取得
	CSound *pSound;
	pSound = CManager::GetSound();



	// 総弾数の種類がHGだった場合
	if (m_nTotalType == CBullet::TYPE_HG)
	{
		// 色を無しにする（表示できなくする）
		m_apNumber[0]->SetColor(0, 0, 0, 0);
		m_apNumber[1]->SetColor(0, 0, 0, 0);

		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_HG_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_HG_total % (int)pow(10, 1));

		// 総弾数が１０以上ある場合
		if (m_nBulletNumber_HG_total >= 10)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineHG();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_HG_MAGAZINE - m_nPass;

			// 情報を渡す
			m_nRemainingTotal = m_nTotal;
		}
	}



	// 総弾数の種類がARだった場合
	else if (m_nTotalType == CBullet::TYPE_AR)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_AR_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_AR_total % (int)pow(10, 1));

		// 総弾数が90以上だったら
		if (m_nBulletNumber_AR_total >= 90)
		{
			// 総弾数を90に固定する
			m_nBulletNumber_AR_total = 90;

			// ナンバーを90にする
			m_apNumber[0]->SetNumber(9);
			m_apNumber[1]->SetNumber(0);

			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 総弾数が89以下かつ1以上だったら
		else if (m_nBulletNumber_AR_total <= 89 && m_nBulletNumber_AR_total >= 1)
		{
			// 色を白にする
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// 所持数が０以下になったら
		else if (m_nBulletNumber_AR_total <= 0)
		{
			// ０で停止する
			m_nBulletNumber_AR_total = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// 総弾数が30以上ある場合
		else if (m_nBulletNumber_AR_total >= 30)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineAR();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_AR_MAGAZINE - m_nPass;

			// 情報を渡す
			m_nRemainingTotal = m_nTotal;
		}

		// 総弾数が9以下の場合
		else if (m_nBulletNumber_AR_total <= 9)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineAR();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_AR_MAGAZINE - m_nPass;

			// 最大数からマガジンの情報を引いた数が30だった場合
			if (m_nTotal == 30)
			{
				// 最大数からマガジンの情報を引いた数から1引いて渡す
				m_nTotal = m_nTotal - 1;
			}

			// マガジンの弾数が29以下かつ総弾数が9以下だった場合
			if (m_nPass <= 29 && m_nBulletNumber_AR_total <= 9)
			{
				// 0にする
				m_nTotal = 0;

				// 情報を渡す
				m_nTotal = m_nBulletNumber_AR_total;
			}

			// 残りの総弾数へ渡す
			m_nRemainingTotal = m_nTotal;
		}
	}



	// ショットガンの場合
	else if (m_nTotalType == CBullet::TYPE_SG)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_SG_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SG_total % (int)pow(10, 1));

		// 総弾数が16以上だったら
		if (m_nBulletNumber_SG_total >= 16)
		{
			// 総弾数を16に固定する
			m_nBulletNumber_SG_total = 16;

			// ナンバーを16にする
			m_apNumber[0]->SetNumber(1);
			m_apNumber[1]->SetNumber(6);

			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 総弾数が15以下かつ1以上だったら
		else if (m_nBulletNumber_SG_total <= 15 && m_nBulletNumber_SG_total >= 1)
		{
			// 色を白にする
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// 総弾数が０以下になったら
		else if (m_nBulletNumber_SG_total <= 0)
		{
			// ０で停止する
			m_nBulletNumber_SG_total = 0;

			// ナンバーを00にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// 総弾数が１０以上ある場合
		else if (m_nBulletNumber_SG_total >= 10)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineSG();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_SG_MAGAZINE - m_nPass;

			// 最大数からマガジンの情報を引いた数を渡す
			m_nRemainingTotal = m_nTotal;
		}

		// 総弾数が９以下の場合
		else if (m_nBulletNumber_SG_total <= 9)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineSG();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_SG_MAGAZINE - m_nPass;

			// 最大数からマガジンの情報を引いた数が8だった場合
			if (m_nTotal == 8)
			{
				// 最大数からマガジンの情報を引いた数から1引いて渡す
				m_nTotal = m_nTotal - 1;
			}

			// マガジンの弾数が7以下かつ総弾数が9以下だった場合
			if (m_nPass <= 7 && m_nBulletNumber_SG_total <= 9)
			{
				// 0にする
				m_nTotal = 0;

				// 情報を渡す
				m_nTotal = m_nBulletNumber_SG_total;
			}

			// 残りの総弾数へ渡す
			m_nRemainingTotal = m_nTotal;
		}
	}



	// スナイパーライフルの場合
	else if (m_nTotalType == CBullet::TYPE_SR)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_SR_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SR_total % (int)pow(10, 1));

		// 総弾数が12以上だったら
		if (m_nBulletNumber_SR_total >= 12)
		{
			// 総弾数を12に固定する
			m_nBulletNumber_SR_total = 12;

			// ナンバーを12にする
			m_apNumber[0]->SetNumber(1);
			m_apNumber[1]->SetNumber(2);

			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 総弾数が11以下かつ1以上だったら
		else if (m_nBulletNumber_SR_total <= 11 && m_nBulletNumber_SR_total >= 1)
		{
			// 色を白にする
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// 所持数が０以下になったら
		else if (m_nBulletNumber_SR_total <= 0)
		{
			// ０で停止する
			m_nBulletNumber_SR_total = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// 弾数が１０以上ある場合
		else if (m_nBulletNumber_SR_total >= 10)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineSR();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_SR_MAGAZINE - m_nPass;

			// 情報を渡す
			m_nRemainingTotal = m_nTotal;
		}

		// 総弾数が9以下の場合
		else if (m_nBulletNumber_SR_total <= 9)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineSR();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_SR_MAGAZINE - m_nPass;

			// 最大数からマガジンの情報を引いた数が6だった場合
			if (m_nTotal == 6)
			{
				// 最大数からマガジンの情報を引いた数から1引いて渡す
				m_nTotal = m_nTotal - 1;
			}

			// マガジンの弾数が5以下かつ総弾数が9以下の場合
			if (m_nPass <= 5 && m_nBulletNumber_SR_total <= 9)
			{
				// 現在の総弾数を0にする
				m_nTotal = 0;

				// 総弾数を現在の総弾数に入れる
				m_nTotal = m_nBulletNumber_SR_total;
			}

			// 残りの総弾数へ渡す
			m_nRemainingTotal = m_nTotal;
		}
	}



	// ロケットランチャーの場合
	else if (m_nTotalType == CBullet::TYPE_RL)
	{
		// 桁数分加算されたスコアを計算する
		m_apNumber[0]->SetNumber(m_nBulletNumber_RL_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_RL_total % (int)pow(10, 1));

		// 総弾数が1以上だったら
		if (m_nBulletNumber_RL_total >= 1)
		{
			// 総弾数を1に固定する
			m_nBulletNumber_RL_total = 1;

			// ナンバーを1にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(1);

			// 色を緑にする
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 所持数が０以下になったら
		else if (m_nBulletNumber_RL_total <= 0)
		{
			// ０で停止する
			m_nBulletNumber_RL_total = 0;

			// ナンバーを0にする
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// 色を赤にする
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// 弾数が１０以上ある場合
		else if (m_nBulletNumber_RL_total >= 10)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineRL();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_RL_MAGAZINE - m_nPass;

			// 情報を渡す
			m_nRemainingTotal = m_nTotal;
		}

		// 総弾数が9以下の場合
		else if (m_nBulletNumber_RL_total <= 9)
		{
			// マガジンの情報を渡す
			m_nPass = pBulletMagazine->GetBulletMagazineRL();

			// 最大数からマガジンの情報を引く
			m_nTotal = MAX_BULLET_RL_MAGAZINE - m_nPass;

			// 最大数からマガジンの情報を引いた数が1だった場合
			if (m_nTotal == 1)
			{
				// 最大数からマガジンの情報を引いた数から1引いて渡す
				m_nTotal = m_nTotal - 1;
			}

			// マガジンの弾数が1以下かつ総弾数が9以下の場合
			if (m_nPass <= 1 && m_nBulletNumber_RL_total <= 9)
			{
				// 現在の総弾数を0にする
				m_nTotal = 0;

				// 総弾数を現在の総弾数に入れる
				m_nTotal = m_nBulletNumber_RL_total;
			}

			// 残りの総弾数へ渡す
			m_nRemainingTotal = m_nTotal;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBulletTotal::Draw(void)
{
	// MAX_BULLET_TOTALの数分
	for (int nCnt = 0; nCnt < MAX_BULLET_TOTAL; nCnt++)
	{
		// ナンバーを描画する
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// 設定処理
//=============================================================================
void CBulletTotal::SetBulletTotal(int nBulletNumber)
{
	// 引数をハンドガン総弾数へ渡す
	m_nBulletNumber_HG_total = nBulletNumber;
}

//=============================================================================
// 減算処理
//=============================================================================
void CBulletTotal::SubBulletTotal(int nValue)
{
	// 弾の種類の情報を渡す
	m_nTotalType = CPlayer::GetBulletType();

	// 弾の種類がハンドガンだった場合
	if (m_nTotalType == CBullet::TYPE_HG)
	{
		// 総弾数と引数を引いて総弾数に渡す
		m_nBulletNumber_HG_total -= nValue;
	}

	// 弾の種類がアサルトライフルだった場合
	else if (m_nTotalType == CBullet::TYPE_AR)
	{
		// 総弾数と引数を引いて総弾数に渡す
		m_nBulletNumber_AR_total -= nValue;
	}

	// 弾の種類がショットガンだった場合
	else if (m_nTotalType == CBullet::TYPE_SG)
	{
		// 総弾数と引数を引いて総弾数に渡す
		m_nBulletNumber_SG_total -= nValue;
	}

	// 弾の種類がスナイパーライフルだった場合
	else if (m_nTotalType == CBullet::TYPE_SR)
	{
		// 総弾数と引数を引いて総弾数に渡す
		m_nBulletNumber_SR_total -= nValue;
	}

	// 弾の種類がロケットランチャーだった場合
	else if (m_nTotalType == CBullet::TYPE_RL)
	{
		// 総弾数と引数を引いて総弾数に渡す
		m_nBulletNumber_RL_total -= nValue;
	}
}

//=============================================================================
// スコアの取得処理
//=============================================================================
int CBulletTotal::GetBulletTotal(void)
{
	// 残りの総弾数を返す
	return m_nRemainingTotal;
}

//=============================================================================
// ハンドガンの総弾数の加算処理
//=============================================================================
void CBulletTotal::AddBulletTotalHG(int nValue)
{
	// ハンドガンの総弾数と引数を足してハンドガンの総弾数へ渡す
	m_nBulletNumber_HG_total += nValue;
}

//=============================================================================
// アサルトライフルの総弾数の加算処理
//=============================================================================
void CBulletTotal::AddBulletTotalAR(int nValue)
{
	// アサルトライフルの総弾数と引数を足してアサルトライフルの総弾数へ渡す
	m_nBulletNumber_AR_total += nValue;
}

//=============================================================================
// ショットガンの総弾数の加算処理
//=============================================================================
void CBulletTotal::AddBulletTotalSG(int nValue)
{
	// ショットガンの総弾数と引数を足してショットガンの総弾数へ渡す
	m_nBulletNumber_SG_total += nValue;
}

//=============================================================================
// スナイパーライフルの総弾数の加算処理
//=============================================================================
void CBulletTotal::AddBulletTotalSR(int nValue)
{
	// スナイパーライフルの総弾数と引数を足してスナイパーライフルの総弾数へ渡す
	m_nBulletNumber_SR_total += nValue;
}

//=============================================================================
// ロケットランチャーの総弾数の加算処理
//=============================================================================
void CBulletTotal::AddBulletTotalRL(int nValue)
{
	// ロケットランチャーの総弾数と引数を足してロケットランチャーの総弾数へ渡す
	m_nBulletNumber_RL_total += nValue;
}
