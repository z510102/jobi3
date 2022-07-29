//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "manager.h"
#include "sound.h"
#include "input_keyboard.h"
#include "input_gamepad.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "clear.h"
#include "over.h"
#include "result.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputGamepad *CManager::m_pInputGamepad = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CClear *CManager::m_pClear = NULL;
COver *CManager::m_pOver = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == NULL)
	{
		// ���������m��
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL)
		{
			// �����_���[�̏�����������
			m_pRenderer->Init(hWnd, TRUE);
		}
	}

	if (m_pInputKeyboard == NULL)
	{
		// ���������m��
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != NULL)
		{
			// �L�[�{�[�h�̏�����������
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	if (m_pInputGamepad == NULL)
	{
		// ���������m��
		m_pInputGamepad = new CInputGamepad;

		if (m_pInputGamepad != NULL)
		{
			// �Q�[���p�b�h�̏�����������
			m_pInputGamepad->Init(hInstance, hWnd);
		}
	}

	if (m_pSound == NULL)
	{
		// ���������m��
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			// �T�E���h�̏�����������
			m_pSound->Init(hWnd);
		}
	}

	// �t�F�[�h�̐���������
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CManager::MODE_TITLE);

	// ���ꂼ��̉�ʂ̓ǂݍ��݂�
	CTitle::Load();
	CTutorial::Load();
	CClear::Load();
	COver::Load();
	CResult::Load();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CManager::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	// ���ꂼ��̉�ʂ̔j����
	CTitle::Unload();
	CTutorial::Unload();
	CClear::Unload();
	COver::Unload();
	CResult::Unload();

	// �����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)
	{
		// �����_���[�̏I��������
		m_pRenderer->Uninit();

		// �����������
		delete m_pRenderer;

		// NULL�ɂ���
		m_pRenderer = NULL;
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I��������
		m_pInputKeyboard->Uninit();

		// �����������
		delete m_pInputKeyboard;

		// NULL�ɂ���
		m_pInputKeyboard = NULL;
	}

	// �Q�[���p�b�h�̔j��
	if (m_pInputGamepad != NULL)
	{
		// �Q�[���p�b�h�̏I��������
		m_pInputGamepad->Uninit();

		// �����������
		delete m_pInputGamepad;

		// NULL�ɂ���
		m_pInputGamepad = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I��������
		m_pSound->Uninit();

		// �����������
		delete m_pSound;

		// NULL�ɂ���
		m_pSound = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	if (m_pInputGamepad != NULL)
	{
		// �Q�[���p�b�h�̍X�V����
		m_pInputGamepad->Update();
	}

	if (m_pRenderer != NULL)
	{
		// �����_�����O�̍X�V����
		m_pRenderer->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �����_�����O�̕`�揈��
		m_pRenderer->Draw();
	}
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	// ���[�h�̎��
	switch (m_mode)
	{
	// �^�C�g���̏ꍇ
	case MODE_TITLE:

		if (m_pTitle != NULL)
		{
			// �^�C�g���̏I����
			m_pTitle->Uninit();

			// �����o��NULL�ɂ���
			m_pTitle = NULL;
		}

		break;



	// �`���[�g���A���̏ꍇ
	case MODE_TUTORIAL:

		if (m_pTutorial != NULL)
		{
			// �`���[�g���A���̏I����
			m_pTutorial->Uninit();

			// �����o��NULL�ɂ���
			m_pTutorial = NULL;
		}

		break;



	// �Q�[���̏ꍇ
	case MODE_GAME:
		
		if (m_pGame != NULL)
		{
			// �Q�[���̏I����
			m_pGame->Uninit();

			// �����o��NULL�ɂ���
			m_pGame = NULL;
		}

		break;



	// �N���A�̏ꍇ
	case MODE_CLEAR:
		
		if (m_pClear != NULL)
		{
			// �N���A�̏I����
			m_pClear->Uninit();

			// �����o��NULL�ɂ���
			m_pClear = NULL;
		}

		break;



	// �I�[�o�[�̏ꍇ
	case MODE_OVER:

		if (m_pOver != NULL)
		{
			// �I�[�o�[�̏I����
			m_pOver->Uninit();

			// �����o��NULL�ɂ���
			m_pOver = NULL;
		}

		break;



	// ���U���g�̏ꍇ
	case MODE_RESULT:

		if (m_pResult != NULL)
		{
			// ���U���g�̏I����
			m_pResult->Uninit();

			// �����o��NULL�ɂ���
			m_pResult = NULL;
		}

		break;
	}

	// �S�ẴI�u�W�F�N�g�̔j����
	CScene::ReleaseAll();

	// ���[�h�̔j��
	switch (mode)
	{
	// �^�C�g���̏ꍇ
	case MODE_TITLE:

		// �^�C�g���̐���
		m_pTitle = CTitle::Create();
		break;



	// �`���[�g���A���̏ꍇ
	case MODE_TUTORIAL:

		// �`���[�g���A���̐���
		m_pTutorial = CTutorial::Create();
		break;



	// �Q�[���̏ꍇ
	case MODE_GAME:

		// �Q�[���̐���
		m_pGame = CGame::Create();
		break;



	// �N���A�̏ꍇ
	case MODE_CLEAR:

		// �N���A�̏ꍇ
		m_pClear = CClear::Create();
		break;



	// �I�[�o�[�̏ꍇ
	case MODE_OVER:

		// �I�[�o�[�̏ꍇ
		m_pOver = COver::Create();
		break;



	// ���U���g�̏ꍇ
	case MODE_RESULT:

		// ���U���g�̏ꍇ
		m_pResult = CResult::Create();
		break;
	}

	// ����n��
	m_mode = mode;
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_mode;
}

//=============================================================================
// �����_�����O�N���X���擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h�N���X���擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pInputKeyboard;
}

//=============================================================================
// �Q�[���p�b�h�N���X���擾
//=============================================================================
CInputGamepad * CManager::GetInputGamepad(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pInputGamepad;
}

//=============================================================================
// �t�F�[�h�N���X���擾
//=============================================================================
CFade * CManager::GetFade(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pFade;
}

//=============================================================================
// �T�E���h�N���X���擾
//=============================================================================
CSound * CManager::GetSound(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pSound;
}
