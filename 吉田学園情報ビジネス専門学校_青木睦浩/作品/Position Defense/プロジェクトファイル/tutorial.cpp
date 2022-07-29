//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "tutorial.h"
#include "input_keyboard.h"
#include "fade.h"
#include "input_gamepad.h"
#include "sound.h"
#include "UI.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//=============================================================================
// �^�C�g���̓ǂݍ���
//=============================================================================
HRESULT CTutorial::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							 // �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/tutorial_bg.png",	 // �ǂݍ��ރt�@�C����
							  &m_pTexture);						 // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// �^�C�g���̔j��
//=============================================================================
void CTutorial::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �^�C�g���̐���
//=============================================================================
CTutorial *CTutorial::Create(void)
{
	// �|�C���^
	CTutorial *pTitle;

	// ���������m��
	pTitle = new CTutorial;

	if (pTitle != NULL)
	{
		// Init��
		pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pTitle;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	// �ϐ����N���A
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
{
	// UI�̃e�N�X�`���ǂݍ��݂�
	CUI::Load();

	// ����
	m_pScene2D = new CScene2D (PRIORITY_SCREEN);

	if (m_pScene2D != NULL)
	{
		// ���ꂼ��̏�����
		m_pScene2D->Init(pos);
		m_pScene2D->SetSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_pScene2D->BindTexture(m_pTexture);
	}

	// UI�̎擾
	CUI *pUI = CGame::GetUI();

	// UI�̐���
	pUI = CUI::Create(D3DXVECTOR3(640, 50, 0),   D3DXVECTOR2(200, 50),  CUI::TYPE_TUTORIAL);
	pUI = CUI::Create(D3DXVECTOR3(640, 400, 0),  D3DXVECTOR2(420, 280), CUI::TYPE_TUTORIAL_ANIMATION);
	pUI = CUI::Create(D3DXVECTOR3(1180, 650, 0), D3DXVECTOR2(100, 50),  CUI::TYPE_SWITCHING);

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// ����炷
	pSound->PlaySound(pSound->SOUND_LABEL_TUTORIAL_BGM);

	// ���ʂ𒲐�
	pSound->SoundVolume(CSound::SOUND_LABEL_TUTORIAL_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// UI�̃e�N�X�`���j����
	CUI::Unload();

	// �w�i�̔j��
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();

		m_pScene2D = NULL;
	}

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �T�E���h�̒�~
	pSound->StopSound();

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTutorial::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// Enter�L�[����START�{�^������������
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_START))
	{
		// �Q�[����ʂ�
		pFade->SetFade(CManager::MODE_GAME);

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);
	}

	// A�{�^������������
	if (pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
	{
		// �^�C�g����ʂ�
		pFade->SetFade(CManager::MODE_TITLE);

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_CANCEL);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_CANCEL, 1.0f);
	}
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}