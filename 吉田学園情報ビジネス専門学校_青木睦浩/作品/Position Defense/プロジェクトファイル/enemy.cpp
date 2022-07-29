//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "enemy.h"
#include "manager.h"
#include "score.h"
#include "game.h"
#include "life.h"
#include "position.h"
#include "item.h"
#include "explosion.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_Type = TYPE_0;
	m_nPatternAnimU = 0;
	m_nCounterAnim = 0;
	m_nStop = 0;
	m_bStop = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/enemy_00.png",	    // �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_0]);            // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/enemy_01.png",	    // �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_1]);            // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/enemy_02.png",		// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_2]);			// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/enemy_03.png",		// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_3]);			// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/enemy_04.png",		// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_4]);			// �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/enemy_05.png",		// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_5]);            // �ǂݍ��ރ�����

	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/enemy_06.png",		// �ǂݍ��ރt�@�C����
							  &m_apTexture[TYPE_6]);            // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`���j��
//=============================================================================
void CEnemy::Unload(void)
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY_TYPE type)
{
	// �|�C���^
	CEnemy *pEnemy;

	// ���������m��
	pEnemy = new CEnemy (PRIORITY_CHARA);

	if (pEnemy != NULL)
	{
		// ���ꂼ��̏�����
		pEnemy->Init(pos, move);
		pEnemy->SetSize(11, 22);
		pEnemy->BindTexture(m_apTexture[type]);
		pEnemy->SetVertexTexture(4, 0.25f, 0, 0, 0.25f, 1.0f);

		// �����o�֏���n��
		pEnemy->m_Type = type;
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pEnemy;
}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// Scene2D�̏�������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_ENEMY);

	// �����o�֏���n��
	m_move = move;

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����o�֏���n��
	m_pos = pos;

	// ��ނ�TYPE_0��������
	if (m_Type == TYPE_0)
	{
		// pos��move�𑫂���pos�֓n��
		m_pos.y += m_move.y;

		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��18�����傫���Ȃ�����
		if (m_nCounterAnim > 18)
		{
			// m_nCounterAnim��0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z����
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ肷��
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// ��ނ�TYPE_1��������
	else if (m_Type == TYPE_1)
	{
		// pos��move�𑫂���pos�֓n��
		m_pos.y += m_move.y;

		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��15�����傫���Ȃ�����
		if (m_nCounterAnim > 15)
		{
			// m_nCounterAnim��0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z����
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ肷��
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// ��ނ�TYPE_2��������
	else if (m_Type == TYPE_2)
	{
		// pos��move�𑫂���pos�֓n��
		m_pos.y += m_move.y;

		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��15�����傫���Ȃ�����
		if (m_nCounterAnim > 12)
		{
			// m_nCounterAnim��0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z����
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ肷��
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// ��ނ�TYPE_3��������
	else if (m_Type == TYPE_3)
	{
		// pos��move�𑫂���pos�֓n��
		m_pos.y += m_move.y;

		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��15�����傫���Ȃ�����
		if (m_nCounterAnim > 9)
		{
			// m_nCounterAnim��0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z����
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ肷��
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// ��ނ�TYPE_4��������
	else if (m_Type == TYPE_4)
	{
		// pos��move�𑫂���pos�֓n��
		m_pos.y += m_move.y;

		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��15�����傫���Ȃ�����
		if (m_nCounterAnim > 6)
		{
			// m_nCounterAnim��0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z����
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ肷��
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// ��ނ�TYPE_5��������
	else if (m_Type == TYPE_5)
	{
		// pos��move�𑫂���pos�֓n��
		m_pos.y += m_move.y;

		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��15�����傫���Ȃ�����
		if (m_nCounterAnim > 3)
		{
			// m_nCounterAnim��0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z����
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ肷��
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// ��ނ�TYPE_6��������
	else if (m_Type == TYPE_6)
	{
		// pos��move�𑫂���pos�֓n��
		m_pos.x += m_move.x;

		// m_nCounterAnim�����Z
		m_nCounterAnim++;

		// m_nCounterAnim��15�����傫���Ȃ�����
		if (m_nCounterAnim > 9)
		{
			// m_nCounterAnim��0�ɂ���
			m_nCounterAnim = 0;

			// m_nPatternAnimU�����Z����
			m_nPatternAnimU++;

			// �e�N�X�`�����W��ݒ肷��
			CScene2D::SetVertexTexture(m_nPatternAnimU, 0.25f, 0, 0, 0.25f, 1.0f);
		}
	}

	// m_bStop��true�̂Ƃ�
	if (m_bStop == true)
	{
		// move��0�ɂ���i��~����j
		m_move.y = 0;

		// m_nStop�����Z
		m_nStop++;

		// m_nStop��700�ȏゾ������
		if (m_nStop >= 700)
		{
			// ��ނ�TYPE_0��������
			if (m_Type == TYPE_0)
			{
				// �ړ��ĊJ
				m_move.y = 0.2f;
			}

			// ��ނ�TYPE_1��������
			else if (m_Type == TYPE_1)
			{
				// �ړ��ĊJ
				m_move.y = 0.3f;
			}

			// ��ނ�TYPE_2��������
			else if (m_Type == TYPE_2)
			{
				// �ړ��ĊJ
				m_move.y = 0.4f;
			}

			// ��ނ�TYPE_3��������
			else if (m_Type == TYPE_3)
			{
				// �ړ��ĊJ
				m_move.y = 0.5f;
			}

			// ��ނ�TYPE_4��������
			else if (m_Type == TYPE_4)
			{
				// �ړ��ĊJ
				m_move.y = 0.6f;
			}

			// ��ނ�TYPE_5��������
			else if (m_Type == TYPE_5)
			{
				// �ړ��ĊJ
				m_move.y = 0.7f;
			}

			// m_nStop��0�ɂ���
			m_nStop = 0;
		}

		// m_nStop��0��������
		if (m_nStop == 0)
		{
			// m_bStop��false�ɂ���
			m_bStop = false;
		}
	}

	// Scene2D�̍X�V������
	CScene2D::Update();

	// �ʒu�̐ݒ菈����
	SetPosition(m_pos);

	// �|�W�V�������擾
	CPosition *pPosition;
	pPosition = CGame::GetPosition();

	// �������擾
	CExplosion *pExplosion;
	pExplosion = CGame::GetExplosion();

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

				//�L���X�g�i�^�ϊ�����2D�|���S���N���X�ɂ���ʒu�����擾�j
				D3DXVECTOR3 pos = ((CScene2D *)pScene)->GetPosition();
				D3DXVECTOR2 size = ((CScene2D *)pScene)->GetSize();

				// �I�u�W�F�N�g�̎�ނ��|�W�V�����������ꍇ
				if (objType == OBJTYPE_POSITION)
				{
					if (m_pos.x >= pos.x - size.x &&
						m_pos.x <  pos.x + size.x &&
						m_pos.y >= pos.y - size.y &&
						m_pos.y <  pos.y + size.y)
					{
						// ���C�t���擾
						CLife *pLife;
						pLife = CGame::GetLife();

						// ���C�t�̌��Z
						pLife->SubLife(1);

						// �I������
						Uninit();

						// �|�W�V�����̒��_�J���[�̐ݒ�
						pPosition->SetColor(255, 0, 0, 255);
					}
				}

				// �I�u�W�F�N�g�̎�ނ��M���������ꍇ
				else if (objType == OBJTYPE_FLASH)
				{
					if (m_pos.x >= pos.x - size.x &&
						m_pos.x <  pos.x + size.x &&
						m_pos.y >= pos.y - size.y &&
						m_pos.y <  pos.y + size.y)
					{
						m_bStop = true;
					}
				}

				// �I�u�W�F�N�g�̎�ނ��e�������ꍇ
				else if (objType == OBJTYPE_BULLET)
				{
					if (m_pos.x >= pos.x - size.x - 5 &&
						m_pos.x <  pos.x + size.x + 5 &&
						m_pos.y >= pos.y - size.y - 5 &&
						m_pos.y <  pos.y + size.y + 5)
					{
						// �e�̎�ނ��擾
						int nBulletType = CPlayer::GetBulletType();

						// �e�̎�ނ��V���b�g�K���ȉ��i�n���h�K�� �` �V���b�g�K���j���̓��P�b�g�����`���[�̏ꍇ
						if (nBulletType <= CBullet::TYPE_SG || nBulletType >= CBullet::TYPE_RL)
						{
							// �e���I��
							pScene->Uninit();

							// �e�̎�ނ����P�b�g�����`���[�̏ꍇ
							if (nBulletType == CBullet::TYPE_RL)
							{
								// �����𐶐�
								pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(200, 200), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CExplosion::TYPE_RL);
							}
						}

						// �G��|����������
						KnockDown();

						// �����𐶐�
						pExplosion->Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(30, 30), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CExplosion::TYPE_KNOCK);

						// �G�̎�ނ�TYPE_5�ȉ��iTYPE_0 �` TYPE_5�j�̏ꍇ
						if (m_Type <= TYPE_5)
						{
							// �����_���Ő��l�𐶐�
							int nItemSpawn = (int)(rand() % 21 + 1);

#if 1
							// ���l�ɂ���ăA�C�e���𐶐����͖���
							switch (nItemSpawn)
							{
							case 1:
								break;

							case 2:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_AR);
								break;

							case 3:
								break;

							case 4:
								break;

							case 5:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_SG);
								break;

							case 6:
								break;

							case 7:
								break;

							case 8:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_SR);
								break;

							case 9:
								break;

							case 10:
								break;

							case 11:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_RL);
								break;

							case 12:
								break;

							case 13:
								break;

							case 14:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_G);
								break;

							case 15:
								break;

							case 16:
								break;

							case 17:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_FG);
								break;

							case 18:
								break;

							case 19:
								break;

							case 20:
								CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR3(0, 1.0f, 0), CItem::TYPE_TIME);
								break;

							case 21:
								break;
							}
#endif
						}

						// �I��������
						Uninit();
					}
				}
			}
		}
	}

	// m_pos.x���w�肵�����l�������E�������ꍇ
	if (m_pos.x <= 25 || m_pos.x >= 890)
	{
		// �I��������
		Uninit();
	}
}

