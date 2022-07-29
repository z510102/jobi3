//=============================================================================
//
// 2D�|���S���N���X [scene2D.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene2D.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pVtxBuff = NULL;
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_scale, 0, sizeof(D3DXVECTOR2));
	memset(&m_color, 0, sizeof(D3DXCOLOR));
	m_nColor_r = 0;
	m_nColor_g = 0;
	m_nColor_b = 0;
	m_nColor_a = 0;
	m_nType = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,										// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,											// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,										// ���\�[�X�̃o�b�t�@��ێ����郁����
		&m_pVtxBuff,											// ���_�o�b�t�@�ւ̃|�C���^
		NULL);													// NULL�ɐݒ�

	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// 2D�|���S���̐���
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nType)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->m_scale = scale;
		pScene2D->m_pos = pos;
		pScene2D->m_nType = nType;
		pScene2D->Init();
	}

	return pScene2D;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CScene2D::SetVtxTexture(int nPatteernAnimU, float fAnimU, int nPatteernAnimV, float fAnimV, float fTexU, float fTexV)
{
	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + 0.0f,  (nPatteernAnimV * fAnimV) + fTexV);
	pVtx[3].tex = D3DXVECTOR2((nPatteernAnimU * fAnimU) + fTexU, (nPatteernAnimV * fAnimV) + fTexV);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �ʒu���擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
// �ʒu����ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_pos = pos;
	m_scale = scale;

	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
void CScene2D::SetTexPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float fPos)
{
	m_pos = pos;
	m_scale = scale;

	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fPos, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fPos, m_pos.y + m_scale.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �T�C�Y���擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_scale;
}
//=============================================================================
// �T�C�Y��ݒ�
//=============================================================================
void CScene2D::SetSize(D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//=============================================================================
// ���_�J���[��ݒ�
//=============================================================================
void CScene2D::SetColor(int nColr, int nColg, int nColb, int nCola)
{
	m_nColor_r = nColr;
	m_nColor_g = nColg;
	m_nColor_b = nColb;
	m_nColor_a = nCola;

	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);
	pVtx[1].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);
	pVtx[2].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);
	pVtx[3].col = D3DCOLOR_RGBA(m_nColor_r, m_nColor_g, m_nColor_b, m_nColor_a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�J���[��ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}