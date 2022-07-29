//=============================================================================
//
// UI���� [UI.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "UI.h"
#include "manager.h"
#include "input_keyboard.h"
#include "title.h"
#include "input_gamepad.h"
#include "bullet_magazine.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CUI::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// �w�i�̓ǂݍ���
//=============================================================================
HRESULT CUI::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/high score.png",			 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_HIGH_SCORE]);          // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/score.png",				 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_SCORE]);				 // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/time.png",				 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_TIME]);				 // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/life.png",				 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_LIFE]);				 // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/grenade.png",				 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_GRENADE]);			 // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/flash_grenade.png",		 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_FLASH_GRENADE]);       // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/weapon.png",				 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_WEAPON]);              // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/tutorial_animation.png",	 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_TUTORIAL_ANIMATION]);  // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/switching.png",			 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_SWITCHING]);           // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/title_logo.png",			 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_TITLE]);				 // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/reload_logo.png",			 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_RELOAD]);				 // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/infinite.png",			 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_INFINITE]);			 // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/ranking_rank.png",		 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_RANKING_RANK]);        // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/clear_logo.png",			 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_GAME_CLEAR]);          // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/over_logo.png",			 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_GAME_OVER]);           // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/start game_logo.png",		 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_START_GAME]);          // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/tutorial_logo.png",		 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_TUTORIAL]);            // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,	         // �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/ranking_logo.png",		 // �ǂݍ��ރt�@�C����
		&m_apTexture[TYPE_RANKING]);             // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// �w�i�̔j��
