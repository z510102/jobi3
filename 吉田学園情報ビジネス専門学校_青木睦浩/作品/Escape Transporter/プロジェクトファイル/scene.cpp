//=============================================================================
//
// オブジェクトクラス [scene.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CScene *CScene::m_apTop[PRIORITY_MAX] = {};		// 先頭オブジェクトのポインタ
CScene *CScene::m_apCur[PRIORITY_MAX] = {};		// 現在(一番後ろ)のオブジェクトのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	// 死亡フラグが立っていない
	m_bDeath = false;

	m_nPriority = nPriority;

	if (m_apCur[m_nPriority] == NULL &&
		m_apTop[m_nPriority] == NULL)		// 現在のオブジェクトがあるとき
	{
		m_apTop[m_nPriority] = this;
		m_apCur[m_nPriority] = this;
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	else									// 現在のオブジェクトがないとき
	{
		m_pPrev = m_apCur[m_nPriority];
		m_apCur[m_nPriority]->m_pNext = this;
		m_apCur[m_nPriority] = this;
		m_pNext = NULL;
	}

	// オブジェクトの種類をクリア
	m_objType = OBJTYPE_NONE;

}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (m_apTop[nCntPriority] == this && m_apCur[nCntPriority] == this)	/* オブジェクトのポインタが一つだけ */
		{
			// 先頭も一番後ろも自分しかいないから全て無くなる
			m_apTop[nCntPriority] = NULL;
			m_apCur[nCntPriority] = NULL;
			m_pNext = NULL;
			m_pPrev = NULL;
		}
		else if (m_apTop[nCntPriority] == this)				/* 先頭オブジェクトのポインタ */
		{
			// 先頭が無くなるから次のオブジェクトを先頭オブジェクトにする
			m_apTop[nCntPriority] = m_pNext;

			// 先頭オブジェクトが無くなったことを教える
			this->m_apCur[nCntPriority]->m_pNext = NULL;
		}
		else if (m_apCur[nCntPriority] == this)				/* 現在のオブジェクトのポインタ */
		{
			// 一番後ろが無くなるから前のオブジェクトを一番後ろのオブジェクトにする
			m_apCur[nCntPriority] = m_pPrev;

			// 一番後ろのオブジェクトが無くなったことを教える
			this->m_pPrev->m_pNext = NULL;
		}
		else									/* 前後のオブジェクトの間にあるオブジェクト */
		{
			if (m_pNext != NULL)
			{
				// 次のオブジェクトは一つ前のオブジェクトが前のオブジェクトになる
				m_pNext->m_pPrev = this->m_pPrev;
			}
			if (m_pPrev != NULL)
			{
				// 前のオブジェクトは一つ後のオブジェクトが後ろのオブジェクトになる
				m_pPrev->m_pNext = this->m_pNext;
			}
		}
	}
}
//=============================================================================
// 全てのオブジェクトの破棄
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// 先頭オブジェクトのポインタを取得
		CScene *pScene = m_apTop[nCntPriority];

		// pSceneがNULLじゃなかったら繰り返す
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			if (nCntPriority != PRIORITY_FADE)
			{
				delete pScene;
				pScene = NULL;
			}

			// 次のオブジェクトのポインタを取得
			pScene = pSceneNext;
		}
	}
}
//=============================================================================
// 全てのオブジェクトの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// 先頭オブジェクトのポインタを取得
		CScene *pScene = m_apTop[nCntPriority];

		// pSceneがNULLじゃなかったら繰り返す
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;
			pScene->Update();

			if (pScene->m_bDeath == true)
			{
				delete pScene;
				pScene = NULL;
			}

			pScene = pSceneNext;
		}
	}
}
//=============================================================================
// 全てのオブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// 先頭オブジェクトのポインタを取得
		CScene *pScene = m_apTop[nCntPriority];

		// pSceneがNULLじゃなかったら繰り返す
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}

}
//=============================================================================
// オブジェクトの種類を設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}
//=============================================================================
// オブジェクトの種類を取得
//=============================================================================
CScene::OBJTYPE CScene::GetobjType(void)
{
	return m_objType;
}
//=============================================================================
// オブジェクトを取得
//=============================================================================
CScene *CScene::GetScene(int nPriority)
{
	return m_apTop[nPriority];
}
//=============================================================================
// オブジェクトの破棄
//=============================================================================
void CScene::Release(void)
{
	m_bDeath = true;
}