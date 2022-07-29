//=============================================================================
//
// �G�t�F�N�g�̋O�Տ��� [straight.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "straight.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CStraight::m_pTexture = NULL;

//=============================================================================
// 2D�|���S���̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CStraight::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
		                      "data/TEXTURE/effect000.jpg",		// �ǂݍ��ރt�@�C����
		                      &m_pTexture);						// �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`���j��
//=============================================================================
void CStraight::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 2D�|���S���̐�������
//=============================================================================
CStraight *CStraight::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,
	int nColorR, int nColorG, int nColorB, int nColorA,
	int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
	int nLife)
{
	// �|�C���^
	CStraight *pEffect = NULL;

	// ���������m��
	pEffect = new CStraight (PRIORITY_EFFECT);

	if (pEffect != NULL)
	{
		// Init��
		pEffect->Init(pos, size, nColorR, nColorG, nColorB, nColorA, nColorSubR, nColorSubG, nColorSubB, nColorSubA, nLife);

		// BindTexture��
		pEffect->BindTexture(m_pTexture);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pEffect;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStraight::CStraight(int nPriority) : CEffect(nPriority)
{
	// �ϐ����N���A
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
	m_nLife = 0;
	m_nColorR = 0;
	m_nColorG = 0;
	m_nColorB = 0;
	m_nColorA = 0;
	m_nColorSubR = 0;
	m_nColorSubG = 0;
	m_nColorSubB = 0;
	m_nColorSubA = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStraight::~CStraight()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStraight::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size,
	int nColorR, int nColorG, int nColorB, int nColorA,
	int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
	int nLife)
{
	// ����������
	CEffect::Init(pos, nColorR, nColorG, nColorB, nColorA, nColorSubR, nColorSubG, nColorSubB, nColorSubA);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_EFFECT);

	//�����o�ɏ���n��
	m_pos = pos;
	m_size = size;
	m_nLife = nLife;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStraight::Uninit(void)
{
	// �I������
	CEffect::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CStraight::Update(void)
{
	//���������炷
	m_nLife--;

	//�T�C�Y������������
	m_size -= D3DXVECTOR2(1.0f, 0.1f);

	//�T�C�Y���X�V
	SetSize(m_size.x, m_size.y);

	//�ʒu���X�V
	SetPosition(m_pos);

	// �X�V����
	CEffect::Update();
	CScene2D::Update();

	//������0�ɂȂ�����
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CStraight::Draw(void)
{
	// �`�揈��
	CEffect::Draw();
}