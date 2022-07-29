//=============================================================================
//
// �n�C�X�R�A���� [high_score.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "high_score.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHighScore::CHighScore(int nPriority) : CScene(nPriority)
{
	// �ϐ����N���A
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	m_nScore = 0;
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nHighScore = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHighScore::~CHighScore()
{

}

//=============================================================================
// �n�C�X�R�A�̐���
//=============================================================================
CHighScore *CHighScore::Create(D3DXVECTOR3 pos)
{
	// �|�C���^
	CHighScore *pHighScore;

	// ���������m��
	pHighScore = new CHighScore(PRIORITY_NUMBER);

	if (pHighScore != NULL)
	{
		// �����o�֏���n��
		pHighScore->m_size = D3DXVECTOR2(30, 40);

		// Init��
		pHighScore->Init(pos);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pHighScore;
}

//=============================================================================
// �n�C�X�R�A�̏���������
//=============================================================================
HRESULT CHighScore::Init(D3DXVECTOR3 pos)
{
	// MAX_HIGH_SCORE�̐���
	for (int nCnt = 0; nCnt < MAX_HIGH_SCORE; nCnt++)
	{
		// �i���o�[�𐶐�
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}

	// �t�@�C���|�C���^
	FILE *pFile;

	// �t�@�C�����J���i���[�h�j
	pFile = fopen("data/SAVE DATA/ranking.txt", "r");

	if (pFile != NULL)
	{
		// ���l��ǂݍ���
		fscanf(pFile, "%d", &m_nHighScore);

		// �t�@�C�������
		fclose(pFile);
	}

	// �����o�֏���n��
	m_nScore = m_nHighScore;

	return S_OK;
}

//=============================================================================
// �n�C�X�R�A�̏I������
//=============================================================================
void CHighScore::Uninit(void)
{
	// MAX_HIGH_SCORE�̐���
	for (int nCnt = 0; nCnt < MAX_HIGH_SCORE; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (m_apNumber[nCnt] != NULL)
		{
			// �i���o�[�̏I��������
			m_apNumber[nCnt]->Uninit();

			// NULL�ɂ���
			m_apNumber[nCnt] = NULL;

			// �����������
			delete m_apNumber[nCnt];
		}
	}

	// �I�u�W�F�N�g�̔j��������
	Release();
}

//=============================================================================
// �n�C�X�R�A�̍X�V����
//=============================================================================
void CHighScore::Update(void)
{
	//���������Z���ꂽ�X�R�A���v�Z����
	m_apNumber[0]->SetNumber(m_nScore / (int)pow(10, 4));
	m_apNumber[1]->SetNumber(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apNumber[2]->SetNumber(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[3]->SetNumber(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[4]->SetNumber(m_nScore % (int)pow(10, 1));
}

//=============================================================================
// �n�C�X�R�A�̕`�揈��
//=============================================================================
void CHighScore::Draw(void)
{
	// MAX_HIGH_SCORE�̐���
	for (int nCnt = 0; nCnt < MAX_HIGH_SCORE; nCnt++)
	{
		// �i���o�[��`��
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// �n�C�X�R�A�̐ݒ菈��
//=============================================================================
void CHighScore::SetScore(int nScore)
{
	// �����������o�֓n��
	m_nScore = nScore;
}

//=============================================================================
// �n�C�X�R�A�̉��Z����
//=============================================================================
void CHighScore::AddScore(int nValue)
{
	// �����o�ƈ����𑫂��ă����o�֓n��
	m_nScore += nValue;
}

//=============================================================================
// �n�C�X�R�A�̎擾����
//=============================================================================
int CHighScore::GetScore(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nScore;
}