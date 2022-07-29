//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "menu.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"ui.h"
#include"bg.h"
#include"sound.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CUI *CMenu::m_pUI[12] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMenu::CMenu()
{
	m_fade = false;
	// ������ԁiStart��I��ł����ԁj
	m_nCntSelect = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMenu::~CMenu()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMenu::Init(void)
{
	// �w�i���
	CBg::Create(D3DXVECTOR3(BG_X, BG_Y, 0.0f), D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f), CTexture::TEXTURETYPE_MENUBG);

	// UI�o��
	m_pUI[0] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y - 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PLAY);
	m_pUI[1] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y + 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_HELP);
	m_pUI[2] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y + 120.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_RANK);
	m_pUI[3] = CUI::Create(D3DXVECTOR3(UITEXT_X, SCREEN_CENTER_Y + 240.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UITEXT_WIDTH, UITEXT_HEIGHT, 0.0f), CTexture::TEXTURETYPE_BACK);
	m_pUI[4] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH, UIICON_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PLAYICON);
	m_pUI[5] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH, UIICON_HEIGHT, 0.0f), CTexture::TEXTURETYPE_HELPICON);
	m_pUI[6] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH, UIICON_HEIGHT, 0.0f), CTexture::TEXTURETYPE_RANKICON);
	m_pUI[7] = CUI::Create(D3DXVECTOR3(UIICON_X, UIICON_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIICON_WIDTH - 50.0f, UIICON_HEIGHT - 100.0f, 0.0f), CTexture::TEXTURETYPE_BACKICON);
	m_pUI[8] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PLAYTEXT);
	m_pUI[9] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_HELPTEXT);
	m_pUI[10] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_RANKTEXT);
	m_pUI[11] = CUI::Create(D3DXVECTOR3(UIICON_X, UIINFO_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(UIINFO_WIDTH, UIINFO_HEIGHT, 0.0f), CTexture::TEXTURETYPE_BACKTEXT);


	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_MENU);
	pSound->SetVolume(pSound->SOUND_LABEL_MENU, 0.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMenu::Uninit(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_MENU);
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMenu::Update(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// UI�̐F�X�����iStart�̂Ƃ��ɂ�����o���ATutorial�̂Ƃ��ɂ�����o���c�j
	switch (m_nCntSelect)
	{
	case 0:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case 1:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case 2:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case 3:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[9]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[10]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pUI[11]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}

	// ���j���[�ړ��i���j
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true || pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_MOVE);
		pSound->SetVolume(pSound->SOUND_LABEL_MOVE, 0.5f);

		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_RANKING;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_PLAY;
			break;
		}
	}

	// ���j���[�ړ��i���j
	if (pInputKeyboard->GetTrigger(DIK_UP) == true || pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_MOVE);
		pSound->SetVolume(pSound->SOUND_LABEL_MOVE, 0.5f);
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_PLAY;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_RANKING;
			break;
		}
	}

	// ����
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_KETTEI);
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_GAME);
				m_fade = true;
			}
			break;
		case SELECT_TUTORIAL:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_TUTORIAL);
				m_fade = true;
			}
			break;
		case SELECT_RANKING:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RANKING2);
				m_fade = true;
			}
			break;
		case SELECT_QUIT:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_TITLE);
				m_fade = true;
			}
			break;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMenu::Draw(void)
{
}

//=============================================================================
// �^�C�g���̐���
//=============================================================================
CMenu * CMenu::Create(void)
{
	//���j���[�̃C���X�^���X����
	CMenu *pMenu = new CMenu;

	//���j���[�̏���
	if (pMenu != NULL)
	{
		pMenu->Init();
	}
	return pMenu;
}

