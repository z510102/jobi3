//=============================================================================
//
// �������� [explosion.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "explosion.h"
#include "manager.h"
#include "enemy.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/explosion000.png",		// �ǂݍ��ރt�@�C����
							  &m_pTexture);							// �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`���j��
//=============================================================================
void CExplosion::Unload(void)
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR color, EXPLOSION_TYPE type)
{
	// �|�C���^
	CExplosion *pExplosion = NULL;

	// ���������m��
	pExplosion = new CExplosion (PRIORITY_ANIM_EFFECT);

	if (pExplosion != NULL)
	{
		// ���ꂼ��̏�����
		pExplosion->Init(pos);
		pExplosion->BindTexture(m_pTexture);

		// �����o�֏���n��
		pExplosion->m_color = color;
		pExplosion->m_size = size;
		pExplosion->m_Type = type;
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pExplosion;
}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_EXPLOSION);

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CExplosion::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CExplosion::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �����o�֏���n��
	m_pos = pos;

	// ���_�J���[��ݒ�
	SetColor(m_color);

	// �T�C�Y��ݒ�
	SetSize(m_size.x, m_size.y);

	// m_nCounterAnim�����Z
	m_nCounterAnim++;

	if (m_nCounterAnim % 2)
	{
		// m_nPatternAnim���Z
		m_nPatternAnim++;

		// Scene2D�̍X�V������
		CScene2D::Update();

		// �e�N�X�`�����W�X�V
		SetVertexTexture(m_nPatternAnim, 0.125f, 0, 0, 0.125f, 1.0f);

		// m_nPatternAnim��8�ɂȂ����ꍇ
		if (m_nPatternAnim == 8)
		{
			// �I��������
			Uninit();
			return;
		}
	}

	//�G�Ǝ��w�̓����蔻��
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// �I�u�W�F�N�g���擾
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			// �G���擾
			CEnemy *pEnemy;
			pEnemy = CGame::GetEnemy();

			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�̎�ނ��擾
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				// �I�u�W�F�N�g�̎�ނ��G�l�~�[�̏ꍇ
				if (objType == OBJTYPE_ENEMY)
				{
					// �����̎�ނ�TYPE_G�̏ꍇ
					if (m_Type == TYPE_G)
					{
						//�L���X�g�i�^�ϊ�����2D�|���S���N���X�ɂ���ʒu�����擾�j
						D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
						D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

						if (m_pos.x + 30 >= pos.x - size.x &&
							m_pos.x - 30 <  pos.x + size.x &&
							m_pos.y + 30 >= pos.y - size.y &&
							m_pos.y - 30 <  pos.y + size.y)
						{
							// �G�̏I��������
							pScene->Uninit();

							// �G��|�����Ƃ��̏�����
							pEnemy->KnockDown();
						}
					}

					// �����̎�ނ�TYPE_RL�̏ꍇ
					if (m_Type == TYPE_RL)
					{
						//�L���X�g�i�^�ϊ�����2D�|���S���N���X�ɂ���ʒu�����擾�j
						D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
						D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

						if (m_pos.x + 90 >= pos.x - size.x &&
							m_pos.x - 90 <  pos.x + size.x &&
							m_pos.y + 90 >= pos.y - size.y &&
							m_pos.y - 90 <  pos.y + size.y)
						{
							// ����炷
							pSound->PlaySound(pSound->SOUND_LABEL_BOMB);

							// ���ʂ𒲐�
							pSound->SoundVolume(CSound::SOUND_LABEL_BOMB, 1.0f);

							// �G�̏I��������
							pScene->Uninit();

							// �G��|�����Ƃ��̏�����
							pEnemy->KnockDown();
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// 2D�|���S���̕`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	// Scene2D�̕`�揈����
	CScene2D::Draw();
}