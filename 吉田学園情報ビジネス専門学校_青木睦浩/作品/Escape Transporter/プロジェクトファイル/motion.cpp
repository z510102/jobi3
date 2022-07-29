//=============================================================================
//
// モーションクラス [motion.h]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "motion.h"
#include "model.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CMotion::CMotion()
{
	// メンバ変数のクリア
}
//=============================================================================
// デストラクタ
//=============================================================================
CMotion::~CMotion()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMotion::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMotion::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CMotion::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMotion::Draw(void)
{

}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CMotion *CMotion::Create(void)
{
	CMotion *pMotion;
	pMotion = new CMotion;

	if (pMotion != NULL)
	{
		pMotion->Init();
	}

	return pMotion;
}
//=============================================================================
// モーション再生
//=============================================================================
void CMotion::PlayMotion(const int nNumModel, CModel **apModel, MOTION_TYPE& motiontype, MOTION_TYPE& motiontypelast)
{

	//*******************************************************
	//　位置と回転情報を計算するためのローカル変数
	//*******************************************************
	float fPosXDiff[MOTION_KEY_MAX];	// 位置情報Xの差分
	float fPosYDiff[MOTION_KEY_MAX];	// 位置情報Yの差分
	float fPosZDiff[MOTION_KEY_MAX];	// 位置情報Zの差分
	float fRotXDiff[MOTION_KEY_MAX];	// 回転情報Xの差分
	float fRotYDiff[MOTION_KEY_MAX];	// 回転情報Yの差分
	float fRotZDiff[MOTION_KEY_MAX];	// 回転情報Zの差分

	float fPosXAsk[MOTION_KEY_MAX];		// 求める値の位置X
	float fPosYAsk[MOTION_KEY_MAX];		// 求める値の位置Y
	float fPosZAsk[MOTION_KEY_MAX];		// 求める値の位置Z
	float fRotXAsk[MOTION_KEY_MAX];		// 求める値の回転X
	float fRotYAsk[MOTION_KEY_MAX];		// 求める値の回転Y
	float fRotZAsk[MOTION_KEY_MAX];		// 求める値の回転Z

	// モーションが変わったとき
	if (motiontypelast != motiontype)
	{
		m_nNumKey = 0;
	}

	// 現在のモーションタイプを保存
	motiontypelast = motiontype;

	// 最大のキーに進むまでの処理
	// 現在のモーションキーがモーションキーの最大数より小さいとき
	if (m_nNumKey < m_aMotionInfo[motiontype].nNumMaxKey - 1)
	{
		while (1)
		{
			// パーツ分ループさせる
			for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
			{
				// 位置の差分(次のキーと現在のキーの差分)
				fPosXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX;
				fPosYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY;
				fPosZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ;

				// 向きの差分(次のキーと現在のキーの差分)
				fRotXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX;
				fRotYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY;
				fRotZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ;

				// 求めた位置・向き = 現在の位置 + 差分 * ((floatでキャスト)モーションカウンター / (floatでキャスト)最大のフレーム)　＊float型で値を正確に取得するため
				fPosXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fPosYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fPosZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);

				fRotXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fRotYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fRotZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);

				// 求めた位置・向きを設定
				apModel[nCntModel]->SetPosition(D3DXVECTOR3(fPosXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fPosYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fPosZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
				apModel[nCntModel]->SetRotation(D3DXVECTOR3(fRotXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fRotYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fRotZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
			}

			// モーションカウンターを加算する
			m_nMotionCounter++;

			// モーションのフレーム最大数をフレームカウンターが越えたら
			if (m_nMotionCounter >= m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame)
			{
				m_nMotionCounter = 0;	// モーションカウンターを初期化

				// 次のキーに進む
				m_nNumKey++;
			}
			else
			{
				break;
			}
		}
	}

	// モーションループの処理
	// 現在のキーと最大のキーが同じとき
	if (m_nNumKey == m_aMotionInfo[motiontype].nNumMaxKey - 1)
	{
		// ループする場合
		if (m_aMotionInfo[motiontype].bLoop == true)
		{
			while (1)
			{

				for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
				{
					// 位置の差分(次のキーと現在のキーの差分)
					fPosXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fPosX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX;
					fPosYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fPosY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY;
					fPosZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fPosZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ;

					// 向きの差分(次のキーと現在のキーの差分)
					fRotXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fRotX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX;
					fRotYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fRotY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY;
					fRotZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fRotZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ;

					// 求める位置・向き = 現在の位置 + 差分 * ((floatでキャスト)モーションカウンター / (floatでキャスト)最大のフレーム)　＊float型で値を正確に取得するため
					fPosXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fPosYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY + fPosYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fPosZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ + fPosZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);

					fRotXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX + fRotXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fRotYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY + fRotYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fRotZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ + fRotZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);

					// 求めた位置・向きを設定
					apModel[nCntModel]->SetPosition(D3DXVECTOR3(fPosXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fPosYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fPosZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
					apModel[nCntModel]->SetRotation(D3DXVECTOR3(fRotXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fRotYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fRotZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
				}

				// モーションカウンターを1フレーム毎に加算
				m_nMotionCounter++;

				// モーションのフレーム最大数をフレームカウンターが越えたら
				if (m_nMotionCounter > m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame)
				{
					// モーションカウンターを初期化
					m_nMotionCounter = 0;

					// キー情報をループさせる
					m_nNumKey = 0;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			while (1)
			{
				for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
				{
					// 位置の差分
					fPosXDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX;
					fPosYDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY;
					fPosZDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ;

					// 向きの差分
					fRotXDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX;
					fRotYDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY;
					fRotZDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ;

					// 求めた位置・向き = 現在の位置 + 差分 * ((floatでキャスト)モーションカウンター / (floatでキャスト)最大のフレーム)
					fPosXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fPosYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosY + fPosYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fPosZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosZ + fPosZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);

					fRotXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotX + fRotXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fRotYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotY + fRotYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fRotZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotZ + fRotZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);

					// 求めた位置・向きを設定
					apModel[nCntModel]->SetPosition(D3DXVECTOR3(fPosXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fPosYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fPosZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
					apModel[nCntModel]->SetRotation(D3DXVECTOR3(fRotXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fRotYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fRotZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
				}

				// モーションカウンターを加算
				m_nMotionCounter++;

				// モーションのフレーム最大数をフレームカウンターが越えたら
				if (m_nMotionCounter >= m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey].nFrame)
				{
					// モーションカウンターを初期化
					m_nMotionCounter = 0;

					// 次のキーに進む
					m_nNumKey++;

					// キー情報をニュートラルモーションに変更
					motiontype = MOTION_NEUTRAL;
				}
				else
				{
					break;
				}
			}
		}
	}

}
//=============================================================================
// モーションファイルの読み込み
//=============================================================================
void CMotion::LoadMotion(const char *pMotionFileName)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	int nLoop = 0;			// モーションループ
	int nNumKey = 0;		// キーの総数
	int nCntKey = 0;		// キー数
	int nCntParts = 0;		// パーツ数
	int nCntMotion = 0;		// モーション数
	bool bMotionSet = false;	// モーションのセット
	bool bKeySet = false;	// モーションキーのセット
	bool bKey = false;		// キーパーツのセット
	D3DXVECTOR3 pos;		// パーツの位置
	D3DXVECTOR3 rot;		// パーツの向き
	char aFile[256];		// 文字列読み込み
	FILE *pFile = fopen(pMotionFileName, "r");	// スクリプトファイル読み込み

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "MOTIONSET") == 0)
			{
				bMotionSet = true;
			}
			if (bMotionSet == true)
			{
				if (strcmp(&aFile[0], "LOOP") == 0)
				{
					// モーションループの設定
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);

					if (nLoop == 0)
					{
						m_aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0)
				{
					// モーションキーの総数
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNumMaxKey);
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)
				{
					// モーションキーのセット
					bKeySet = true;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)
				{
					// モーションキーのセット終了
					bKeySet = false;
					nCntKey++;
				}
				if (bKeySet == true)
				{
					if (strcmp(&aFile[0], "FRAME") == 0)
					{
						// キーフレームの設定
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "KEY") == 0)
					{
						// キーパーツのセット
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)
					{
						// キーパーツのセット終了
						bKey = false;
						nCntParts++;
					}
					if (bKey == true)
					{
						// 位置
						if (strcmp(&aFile[0], "POS") == 0)
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);

						}
						// 向き
						if (strcmp(&aFile[0], "ROT") == 0)
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
						}
					}
				}
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)
			{
				// モーションタイプの加算
				nCntMotion++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// 読み込み終了
				break;
			}
		}
		fclose(pFile);
	}

}
