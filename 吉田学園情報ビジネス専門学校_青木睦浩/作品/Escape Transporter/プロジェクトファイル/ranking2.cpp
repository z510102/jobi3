//=============================================================================
//
// ���U���g�i�����L���O�j�̏��� [result.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ranking2.h"
#include"keyboard.h"
#include"manager.h"
#include"score.h"
#include"fade.h"
#include"time.h"
#include"bg.h"
#include"sound.h"
#include"rankingdata.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CRankingData *CRanking2::m_pRanking = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking2::CRanking2()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking2::~CRanking2()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking2::Init(void)
{
	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 38);

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_RESULT, 0.8f);

	// �����L���O�̐���
	CRankingData::Create(D3DXVECTOR3(SCREEN_CENTER_X + 50.0f, 180.0f, 0.0f), D3DXVECTOR3(45.0f, 47.0f, 0.0f), false);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRanking2::Uninit(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_RESULT);
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRanking2::Update(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �^�C�g���s��
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (m_fade == false)
		{
			pFade->SetFade(CManager::MODE_TITLE);
			m_fade = true;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRanking2::Draw(void)
{
}

//=============================================================================
// ���U���g�̐���
//=============================================================================
CRanking2 * CRanking2::Create(void)
{
	//���U���g�̃C���X�^���X����
	CRanking2 *pRanking = new CRanking2;

	//���U���g�̏���
	if (pRanking != NULL)
	{
		pRanking->Init();
	}
	return pRanking;
}

//=============================================================================
// �����L���O�擾
//=============================================================================
CRankingData * CRanking2::GetRanking(void)
{
	return m_pRanking;
}

