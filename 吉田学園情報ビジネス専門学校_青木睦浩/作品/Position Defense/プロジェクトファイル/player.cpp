//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "player.h"
#include "input_keyboard.h"
#include "manager.h"
#include "input_gamepad.h"
#include "sound.h"
#include "grenade.h"
#include "flash_grenade.h"
#include "g_possession.h"
#include "f_g_possession.h"
#include "game.h"
#include "bullet_magazine.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
int CPlayer::m_nBullet = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_nPatternAnimU = 0;
	m_nCounterAnim = 0;
	m_nBulletNumber_HG_magazine = 0;
	m_nBulletNumber_AR_magazine = 0;
	m_nBulletNumber_SG_magazine = 0;
	m_nBulletNumber_SR_magazine = 0;
	m_nBulletNumber_RL_magazine = 0;
	m_nRapidSpeedHG = 0;
	m_nRapidSpeedAR = 0;
	m_nRapidSpeedSG = 0;
	m_nRapidSpeedSR = 0;
	m_nRapidSpeedRL = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,								 // �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/player_animation.png",	 // �ǂݍ��ރt�@�C����
							  &m_pTexture);							 // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`���j��
//=============================================================================
void CPlayer::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//int CPlayer::GetBulletRemainig(void)
//{
//	return m_nRemaining;
//}

