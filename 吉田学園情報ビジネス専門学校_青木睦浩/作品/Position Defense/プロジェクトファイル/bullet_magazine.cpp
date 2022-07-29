//=============================================================================
//
// �e������ [bullet_number.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "bullet_magazine.h"
#include "input_keyboard.h"
#include "input_gamepad.h"
#include "manager.h"
#include "player.h"
#include "bullet_total.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// ��������
//=============================================================================
CBulletMagazine *CBulletMagazine::Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type)
{
	// �|�C���^
	CBulletMagazine *pNumber;

	// ���������m��
	pNumber = new CBulletMagazine (PRIORITY_NUMBER);

	if (pNumber != NULL)
	{
		// �����o�ϐ��֏���n��
		pNumber->m_size = D3DXVECTOR2(30, 40);
		pNumber->m_nMagazineType = type;

		// ������������
		pNumber->Init(pos);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pNumber;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletMagazine::CBulletMagazine(int nPriority) : CScene(nPriority)
{
	// �ϐ����N���A����
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nBulletNumber_HG_magazine = 0;
	m_nBulletNumber_AR_magazine = 0;
	m_nBulletNumber_SG_magazine = 0;
	m_nBulletNumber_SR_magazine = 0;
	m_nBulletNumber_RL_magazine = 0;
	m_nMagazineType = 0;
	m_nMagazine = 0;
	m_nTotal_Magazine = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletMagazine::~CBulletMagazine()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBulletMagazine::Init(D3DXVECTOR3 pos)
{
	// �e�̎�ނ̏���n��
	m_nMagazineType = CPlayer::GetBulletType();

	// MAX_BULLET_MAGAZINE�̐���
	for (int nCnt = 0; nCnt < MAX_BULLET_MAGAZINE; nCnt++)
	{
		// ����
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}
	
	// �}�K�W���̐��l�����߂�
	m_nBulletNumber_HG_magazine = 10;
	m_nBulletNumber_AR_magazine = 30;
	m_nBulletNumber_SG_magazine = 8;
	m_nBulletNumber_SR_magazine = 6;
	m_nBulletNumber_RL_magazine = 1;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBulletMagazine::Uninit(void)
{
	// MAX_BULLET_MAGAZINE�̐���
	for (int nCnt = 0; nCnt < MAX_BULLET_MAGAZINE; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;

			delete m_apNumber[nCnt];
		}
	}

	// �I�u�W�F�N�g��j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBulletMagazine::Update(void)
{
	// �e�̎�ނ̏���n��
	m_nMagazineType = CPlayer::GetBulletType();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CInputGamepad *pInputGamepad;
	pInputGamepad = CManager::GetInputGamepad();

	// ���e���̎擾
	CBulletTotal *pBulletTotal;
	pBulletTotal = CGame::GetBulletTotal();

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �e�̎�ނ�HG�������ꍇ
	if (m_nMagazineType == CBullet::TYPE_HG)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_HG_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_HG_magazine % (int)pow(10, 1));

		// 10�ȏゾ������
		if (m_nBulletNumber_HG_magazine >= 10)
		{
			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// 9�ȉ�����1�ȏゾ������
		if (m_nBulletNumber_HG_magazine <= 9 && m_nBulletNumber_HG_magazine >= 1)
		{
			// �F�𔒂ɂ���
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// ���������O�ȉ��ɂȂ�����
		if (m_nBulletNumber_HG_magazine <= 0)
		{
			// �O�Œ�~����
			m_nBulletNumber_HG_magazine = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// R�L�[�EX�{�^������������
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SE�𗬂�
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// �e����9�ȉ�����1�ȏゾ������
			if (m_nBulletNumber_HG_magazine <= 9 || m_nBulletNumber_HG_magazine >= 1)
			{
				// �e����9�ȉ�����1�ȏゾ������
				if (m_nBulletNumber_HG_magazine <= 9 && m_nBulletNumber_HG_magazine >= 1)
				{
					// �����o��
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// �e����10�ȏゾ������
				if (m_nBulletNumber_HG_magazine >= 10)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// �e�̍ő吔���猻�݂̒e��������
				m_nMagazine = MAX_BULLET_HG_MAGAZINE - m_nBulletNumber_HG_magazine;

				// ���������𑍒e���������
				pBulletTotal->SubBulletTotal(m_nMagazine);

				// �g�[�^���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// �g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_HG_magazine += m_nTotal_Magazine;

				// �}�K�W�����}�b�N�X�̒l�𒴂�����
				if (m_nBulletNumber_HG_magazine >= MAX_BULLET_HG_MAGAZINE)
				{
					// ����������
					m_nBulletNumber_HG_magazine = 0;

					// �}�K�W����10������
					m_nBulletNumber_HG_magazine = 10;
				}
			}

			// ���������O�ȉ��ɂȂ�����
			if (m_nBulletNumber_HG_magazine <= 0)
			{
				// �g�[�^���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// �g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_HG_magazine += m_nTotal_Magazine;
			}
		}
	}



	// �e�̎�ނ�AR�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_AR)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_AR_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_AR_magazine % (int)pow(10, 1));

		// �e����30�ȏゾ������
		if (m_nBulletNumber_AR_magazine >= 30)
		{
			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// �e����29�ȉ�����1�ȏゾ������
		if (m_nBulletNumber_AR_magazine <= 29 && m_nBulletNumber_AR_magazine >= 1)
		{
			// �F�𔒂ɂ���
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// ���������O�ȉ��ɂȂ�����
		if (m_nBulletNumber_AR_magazine <= 0)
		{
			// 0�Œ�~����
			m_nBulletNumber_AR_magazine = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// R�L�[�EX�{�^������������
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SE�𗬂�
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);
			
			// �e����29�ȉ�����1�ȏゾ������
			if (m_nBulletNumber_AR_magazine <= 29 || m_nBulletNumber_AR_magazine >= 1)
			{
				// �e����29�ȉ�����1�ȏゾ������
				if (m_nBulletNumber_AR_magazine <= 29 && m_nBulletNumber_AR_magazine >= 1)
				{
					// �����o��
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// �e����30�ȏゾ������
				if (m_nBulletNumber_AR_magazine >= 30)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// �e�̍ő吔���猻�݂̒e��������
				m_nMagazine = MAX_BULLET_AR_MAGAZINE - m_nBulletNumber_AR_magazine;

				// ���������𑍒e���������
				pBulletTotal->SubBulletTotal(m_nMagazine);

				// ���e���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// ���e����0��������
				if (m_nTotal_Magazine <= 0)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// ���e���̏����}�K�W���ɉ��Z
				m_nBulletNumber_AR_magazine += m_nTotal_Magazine;

				// �}�K�W�����}�b�N�X�̒l�𒴂�����
				if (m_nBulletNumber_AR_magazine >= MAX_BULLET_AR_MAGAZINE)
				{
					// ����������
					m_nBulletNumber_AR_magazine = 0;

					// �}�K�W����30������
					m_nBulletNumber_AR_magazine = 30;
				}
			}

			// ���������O�ȉ��ɂȂ�����
			if (m_nBulletNumber_AR_magazine <= 0)
			{
				// ���e���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// ���e���̏����}�K�W���ɉ��Z
				m_nBulletNumber_AR_magazine += m_nTotal_Magazine;
			}
		}
	}



	// �e�̎�ނ�SG�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_SG)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_SG_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SG_magazine % (int)pow(10, 1));

		// �����e����8�ȏゾ������
		if (m_nBulletNumber_SG_magazine >= 8)
		{
			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// �����e����7�ȉ�����1�ȏゾ������
		if (m_nBulletNumber_SG_magazine <= 7 && m_nBulletNumber_SG_magazine >= 1)
		{
			// �F�𔒂ɂ���
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// ���������O�ȉ��ɂȂ�����
		if (m_nBulletNumber_SG_magazine <= 0)
		{
			// 0�Œ�~����
			m_nBulletNumber_SG_magazine = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// R�L�[�EX�{�^������������
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SE�𗬂�
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// �e����7�ȉ�����1�ȏゾ������
			if (m_nBulletNumber_SG_magazine <= 7 || m_nBulletNumber_SG_magazine >= 1)
			{
				// �e����7�ȉ�����1�ȏゾ������
				if (m_nBulletNumber_SG_magazine <= 7 && m_nBulletNumber_SG_magazine >= 1)
				{
					// �����o��
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// �e����8�ȏゾ������
				if (m_nBulletNumber_SG_magazine >= 8)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				//�e�̍ő吔���猻�݂̒e��������
				m_nMagazine = MAX_BULLET_SG_MAGAZINE - m_nBulletNumber_SG_magazine;

				//���������𑍒e���������
				pBulletTotal->SubBulletTotal(m_nMagazine);

				//�g�[�^���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// ���e����0��������
				if (m_nTotal_Magazine <= 0)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// �g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_SG_magazine += m_nTotal_Magazine;

				// �}�K�W�����}�b�N�X�̒l�𒴂�����
				if (m_nBulletNumber_SG_magazine >= MAX_BULLET_SG_MAGAZINE)
				{
					// ����������
					m_nBulletNumber_SG_magazine = 0;

					// �}�K�W����10������
					m_nBulletNumber_SG_magazine = 8;
				}
			}

			// ���������O�ȉ��ɂȂ�����
			if (m_nBulletNumber_SG_magazine <= 0)
			{
				// �g�[�^���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// �g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_SG_magazine += m_nTotal_Magazine;
			}
		}
	}



	// �e�̎�ނ�SR�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_SR)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_SR_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SR_magazine % (int)pow(10, 1));

		// �����e����6�ȏゾ������
		if (m_nBulletNumber_SR_magazine >= 6)
		{
			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// �����e����5�ȉ�����1�ȏゾ������
		if (m_nBulletNumber_SR_magazine <= 5 && m_nBulletNumber_SR_magazine >= 1)
		{
			// �F�𔒂ɂ���
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		//��������0�ȉ��ɂȂ�����
		if (m_nBulletNumber_SR_magazine <= 0)
		{
			//0�Œ�~����
			m_nBulletNumber_SR_magazine = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// R�L�[�EX�{�^������������
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SE�𗬂�
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// �e����5�ȉ�����1�ȏゾ������
			if (m_nBulletNumber_SR_magazine <= 5 || m_nBulletNumber_SR_magazine >= 1)
			{
				// �e����5�ȉ�����1�ȏゾ������
				if (m_nBulletNumber_SR_magazine <= 5 && m_nBulletNumber_SR_magazine >= 1)
				{
					// �����o��
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);
				}

				// �e����6�ȏゾ������
				if (m_nBulletNumber_SR_magazine >= 6)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				//�@�e�̍ő吔���猻�݂̒e��������
				m_nMagazine = MAX_BULLET_SR_MAGAZINE - m_nBulletNumber_SR_magazine;

				//�@���������𑍒e���������
				pBulletTotal->SubBulletTotal(m_nMagazine);

				//�@�g�[�^���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// ���e����0�ȉ���������
				if (m_nTotal_Magazine <= 0)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				// �g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_SR_magazine += m_nTotal_Magazine;

				// �}�K�W�����}�b�N�X�̒l�𒴂�����
				if (m_nBulletNumber_SR_magazine >= MAX_BULLET_SR_MAGAZINE)
				{
					// ����������
					m_nBulletNumber_SR_magazine = 0;

					// �}�K�W����10������
					m_nBulletNumber_SR_magazine = 6;
				}
			}

			// ���������O�ȉ��ɂȂ�����
			if (m_nBulletNumber_SR_magazine <= 0)
			{
				// �g�[�^���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// �g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_SR_magazine += m_nTotal_Magazine;
			}
		}
	}



	// �e�̎�ނ�RL�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_RL)
	{
		//���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_RL_magazine / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_RL_magazine % (int)pow(10, 1));

		// �e����1�ȏゾ������
		if (m_nBulletNumber_HG_magazine >= 1)
		{
			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		//���������O�ȉ��ɂȂ�����
		if (m_nBulletNumber_RL_magazine <= 0)
		{
			//�O�Œ�~����
			m_nBulletNumber_RL_magazine = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// R�L�[�EX�{�^������������
		if (pInputKeyboard->GetKeyboardTrigger(DIK_R) == true || pInputGamepad->GetButtonTrigger(XINPUT_GAMEPAD_X))
		{
			// SE�𗬂�
			pSound->PlaySound(pSound->SOUND_LABEL_RELOAD);

			// �e����0�ȉ��ɂȂ�����
			if (m_nBulletNumber_RL_magazine <= 0)
			{
				// �����o��
				pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 1.0f);

				// �e�̍ő吔���猻�݂̒e��������
				m_nMagazine = MAX_BULLET_RL_MAGAZINE - m_nBulletNumber_RL_magazine;

				// ���������𑍒e���������
				pBulletTotal->SubBulletTotal(m_nMagazine);

				// ���e���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				// ���e����0�ȉ���������
				if (m_nTotal_Magazine <= 0)
				{
					// �����o���Ȃ�
					pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
				}

				//�g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_RL_magazine += m_nTotal_Magazine;

				//�}�K�W�����}�b�N�X�̒l�𒴂�����
				if (m_nBulletNumber_RL_magazine >= MAX_BULLET_RL_MAGAZINE)
				{
					//����������
					m_nBulletNumber_RL_magazine = 0;

					//�}�K�W����1������
					m_nBulletNumber_RL_magazine = 1;
				}
			}

			// �e����1�ȏゾ������
			else
			{
				// �����o���Ȃ�
				pSound->SoundVolume(CSound::SOUND_LABEL_RELOAD, 0.0f);
			}

			//���������O�ȉ��ɂȂ�����
			if (m_nBulletNumber_RL_magazine <= 0)
			{
				//�g�[�^���̏���n��
				m_nTotal_Magazine = pBulletTotal->GetBulletTotal();

				//�g�[�^���̏����}�K�W���ɉ��Z
				m_nBulletNumber_RL_magazine += m_nTotal_Magazine;
			}
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CBulletMagazine::Draw(void)
{
	// MAX_BULLET_MAGAZINE�̐���
	for (int nCnt = 0; nCnt < MAX_BULLET_MAGAZINE; nCnt++)
	{
		// �`�揈��
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// ���Z����
//=============================================================================
void CBulletMagazine::SubBulletMagazine(int nValue)
{
	// �|�C���^
	CPlayer *pPlayer = NULL;

	// �e�̎�ނ̏���n��
	m_nMagazineType = CPlayer::GetBulletType();

	// �e�̎�ނ�HG�������ꍇ
	if (m_nMagazineType == CBullet::TYPE_HG)
	{
		// nValue�̐�������
		m_nBulletNumber_HG_magazine -= nValue;
	}

	// �e�̎�ނ�AR�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_AR)
	{
		// nValue�̐�������
		m_nBulletNumber_AR_magazine -= nValue;
	}
	
	// �e�̎�ނ�SG�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_SG)
	{
		// nValue�̐�������
		m_nBulletNumber_SG_magazine -= nValue;
	}

	// �e�̎�ނ�SR�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_SR)
	{
		// nValue�̐�������
		m_nBulletNumber_SR_magazine -= nValue;
	}

	// �e�̎�ނ�RL�������ꍇ
	else if (m_nMagazineType == CBullet::TYPE_RL)
	{
		// nValue�̐�������
		m_nBulletNumber_RL_magazine -= nValue;
	}
}

//=============================================================================
// �n���h�K���e���̎擾����
//=============================================================================
int CBulletMagazine::GetBulletMagazineHG(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nBulletNumber_HG_magazine;
}

//=============================================================================
// �A�T���g���C�t���e���̎擾����
//=============================================================================
int CBulletMagazine::GetBulletMagazineAR(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nBulletNumber_AR_magazine;
}

//=============================================================================
// �V���b�g�K���e���̎擾����
//=============================================================================
int CBulletMagazine::GetBulletMagazineSG(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nBulletNumber_SG_magazine;
}

//=============================================================================
// �X�i�C�p�[���C�t���e���̎擾����
//=============================================================================
int CBulletMagazine::GetBulletMagazineSR(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nBulletNumber_SR_magazine;
}

//=============================================================================
// ���P�b�g�����`���[�e���̎擾����
//=============================================================================
int CBulletMagazine::GetBulletMagazineRL(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nBulletNumber_RL_magazine;
}

//=============================================================================
// �e�̎�ނ̎擾����
//=============================================================================
int CBulletMagazine::GetBulletType(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_nMagazineType;
}
