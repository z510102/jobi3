//=============================================================================
//
// 2D�|���S������ [scene2D.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "scene2D.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	// �l���N���A�i�����ݒ�j
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXVECTOR2));
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nColorR = 0;
	m_nColorG = 0;
	m_nColorB = 0;
	m_nColorA = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 2D�|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�i��������j
	m_pos = pos;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,  //�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,          //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,            //���_�o�b�t�@�ւ̃|�C���^
		NULL);

	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 2D�|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// 2D�|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{
	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N�����_���W�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2D�|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  //�v���~�e�B�u�̎��
						   0,                    //�J�n���钸�_�̃C���f�b�N�X
						   2);                   //�`�悷��v���~�e�B�u��
}

//=============================================================================
// 2D�|���S���̐���
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos)
{
	// �|�C���^
	CScene2D *pScene2D;

	// ���������m��
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		// Init��
		pScene2D->Init(pos);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pScene2D;
}

//=============================================================================
// 2D�|���S���̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	// �����������o�֓n��
	m_pos = pos;
}

//=============================================================================
// 2D�|���S���̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pos;
}

//=============================================================================
// 2D�|���S���̃T�C�Y�̐ݒ�
//=============================================================================
void CScene2D::SetSize(float fWidth, float fHeight)
{
	// �����������o�֓n��
	m_size = D3DXVECTOR2(fWidth, fHeight);
}

//=============================================================================
// 2D�|���S���̃T�C�Y�̎擾
//=============================================================================
D3DXVECTOR2 CScene2D::GetSize(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_size;
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	//�����o�ɏ���n��
	m_color = col;

	//���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void CScene2D::SetColor(int nColR, int nColG, int nColB, int nColA)
{
	// �����������o�֓n��
	m_nColorR = nColR;
	m_nColorG = nColG;
	m_nColorB = nColB;
	m_nColorA = nColA;

	//���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
	pVtx[1].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
	pVtx[2].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);
	pVtx[3].col = D3DCOLOR_RGBA(m_nColorR, m_nColorG, m_nColorB, m_nColorA);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2D�|���S���̃e�N�X�`�����蓖��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	// �����������o�֓n��
	m_pTexture = pTexture;
}

//=============================================================================
// 2D�|���S���̃e�N�X�`�����W�̐ݒ�
//=============================================================================
void CScene2D::SetVertexTexture(int nPatternAnimU, float fAnimU, int nPatternAnimV, float fAnimV, float fTexU, float fTexV)
{
	// �����������o�֓n��
	m_fTexU = fTexU;
	m_fTexV = fTexV;

	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + 0.0f, (nPatternAnimV * fAnimV) + 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + m_fTexU, (nPatternAnimV * fAnimV) + 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + 0.0f, (nPatternAnimV * fAnimV) + m_fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPatternAnimU * fAnimU) + m_fTexU, (nPatternAnimV * fAnimV) + m_fTexV);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}