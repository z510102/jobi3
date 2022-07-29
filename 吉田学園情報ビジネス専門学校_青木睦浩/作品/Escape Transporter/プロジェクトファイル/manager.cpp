//=============================================================================
//
// �}�l�[�W�� [manager.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "keyboard.h"
#include "xinput_gamepad.h"
#include "sound.h"
#include "texture.h"

#include "title.h"
#include "menu.h"
#include "tutorial.h"
//#include "select.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "ranking2.h"
#include "fade.h"

#include "light.h"
#include "camera.h"
#include "scene3D.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CRenderer		*CManager::m_pRenderer = NULL;
CInputKeyboard	*CManager::m_pInputKeyboard = NULL;
CXinputPad		*CManager::m_pXinputPad = NULL;
CSound			*CManager::m_pSound = NULL;

CTitle			*CManager::m_pTitle = NULL;
CMenu			*CManager::m_pMenu = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CSelect			*CManager::m_pSelect = NULL;
CGame			*CManager::m_pGame = NULL;
CResult			*CManager::m_pResult = NULL;
CRanking		*CManager::m_pRanking = NULL;
CRanking2		*CManager::m_pRanking2 = NULL;

CFade			*CManager::m_pFade = NULL;
CTexture		*CManager::m_pTexture = NULL;
CModel			*CManager::m_pModel = NULL;

CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_pLight = NULL;
CManager::MODE	CManager::m_mode = MODE_TITLE;

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
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;

		// �����_���[�̏���������
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}
	// �L�[�{�[�h�̐���
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;

		// �L�[�{�[�h�̏���������
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}
	// �Q�[���p�b�h�̐���
	if (m_pXinputPad == NULL)
	{
		m_pXinputPad = new CXinputPad;

		// �Q�[���p�b�h�̏���������
		if (m_pXinputPad != NULL)
		{
			m_pXinputPad->Init(hInstance, hWnd);
		}
	}
	// �T�E���h����
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}
	

	// �e�N�X�`���N���X����
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;

		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}


	//SetMode(m_mode);


	m_pCamera = CCamera::Create();
	m_pLight = CLight::Create();

	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	// Xinput�Q�[���p�b�h�̔j��
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Uninit();
		delete m_pXinputPad;
		m_pXinputPad = NULL;
	}
	//// �T�E���h�̔j��
	//if (m_pSound != NULL)
	//{
	//	m_pSound->Uninit();
	//	delete m_pSound;
	//	m_pSound = NULL;
	//}
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// �S�ẴI�u�W�F�N�g�N���X��j��
	CScene::ReleaseAll();

}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	// �L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	// �Q�[���p�b�h�̍X�V����
	if (m_pXinputPad != NULL)
	{
		m_pXinputPad->Update();
	}
	if (m_mode == MODE_GAME)
	{
		if (m_pCamera != NULL)
		{
			m_pCamera->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();	// �����_���[�̕`�揈��
	}
	if (m_mode == MODE_GAME)
	{
		m_pCamera->SetCamera();

	}


}
//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_MENU:
		if (m_pMenu != NULL)
		{
			m_pMenu->Uninit();
			m_pMenu = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;
		//case MODE_SELECT:
		//	if (m_pSelect != NULL)
		//	{
		//		m_pSelect->Uninit();
		//		m_pSelect = NULL;
		//	}
		//	break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}
		break;
	case MODE_RANKING2:
		if (m_pRanking2 != NULL)
		{
			m_pRanking2->Uninit();
			m_pRanking2 = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	default:
		break;
	}

	// �S�ẴI�u�W�F�N�g�N���X��j��
	CScene::ReleaseAll();

	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_MENU:
		m_pMenu = CMenu::Create();
		break;
	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create();
		break;
		//case MODE_SELECT:
		//	m_pSelect = CSelect::Create();
		//	break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RANKING:
		m_pRanking = CRanking::Create();
		break;
	case MODE_RANKING2:
		m_pRanking2 = CRanking2::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	default:
		break;
	}

	m_mode = mode;
}
#if 1
//=============================================================================
// ���[�h���擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}
//=============================================================================
// �����_���[���擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//=============================================================================
// �L�[�{�[�h���擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//=============================================================================
// �Q�[���p�b�h�̎擾
//=============================================================================
CXinputPad *CManager::GetXinputPad(void)
{
	return m_pXinputPad;
}
//=============================================================================
// �T�E���h�擾
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}
//=============================================================================
// �^�C�g���擾
//=============================================================================
CTitle *CManager::GetTitle(void)
{
	return m_pTitle;
}
//=============================================================================
// ���j���[�擾
//=============================================================================
CMenu *CManager::GetMenu(void)
{
	return m_pMenu;
}
CTutorial * CManager::GetTutorial(void)
{
	return m_pTutorial;
}
//=============================================================================
// �Z���N�g�擾
//=============================================================================
CSelect *CManager::GetSelect(void)
{
	return m_pSelect;
}
//=============================================================================
// �Q�[���擾
//=============================================================================
CGame *CManager::GetGame(void)
{
	return m_pGame;
}
//=============================================================================
// ���U���g�擾
//=============================================================================
CResult *CManager::GetResult(void)
{
	return m_pResult;
}
CRanking * CManager::GetRanking(void)
{
	return m_pRanking;
}
CRanking2 * CManager::GetRanking2(void)
{
	return m_pRanking2;
}
//=============================================================================
// �t�F�[�h�擾
//=============================================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}
//=============================================================================
// �t�F�[�h�擾
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}
//=============================================================================
// ���C�g�擾
//=============================================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}
//=============================================================================
// �J�����擾
//=============================================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}
#endif