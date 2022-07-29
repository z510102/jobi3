//=============================================================================
//
// タイム処理 [time.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "time.h"
#include "manager.h"
#include "game.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime(int nPriority) : CScene(nPriority)
{
	// 変数をクリア
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	m_nTime = 0;
	m_nCntTimer = 0;
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_bUse = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// タイムの生成
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	// ポインタ
	CTime *pNumber;

	// メモリを確保
	pNumber = new CTime(PRIORITY_NUMBER);

	if (pNumber != NULL)
	{
		// メンバへ情報を渡す
		pNumber->m_size = D3DXVECTOR2(30, 40);

		// Initへ
		pNumber->Init(pos);
	}

	// ポインタを戻り値へ返す
	return pNumber;
}

//=============================================================================
// タイムの初期化処理
//=============================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos)
{
	// MAX_TIMEの数分
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// ナンバーを生成
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}

	// タイムを設定
	m_nTime = 180;

	return S_OK;
}

//=============================================================================
// タイムの終了処理
//=============================================================================
void CTime::Uninit(void)
{
	// MAX_TIMEの数分
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		//頂点バッファの破棄
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;

			// メモリを解放
			delete m_apNumber[nCnt];
		}
	}

	// オブジェクトの破棄へ
	Release();
}

//=============================================================================
// タイムの更新処理
//=============================================================================
void CTime::Update(void)
{
	// 桁数分加算されたスコアを計算する
	m_apNumber[0]->SetNumber(m_nTime / (int)pow(10, 2));
	m_apNumber[1]->SetNumber(m_nTime % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[2]->SetNumber(m_nTime % (int)pow(10, 1));

	// タイマーのカウントを加算
	m_nCntTimer++;

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// タイマーのカウントが70以上になったら
	if (m_nCntTimer >= 70)
	{
		// タイムを１秒減らす
		m_nTime--;

		// タイマーのカウントを０に戻す
		m_nCntTimer = 0;
	}

	//タイムが30以下の場合
	if (m_nTime <= 30)
	{
		// 色を設定
		m_apNumber[0]->SetColor(255, 0, 0, 255);
		m_apNumber[1]->SetColor(255, 0, 0, 255);
		m_apNumber[2]->SetColor(255, 0, 0, 255);
	}

	// タイムが31以上の場合
	if (m_nTime >= 31)
	{
		// 色を設定
		m_apNumber[0]->SetColor(255, 255, 255, 255);
		m_apNumber[1]->SetColor(255, 255, 255, 255);
		m_apNumber[2]->SetColor(255, 255, 255, 255);
	}

	//タイムが0以下かつ使用している場合
	if (m_nTime <= 0 && m_bUse == true)
	{
		// ゲームクリア処理へ
		CGame *pGame = NULL;
		pGame->Clear();

		// 使用していないようにする
		m_bUse = false;
	}

	// 使用していない場合
	else if (m_bUse == false)
	{
		// 0で停止する
		m_nTime = 0;

		// ナンバーを0で固定する
		m_apNumber[0]->SetNumber(0);
		m_apNumber[1]->SetNumber(0);
		m_apNumber[2]->SetNumber(0);
	}
}

//=============================================================================
// タイムの描画処理
//=============================================================================
void CTime::Draw(void)
{
	// MAX_TIMEの数分
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// ナンバーの描画処理へ
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// タイムの設定処理
//=============================================================================
void CTime::SetTime(int nScore)
{
	// 引数をメンバへ渡す
	m_nTime = nScore;

	/*for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
	m_apNumber[nCnt]->SetNumber();
	}*/
}

//=============================================================================
// タイムの加算処理
//=============================================================================
void CTime::AddTime(int nValue)
{
	// メンバと引数を足してメンバへ渡す
	m_nTime += nValue;
}

//=============================================================================
// タイムの取得処理
//=============================================================================
int CTime::GetTime(void)
{
	// タイムを戻り値へ返す
	return m_nTime;
}