//=============================================================================
//
// ���U���g�i�����L���O�j�̏��� [result.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ranking.h"
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
CRankingData *CRanking::m_pRanking = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 6);
	
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_RESULT, 0.8f);

	// �����L���O�̐���
	CRankingData::Create(D3DXVECTOR3(SCREEN_CENTER_X + 150.0f, 180.0f, 0.0f), D3DXVECTOR3(45.0f, 47.0f, 0.0f), true);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_RESULT);
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRanking::Update(void)
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
void CRanking::Draw(void)
{
}

//=============================================================================
// ���U���g�̐���
//=============================================================================
CRanking * CRanking::Create(void)
{
	//���U���g�̃C���X�^���X����
	CRanking *pRanking = new CRanking;

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
CRankingData * CRanking::GetRanking(void)
{
	return m_pRanking;
}

