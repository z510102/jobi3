//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "effect.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	// �ϐ����N���A����
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
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
CEffect::~CEffect()
{

}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos,
	int nColorR, int nColorG, int nColorB, int nColorA,
	int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA)
{
	// Scene2D�̏�����������
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ����߂�
	SetObjType(OBJTYPE_EFFECT);

	//�����o�ɏ���n��
	m_pos = pos;
	m_nColorR = nColorR;
	m_nColorG = nColorG;
	m_nColorB = nColorB;
	m_nColorA = nColorA;
	m_nColorSubR = nColorSubR;
	m_nColorSubG = nColorSubG;
	m_nColorSubB = nColorSubB;
	m_nColorSubA = nColorSubA;

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CEffect::Uninit(void)
{
	// Scene2D�̏I��������
	CScene2D::Uninit();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CEffect::Update(void)
{
	//���_�J���[��RGB�l�����Z
	m_nColorR -= m_nColorSubR;
	m_nColorG -= m_nColorSubG;
	m_nColorB -= m_nColorSubB;
	m_nColorA -= m_nColorSubA;

	//RGBA�����ꂼ��0�ȉ��ɂȂ����Ƃ�
	if (m_nColorR <= 0)
	{
		//0�ɖ߂�
		m_nColorR = 0;
	}

	if (m_nColorG <= 0)
	{
		//0�ɖ߂�
		m_nColorG = 0;
	}

	if (m_nColorB <= 0)
	{
		//0�ɖ߂�
		m_nColorB = 0;
	}

	if (m_nColorA <= 0)
	{
		//0�ɖ߂�
		m_nColorA = 0;
	}

	//�F���X�V
	SetColor(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
}

//=============================================================================
// 2D�|���S���̕`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	CManager::GetRenderer()->SetAddSynthesis(true);

	// Scene2D�̕`�揈����
	CScene2D::Draw();

	//�A���t�@�u�����f�B���O��ʏ퍇���ɐݒ�
	CManager::GetRenderer()->SetAddSynthesis(false);
}