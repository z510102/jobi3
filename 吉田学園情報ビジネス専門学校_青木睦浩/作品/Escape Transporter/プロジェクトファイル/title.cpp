//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "title.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"sound.h"
#include"ui.h"
#include"bg.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_dwCurrentTime = 0;
	// ���݂̎������擾
	m_dwExecLastTime = timeGetTime();
	m_fade = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_TITLE);
	pSound->SetVolume(pSound->SOUND_LABEL_TITLE, 0.5f);

	// �w�i���
	CBg::Create(D3DXVECTOR3(BG_X, BG_Y, 0.0f), D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f), CTexture::TEXTURETYPE_TITLEBG);

	// UI�o��
	CUI::Create(D3DXVECTOR3(PUSH_X, PUSH_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(PUSH_WIDTH, PUSH_HEIGHT, 0.0f), CTexture::TEXTURETYPE_PUSH);
	CUI::Create(D3DXVECTOR3(TITLE_X, TITLE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f), CTexture::TEXTURETYPE_NAME);
	CUI::Create(D3DXVECTOR3(HUMAN_X, HUMAN_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(HUMAN_WIDTH, HUMAN_HEIGHT, 0.0f), CTexture::TEXTURETYPE_WITCH);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_TITLE);
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ���݂̎��Ԃ��擾
	m_dwCurrentTime = timeGetTime();

	//// �\�b�o�߂�
	//if ((m_dwCurrentTime - m_dwExecLastTime) >= 10000)
	//{
	//	if (m_fade == false)
	//	{
	//		// �����L���O��ʂ�
	//		pFade->SetFade(CManager::MODE_RANKING);
	//		m_fade = true;
	//		// �����L���O���\�b�Ŗ߂�悤�ɂ������񂾂��ǋ�풆
	//	}
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// �^�C�g���̐���
//=============================================================================
CTitle * CTitle::Create(void)
{
	// �^�C�g���̃C���X�^���X����
	CTitle *pTitle = new CTitle;

	// �^�C�g���̏���
	if (pTitle != NULL)
	{
		pTitle->Init();
	}
	return pTitle;
}
