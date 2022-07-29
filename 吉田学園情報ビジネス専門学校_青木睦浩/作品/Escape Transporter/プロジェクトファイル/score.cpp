//=============================================================================
//
// �X�R�A�̏��� [score.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include "score.h"
#include "number.h"
#include"ui.h"
#include"keyboard.h"
#include<stdio.h>

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	m_nScore = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CScore::Init(void)
{
	// �����̐���
	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		m_apNumber[nCntNum] = CNumber::Create(D3DXVECTOR3(m_pos.x + m_size.x + 50 * nCntNum, m_pos.y, 0.0f), D3DXVECTOR3(m_size.x, m_size.y, 0.0f), CTexture::TEXTURETYPE_SCORE);
	}
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			m_apNumber[nCntNum]->Uninit();
			delete m_apNumber[nCntNum];
			m_apNumber[nCntNum] = NULL;
		}
	}
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CScore::Update(void)
{
	m_apNumber[0]->SetNumber(m_nScore % (int)pow(10, 5) / (int)pow(10, 4));
	m_apNumber[1]->SetNumber(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apNumber[2]->SetNumber(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[3]->SetNumber(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[4]->SetNumber(m_nScore % (int)pow(10, 1));

	//�L�[�{�[�h�̎擾�i���͂��Ă邾���j
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

}

//=============================================================================
//�`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
//�X�R�A�̐ݒ�
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		m_apNumber[nCntNum]->SetNumber(m_nScore);
	}
}

//=============================================================================
//�X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//=============================================================================
//�X�R�A�̎擾
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
//�X�R�A�̐���
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�X�R�A�̃C���X�^���X����
	CScore *pScore = new CScore;

	//�X�R�A�̏���
	if (pScore != NULL)
	{
		pScore->m_pos = pos;
		pScore->m_size = size;
		pScore->Init();
	}

	return pScore;
}
