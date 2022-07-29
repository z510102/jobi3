//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "item.h"
#include "manager.h"
#include "bullet_total.h"
#include "time.h"
#include "game.h"
#include "g_possession.h"
#include "f_g_possession.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItem::CItem(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_type = TYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CItem::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/item_AR.png",			// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_AR]);				// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/item_SG.png",			// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_SG]);				// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/item_SR.png",			// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_SR]);				// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/item_RL.png",			// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_RL]);				// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/item_G.png",			// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_G]);				// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/item_FG.png",			// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_FG]);				// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,								// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/item_TIME.png",			// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_TIME]);				// �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`���j��
//=============================================================================
void CItem::Unload(void)
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
// 2D�|���S���̐�������
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ITEM_TYPE type)
{
	// �|�C���^
	CItem *pItem;

	// ���������m��
	pItem = new CItem (PRIORITY_ITEM);

	if (pItem != NULL)
	{
		// ������
		pItem->Init(pos, move);
		pItem->SetSize(11, 11);
		pItem->BindTexture(m_apTexture[type]);

		// �����o�֏���n��
		pItem->m_type = type;
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pItem;
}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_ITEM);

	// �����������o�֓n��
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CItem::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CItem::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����o�֏���n��
	m_pos = pos;

	// pos��move�𑫂���pos�֓n��
	m_pos.y += m_move.y;

	// Scene2D�̍X�V������
	CScene2D::Update();

	// �ʒu�̐ݒ菈����
	SetPosition(m_pos);

	//�A�C�e���ƃv���C���[�̓����蔻��
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

				if (objType == OBJTYPE_PLAYER)
				{
					// �L���X�g�i�^�ϊ�����2D�|���S���N���X�ɂ���ʒu�����擾�j
					D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
					D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

					if (m_pos.x >= pos.x - size.x &&
						m_pos.x <  pos.x + size.x &&
						m_pos.y >= pos.y - size.y &&
						m_pos.y <  pos.y + size.y)
					{
						// �^�C�����擾
						CTime *pTime;
						pTime = CGame::GetTime();

						// ���e�����擾
						CBulletTotal *pBulletTotal;
						pBulletTotal = CGame::GetBulletTotal();

						// �O���l�[�h���������擾
						CG_Possession *pG_Possession;
						pG_Possession = CGame::GetG_Possession();

						// �t���b�V���O���l�[�h���������擾
						CF_G_Possession *pF_G_Possession;
						pF_G_Possession = CGame::GetF_G_Possession();

						// �A�C�e���̎�ނɂ���đ��e���E���Ԃ����Z����
						switch (m_type)
						{
						case TYPE_AR:
							pBulletTotal->AddBulletTotalAR(30);
							break;

						case TYPE_SG:
							pBulletTotal->AddBulletTotalSG(8);
							break;

						case TYPE_SR:
							pBulletTotal->AddBulletTotalSR(6);
							break;

						case TYPE_RL:
							pBulletTotal->AddBulletTotalRL(1);
							break;

						case TYPE_G:
							pG_Possession->AddG_Ppssession(1);
							break;

						case TYPE_FG:
							pF_G_Possession->AddF_G_Ppssession(1);
							break;

						case TYPE_TIME:
							pTime->AddTime(30);
							break;

						default:
							break;
						}


						// �I��������
						Uninit();
					}
				}
			}
		}
	}

	// �ʒu�����W�̐��l�𒴂�����
	if (m_pos.y >= SCREEN_HEIGHT)
	{
		// �I��������
		Uninit();
	}
}

//=============================================================================
// 2D�|���S���̕`�揈��
//=============================================================================
void CItem::Draw(void)
{
	// Scene2D�̕`�揈����
	CScene2D::Draw();
}