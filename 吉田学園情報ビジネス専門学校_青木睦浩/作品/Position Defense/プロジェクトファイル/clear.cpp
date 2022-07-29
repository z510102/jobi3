//=============================================================================
//
// �N���A���� [clear.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "clear.h"
#include "input_keyboard.h"
#include "fade.h"
#include "input_gamepad.h"
#include "UI.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CClear::m_pTexture = NULL;

//=============================================================================
// �N���A�̓ǂݍ���
//=============================================================================
HRESULT CClear::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						 // �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/clear_bg.png",	 // �ǂݍ��ރt�@�C����
							  &m_pTexture);					 // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// �N���A�̔j��
//=============================================================================
void CClear::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �N���A�̐���
//=============================================================================
CClear *CClear::Create(void)
{
	// �|�C���^
	CClear *pClear;

	// ���������m��
	pClear = new CClear;

	if (pClear != NULL)
	{
		// Init��
		pClear->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pClear;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CClear::CClear()
{
	// �ϐ����N���A
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CClear::~CClear()
{

}

//=============================================================================
// �N���A�̏���������
//=============================================================================
HRESULT CClear::Init(D3DXVECTOR3 pos)
{
	// UI�̃e�N�X�`���ǂݍ��݂�
	CUI::Load();

	//����
	m_pScene2D = new CScene2D(PRIORITY_SCREEN);

	if (m_pScene2D != NULL)
	{
		m_pScene2D->Init(pos);
		m_pScene2D->SetSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_pScene2D->BindTexture(m_pTexture);
	}

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// UI�̎擾
	CUI *pUI = CGame::GetUI();

	// UI�̐���
	pUI = CUI::Create(D3DXVECTOR3(640, 200, 0), D3DXVECTOR2(400, 100), CUI::TYPE_GAME_CLEAR);

	// ����炷
	pSound->PlaySound(pSound->SOUND_LABEL_CLEAR_BGM);

	// ���ʂ𒲐�
	pSound->SoundVolume(CSound::SOUND_LABEL_CLEAR_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// �N���A�̏I������
//=============================================================================
void CClear::Uninit(void)
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

	// �I�u�W�F�N�g�̔j����
	Release();
}

//=============================================================================
// �N���A�̍X�V����
//=============================================================================
void CClear::Update(void)
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

	// Enter�L�[����������
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
	{
		//�^�C�g����ʂ�
		pFade->SetFade(CManager::MODE_RESULT);

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);

		/*CManager::SetMode(CManager::MODE_TITLE);*/
	}
}

//=============================================================================
// �N���A�̕`�揈��
//=============================================================================
void CClear::Draw(void)
{

}