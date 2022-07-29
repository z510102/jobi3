//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "ranking.h"
#include "score.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScore *CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	// �ϐ����N���A
	memset(&m_apScore[0], 0, sizeof(CNumber));
	m_nScore = 0;
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// �X�R�A�̐���
//=============================================================================
CRanking *CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �|�C���^
	CRanking *pRanking;

	// ���������m��
	pRanking = new CRanking(PRIORITY_NUMBER);

	if (pRanking != NULL)
	{
		// �����o�֏���n��
		pRanking->m_size = size;

		// Init��
		pRanking->Init(pos);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pRanking;
}

//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos)
{
	// MAX_RANKING�̐���
	for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
	{
		// �����X�R�A���쐬
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x , pos.y + m_size.y * nCnt, 0.0f), D3DXVECTOR2(50, 60));
	}

	// �t�@�C���̃|�C���^
	FILE *pFile;

	// �t�@�C�����J���i���[�h�j
	pFile = fopen("data/SAVE DATA/ranking.txt", "r");

	if (pFile != NULL)
	{
		// MAX_RANKING�̐���
		for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
		{
			// �ǂݍ���
			fscanf(pFile, "%d", &m_aScore[nCnt]);
		}

		// �t�@�C�������
		fclose(pFile);
	}

	// �t�@�C�����J���i���[�h�j
	pFile = fopen("data/SAVE DATA/score.txt", "r");

	if (pFile != NULL)
	{
		// ���݂̃X�R�A��ǂݍ���
		fscanf(pFile, "%d", &m_nScore);

		// �t�@�C�������
		fclose(pFile);
	}

	// ���݂̃X�R�A��n��
	m_aScore[MAX_RANKING - 1] = m_nScore;

	// �X�R�A����בւ�
	// MAX_RANKING�̐���
	for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
	{
		for (int nCount = 0; nCount < MAX_RANKING - 1; nCount++)
		{
			// �Ō�̃X�R�A�����̃X�R�A��菬�����ꍇ
			if (m_aScore[nCount] < m_aScore[nCount + 1])
			{
				// �ۑ�
				int nScore = m_aScore[nCount];

				// ���̃X�R�A�����݂̃X�R�A��
				m_aScore[nCount] = m_aScore[nCount + 1];

				// �߂�
				m_aScore[nCount + 1] = nScore;
			}
		}
	}

	// MAX_RANKING�̐���
	for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
	{
		// ���ѕς�����̃X�R�A��ݒ�
		m_apScore[nCnt]->SetScore(m_aScore[nCnt]);
	}

	// �X�R�A�̔z��̍Ō��0�ɂ���
	m_aScore[MAX_RANKING - 1] = 0;

	// �t�@�C�����J���i�������݁j
	pFile = fopen("data/SAVE DATA/ranking.txt", "w");

	if (pFile != NULL)
	{
		// MAX_RANKING�̐���
		for (int nCnt = 0; nCnt < MAX_RANKING - 1; nCnt++)
		{
			// txt�ɐV�����������݁i�㏑���j
			fprintf(pFile, "%d\n", m_aScore[nCnt]);
		}

		// �t�@�C�������
		fclose(pFile);
	}

	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CRanking::Uninit(void)
{
	
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CRanking::Update(void)
{
	
}

//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CRanking::Draw(void)
{
	
}