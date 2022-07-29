//=============================================================================
//
// �����L���O�̏��� [rankingdata.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "rankingdata.h"
#include"score.h"
#include"time.h"
#include"game.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CTime *CRankingData::m_pTime[MAX_RANKING] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRankingData::CRankingData(int nPriority) : CScene(nPriority)
{
	m_bFlag = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRankingData::~CRankingData()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRankingData::Init(void)
{
	//���[�h����
	FILE *pFile;

	pFile = fopen(RANKING_TEXT, "r");
	if (pFile != NULL)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			fscanf(pFile, "%d", &m_nTime[nCntRank]);
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	// ����̃X�R�A�����[�h
	int nNewdata;
	if (m_bFlag == true)
	{
		pFile = fopen(SCORE_TEXT, "r");
		if (pFile != NULL)
		{
			fscanf(pFile, "%d", &nNewdata);
		}
		else
		{
			printf("�t�@�C�����J���܂���ł���\n");
		}
		fclose(pFile);
	}
	if (m_bFlag == true)
	{
		m_nTime[MAX_RANKING - 1] = nNewdata;
	}
	// ����̃X�R�A�̕�������
	if (m_bFlag == true)
	{
		m_pNowTime = CTime::Create(D3DXVECTOR3(50.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(NUMBER_WIDTH, NUMBER_HEIGHT, 0.0f), nNewdata,true);
	}

	// ����ւ��ă����L���O�����
	for (int nCntRank = 0; nCntRank < MAX_RANKING - 1; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_RANKING - 1; nCntRank2++)
		{
			if (m_nTime[nCntRank2] < m_nTime[nCntRank2 + 1])
			{
				int nScore = m_nTime[nCntRank2];
				m_nTime[nCntRank2] = m_nTime[nCntRank2 + 1];
				m_nTime[nCntRank2 + 1] = nScore;
			}
		}
	}
	// �X�R�A�̕������𐶐�
	for (int nCntNum = 0; nCntNum < MAX_RANKING - 1; nCntNum++)
	{
		m_pTime[nCntNum] = CTime::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (100 * nCntNum), 0.0f), D3DXVECTOR3(NUMBER_WIDTH, NUMBER_HEIGHT, 0.0f), m_nTime[nCntNum], true);
	}


	//�Z�[�u����
	pFile = fopen(RANKING_TEXT, "w");
	if (pFile != NULL)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			fprintf(pFile, "%d\n", m_nTime[nCntRank]);
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	return S_OK;
}

void CRankingData::Uninit(void)
{
}

void CRankingData::Update(void)
{
}


void CRankingData::Draw(void)
{
}

CRankingData * CRankingData::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bFlag)
{
	//�����L���O�̃C���X�^���X����
	CRankingData *pRankingData = new CRankingData;

	//�����L���O�̏���
	if (pRankingData != NULL)
	{
		pRankingData->m_bFlag = bFlag;
		pRankingData->m_size = size;
		pRankingData->m_pos = pos;
		pRankingData->Init();
	}

	return pRankingData;
}