//=============================================================================
// 2D�|���S���̐�������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	// �|�C���^
	CPlayer *pPlayer;

	// ���������m��
	pPlayer = new CPlayer (PRIORITY_CHARA);

	if (pPlayer != NULL)
	{
		// ������
		pPlayer->Init(pos);
		pPlayer->SetSize(11, 22);
		pPlayer->BindTexture(m_pTexture);
		pPlayer->SetVertexTexture(4, 0.25f, 0, 0, 0.25f, 1.0f);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pPlayer;
}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_PLAYER);

	// �e�̎�ނ������o�֓n��
	m_nBullet = CBullet::TYPE_HG;

	// �}�K�W���̒e����ݒ�
	m_nBulletNumber_HG_magazine = 10;
	m_nBulletNumber_AR_magazine = 30;
	m_nBulletNumber_SG_magazine = 8;
	m_nBulletNumber_SR_magazine = 6;
	m_nBulletNumber_RL_magazine = 1;


	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����o�֏���n��
	m_pos = pos;

	//=============================================================================
	// �v���C���[�̈ړ��ƈړ�����
	//=============================================================================

	//�㉺
	/*if (pInputKeyboard->GetKeyboardPress(DIK_W) == true && SCREEN_HEIGHT - SCREEN_HEIGHT <= pos.y - 30)
	{
		pos.y -= 3.0f;
	}

	if (pInputKeyboard->GetKeyboardPress(DIK_S) == true && pos.y + 30 <= SCREEN_HEIGHT)
	{
		pos.y += 3.0f;
	}*/

	// ���ւ̈ړ��ƈړ�����
	if (pInputKeyboard->GetKeyboardPress(DIK_A) == true && MOVE_MIN <= m_pos.x - 15 || pInputGamepad->GetLeftStick(CInputGamepad::STICK_TYPE_LEFT) && MOVE_MIN <= m_pos.x - 15)
	{
		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��10���傫���Ȃ����ꍇ
		if (m_nCounterAnim > 10)
		{
			// 0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z
			m_nPatternAnimU--;

			// �e�N�X�`�����W��ݒ�
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}

		// �ړ��ipos�Ɛ��l��������pos�֓n���j
		m_pos.x -= 2.2f;
	}

	// �E�ւ̈ړ��ƈړ�����
	if (pInputKeyboard->GetKeyboardPress(DIK_D) == true && m_pos.x + 15 <= MOVE_MAX || pInputGamepad->GetLeftStick(CInputGamepad::STICK_TYPE_RIGHT) && m_pos.x + 15 <= MOVE_MAX)
	{
		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��10���傫���Ȃ����ꍇ
		if (m_nCounterAnim > 10)
		{
			// 0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ�
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}

		// �ړ��ipos�Ɛ��l�𑫂���pos�֓n���j
		m_pos.x += 2.2f;
	}

	// ���e�����擾
	CBulletTotal *pBulletTotal;
	pBulletTotal = CGame::GetBulletTotal();

	//=============================================================================
	// �e����
	//=============================================================================

	// ���ˊԊu�����Z
	m_nRapidSpeedHG++;
	m_nRapidSpeedAR++;
	m_nRapidSpeedSG++;
	m_nRapidSpeedSR++;
	m_nRapidSpeedRL++;

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_nRapidSpeedHG >= 50)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//�e�����擾
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//�n���h�K��
			if (m_nBullet == CBullet::TYPE_HG)
			{
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_HG);

				//�e�����Z
				pBulletMagazine->SubBulletMagazine(1);

				int nHG = pBulletMagazine->GetBulletMagazineHG();

				if (nHG <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nHG >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedHG = 0;
		}
	}

	if (m_nRapidSpeedAR >= 12)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonPress(XINPUT_GAMEPAD_A))
		{
			//�e�����擾
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//�A�T���g���C�t��
			if (m_nBullet == CBullet::TYPE_AR)
			{
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_AR);

				//�e�����Z
				pBulletMagazine->SubBulletMagazine(1);

				int nAR = pBulletMagazine->GetBulletMagazineAR();

				if (nAR <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nAR >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_HG_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_HG_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedAR = 0;
		}
	}

	if (m_nRapidSpeedSG >= 100)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//�e�����擾
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//�V���b�g�K��
		    if (m_nBullet == CBullet::TYPE_SG)
		    {
		    	//�e�̐���
		    	CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SG);
		    	CBullet::Create(D3DXVECTOR3(m_pos.x + 30, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SG);
		    	CBullet::Create(D3DXVECTOR3(m_pos.x - 30, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SG);
		    
		    	//�e�����Z
		    	pBulletMagazine->SubBulletMagazine(1);

				int nSG = pBulletMagazine->GetBulletMagazineSG();

				if (nSG <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nSG >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SG_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_SG_SHOT, 1.0f);
				}
		    }

			m_nRapidSpeedSG = 0;
		}
	}

	if (m_nRapidSpeedSR >= 170)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//�e�����擾
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//�X�i�C�p�[���C�t��
			if (m_nBullet == CBullet::TYPE_SR)
			{
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_SR);

				//�e�����Z
				pBulletMagazine->SubBulletMagazine(1);

				int nSR = pBulletMagazine->GetBulletMagazineSR();

				if (nSR <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nSR >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SR_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_SR_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedSR = 0;
		}
	}

	if (m_nRapidSpeedRL >= 70)
	{
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			//�e�����擾
			CBulletMagazine *pBulletMagazine;
			pBulletMagazine = CGame::GetBulletMagazine();

			//���P�b�g�����`���[
			if (m_nBullet == CBullet::TYPE_RL)
			{
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0), D3DXToRadian(0), CBullet::TYPE_RL);

				//�e�����Z
				pBulletMagazine->SubBulletMagazine(1);

				int nRL = pBulletMagazine->GetBulletMagazineRL();

				if (nRL <= -1)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_BULLET_OUT);
					pSound->SoundVolume(CSound::SOUND_LABEL_BULLET_OUT, 1.0f);
				}

				if (nRL >= 0)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_RL_SHOT);
					pSound->SoundVolume(CSound::SOUND_LABEL_RL_SHOT, 1.0f);
				}
			}

			m_nRapidSpeedRL = 0;
		}
	}

	//=============================================================================
	// �����[�h
	//=============================================================================
