//=============================================================================
//
// 3D�|���S���N���X [scene3D.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene3D.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CScene3D::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(int nPriority) : CScene(nPriority)
{
	m_pVtxBuff = NULL;
	memset(&m_pos, 0, sizeof(m_pos));
	memset(&m_rot, 0, sizeof(m_rot));
	memset(&m_scale, 0, sizeof(m_scale));
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x,  m_pos.y,  m_pos.z);

	//rhw�̐ݒ�
	pVtx[0].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
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
void CScene3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{	
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,							//�J�n����n�_�̃C���f�b�N�X
		2);							//�`�悷��v���~�e�B�u��
}
//=============================================================================
// 3D�|���S���̐���
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nType)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;

	if (pScene3D != NULL)
	{
		pScene3D->m_pos = pos;
		pScene3D->m_rot = rot;
		pScene3D->m_scale = scale;
		pScene3D->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		pScene3D->Init();
	}

	return pScene3D;
}
//=============================================================================
// 3D�|���S���̈ʒu��ݒ�
//=============================================================================
void CScene3D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_pos = pos;
	m_scale = scale;

	VERTEX_3D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

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
//=============================================================================
// 3D�|���S���̈ʒu���擾
//=============================================================================
D3DXVECTOR3 CScene3D::GetPosition(void)
{
	return m_pos;
}
