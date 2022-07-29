//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "score.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	// �ϐ����N���A
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	m_nScore = 0;
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// �X�R�A�̐���
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �|�C���^
	CScore *pNumber;

	// ���������m��
	pNumber = new CScore(PRIORITY_NUMBER);

	if (pNumber != NULL)
	{
		// �����o�֏���n��
		pNumber->m_size = size;

		// Init��
		pNumber->Init(pos);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pNumber;
}

//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	// MAX_SCORE�̐���
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// �i���o�[�𐶐�
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}

	// �X�R�A��ݒ�
	m_nScore = 0;

	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CScore::Uninit(void)
{
	// �t�@�C���̃|�C���^
	FILE *pFile;

	// �t�@�C�����J���i�������ށj
	pFile = fopen("data/SAVE DATA/score.txt", "w");

	if (pFile != NULL)
	{
		// txt�ɃX�R�A�̐��l����������
		fprintf(pFile, "%d", m_nScore);

		// �t�@�C�������
		fclose(pFile);
	}

	// MAX_SCORE�̐���
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;

			delete m_apNumber[nCnt];
		}
	}

	// // �I�u�W�F�N�g�̔j����
	Release();
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CScore::Update(void)
{
	//���������Z���ꂽ�X�R�A���v�Z����
	m_apNumber[0]->SetNumber(m_nScore / (int)pow(10, 4));
	m_apNumber[1]->SetNumber(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apNumber[2]->SetNumber(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[3]->SetNumber(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[4]->SetNumber(m_nScore % (int)pow(10, 1));
}

//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CScore::Draw(void)
{
	// MAX_SCORE�̐���
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// �i���o�[�̕`�揈����
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// �X�R�A�̐ݒ菈��
//=============================================================================
void CScore::SetScore(int nScore)
{
	// �����������o�֓n��
	m_nScore = nScore;

	/*for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
	m_apNumber[nCnt]->SetNumber();
	}*/
}

//=============================================================================
// �X�R�A�̉��Z����
//=============================================================================
void CScore::AddScore(int nValue)
{
	// �����o�ƈ����𑫂��ă����o�֓n��
	m_nScore += nValue;
}

//=============================================================================
// �X�R�A�̎擾����
//=============================================================================
int CScore::GetScore(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nScore;
}