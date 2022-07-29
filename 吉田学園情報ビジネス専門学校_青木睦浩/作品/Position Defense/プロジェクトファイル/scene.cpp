//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "scene.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	// MAX_SCENEの数分
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		// m_apSceneがNULLだったら
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;

			// 自分の番号を設定
			m_nID = nCntScene;

			// 情報を渡す
			m_nPriority = nPriority;

			// 加算する
			m_nNumAll++;

			// 抜ける
			break;
		}
	}

	// オブジェクトの種類をなしにする
	m_objType = OBJTYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// 全てのオブジェクトの破棄
//=============================================================================
void CScene::ReleaseAll(void)
{
	// PRIORITY_MAXの数分
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// MAX_SCENEの数分
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// m_apSceneがNULLじゃなかったら
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// nCntPriorityが9じゃなかったら
				if (nCntPriority != 9)
				{
					// 2Dポリゴンの終了処理
					m_apScene[nCntPriority][nCntScene]->Uninit();
				}
			}
		}
	}
}

//=============================================================================
// 全てのオブジェクトの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	// PRIORITY_MAXの数分
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// MAX_SCENEの数分
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// m_apSceneがNULLじゃなかったら
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// 2Dポリゴンの更新処理
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
// 全てのオブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	// PRIORITY_MAXの数分
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// MAX_SCENEの数分
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// m_apSceneがNULLじゃなかったら
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// 2Dポリゴンの描画処理
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

//=============================================================================
// 全てのオブジェクトの設定処理
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	// メンバへ情報を渡す
	m_objType = objType;
}

//=============================================================================
// オブジェクトの種類の取得処理
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	// メンバを戻り値へ返す
	return m_objType;
}

//=============================================================================
// オブジェクトの取得処理
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nIndex)
{
	// ポインタ配列を戻り値へ返す
	return m_apScene[nPriority][nIndex];
}

//=============================================================================
// オブジェクトの破棄
//=============================================================================
void CScene::Release(void)
{
	// m_apSceneがNULLじゃなかったら
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		// インスタンスの破棄
		int nID = m_nID;
		
		// メンバの情報を渡す
		int nPriority = m_nPriority;

		// ポインタ配列を解放する
		delete m_apScene[nPriority][nID];

		// m_apSceneをNULLにする
		m_apScene[nPriority][nID] = NULL;

		// m_nNumAllを減算する
		m_nNumAll--;
	}
}