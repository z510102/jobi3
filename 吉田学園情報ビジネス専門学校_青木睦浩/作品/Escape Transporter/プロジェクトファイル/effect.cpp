//=============================================================================
//
// �G�t�F�N�g [effect.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect()
{
	// �����o�ϐ��̃N���A
	memset(m_pos, 0, sizeof(D3DXVECTOR3));		// �ʒu
	memset(m_move, 0, sizeof(D3DXVECTOR3));		// �ړ���
	memset(m_size, 0, sizeof(D3DXVECTOR2));		// �傫��
	m_nColorR = 0;								// �ԐF
	m_nColorG = 0;								// �ΐF
	m_nColorB = 0;								// �F
	m_nColorA = 0;								// �����x
	m_nSubColorR = 0;							// �ԐF�F�����l
	m_nSubColorG = 0;							// �ΐF�F�����l
	m_nSubColorB = 0;							// �F�F�����l
	m_nSubColorA = 0;							// �����x�F�����l
	m_nLife = 0;								// ����
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int nColr, int nColg, int nColb, int nCola, int nSubColr, int nSubColg, int nSubColb, int nSubCola,
	int nLife)
{
	CBillboard::Init();
	SetObjType(OBJTYPE_EFFECT);
	m_pos = pos;
	m_move = move;
	m_size = size;
	m_nColorR = nColr;
	m_nColorG = nColg;
	m_nColorB = nColb;
	m_nColorA = nCola;
	m_nSubColorR = nSubColr;
	m_nSubColorG = nSubColg;
	m_nSubColorB = nSubColb;
	m_nSubColorA = nSubCola;

	m_nLife = nLife;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	// ���_�J���[�����Z
	m_nColorR -= m_nSubColorR;
	m_nColorG -= m_nSubColorG;
	m_nColorB -= m_nSubColorB;
	m_nColorA -= m_nSubColorA;

	if (m_nColorR < 0)
	{
		m_nColorR = 0;
	}
	if (m_nColorG < 0)
	{
		m_nColorG = 0;
	}
	if (m_nColorB < 0)
	{
		m_nColorB = 0;
	}
	if (m_nColorA < 0)
	{
		m_nColorA = 0;
	}


	// �F���X�V
	//SetColor(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	// ���u�����f�B���O�����Z�����ɐݒ�
	CManager::GetRenderer()->SetAddSynthesis(true);

	// �r���{�[�h�̕`��
	CBillboard::Draw();

	// ���u�����f�B���O��ʏ퍇���ɐݒ�
	CManager::GetRenderer()->SetAddSynthesis(false);
}
