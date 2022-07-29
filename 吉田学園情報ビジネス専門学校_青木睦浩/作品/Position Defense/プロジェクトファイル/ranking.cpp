//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "ranking.h"
#include "score.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScore *CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	// 変数をクリア
	memset(&m_apScore[0], 0, sizeof(CNumber));
	m_nScore = 0;
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// スコアの生成
//=============================================================================
CRanking *CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ポインタ
	CRanking *pRanking;

	// メモリを確保
	pRanking = new CRanking(PRIORITY_NUMBER);

	if (pRanking != NULL)
	{
		// メンバへ情報を渡す
		pRanking->m_size = size;

		// Initへ
		pRanking->Init(pos);
	}

	// ポインタを戻り値へ返す
	return pRanking;
}

//=============================================================================
// スコアの初期化処理
//=============================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos)
{
	// MAX_RANKINGの数分
	for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
	{
		// 数分スコアを作成
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x , pos.y + m_size.y * nCnt, 0.0f), D3DXVECTOR2(50, 60));
	}

	// ファイルのポインタ
	FILE *pFile;

	// ファイルを開く（ロード）
	pFile = fopen("data/SAVE DATA/ranking.txt", "r");

	if (pFile != NULL)
	{
		// MAX_RANKINGの数分
		for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
		{
			// 読み込む
			fscanf(pFile, "%d", &m_aScore[nCnt]);
		}

		// ファイルを閉じる
		fclose(pFile);
	}

	// ファイルを開く（ロード）
	pFile = fopen("data/SAVE DATA/score.txt", "r");

	if (pFile != NULL)
	{
		// 現在のスコアを読み込む
		fscanf(pFile, "%d", &m_nScore);

		// ファイルを閉じる
		fclose(pFile);
	}

	// 現在のスコアを渡す
	m_aScore[MAX_RANKING - 1] = m_nScore;

	// スコアを並べ替え
	// MAX_RANKINGの数分
	for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
	{
		for (int nCount = 0; nCount < MAX_RANKING - 1; nCount++)
		{
			// 最後のスコアが今のスコアより小さい場合
			if (m_aScore[nCount] < m_aScore[nCount + 1])
			{
				// 保存
				int nScore = m_aScore[nCount];

				// 一つ上のスコアを現在のスコアへ
				m_aScore[nCount] = m_aScore[nCount + 1];

				// 戻す
				m_aScore[nCount + 1] = nScore;
			}
		}
	}

	// MAX_RANKINGの数分
	for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
	{
		// 並び変えた後のスコアを設定
		m_apScore[nCnt]->SetScore(m_aScore[nCnt]);
	}

	// スコアの配列の最後を0にする
	m_aScore[MAX_RANKING - 1] = 0;

	// ファイルを開く（書き込み）
	pFile = fopen("data/SAVE DATA/ranking.txt", "w");

	if (pFile != NULL)
	{
		// MAX_RANKINGの数分
		for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
		{
			// txtに新しく書き込み（上書き）
			fprintf(pFile, "%d\n", m_aScore[nCnt]);
		}

		// ファイルを閉じる
		fclose(pFile);
	}

	return S_OK;
}

//=============================================================================
// スコアの終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	
}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CRanking::Update(void)
{
	
}

//=============================================================================
// スコアの描画処理
//=============================================================================
void CRanking::Draw(void)
{
	
}