//=============================================================================
void CUI::Unload(void)
{
	// TYPE_MAX�̐���
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �X�R�A�̐���
//=============================================================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, UI_TYPE type)
{
	// �|�C���^
	CUI *pUI;

	// ���������m�ۂƃv���C�I���e�B
	pUI = new CUI (PRIORITY_UI);

	if (pUI != NULL)
	{
		// ������
		pUI->Init(pos);
		pUI->SetSize(size.x, size.y);
		pUI->BindTexture(m_apTexture[type]);

		// �����o�֏���n��
		pUI->m_Type = type;

		// ��ނ�TYPE_WEAPON�̏ꍇ
		if (type == TYPE_WEAPON)
		{
			// �e�N�X�`�����W��ݒ�
			pUI->SetVertexTexture(0, 0.2f, 0, 0, 0.2f, 1.0f);
		}

		// ��ނ�TYPE_TUTORIAL_ANIMATION�̏ꍇ
		else if (type == TYPE_TUTORIAL_ANIMATION)
		{
			// �e�N�X�`�����W��ݒ�
			pUI->SetVertexTexture(0, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pUI;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUI::CUI(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_Type = TYPE_NONE;
	m_nPatternAnimU = 0;
	m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nType = 0;
	m_nReloadHG = 0;
	m_nReloadAR = 0;
	m_nReloadSG = 0;
	m_nReloadSR = 0;
	m_nReloadRL = 0;
	m_nBulletType = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUI::~CUI()
{

}

//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CUI::Init(D3DXVECTOR3 pos)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(OBJTYPE_UI);

	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CUI::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CUI::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// �}�K�W���̎擾
	CBulletMagazine *pBulletMagazine;
	pBulletMagazine = CGame::GetBulletMagazine();

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//=============================================================================
	// ����̎�ޕύX
	//=============================================================================

	// �\���L�[�E
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_RIGHT))
	{
		// m_nPatternAnimU�����Z
		m_nPatternAnimU++;

		// ��ނ�TYPE_WEAPON�̏ꍇ
		if (m_Type == TYPE_WEAPON)
		{
			// �e�N�X�`�����W��ݒ�
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.2f, 0, 0, 0.2f, 1.0f);
		}

		// ��ނ�TYPE_TUTORIAL_ANIMATION�̏ꍇ
		else if (m_Type == TYPE_TUTORIAL_ANIMATION)
		{
			// ����炷
			pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

			// ���ʂ𒲐�
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

			// �e�N�X�`�����W��ݒ�
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);

			// m_nPatternAnimU��4�ȏ�̏ꍇ
			if (m_nPatternAnimU >= 3 + 1)
			{
				// ���ʂ𒲐�
				pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

				// m_nPatternAnimU��3�ɂ���
				m_nPatternAnimU = 3;

				// �e�N�X�`�����W��ݒ�
				CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
			}
		}
	}

	// �\���L�[��
	else if (pInputKeyboard->GetKeyboardTrigger(DIK_LEFT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_LEFT))
	{
		// m_nPatternAnimU�����Z
		m_nPatternAnimU--;

		// ��ނ�TYPE_WEAPON�̏ꍇ
		if (m_Type == TYPE_WEAPON)
		{
			// �e�N�X�`�����W��ݒ�
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.2f, 0, 0, 0.2f, 1.0f);
		}

		// ��ނ�TYPE_TUTORIAL_ANIMATION�̏ꍇ
		else if (m_Type == TYPE_TUTORIAL_ANIMATION)
		{
			// ����炷
			pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

			// ���ʂ𒲐�
			pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 1.0f);

			// �e�N�X�`�����W��ݒ�
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);

			// m_nPatternAnimU��-1�ȉ��̏ꍇ
			if (m_nPatternAnimU <= 0 - 1)
			{
				// ���ʂ𒲐�
				pSound->SoundVolume(CSound::SOUND_LABEL_SELECT, 0.0f);

				// m_nPatternAnimU��0�ɂ���
				m_nPatternAnimU = 0;

				// �e�N�X�`�����W��ݒ�
				CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
			}
		}
	}

	// �I�����ڂ̎擾
	int nSelect = CTitle::GetSelect();

	// UI�̎��
	switch (m_Type)
	{
	// TYPE_START_GAME�̏ꍇ
	case TYPE_START_GAME:

		// �I�����ڂ�TYPE_START_GAME�̏ꍇ
		if (nSelect == CTitle::TYPE_START_GAME)
		{
			// �F��ݒ�
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			// ���_�J���[�̐ݒ��
			SetColor(m_Color);
		}

		// ����ȊO�̏ꍇ
		else
		{
			// �F��ݒ�
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

			// ���_�J���[�̐ݒ��
			SetColor(m_Color);
		}

		break;



	// TYPE_TUTORIAL�̏ꍇ
	case TYPE_TUTORIAL:

		// �I�����ڂ�TYPE_TUTORIAL�̏ꍇ
		if (nSelect == CTitle::TYPE_TUTORIAL)
		{
			// �F��ݒ�
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			// ���_�J���[�̐ݒ��
			SetColor(m_Color);
		}

		// ����ȊO�̏ꍇ
		else
		{
			// �F��ݒ�
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

			// ���_�J���[�̐ݒ��
			SetColor(m_Color);
		}

		break;



	// TYPE_RANKING�̏ꍇ
	case TYPE_RANKING:

		// �I�����ڂ�TYPE_RANKING�̏ꍇ
		if (nSelect == CTitle::TYPE_RANKING)
		{
			// �F��ݒ�
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			// ���_�J���[�̐ݒ��
			SetColor(m_Color);
		}

		// ����ȊO�̏ꍇ
		else
		{
			// �F��ݒ�
			m_Color = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

			// ���_�J���[�̐ݒ��
			SetColor(m_Color);
		}

		break;



	// TYPE_RELOAD�̏ꍇ
	case TYPE_RELOAD:

		// ���ꂼ��̃}�K�W���̒e�����擾
		m_nReloadHG = pBulletMagazine->GetBulletMagazineHG();
		m_nReloadAR = pBulletMagazine->GetBulletMagazineAR();
		m_nReloadSG = pBulletMagazine->GetBulletMagazineSG();
		m_nReloadSR = pBulletMagazine->GetBulletMagazineSR();
		m_nReloadRL = pBulletMagazine->GetBulletMagazineRL();

		// �e�̎�ނ��擾
		m_nBulletType = pBulletMagazine->GetBulletType();

		// ���ꂼ��̃}�K�W���̒e����0���e�̎��
		if (m_nReloadHG == 0 && m_nBulletType == 0 || m_nReloadAR == 0 && m_nBulletType == 1 || m_nReloadSG == 0 && m_nBulletType == 2 || m_nReloadSR == 0 && m_nBulletType == 3 || m_nReloadRL == 0 && m_nBulletType == 4)
		{
			// �F��ݒ�
			SetColor(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}

		// ����ȊO
		else
		{
			// �F��ݒ�
			SetColor(D3DXCOLOR(0.0, 0.0, 0.0, 0.0));
		}
		break;

	// TYPE_INFINITE�̏ꍇ
	case TYPE_INFINITE:

		// �e�̎�ނ��擾
		m_nBulletType = pBulletMagazine->GetBulletType();

		// �e�̎�ނ�0�iHG�j�̏ꍇ
		if (m_nBulletType == 0)
		{
			// �F��ݒ�
			SetColor(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}

		else
		{
			// �F��ݒ�
			SetColor(D3DXCOLOR(0.0, 0.0, 0.0, 0.0));
		}
		break;
	}

	// Scene2D�̍X�V������
	CScene2D::Update();
}

//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CUI::Draw(void)
{
	// Scene2D�̕`�揈����
	CScene2D::Draw();
}