//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "game.h"
#include "player.h"
#include "input_keyboard.h"
#include "enemy.h"
#include "score.h"
#include "high_score.h"
#include "position.h"
#include "straight.h"
#include "UI.h"
#include "fade.h"
#include "time.h"
#include "life.h"
#include "grenade.h"
#include "flash_grenade.h"
#include "g_possession.h"
#include "f_g_possession.h"
#include "bullet_magazine.h"
#include "bullet_total.h"
#include "explosion.h"
#include "item.h"
#include "sound.h"
#include "flash.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer *CGame::m_pPlayer = NULL;
CBg *CGame::m_pBg = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CScore *CGame::m_pScore = NULL;
CPosition *CGame::m_pPosition = NULL;
CHighScore *CGame::m_pHighScore = NULL;
CUI *CGame::m_pUI = NULL;
CTime *CGame::m_pTime = NULL;
CLife *CGame::m_pLife = NULL;
CG_Possession *CGame::m_pG_Possession = NULL;
CF_G_Possession *CGame::m_pF_G_Possession = NULL;
CBulletMagazine *CGame::m_pBulletMagazine = NULL;
CBulletTotal *CGame::m_pBulletTotal = NULL;
CExplosion *CGame::m_pExplosion = NULL;
CFlash *CGame::m_pFlash = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	// �ϐ����N���A
	m_nSpawn = 0;
	m_nSpawn2 = 0;
	m_nSpawn3 = 0;
	m_nSpawn4 = 0;
	m_nSpawn5 = 0;
	m_nSpawn6 = 0;
	m_nSpawn7 = 0;
	m_nCntSpawn = 0;
	m_nCntLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �e�N�X�`���ǂݍ��݂�
	Load();

	// �w�i�𐶐�
	m_pBg = CBg::Create();

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(458, 685, 0));

#if 0
	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(125, 80, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);*/

	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(130, 130, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(130, 180, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);*/

	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 80, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 130, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 180, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 80, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 130, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 180, 0), D3DXVECTOR3(0, 0.25f, 0), CEnemy::TYPE_0);*/

	/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(160, 80, 0),  D3DXVECTOR3(0, 1, 0),    CEnemy::TYPE_1);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(190, 80, 0),  D3DXVECTOR3(0, 1.5f, 0), CEnemy::TYPE_2);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(220, 80, 0),  D3DXVECTOR3(0, 2, 0),    CEnemy::TYPE_3);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(250, 80, 0),  D3DXVECTOR3(0, 2.5f, 0), CEnemy::TYPE_4);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(280, 80, 0),  D3DXVECTOR3(0, 3, 0),    CEnemy::TYPE_5);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(20, 30, 0),   D3DXVECTOR3(2, 0, 0),    CEnemy::TYPE_6);*/
#endif

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(1130, 100, 0), D3DXVECTOR2(30, 40));

	// �n�C�X�R�A�̐���
	m_pHighScore = CHighScore::Create(D3DXVECTOR3(1130, 50, 0));

	// �|�W�V�����̐���
	m_pPosition = CPosition::Create(D3DXVECTOR3(457, 685, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	// UI�̐���
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 50, 0),  D3DXVECTOR2(70, 20),  CUI::TYPE_HIGH_SCORE);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 100, 0), D3DXVECTOR2(70, 20),  CUI::TYPE_SCORE);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 170, 0), D3DXVECTOR2(70, 20),  CUI::TYPE_TIME);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 240, 0), D3DXVECTOR2(70, 20),  CUI::TYPE_LIFE);
	m_pUI = CUI::Create(D3DXVECTOR3(1000, 330, 0), D3DXVECTOR2(70, 40),  CUI::TYPE_GRENADE);
	m_pUI = CUI::Create(D3DXVECTOR3(1190, 330, 0), D3DXVECTOR2(70, 40),  CUI::TYPE_FLASH_GRENADE);
	m_pUI = CUI::Create(D3DXVECTOR3(1100, 480, 0), D3DXVECTOR2(170, 80), CUI::TYPE_WEAPON);
	m_pUI = CUI::Create(D3DXVECTOR3(1100, 630, 0), D3DXVECTOR2(200, 30), CUI::TYPE_RELOAD);
	m_pUI = CUI::Create(D3DXVECTOR3(1235, 515, 0), D3DXVECTOR2(25, 20),  CUI::TYPE_INFINITE);

	// �^�C���̐���
	m_pTime = CTime::Create(D3DXVECTOR3(1130, 170, 0));

	// ���C�t�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(1100, 240, 0));

	// �O���l�[�h�������̐���
	m_pG_Possession = CG_Possession::Create(D3DXVECTOR3(1000, 310, 0));

	// �t���b�V���O���l�[�h�������̐���
	m_pF_G_Possession = CF_G_Possession::Create(D3DXVECTOR3(1190, 310, 0));

	// �}�K�W���̐���
	m_pBulletMagazine = CBulletMagazine::Create(D3DXVECTOR3(1140, 510, 0), CBullet::TYPE_HG);

	// ���e���̐���
	m_pBulletTotal = CBulletTotal::Create(D3DXVECTOR3(1220, 515, 0), CBullet::TYPE_HG);

	// ����炷
	pSound->PlaySound(pSound->SOUND_LABEL_GAME_BGM);

	// ���ʂ𒲐�
	pSound->SoundVolume(CSound::SOUND_LABEL_GAME_BGM, 3.0f);

	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	// �e�N�X�`���j����
	Unload();

	// �T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �T�E���h�̒�~
	pSound->StopSound();

	// �I�u�W�F�N�g�̔j����
	Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���C�t�̎擾
	CLife *pLife;
	pLife = CGame::GetLife();

	// �X�R�A�������o�֓n��
	int nScore = m_pScore->GetScore();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	//Enter�L�[����������
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//�N���A��ʂ�
		pFade->SetFade(CManager::MODE_CLEAR);
	}

	// �X�|�[���l�����Z
	m_nSpawn++;
	m_nSpawn7++;

	// �����_���ŏo���ʒu�����߂�
	float fPosX = (float)(rand() % 666 + 125);

	// m_nSpawn��350�ȏ�ɂȂ����ꍇ
	if (m_nSpawn >= 350)
	{
		//�G�̐���
		m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.2f, 0), CEnemy::TYPE_0);

		// 0�ɂ���
		m_nSpawn = 0;
	}

	// m_nSpawn7��1050�ȏォ��m_nCntSpawn��0�̏ꍇ
	if (m_nSpawn7 >= 1050 && m_nCntSpawn == 0)
	{
		// 1��2�����߂Ēl������
		int nSpawn = (int)(rand() % 2 + 1);

		switch (nSpawn)
		{
		// 1�̏ꍇ
		case 1:
			// �����ƓG�𐶐�
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR3(1.0f, 0, 0), CEnemy::TYPE_6);
			break;

		// 2�̏ꍇ
		case 2:
			// �����ƓG�𐶐�
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR3(-1.0f, 0, 0), CEnemy::TYPE_6);
			break;
		}

		// m_nSpawn7��0�ɂ���
		m_nSpawn7 = 0;

		// m_nCntSpawn�����Z����
		m_nCntSpawn++;
	}

	// m_nSpawn7��2100�ȏォ��m_nCntSpawn��1�ȏ�̏ꍇ
	else if (m_nSpawn7 >= 2100 && m_nCntSpawn >= 1)
	{
		// 1��2�����߂�nSpawn�ɓ����
		int nSpawn = (int)(rand() % 2 + 1);

		switch (nSpawn)
		{
		// 1�̏ꍇ
		case 1:
			// �����ƓG�𐶐�
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(30, 30, 0), D3DXVECTOR3(1.0f, 0, 0), CEnemy::TYPE_6);
			break;

		// 2�̏ꍇ
		case 2:
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(880, 30, 0), D3DXVECTOR3(-1.0f, 0, 0), CEnemy::TYPE_6);
			break;
		}

		// m_nSpawn7��0�ɂ���
		m_nSpawn7 = 0;

		// m_nCntSpawn�����Z����
		m_nCntSpawn++;
	}

	// nScore��50�ȏ�ɂȂ����ꍇ
	if (nScore >= 50)
	{
		// m_nSpawn2�����Z����
		m_nSpawn2++;

		// m_nSpawn2��455�ɂȂ����ꍇ
		if (m_nSpawn2 >= 455)
		{
			//�G�Ɣ����̐���
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.3f, 0), CEnemy::TYPE_1);

			// m_nSpawn2��0�ɂ���
			m_nSpawn2 = 0;
		}
	}

	// m_nScore��150�ȏ�ɂȂ����ꍇ
	else if (nScore >= 150)
	{
		// m_nSpawn3�����Z����
		m_nSpawn3++;

		// m_nSpawn3��525�ɂȂ����ꍇ
		if (m_nSpawn3 >= 525)
		{
			//�G�Ɣ����̐���
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.4f, 0), CEnemy::TYPE_2);

			// m_nSpawn3��0�ɂ���
			m_nSpawn3 = 0;
		}
	}

	// m_nScore��300�ȏ�ɂȂ����ꍇ
	else if (nScore >= 300)
	{
		// m_nSpawn4�����Z����
		m_nSpawn4++;

		// m_nSpawn4��595�ɂȂ����ꍇ
		if (m_nSpawn4 >= 595)
		{
			//�G�Ɣ����̐���
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.5f, 0), CEnemy::TYPE_3);

			// m_nSpawn4��0�ɂ���
			m_nSpawn4 = 0;
		}
	}

	// m_nScore��500�ȏ�ɂȂ����ꍇ
	else if (nScore >= 500)
	{
		// m_nSpawn5�����Z����
		m_nSpawn5++;

		// m_nSpawn5��665�ɂȂ����ꍇ
		if (m_nSpawn5 >= 665)
		{
			//�G�Ɣ����̐���
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.6f, 0), CEnemy::TYPE_4);

			// m_nSpawn5��0�ɂ���
			m_nSpawn5 = 0;
		}
	}

	// m_nScore��750�ȏ�ɂȂ����ꍇ
	else if (nScore >= 750)
	{
		// m_nSpawn6�����Z����
		m_nSpawn6++;

		// m_nSpawn6��725�ɂȂ����ꍇ
		if (m_nSpawn6 >= 725)
		{
			//�G�Ɣ����̐���
			m_pExplosion = CExplosion::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(0.5f, 0.25f, 0.16f, 1.0f), CExplosion::TYPE_APPEARANCE);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(fPosX, 80, 0), D3DXVECTOR3(0, 0.7f, 0), CEnemy::TYPE_5);

			// m_nSpawn6��0�ɂ���
			m_nSpawn6 = 0;
		}
	}

	// �X�R�A��1000�ȏォ��m_nCntLife��0�̏ꍇ
	if (nScore >= 1000 && m_nCntLife == 0)
	{
		// ���C�t�����Z����
		pLife->AddLife(1);

		// m_nCntLife�����Z����
		m_nCntLife++;
	}

	// �X�R�A��2000�ȏォ��m_nCntLife��1�̏ꍇ
	else if (nScore >= 2000 && m_nCntLife == 1)
	{
		// ���C�t�����Z����
		pLife->AddLife(1);

		// m_nCntLife�����Z����
		m_nCntLife++;
	}

	// �X�R�A��3000�ȏォ��m_nCntLife��2�̏ꍇ
	else if (nScore >= 3000 && m_nCntLife == 2)
	{
		// ���C�t�����Z����
		pLife->AddLife(1);

		// m_nCntLife�����Z����
		m_nCntLife++;
	}

	// �X�R�A��4000�ȏォ��m_nCntLife��3�̏ꍇ
	else if (nScore >= 4000 && m_nCntLife == 3)
	{
		// ���C�t�����Z����
		pLife->AddLife(1);

		// m_nCntLife�����Z����
		m_nCntLife++;
	}

	// �X�R�A��5000�ȏォ��m_nCntLife��4�̏ꍇ
	else if (nScore >= 5000 && m_nCntLife == 4)
	{
		// ���C�t�����Z����
		pLife->AddLife(1);

		// m_nCntLife�����Z����
		m_nCntLife++;
	}
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{
	
}

