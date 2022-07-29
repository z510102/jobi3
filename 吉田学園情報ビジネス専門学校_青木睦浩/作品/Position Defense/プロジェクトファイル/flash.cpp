//=============================================================================
//
// �M������ [flash.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "flash.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CFlash::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFlash::CFlash(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFlash::~CFlash()
{

}

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CFlash::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/flash.png",		// �ǂݍ��ރt�@�C����
							  &m_pTexture);					// �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`���j��
//=============================================================================
void CFlash::Unload(void)
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
CFlash *CFlash::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �|�C���^
	CFlash *pFlash = NULL;

	// ���������m��
	pFlash = new CFlash(PRIORITY_ANIM_EFFECT);

	if (pFlash != NULL)
	{
		// ���ꂼ��̏����ւ�
		pFlash->Init(pos);
		pFlash->BindTexture(m_pTexture);

		// �����o�֏���n��
		pFlash->m_size = size;
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pFlash;
}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CFlash::Init(D3DXVECTOR3 pos)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_FLASH);

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CFlash::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CFlash::Update(void)
{
	//�ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����o�֏���n��
	m_pos = pos;

	// �T�C�Y��ݒ肷��
	SetSize(m_size.x, m_size.y);

	// m_nCounterAnim�����Z
	m_nCounterAnim++;

	if (m_nCounterAnim % 2)
	{
		// m_nPatternAnim�����Z
		m_nPatternAnim++;

		// ���_���X�V
		CScene2D::Update();

		// �e�N�X�`�����W�ݒ�
		SetVertexTexture(m_nPatternAnim, 0.125f, 0, 0, 0.125f, 1.0f);

		// m_nPatternAnim��8�ɂȂ����ꍇ
		if (m_nPatternAnim == 8)
		{
			// �I��������
			Uninit();
			return;
		}
	}

#if 0
	//�G�Ǝ��w�̓����蔻��
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
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

					if (m_pos.x + 50 >= pos.x - size.x &&
						m_pos.x - 50 <  pos.x + size.x &&
						m_pos.y + 50 >= pos.y - size.y &&
						m_pos.y - 50 <  pos.y + size.y)
					{
						CEnemy *pEnemy;
						pEnemy = CGame::GetEnemy();

						pEnemy->Stop();
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
void CFlash::Draw(void)
{
	// Scene2D�̕`�揈����
	CScene2D::Draw();
}