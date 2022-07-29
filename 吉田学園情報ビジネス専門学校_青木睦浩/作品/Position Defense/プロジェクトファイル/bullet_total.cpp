//=============================================================================
//
// ���e������ [bullet_total.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "bullet_total.h"
#include "manager.h"
#include "player.h"
#include "bullet_magazine.h"
#include "game.h"

//=============================================================================
// ��������
//=============================================================================
CBulletTotal *CBulletTotal::Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type)
{
	// �|�C���^
	CBulletTotal *pNumber;

	// ���������m��
	pNumber = new CBulletTotal (PRIORITY_NUMBER);

	if (pNumber != NULL)
	{
		// �����o�ϐ��֏���n��
		pNumber->m_size = D3DXVECTOR2(30, 30);
		pNumber->m_type_total = type;

		// ������
		pNumber->Init(pos);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pNumber;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletTotal::CBulletTotal(int nPriority) : CScene(nPriority)
{
	// �ϐ����N���A����
	memset(&m_apNumber[0], 0, sizeof(CNumber));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nBulletNumber_HG_total = 0;
	m_nBulletNumber_AR_total = 0;
	m_nBulletNumber_SG_total = 0;
	m_nBulletNumber_SR_total = 0;
	m_nBulletNumber_RL_total = 0;
	m_type_total = CBullet::TYPE_HG;
	m_nTotal = 0;
	m_nPass = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletTotal::~CBulletTotal()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBulletTotal::Init(D3DXVECTOR3 pos)
{
	// �|�C���^
	CPlayer *pPlayer = NULL;

	// �e�̎�ނ̏���n��
	m_nTotalType = CPlayer::GetBulletType();

	// MAX_BULLET_TOTAL�̐���
	for (int nCnt = 0; nCnt < MAX_BULLET_TOTAL; nCnt++)
	{
		// ����
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCnt, pos.y, 0.0f), m_size.x, m_size.y);
	}

	// ���l������
	m_nBulletNumber_HG_total = 9999;
	m_nBulletNumber_AR_total = 90;
	m_nBulletNumber_SG_total = 16;
	m_nBulletNumber_SR_total = 12;
	m_nBulletNumber_RL_total = 1;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBulletTotal::Uninit(void)
{
	// MAX_BULLET_TOTAL�̐���
	for (int nCnt = 0; nCnt < MAX_BULLET_TOTAL; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (m_apNumber[nCnt] != NULL)
		{
			// �i���o�[�̏I��������
			m_apNumber[nCnt]->Uninit();

			// �����o��NULL�ɂ���
			m_apNumber[nCnt] = NULL;

			// �����������
			delete m_apNumber[nCnt];
		}
	}

	// �I�u�W�F�N�g��j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBulletTotal::Update(void)
{
	// �|�C���^
	CPlayer *pPlayer = NULL;

	// �e�̎�ނ̏���n��
	m_nTotalType = CPlayer::GetBulletType();

	// �}�K�W���̎擾
	CBulletMagazine *pBulletMagazine;
	pBulletMagazine = CGame::GetBulletMagazine();

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();



	// ���e���̎�ނ�HG�������ꍇ
	if (m_nTotalType == CBullet::TYPE_HG)
	{
		// �F�𖳂��ɂ���i�\���ł��Ȃ�����j
		m_apNumber[0]->SetColor(0, 0, 0, 0);
		m_apNumber[1]->SetColor(0, 0, 0, 0);

		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_HG_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_HG_total % (int)pow(10, 1));

		// ���e�����P�O�ȏ゠��ꍇ
		if (m_nBulletNumber_HG_total >= 10)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineHG();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_HG_MAGAZINE - m_nPass;

			// ����n��
			m_nRemainingTotal = m_nTotal;
		}
	}



	// ���e���̎�ނ�AR�������ꍇ
	else if (m_nTotalType == CBullet::TYPE_AR)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_AR_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_AR_total % (int)pow(10, 1));

		// ���e����90�ȏゾ������
		if (m_nBulletNumber_AR_total >= 90)
		{
			// ���e����90�ɌŒ肷��
			m_nBulletNumber_AR_total = 90;

			// �i���o�[��90�ɂ���
			m_apNumber[0]->SetNumber(9);
			m_apNumber[1]->SetNumber(0);

			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// ���e����89�ȉ�����1�ȏゾ������
		else if (m_nBulletNumber_AR_total <= 89 && m_nBulletNumber_AR_total >= 1)
		{
			// �F�𔒂ɂ���
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// ���������O�ȉ��ɂȂ�����
		else if (m_nBulletNumber_AR_total <= 0)
		{
			// �O�Œ�~����
			m_nBulletNumber_AR_total = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// ���e����30�ȏ゠��ꍇ
		else if (m_nBulletNumber_AR_total >= 30)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineAR();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_AR_MAGAZINE - m_nPass;

			// ����n��
			m_nRemainingTotal = m_nTotal;
		}

		// ���e����9�ȉ��̏ꍇ
		else if (m_nBulletNumber_AR_total <= 9)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineAR();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_AR_MAGAZINE - m_nPass;

			// �ő吔����}�K�W���̏�������������30�������ꍇ
			if (m_nTotal == 30)
			{
				// �ő吔����}�K�W���̏���������������1�����ēn��
				m_nTotal = m_nTotal - 1;
			}

			// �}�K�W���̒e����29�ȉ������e����9�ȉ��������ꍇ
			if (m_nPass <= 29 && m_nBulletNumber_AR_total <= 9)
			{
				// 0�ɂ���
				m_nTotal = 0;

				// ����n��
				m_nTotal = m_nBulletNumber_AR_total;
			}

			// �c��̑��e���֓n��
			m_nRemainingTotal = m_nTotal;
		}
	}



	// �V���b�g�K���̏ꍇ
	else if (m_nTotalType == CBullet::TYPE_SG)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_SG_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SG_total % (int)pow(10, 1));

		// ���e����16�ȏゾ������
		if (m_nBulletNumber_SG_total >= 16)
		{
			// ���e����16�ɌŒ肷��
			m_nBulletNumber_SG_total = 16;

			// �i���o�[��16�ɂ���
			m_apNumber[0]->SetNumber(1);
			m_apNumber[1]->SetNumber(6);

			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// ���e����15�ȉ�����1�ȏゾ������
		else if (m_nBulletNumber_SG_total <= 15 && m_nBulletNumber_SG_total >= 1)
		{
			// �F�𔒂ɂ���
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// ���e�����O�ȉ��ɂȂ�����
		else if (m_nBulletNumber_SG_total <= 0)
		{
			// �O�Œ�~����
			m_nBulletNumber_SG_total = 0;

			// �i���o�[��00�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// ���e�����P�O�ȏ゠��ꍇ
		else if (m_nBulletNumber_SG_total >= 10)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineSG();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_SG_MAGAZINE - m_nPass;

			// �ő吔����}�K�W���̏�������������n��
			m_nRemainingTotal = m_nTotal;
		}

		// ���e�����X�ȉ��̏ꍇ
		else if (m_nBulletNumber_SG_total <= 9)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineSG();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_SG_MAGAZINE - m_nPass;

			// �ő吔����}�K�W���̏�������������8�������ꍇ
			if (m_nTotal == 8)
			{
				// �ő吔����}�K�W���̏���������������1�����ēn��
				m_nTotal = m_nTotal - 1;
			}

			// �}�K�W���̒e����7�ȉ������e����9�ȉ��������ꍇ
			if (m_nPass <= 7 && m_nBulletNumber_SG_total <= 9)
			{
				// 0�ɂ���
				m_nTotal = 0;

				// ����n��
				m_nTotal = m_nBulletNumber_SG_total;
			}

			// �c��̑��e���֓n��
			m_nRemainingTotal = m_nTotal;
		}
	}



	// �X�i�C�p�[���C�t���̏ꍇ
	else if (m_nTotalType == CBullet::TYPE_SR)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_SR_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_SR_total % (int)pow(10, 1));

		// ���e����12�ȏゾ������
		if (m_nBulletNumber_SR_total >= 12)
		{
			// ���e����12�ɌŒ肷��
			m_nBulletNumber_SR_total = 12;

			// �i���o�[��12�ɂ���
			m_apNumber[0]->SetNumber(1);
			m_apNumber[1]->SetNumber(2);

			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// ���e����11�ȉ�����1�ȏゾ������
		else if (m_nBulletNumber_SR_total <= 11 && m_nBulletNumber_SR_total >= 1)
		{
			// �F�𔒂ɂ���
			m_apNumber[0]->SetColor(255, 255, 255, 255);
			m_apNumber[1]->SetColor(255, 255, 255, 255);
		}

		// ���������O�ȉ��ɂȂ�����
		else if (m_nBulletNumber_SR_total <= 0)
		{
			// �O�Œ�~����
			m_nBulletNumber_SR_total = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// �e�����P�O�ȏ゠��ꍇ
		else if (m_nBulletNumber_SR_total >= 10)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineSR();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_SR_MAGAZINE - m_nPass;

			// ����n��
			m_nRemainingTotal = m_nTotal;
		}

		// ���e����9�ȉ��̏ꍇ
		else if (m_nBulletNumber_SR_total <= 9)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineSR();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_SR_MAGAZINE - m_nPass;

			// �ő吔����}�K�W���̏�������������6�������ꍇ
			if (m_nTotal == 6)
			{
				// �ő吔����}�K�W���̏���������������1�����ēn��
				m_nTotal = m_nTotal - 1;
			}

			// �}�K�W���̒e����5�ȉ������e����9�ȉ��̏ꍇ
			if (m_nPass <= 5 && m_nBulletNumber_SR_total <= 9)
			{
				// ���݂̑��e����0�ɂ���
				m_nTotal = 0;

				// ���e�������݂̑��e���ɓ����
				m_nTotal = m_nBulletNumber_SR_total;
			}

			// �c��̑��e���֓n��
			m_nRemainingTotal = m_nTotal;
		}
	}



	// ���P�b�g�����`���[�̏ꍇ
	else if (m_nTotalType == CBullet::TYPE_RL)
	{
		// ���������Z���ꂽ�X�R�A���v�Z����
		m_apNumber[0]->SetNumber(m_nBulletNumber_RL_total / (int)pow(10, 1));
		m_apNumber[1]->SetNumber(m_nBulletNumber_RL_total % (int)pow(10, 1));

		// ���e����1�ȏゾ������
		if (m_nBulletNumber_RL_total >= 1)
		{
			// ���e����1�ɌŒ肷��
			m_nBulletNumber_RL_total = 1;

			// �i���o�[��1�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(1);

			// �F��΂ɂ���
			m_apNumber[0]->SetColor(0, 255, 0, 255);
			m_apNumber[1]->SetColor(0, 255, 0, 255);
		}

		// ���������O�ȉ��ɂȂ�����
		else if (m_nBulletNumber_RL_total <= 0)
		{
			// �O�Œ�~����
			m_nBulletNumber_RL_total = 0;

			// �i���o�[��0�ɂ���
			m_apNumber[0]->SetNumber(0);
			m_apNumber[1]->SetNumber(0);

			// �F��Ԃɂ���
			m_apNumber[0]->SetColor(255, 0, 0, 255);
			m_apNumber[1]->SetColor(255, 0, 0, 255);
		}

		// �e�����P�O�ȏ゠��ꍇ
		else if (m_nBulletNumber_RL_total >= 10)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineRL();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_RL_MAGAZINE - m_nPass;

			// ����n��
			m_nRemainingTotal = m_nTotal;
		}

		// ���e����9�ȉ��̏ꍇ
		else if (m_nBulletNumber_RL_total <= 9)
		{
			// �}�K�W���̏���n��
			m_nPass = pBulletMagazine->GetBulletMagazineRL();

			// �ő吔����}�K�W���̏�������
			m_nTotal = MAX_BULLET_RL_MAGAZINE - m_nPass;

			// �ő吔����}�K�W���̏�������������1�������ꍇ
			if (m_nTotal == 1)
			{
				// �ő吔����}�K�W���̏���������������1�����ēn��
				m_nTotal = m_nTotal - 1;
			}

			// �}�K�W���̒e����1�ȉ������e����9�ȉ��̏ꍇ
			if (m_nPass <= 1 && m_nBulletNumber_RL_total <= 9)
			{
				// ���݂̑��e����0�ɂ���
				m_nTotal = 0;

				// ���e�������݂̑��e���ɓ����
				m_nTotal = m_nBulletNumber_RL_total;
			}

			// �c��̑��e���֓n��
			m_nRemainingTotal = m_nTotal;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBulletTotal::Draw(void)
{
	// MAX_BULLET_TOTAL�̐���
	for (int nCnt = 0; nCnt < MAX_BULLET_TOTAL; nCnt++)
	{
		// �i���o�[��`�悷��
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CBulletTotal::SetBulletTotal(int nBulletNumber)
{
	// �������n���h�K�����e���֓n��
	m_nBulletNumber_HG_total = nBulletNumber;
}

//=============================================================================
// ���Z����
//=============================================================================
void CBulletTotal::SubBulletTotal(int nValue)
{
	// �e�̎�ނ̏���n��
	m_nTotalType = CPlayer::GetBulletType();

	// �e�̎�ނ��n���h�K���������ꍇ
	if (m_nTotalType == CBullet::TYPE_HG)
	{
		// ���e���ƈ����������đ��e���ɓn��
		m_nBulletNumber_HG_total -= nValue;
	}

	// �e�̎�ނ��A�T���g���C�t���������ꍇ
	else if (m_nTotalType == CBullet::TYPE_AR)
	{
		// ���e���ƈ����������đ��e���ɓn��
		m_nBulletNumber_AR_total -= nValue;
	}

	// �e�̎�ނ��V���b�g�K���������ꍇ
	else if (m_nTotalType == CBullet::TYPE_SG)
	{
		// ���e���ƈ����������đ��e���ɓn��
		m_nBulletNumber_SG_total -= nValue;
	}

	// �e�̎�ނ��X�i�C�p�[���C�t���������ꍇ
	else if (m_nTotalType == CBullet::TYPE_SR)
	{
		// ���e���ƈ����������đ��e���ɓn��
		m_nBulletNumber_SR_total -= nValue;
	}

	// �e�̎�ނ����P�b�g�����`���[�������ꍇ
	else if (m_nTotalType == CBullet::TYPE_RL)
	{
		// ���e���ƈ����������đ��e���ɓn��
		m_nBulletNumber_RL_total -= nValue;
	}
}

//=============================================================================
// �X�R�A�̎擾����
//=============================================================================
int CBulletTotal::GetBulletTotal(void)
{
	// �c��̑��e����Ԃ�
	return m_nRemainingTotal;
}

//=============================================================================
// �n���h�K���̑��e���̉��Z����
//=============================================================================
void CBulletTotal::AddBulletTotalHG(int nValue)
{
	// �n���h�K���̑��e���ƈ����𑫂��ăn���h�K���̑��e���֓n��
	m_nBulletNumber_HG_total += nValue;
}

//=============================================================================
// �A�T���g���C�t���̑��e���̉��Z����
//=============================================================================
void CBulletTotal::AddBulletTotalAR(int nValue)
{
	// �A�T���g���C�t���̑��e���ƈ����𑫂��ăA�T���g���C�t���̑��e���֓n��
	m_nBulletNumber_AR_total += nValue;
}

//=============================================================================
// �V���b�g�K���̑��e���̉��Z����
//=============================================================================
void CBulletTotal::AddBulletTotalSG(int nValue)
{
	// �V���b�g�K���̑��e���ƈ����𑫂��ăV���b�g�K���̑��e���֓n��
	m_nBulletNumber_SG_total += nValue;
}

//=============================================================================
// �X�i�C�p�[���C�t���̑��e���̉��Z����
//=============================================================================
void CBulletTotal::AddBulletTotalSR(int nValue)
{
	// �X�i�C�p�[���C�t���̑��e���ƈ����𑫂��ăX�i�C�p�[���C�t���̑��e���֓n��
	m_nBulletNumber_SR_total += nValue;
}

//=============================================================================
// ���P�b�g�����`���[�̑��e���̉��Z����
//=============================================================================
void CBulletTotal::AddBulletTotalRL(int nValue)
{
	// ���P�b�g�����`���[�̑��e���ƈ����𑫂��ă��P�b�g�����`���[�̑��e���֓n��
	m_nBulletNumber_RL_total += nValue;
}