//=============================================================================
// 2D�|���S���̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	// Scene2D�̕`�揈����
	CScene2D::Draw();
}

//=============================================================================
// �G��|�������̏���
//=============================================================================
void CEnemy::KnockDown(void)
{
	// �X�R�A���擾
	CScore *pScore = CGame::GetScore();

	// �G�̎�ނ�TYPE_0�̏ꍇ
	if (m_Type == TYPE_0)
	{
		// �X�R�A�����Z
		pScore->AddScore(10);
	}

	// �G�̎�ނ�TYPE_1�̏ꍇ
	else if (m_Type == TYPE_1)
	{
		// �X�R�A�����Z
		pScore->AddScore(20);
	}

	// �G�̎�ނ�TYPE_2�̏ꍇ
	else if (m_Type == TYPE_2)
	{
		// �X�R�A�����Z
		pScore->AddScore(30);
	}

	// �G�̎�ނ�TYPE_3�̏ꍇ
	else if (m_Type == TYPE_3)
	{
		// �X�R�A�����Z
		pScore->AddScore(40);
	}

	// �G�̎�ނ�TYPE_4�̏ꍇ
	else if (m_Type == TYPE_4)
	{
		// �X�R�A�����Z
		pScore->AddScore(50);
	}

	// �G�̎�ނ�TYPE_5�̏ꍇ
	else if (m_Type == TYPE_5)
	{
		// �X�R�A�����Z
		pScore->AddScore(60);
	}

	// �G�̎�ނ�TYPE_6�̏ꍇ
	else if (m_Type == TYPE_6)
	{
		// �X�R�A�����Z
		pScore->AddScore(100);
	}
}