//=============================================================================
// �Q�[���̐���
//=============================================================================
CGame *CGame::Create(void)
{
	// �|�C���^
	CGame *pGame;

	// ���������m��
	pGame = new CGame;

	if (pGame != NULL)
	{
		// Init������
		pGame->Init(D3DXVECTOR3(0, 0, 0));
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pGame;
}

//=============================================================================
// �Q�[���N���A
//=============================================================================
void CGame::Clear(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �N���A��ʂ�
	pFade->SetFade(CManager::MODE_CLEAR);
}

//=============================================================================
// �Q�[���I�[�o�[
//=============================================================================
void CGame::Over(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �I�[�o�[��ʂ�
	pFade->SetFade(CManager::MODE_OVER);
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CGame::Load(void)
{
	// ���ꂼ��̃e�N�X�`���ǂݍ��ݏ�����
	CBg::Load();
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	CNumber::Load();
	CStraight::Load();
	CPosition::Load();
	CUI::Load();
	CGrenade::Load();
	CFlashGrenade::Load();
	CItem::Load();
	CFlash::Load();

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CGame::Unload(void)
{
	// ���ꂼ��̃e�N�X�`���j��������
	CBg::Unload();
	CPlayer::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CNumber::Unload();
	CStraight::Unload();
	CPosition::Unload();
	CUI::Unload();
	CGrenade::Unload();
	CFlashGrenade::Unload();
	CItem::Unload();
	CFlash::Unload();
}





//=============================================================================
// �G�l�~�[�N���X���擾
//=============================================================================
CEnemy * CGame::GetEnemy(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pEnemy;
}

//=============================================================================
// �X�R�A�N���X���擾
//=============================================================================
CScore * CGame::GetScore(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pScore;
}

//=============================================================================
// �|�W�V�����N���X���擾
//=============================================================================
CPosition * CGame::GetPosition(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pPosition;
}

//=============================================================================
// UI�N���X���擾
//=============================================================================
CUI * CGame::GetUI(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pUI;
}

//=============================================================================
// �^�C���N���X���擾
//=============================================================================
CTime * CGame::GetTime(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pTime;
}

//=============================================================================
// ���C�t�N���X���擾
//=============================================================================
CLife * CGame::GetLife(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pLife;
}

//=============================================================================
// �O���l�[�h�������N���X���擾
//=============================================================================
CG_Possession * CGame::GetG_Possession(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pG_Possession;
}

//=============================================================================
// �t���b�V���O���l�[�h�������N���X���擾
//=============================================================================
CF_G_Possession * CGame::GetF_G_Possession(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pF_G_Possession;
}

//=============================================================================
// �}�K�W���N���X���擾
//=============================================================================
CBulletMagazine * CGame::GetBulletMagazine(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pBulletMagazine;
}

//=============================================================================
// ���e���N���X���擾
//=============================================================================
CBulletTotal * CGame::GetBulletTotal(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pBulletTotal;
}

//=============================================================================
// �����N���X���擾
//=============================================================================
CExplosion * CGame::GetExplosion(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pExplosion;
}

//=============================================================================
// �M���N���X���擾
//=============================================================================
CFlash * CGame::GetFlash(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pFlash;
}
