//=============================================================================
//
// UI�̏��� [ui.cpp]
// Author : �쑺�D�l
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"
#include"fade.h"
#include"keyboard.h"
#include"time.h"
#include"game.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUI::CUI(int nPriority) : CScene2D(nPriority)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Lifesize = D3DXVECTOR3(LIFE_WIDTH, LIFE_HEIGHT, 0.0f);
	m_type = CTexture::TEXTURETYPE_NAME;
	m_fPosU = 0.0f;
	m_fPosV = 0.0f;
	m_bBrinkFlag = false;
	m_bBrinkFlag2 = false;
	m_fade = false;
	m_bDisplay = false;

	// ���C�t�̏����ݒ�
	m_nLife = LIFE_MAX;
	m_dwCurrentTime = 0;
	m_dwExecLastTime = timeGetTime();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUI::~CUI()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUI::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUI::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CUI::Update(void)
{
	//UI�̑傫����ݒ�
	D3DXVECTOR3 pPos = GetPosition();

	// UI�̃T�C�Y��ݒ�
	D3DXVECTOR3 pSize = GetSize();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//�t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// ���Ԑ؂�̂Ƃ��̓X�R�A�����Ȃ��悤��
	CTime *pTime = CGame::GetTime();

	if (m_mode == CManager::MODE_GAME)
	{
		int nTime = pTime->GetTime();
	}

	CScene2D::Update();

	//�^�C�v���Ƃɓ������w��
	switch (m_type)
	{
	case CTexture::TEXTURETYPE_NAME:
		if (m_bBrinkFlag2 == false)
		{
			m_col.a = 0.0f;
		}
		m_col.a += 0.01f;
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			pPos.y = STOP_PUSH;
			m_col.a = 0.9f;
		}
		m_bBrinkFlag2 = true;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_bDisplay = true;
		}

		//�F�ݒ�
		SetColor(m_col);

		//���X�ɍ~��Ă�
		pPos.y += MOVE_PUSH;
		if (pPos.y >= STOP_PUSH)
		{
			//�^�񒆂Ŏ~�܂�
			pPos.y -= MOVE_PUSH;
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				if (m_fade == false)
				{
					if (m_bDisplay == true)
					{
						//�Q�[���s��
						pFade->SetFade(CManager::MODE_MENU);
						m_fade = true;
					}
				}
			}
		}
		break;
	case CTexture::TEXTURETYPE_PUSH:
		//�_�ł�����
		if (m_bBrinkFlag == false)
		{
			m_col.a -= 0.01f;
			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_bBrinkFlag = true;
			}
		}
		else
		{
			m_col.a += 0.01f;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_bBrinkFlag = false;
			}
		}

		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_WITCH:
		//����E���E�������Ƃ�
		pPos.x += MOVE_PICT;

		//�[�܂ōs�����烏�[�v
		if (pPos.x >= 1400.0f)
		{
			pPos.x = -70.0f;
		}
		break;
	case CTexture::TEXTURETYPE_HPHONTAI:

		if (pInputKeyboard->GetTrigger(DIK_L) == true)
		{
			AddLife(-10);
			m_Lifesize.x -= LIFE_DAMAGE;
			pPos.x += LIFE_DAMAGE;
		}
		if (m_nLife <= 0)
		{
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RESULT);
				m_fade = true;
				m_nLife = 0;
			}
		}
		break;

	default:
		break;
	}
	// HP�Q�[�W��������ȏ���
	if (m_type == CTexture::TEXTURETYPE_HPHONTAI)
	{
		SetTexPos(m_pos, m_size, m_Lifesize.x);
	}
	else
	{
		//�v���C���[�̈ʒu�ݒ�
		SetPosition(pPos, pSize);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ���C�t�̉��Z
//=============================================================================
void CUI::AddLife(int nValue)
{
	m_nLife += nValue;
}

//=============================================================================
// ���C�t�̎擾
//=============================================================================
int CUI::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// UI�̐���
//=============================================================================
CUI * CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, CTexture::TEXTURETYPE type)
{
	// UI�̃C���X�^���X����
	CUI *pUI = new CUI(PRIORITY_UI);

	// UI�̏���
	if (pUI != NULL)
	{
		pUI->m_type = type;
		pUI->m_pos = pos;
		pUI->m_size = size;
		pUI->Init();
		pUI->SetPosition(pos, size);
		pUI->SetSize(size);
		pUI->BindTexture(CManager::GetTexture()->SetTextureType(type));
	}
	return pUI;
}


