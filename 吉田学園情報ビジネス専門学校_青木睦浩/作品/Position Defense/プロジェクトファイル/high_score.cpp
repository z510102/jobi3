//=============================================================================
//
// ハイスコア処理 [high_score.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "high_score.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CHighScore::CHighScore(int nPriority) : CScene(nPriority)
{
	// 変数をクリア
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	m_nScore = 0;
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nHighScore = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CHighScore::~CHighScore()
{

}

//=============================================================================
// ハイスコアの生成
//=============================================================================
CHighScore *CHighScore::Create(D3DXVECTOR3 pos)
{
	// ポインタ
	CHighScore *pHighScore;

	// メモリを確保
	pHighScore = new CHighScore(PRIORITY_NUMBER);

	if (pHighScore != NULL)
	{
		// メンバへ情報を渡す
		pHighScore->m_size = D3DXVECTOR2(30, 40);

		// Initへ
		pHighScore->Init(pos);
	}

	// ポインタを戻り値へ返す
	return pHighScore;
}

//=============================================================================
// ハイスコアの初期化処理
//=============================================================================
HRESULT CHighScore::Init(D3DXVECTOR3 pos)
{
	// MAX_HIGH_SCOREの数分
	for (int nCnt = 0; nCnt < MAX_HIGH_SCORE; nCnt++)
	{
		// ナンバーを生成
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}

	// ファイルポインタ
	FILE *pFile;

	// ファイルを開く（ロード）
	pFile = fopen("data/SAVE DATA/ranking.txt", "r");

	if (pFile != NULL)
	{
		// 数値を読み込む
		fscanf(pFile, "%d", &m_nHighScore);

		// ファイルを閉じる
		fclose(pFile);
	}

	// メンバへ情報を渡す
	m_nScore = m_nHighScore;

	return S_OK;
}

//=============================================================================
// ハイスコアの終了処理
//=============================================================================
void CHighScore::Uninit(void)
{
	// MAX_HIGH_SCOREの数分
	for (int nCnt = 0; nCnt < MAX_HIGH_SCORE; nCnt++)
	{
		//頂点バッファの破棄
		if (m_apNumber[nCnt] != NULL)
		{
			// ナンバーの終了処理へ
			m_apNumber[nCnt]->Uninit();

			// NULLにする
			m_apNumber[nCnt] = NULL;

			// メモリを解放
			delete m_apNumber[nCnt];
		}
	}

	// オブジェクトの破棄処理へ
	Release();
}

//=============================================================================
// ハイスコアの更新処理
//=============================================================================
void CHighScore::Update(void)
{
	//桁数分加算されたスコアを計算する
	m_apNumber[0]->SetNumber(m_nScore / (int)pow(10, 4));
	m_apNumber[1]->SetNumber(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apNumber[2]->SetNumber(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[3]->SetNumber(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[4]->SetNumber(m_nScore % (int)pow(10, 1));
}

//=============================================================================
// ハイスコアの描画処理
//=============================================================================
void CHighScore::Draw(void)
{
	// MAX_HIGH_SCOREの数分
	for (int nCnt = 0; nCnt < MAX_HIGH_SCORE; nCnt++)
	{
		// ナンバーを描画
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// ハイスコアの設定処理
//=============================================================================
void CHighScore::SetScore(int nScore)
{
	// 引数をメンバへ渡す
	m_nScore = nScore;
}

//=============================================================================
// ハイスコアの加算処理
//=============================================================================
void CHighScore::AddScore(int nValue)
{
	// メンバと引数を足してメンバへ渡す
	m_nScore += nValue;
}

//=============================================================================
// ハイスコアの取得処理
//=============================================================================
int CHighScore::GetScore(void)
{
	// メンバを戻り値へ返す
	return m_nScore;
}