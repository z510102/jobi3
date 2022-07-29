//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "title.h"
#include "input_keyboard.h"
#include "fade.h"
#include "UI.h"
#include "game.h"
#include "input_gamepad.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;
int CTitle::m_nSelect = TYPE_START_GAME;

//=============================================================================
// �^�C�g���̓ǂݍ���
//=============================================================================
HRESULT CTitle::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					 // �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/bg.png",	 // �ǂݍ��ރt�@�C����
							  &m_pTexture);				 // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// �^�C�g���̔j��
//=============================================================================
void CTitle::Unload(void)
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
CTitle *CTitle::Create(void)
{
	// �|�C���^
	CTitle *pTitle;

	// ���������m��
	pTitle = new CTitle;

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
CTitle::CTitle()
{
	// �ϐ����N���A
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos)
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

	// �I�����ڂ�TYPE_START_GAME��
	m_nSelect = TYPE_START_GAME;

	// UI���擾
	CUI *pUI = CGame::GetUI();

	// UI�̐���
	pUI = CUI::Create(D3DXVECTOR3(640, 200, 0), D3DXVECTOR2(380, 80), CUI::TYPE_TITLE);

	// TYPE_MAX�̐���
	for (int nCnt = CUI::TYPE_START_GAME; nCnt < CUI::TYPE_MAX; nCnt++)
	{
		// UI�̐���
		pUI = CUI::Create(D3DXVECTOR3(640, (float)(90 * nCnt - 1000), 0), D3DXVECTOR2(140, 40), (CUI::UI_TYPE)nCnt);
	}

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// ����炷
	pSound->PlaySound(pSound->SOUND_LABEL_TITLE_BGM);

	// ���ʂ𒲐�
	pSound->SoundVolume(CSound::SOUND_LABEL_TITLE_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTitle::Uninit(void)
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
void CTitle::Update(void)
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

	// �\���L�[��
	if (pInputKeyboard->GetKeyboardTrigger(DIK_DOWN) == true || pInputGamepad->GetLeftStickTrigger(CInputGamepad::STICK_TYPE_DOWN))
	{
		// �I�����ڂ̐��l�����Z
		m_nSelect++;

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

		// �I�����ڂ�TYPE_RANKING + 1�̏ꍇ
		if (m_nSelect >= TYPE_RANKING + 1)
		{
			// ���ʂ𒲐�
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

			// �I�����ڂ�TYPE_RANKING�ɒ���
			m_nSelect = TYPE_RANKING;
		}
	}

	//�\���L�[��
	else if (pInputKeyboard->GetKeyboardTrigger(DIK_UP) == true || pInputGamepad->GetLeftStickTrigger(CInputGamepad::STICK_TYPE_UP))
	{
		// �I�����ڂ̐��l�����Z
		m_nSelect--;

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

		// �I�����ڂ�TYPE_START_GAME - 1�̏ꍇ
		if (m_nSelect <= TYPE_START_GAME - 1)
		{
			// ���ʂ𒲐�
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

			// �I�����ڂ�TYPE_START_GAME�ɒ���
			m_nSelect = TYPE_START_GAME;
		}
	}

	// Enter�L�[����������
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
	{
		// �I�����ڂ̎��
		switch (m_nSelect)
		{

		// TYPE_START_GAME�̏ꍇ
		case TYPE_START_GAME:

			// ����炷
			pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);

			// ���ʂ𒲐�
			pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);

			// GAME��ʂ�
			pFade->SetFade(CManager::MODE_GAME);
			break;



		// TYPE_TUTORIAL�̏ꍇ
		case TYPE_TUTORIAL:

			// ����炷
			pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

			// ���ʂ𒲐�
			pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);

			// �`���[�g���A����ʂ�
			pFade->SetFade(CManager::MODE_TUTORIAL);
			break;



		// TYPE_RANKING�̏ꍇ
		case TYPE_RANKING:

			// ����炷
			pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

			// ���ʂ𒲐�
			pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);

			// ���U���g��ʂ�
			pFade->SetFade(CManager::MODE_RESULT);
			break;



		// ��O����
		default:
			break;
		}
	}
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	
}

int CTitle::GetSelect(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nSelect;
}
