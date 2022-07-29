//=============================================================================
//
// �O���l�[�h���� [grenade.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "grenade.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "straight.h"
#include "g_possession.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CGrenade::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGrenade::CGrenade(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_bUse = true;
	m_nPassG = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGrenade::~CGrenade()
{

}

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CGrenade::Load(void)
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
void CGrenade::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �O���l�[�h�̎g�p��������
//=============================================================================
void CGrenade::NotUse(void)
{
	// �O���l�[�h���������擾
	CG_Possession *pG_Possession;
	pG_Possession = CGame::GetG_Possession();

	// �����o�֏���n��
	m_nPassG = pG_Possession->GetG_Ppssession();

	// �O���l�[�h��������-1�ȉ��ɂȂ�����
	if (m_nPassG <= -1)
	{
		// �g�p�ł��Ȃ�����
		m_bUse = false;
	}
}

//=============================================================================
// 2D�|���S���̐���
//=============================================================================
CGrenade *CGrenade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// �|�C���^
	CGrenade *pGrenade = NULL;

	// ���������m��
	pGrenade = new CGrenade(PRIORITY_GRENADE);

	if (pGrenade != NULL)
	{
		// ������
		pGrenade->Init(pos, move);
		pGrenade->SetSize(6, 6);
		pGrenade->BindTexture(m_pTexture);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pGrenade;
}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CGrenade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_GRENADE);

	// �����o�֏���n��
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CGrenade::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CGrenade::Update(void)
{
	// �O���l�[�h���������擾
	CG_Possession *pG_Possession;
	pG_Possession = CGame::GetG_Possession();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	/*int nPassG = 0;
	nPassG = pG_Possession->GetG_Ppssession();*/

	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����o�֏���n��
	m_pos = pos;

	// �O���l�[�h�̈ړ�
	m_pos.y += m_move.y;

	// Scene2D�̍X�V������
	CScene2D::Update();

	// �ʒu�̐ݒ菈��
	SetPosition(m_pos);

	// �G�t�F�N�g�𐶐�
	CStraight::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 8, m_pos.z), D3DXVECTOR2(8, 16), 0, 128, 0, 255, 0, 10, 0, 0, 10);

	// �O���l�[�h�g�p����������
	NotUse();

	// �ʒu���w�肵�����W�̐��l�ȏ�ɂ����Ďg�p����Ă��邩���͈ʒu���w�肵�����l�̐��l�ȏ�ɂ����Ďg�p����Ă��Ȃ��ꍇ
	if (SCREEN_HEIGHT - 400 >= m_pos.y && m_bUse == true || SCREEN_HEIGHT - 400 >= m_pos.y && m_bUse == false)
	{
		// �������擾
		CExplosion *pExplosion;
		pExplosion = CGame::GetExplosion();

		// ����炷
		pSound->PlaySound(pSound->SOUND_LABEL_BOMB);

		// ���ʂ𒲐�
		pSound->SoundVolume(CSound::SOUND_LABEL_BOMB, 1.0f);

		// �����̐���
		pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(100, 100), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CExplosion::TYPE_G);

		// �I��������
		Uninit();
	}

	// �ʒu���w�肵�����W�̐��l�ȉ��Ŏg�p����Ă��Ȃ��ꍇ
	else if (SCREEN_HEIGHT - 400 <= m_pos.y && m_bUse == false)
	{
		// �g�p����
		m_bUse = true;
	}

	// �O���l�[�h�g�p����������
	NotUse();

	// ���ˈʒu���e���ړ����Ă��Ȃ��Ďg�p����Ă��Ȃ������ꍇ
	if (SCREEN_HEIGHT - 100 <= m_pos.y && m_bUse == false)
	{
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

						CExplosion *pExplosion;
						pExplosion = CGame::GetExplosion();

						//�X�R�A���Z
						pScore->AddScore(10);

						//�����̐���
						pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(88, 88), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

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
void CGrenade::Draw(void)
{
	// Scene2D�̕`�揈����
	CScene2D::Draw();
}