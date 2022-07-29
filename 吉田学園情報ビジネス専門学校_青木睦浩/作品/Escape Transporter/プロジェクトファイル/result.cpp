//=============================================================================
//
// ���U���g�̏��� [result.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "result.h"
#include"keyboard.h"
#include"manager.h"
#include"score.h"
#include"fade.h"
#include"time.h"
#include"sound.h"
#include"game.h"
#include"bg.h"
#include"ranking.h"
#include "ui.h"
//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScore *CResult::m_pScore = NULL;
CTime *CResult::m_pTime = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_dwCurrentTime = 0;
	// ���݂̎��Ԃ��擾
	m_dwExecLastTime = timeGetTime();
	m_fade = false;
	m_bflag1 = false;
	m_bflag2 = false;
	m_bflag3 = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 24);


	// ����̎��Ԃ����[�h
	FILE *pFile;
	//���[�h����
	pFile = fopen(FILE_TIME, "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%d\n", &m_nNewdata);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_RESULT, 0.5f);
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	//�t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	m_dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾


	// ���Ԍo�ߏ����i1�b�Ō��炷�j
	if ((m_dwCurrentTime - m_dwExecLastTime) >= 400)
	{
		// ����̎��Ԃ𐶐�
		m_pTime = CTime::Create(D3DXVECTOR3(NOWTIME_X, NOWTIME_Y, 0.0f), D3DXVECTOR3(NOWTIME_WIDTH, NOWTIME_HEIGHT, 0.0f), m_nNewdata, true);
		if (m_bflag2 == false)
		{
			pSound->Play(pSound->SOUND_LABEL_TAIKODON);
			pSound->SetVolume(pSound->SOUND_LABEL_TAIKODON, 2.0f);
			m_bflag2 = true;
		}
	}

	if ((m_dwCurrentTime - m_dwExecLastTime) >= 1200)
	{
		if (m_nNewdata == 0)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_GRANK);
		}
		else if (m_nNewdata <= 5 && m_nNewdata > 0)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_FRANK);
		}
		else if (m_nNewdata <= 10 && m_nNewdata > 5)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_ERANK);
		}
		else if (m_nNewdata <= 15 && m_nNewdata > 10)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_DRANK);
		}
		else if (m_nNewdata <= 20 && m_nNewdata > 15)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_CRANK);

		}
		else if (m_nNewdata <= 25 && m_nNewdata > 20)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_BRANK);

		}
		else if (m_nNewdata <= 20 && m_nNewdata > 25)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_ARANK);
		}
		else if (m_nNewdata > 30)
		{
			CUI::Create(D3DXVECTOR3(RANK_X, RANK_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RANK_WIDTH, RANK_HEIGHT, 0.0f), CTexture::TEXTURETYPE_SRANK);
		}
		if (m_bflag3 == false)
		{
			pSound->Play(pSound->SOUND_LABEL_TADA);
			pSound->SetVolume(pSound->SOUND_LABEL_TADA, 1.0f);
			m_bflag3 = true;
		}
	}


	// �����L���O�s��
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (m_bflag3 == true)
		{
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RANKING);
				pSound->Stop(pSound->SOUND_LABEL_TADA);
				m_fade = true;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// ���U���g�̐���
//=============================================================================
CResult * CResult::Create(void)
{
	//���U���g�̃C���X�^���X����
	CResult *pResult = new CResult;

	//���U���g�̏���
	if (pResult != NULL)
	{
		pResult->Init();
	}
	return pResult;
}
