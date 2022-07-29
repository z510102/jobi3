//=============================================================================
//
// �^�C������ [time.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "time.h"
#include "manager.h"
#include "game.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime(int nPriority) : CScene(nPriority)
{
	// �ϐ����N���A
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	m_nTime = 0;
	m_nCntTimer = 0;
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_bUse = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// �^�C���̐���
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	// �|�C���^
	CTime *pNumber;

	// ���������m��
	pNumber = new CTime(PRIORITY_NUMBER);

	if (pNumber != NULL)
	{
		// �����o�֏���n��
		pNumber->m_size = D3DXVECTOR2(30, 40);

		// Init��
		pNumber->Init(pos);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pNumber;
}

//=============================================================================
// �^�C���̏���������
//=============================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos)
{
	// MAX_TIME�̐���
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// �i���o�[�𐶐�
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}

	// �^�C����ݒ�
	m_nTime = 180;

	return S_OK;
}

//=============================================================================
// �^�C���̏I������
//=============================================================================
void CTime::Uninit(void)
{
	// MAX_TIME�̐���
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;

			// �����������
			delete m_apNumber[nCnt];
		}
	}

	// �I�u�W�F�N�g�̔j����
	Release();
}

//=============================================================================
// �^�C���̍X�V����
//=============================================================================
void CTime::Update(void)
{
	// ���������Z���ꂽ�X�R�A���v�Z����
	m_apNumber[0]->SetNumber(m_nTime / (int)pow(10, 2));
	m_apNumber[1]->SetNumber(m_nTime % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[2]->SetNumber(m_nTime % (int)pow(10, 1));

	// �^�C�}�[�̃J�E���g�����Z
	m_nCntTimer++;

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �^�C�}�[�̃J�E���g��70�ȏ�ɂȂ�����
	if (m_nCntTimer >= 70)
	{
		// �^�C�����P�b���炷
		m_nTime--;

		// �^�C�}�[�̃J�E���g���O�ɖ߂�
		m_nCntTimer = 0;
	}

	//�^�C����30�ȉ��̏ꍇ
	if (m_nTime <= 30)
	{
		// �F��ݒ�
		m_apNumber[0]->SetColor(255, 0, 0, 255);
		m_apNumber[1]->SetColor(255, 0, 0, 255);
		m_apNumber[2]->SetColor(255, 0, 0, 255);
	}

	// �^�C����31�ȏ�̏ꍇ
	if (m_nTime >= 31)
	{
		// �F��ݒ�
		m_apNumber[0]->SetColor(255, 255, 255, 255);
		m_apNumber[1]->SetColor(255, 255, 255, 255);
		m_apNumber[2]->SetColor(255, 255, 255, 255);
	}

	//�^�C����0�ȉ����g�p���Ă���ꍇ
	if (m_nTime <= 0 && m_bUse == true)
	{
		// �Q�[���N���A������
		CGame *pGame = NULL;
		pGame->Clear();

		// �g�p���Ă��Ȃ��悤�ɂ���
		m_bUse = false;
	}

	// �g�p���Ă��Ȃ��ꍇ
	else if (m_bUse == false)
	{
		// 0�Œ�~����
		m_nTime = 0;

		// �i���o�[��0�ŌŒ肷��
		m_apNumber[0]->SetNumber(0);
		m_apNumber[1]->SetNumber(0);
		m_apNumber[2]->SetNumber(0);
	}
}

//=============================================================================
// �^�C���̕`�揈��
//=============================================================================
void CTime::Draw(void)
{
	// MAX_TIME�̐���
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// �i���o�[�̕`�揈����
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// �^�C���̐ݒ菈��
//=============================================================================
void CTime::SetTime(int nScore)
{
	// �����������o�֓n��
	m_nTime = nScore;

	/*for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
	m_apNumber[nCnt]->SetNumber();
	}*/
}

//=============================================================================
// �^�C���̉��Z����
//=============================================================================
void CTime::AddTime(int nValue)
{
	// �����o�ƈ����𑫂��ă����o�֓n��
	m_nTime += nValue;
}

//=============================================================================
// �^�C���̎擾����
//=============================================================================
int CTime::GetTime(void)
{
	// �^�C����߂�l�֕Ԃ�
	return m_nTime;
}