#if 0
	if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true)
	{
		//�g�[�^���̐��l��n��
		m_nRemainingTotal = pBulletTotal->GetBulletTotal();

		if (m_nBullet == CBullet::TYPE_HG)
		{
			//�e�����X�ȉ��ɂȂ�����
			if (m_nBulletNumber_HG_magazine <= 9)
			{
				//�e�̍ő吔���猻�݂̒e��������
				m_nRemaining = MAX_BULLET_HG - m_nBulletNumber_HG_magazine;

				//���������𑍒e���������
				pBulletTotal->SubBulletTotal(m_nRemaining);

				m_nBulletNumber_HG_magazine += m_nRemaining;

				m_bRemaiing = true;

			}

			if (m_nRemainingTotal <= 9)
			{
				m_nRemaining = m_nRemainingTotal - m_nBulletNumber_HG_magazine;

				m_bRemaiing = false;
			}
			
		}
	
	}
#endif

	//=============================================================================
	// �O���l�[�h����
	//=============================================================================
	if (pInputKeyboard->GetKeyboardTrigger(DIK_G) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_B))
	{
		//�O���l�[�h�̐���
		CGrenade::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0));

		//�O���l�[�h���������擾
		CG_Possession *pG_Possession;
		pG_Possession = CGame::GetG_Possession();

		//�O���l�[�h���������Z
		pG_Possession->SubG_Ppssession(1);

		int nG = pG_Possession->GetG_Ppssession();

		if (nG <= -1)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 0.0f);
		}

		if (nG >= 0)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 1.0f);
		}
	}

	//=============================================================================
	// �t���b�V���O���l�[�h����
	//=============================================================================
	if (pInputKeyboard->GetKeyboardTrigger(DIK_H) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_Y))
	{
		//�t���b�V���O���l�[�h�̐���
		CFlashGrenade::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 40, m_pos.z), D3DXVECTOR3(0, -5, 0));

		//�t���b�V���O���l�[�h���������擾
		CF_G_Possession *pF_G_Possession;
		pF_G_Possession = CGame::GetF_G_Possession();

		//�t���b�V���O���l�[�h���������Z
		pF_G_Possession->SubF_G_Ppssession(1);

		int nFG = pF_G_Possession->GetF_G_Ppssession();

		if (nFG <= -1)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 0.0f);
		}

		if (nFG >= 0)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_GRENADE);
			pSound->SoundVolume(CSound::SOUND_LABEL_GRENADE, 1.0f);
		}
	}

	//=============================================================================
	// �e�̎�ޕύX
	//=============================================================================

	//�\���L�[�E
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_RIGHT))
	{
		// �e�̎�ނ����Z
		m_nBullet++;

		// �e�̎�ނ����P�b�g�����`���[+1�ȏ�ɂȂ����ꍇ
		if (m_nBullet >= CBullet::TYPE_RL + 1)
		{
			// �e�̎�ނ��n���h�K���ɂ���
			m_nBullet = CBullet::TYPE_HG;
		}
	}

	//�\���L�[��
	if (pInputKeyboard->GetKeyboardTrigger(DIK_LEFT) == true || pInputGamepad->GetLeftShoulderTrigger(CInputGamepad::SHOULDER_TYPE_LEFT))
	{
		// �e�̎�ނ����Z
		m_nBullet--;

		// �e�̎�ނ��n���h�K��-1�ȉ��ɂȂ����ꍇ
		if (m_nBullet <= CBullet::TYPE_HG - 1)
		{
			// �e�̎�ނ����P�b�g�����`���[�ɂ���
			m_nBullet = CBullet::TYPE_RL;
		}
	}

	// Scene2D�̍X�V������
	CScene2D::Update();

	// �ʒu�̐ݒ菈����
	SetPosition(m_pos);
}

//=============================================================================
// 2D�|���S���̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// Scene2D�̕`�揈����
	CScene2D::Draw();
}

//=============================================================================
// �e�̎�ނ̎擾����
//=============================================================================
int CPlayer::GetBulletType(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nBullet;
}