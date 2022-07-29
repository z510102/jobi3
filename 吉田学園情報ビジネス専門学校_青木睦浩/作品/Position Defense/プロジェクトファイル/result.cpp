//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "result.h"
#include "input_keyboard.h"
#include "fade.h"
#include "ranking.h"
#include "number.h"
#include "input_gamepad.h"
#include "sound.h"
#include "UI.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;

//=============================================================================
// �^�C�g���̓ǂݍ���
//=============================================================================
HRESULT CResult::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							 // �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/ranking_bg.png",	 // �ǂݍ��ރt�@�C����
							  &m_pTexture);						 // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// �^�C�g���̔j��
//=============================================================================
void CResult::Unload(void)
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
CResult *CResult::Create(void)
{
	// �|�C���^
	CResult *pResult;

	// ���������m��
	pResult = new CResult;

	if (pResult != NULL)
	{
		// Init��
		pResult->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pResult;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	// �ϐ����N���A
	m_pScene2D = NULL;
	memset(&m_Pos, 0, sizeof(D3DXVECTOR3));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos)
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
	pUI = CUI::Create(D3DXVECTOR3(480, 400, 0), D3DXVECTOR2(100, 200), CUI::TYPE_RANKING_RANK);

	// �i���o�[�̃e�N�X�`���ǂݍ��݂�
	CNumber::Load();

	// �����L���O�̐���
	CRanking::Create(D3DXVECTOR3(650, 230, 0), D3DXVECTOR2(60, 80));

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// ����炷
	pSound->PlaySound(pSound->SOUND_LABEL_RANKING_BGM);

	// ���ʂ𒲐�
	pSound->SoundVolume(CSound::SOUND_LABEL_RANKING_BGM, 2.0f);

	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CResult::Uninit(void)
{
	// UI�̃e�N�X�`���j����
	CUI::Unload();

	//�w�i�̔j��
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();

		m_pScene2D = NULL;
	}

	// �i���o�[�̃e�N�X�`���j����
	CNumber::Unload();

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
void CResult::Update(void)
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
		// �Q�[����ʂ�
		pFade->SetFade(CManager::MODE_TITLE);

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_DECISION);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_DECISION, 1.0f);
	}
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CResult::Draw(void)
{

}