//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "manager.h"
#include "game.h"
#include "straight.h"
#include "explosion.h"
#include "item.h"
#include "bullet_magazine.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A����
	memset(&m_move, 0, sizeof(D3DXVECTOR3));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_type = TYPE_HG;
	m_fAngle = 0.0f;
	m_nDamage = 0;
	m_nLife = 0;
	m_bUse = true;
	m_nPassHG = 0;
	m_nPassAR = 0;
	m_nPassSG = 0;
	m_nPassSR = 0;
	m_nPassRL = 0;
	m_nType = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
							  "data/TEXTURE/bullet000.png",		// �ǂݍ��ރt�@�C����
							  &m_pTexture);						// �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
void CBullet::Delete(void)
{
	// �}�K�W���̒e���̏����擾
	CBulletMagazine *pBulletMagazine;
	pBulletMagazine = CGame::GetBulletMagazine();

	// �����o�ϐ��ɏ���n��
	m_nPassHG = pBulletMagazine->GetBulletMagazineHG();
	m_nPassAR = pBulletMagazine->GetBulletMagazineAR();
	m_nPassSG = pBulletMagazine->GetBulletMagazineSG();
	m_nPassSR = pBulletMagazine->GetBulletMagazineSR();
	m_nPassRL = pBulletMagazine->GetBulletMagazineRL();
	m_nType   = pBulletMagazine->GetBulletType();

	// �e��-1�Ń^�C�v��0(HG)��������
	if (m_nPassHG <= -1 && m_nType == 0)
	{
		// �g�p�ł��Ȃ�����
		m_bUse = false;
	}

	// �e��-1�Ń^�C�v��1(AR)��������
	else if (m_nPassAR <= -1 && m_nType == 1)
	{
		// �g�p�ł��Ȃ�����
		m_bUse = false;
	}

	// �e��-1�Ń^�C�v��2(SG)��������
	else if (m_nPassSG <= -1 && m_nType == 2)
	{
		// �g�p�ł��Ȃ�����
		m_bUse = false;
	}

	// �e��-1�Ń^�C�v��3(SR)��������
	else if (m_nPassSR <= -1 && m_nType == 3)
	{
		// �g�p�ł��Ȃ�����
		m_bUse = false;
	}

	// �e��-1�Ń^�C�v��4(RL)��������
	else if (m_nPassRL <= -1 && m_nType == 4)
	{
		// �g�p�ł��Ȃ�����
		m_bUse = false;
	}
}

//=============================================================================
// ��������
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fAngle, BULLET_TYPE bullettype)
{
	// �|�C���^
	CBullet *pBullet = NULL;

	// ���������m��
	pBullet = new CBullet(PRIORITY_BULLET);

	if (pBullet != NULL)
	{
		// ���ꂼ��̏�����
		pBullet->Init(pos, move);
		pBullet->SetSize(6, 6);
		pBullet->BindTexture(m_pTexture);

		// �����o�ϐ��֏���n��
		pBullet->m_fAngle = fAngle;
		pBullet->m_type = bullettype;
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pBullet;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ������������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_BULLET);

	// �e�̏�����
	m_move = move;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	// �I��������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	// �X�V������
	CScene2D::Update();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// �����o�ϐ��֏���n��
	m_pos = pos;

	// �e�̈ړ��i�����Z�����č��̕ϐ��֓n���j
	m_pos.y += m_move.y;

	// �ݒ菈����
	SetPosition(m_pos);

	// ����������
	Delete();

	// �g�p���Ă�����
	if (m_bUse == true)
	{
		//�G�t�F�N�g�𐶐�
		CStraight::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 8, m_pos.z), D3DXVECTOR2(8, 16), 255, 255, 0, 255, 0, 10, 0, 0, 10);
	}

	//��ʊO�ɍs����������@���͉�ʊO�ɍs���Ă��Ďg�p����Ă��Ȃ����������
	if (SCREEN_HEIGHT - SCREEN_HEIGHT >= m_pos.y && m_bUse == true || SCREEN_HEIGHT - SCREEN_HEIGHT >= m_pos.y && m_bUse == false)
	{
		// �I��������
		Uninit();
	}

	//��ʊO�ɍs���Ă��Ȃ��āA�g�p����Ă��Ȃ�������
	else if (SCREEN_HEIGHT - SCREEN_HEIGHT <= m_pos.y && m_bUse == false)
	{
		//�g�p����
		m_bUse = true;
	}

	// ����������
	Delete();

	//���ˈʒu���e���ړ����Ă��Ȃ��Ďg�p����Ă��Ȃ����������
	if (SCREEN_HEIGHT - 100 <= m_pos.y && m_bUse == false)
	{
		// �I��������
		Uninit();
	}

	//�e�̈ʒu����
	if (MOVE_MAX <= m_pos.x || MOVE_MIN >= m_pos.x)
	{
		// �����𐶐�
		CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0), D3DXVECTOR2(20, 20), D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f), CExplosion::TYPE_SG);

		// �I��������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	// �`�揈����
	CScene2D::Draw();
}