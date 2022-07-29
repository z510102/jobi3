//=============================================================================
//
// �t���b�V���O���l�[�h���� [flash_grenade.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "flash_grenade.h"
#include "manager.h"
#include "game.h"
#include "flash.h"
#include "straight.h"
#include "f_g_possession.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CFlashGrenade::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFlashGrenade::CFlashGrenade(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_bUse = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFlashGrenade::~CFlashGrenade()
{

}

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CFlashGrenade::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						 // �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/bullet000.png",	 // �ǂݍ��ރt�@�C����
							  &m_pTexture);					 // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`���j��
//=============================================================================
void CFlashGrenade::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 2D�|���S���̐���
//=============================================================================
CFlashGrenade *CFlashGrenade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// �|�C���^
	CFlashGrenade *pFlashGrenade = NULL;

	// ���������m��
	pFlashGrenade = new CFlashGrenade(PRIORITY_GRENADE);

	if (pFlashGrenade != NULL)
	{
		// ������
		pFlashGrenade->Init(pos, move);
		pFlashGrenade->SetSize(6, 6);
		pFlashGrenade->BindTexture(m_pTexture);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pFlashGrenade;
}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CFlashGrenade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_FLASH_GRENADE);

	// �����o�֏���n��
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CFlashGrenade::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CFlashGrenade::Update(void)
{
	// �t���b�V���O���l�[�h���������擾
	CF_G_Possession *pF_G_Possession;
	pF_G_Possession = CGame::GetF_G_Possession();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �t���b�V���O���l�[�h�������̏���n��
	int nPassF_G = 0;
	nPassF_G = pF_G_Possession->GetF_G_Ppssession();

	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����o�֏���n��
	m_pos = pos;

	// �t���b�V���O���l�[�h�̈ړ�
	m_pos.y += m_move.y;

	// Scene2D�̍X�V������
	CScene2D::Update();

	// �ʒu�̐ݒ菈����
	SetPosition(m_pos);

	// �G�t�F�N�g�𐶐�
	CStraight::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 8, m_pos.z), D3DXVECTOR2(8, 16), 24, 235, 249, 255, 0, 10, 0, 0, 10);

	// �t���b�V���O���l�[�h��������-1�ȉ��ɂȂ����ꍇ
	if (nPassF_G <= -1)
	{
		// �g�p�ł��Ȃ�����
		m_bUse = false;

		// �I��������
		Uninit();
	}

	// �e�̈ʒu���w�肵���ʒu�𒴂����Ƃ�
	if (SCREEN_HEIGHT - 400 >= m_pos.y)
	{
		// �M�����擾
		CFlash *pFlash;
		pFlash = CGame::GetFlash();

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_FLASH_BOMB);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_FLASH_BOMB, 1.0f);

		// �����̐���
		pFlash->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(100, 100));

		// �I��������
		Uninit();
	}

#if 0
	//�e�ƓG�̓����蔻��
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == OBJTYPE_ENEMY)
				{
					//�L���X�g�i�^�ϊ�����2D�|���S���N���X�ɂ���ʒu�����擾�j
					D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
					D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

					if (m_pos.x >= pos.x - size.x / 2 &&
						m_pos.x <  pos.x + size.x / 2 &&
						m_pos.y >= pos.y - size.y / 2 &&
						m_pos.y <  pos.y + size.y / 2)
					{
						//�X�R�A���擾
						CScore *pScore;
						pScore = CGame::GetScore();

						//�X�R�A���Z
						pScore->AddScore(10);

						//�����̐���
						/*CExplosion::Create(pos);*/

						//�G�̔j��
						pScene->Uninit();

						//�e�̔j��
						Uninit();
					}
				}
			}
		}
	}
#endif
}

//=============================================================================
// 2D�|���S���̕`�揈��
//=============================================================================
void CFlashGrenade::Draw(void)
{
	// Scene2D�̕`���
	CScene2D::Draw();
}