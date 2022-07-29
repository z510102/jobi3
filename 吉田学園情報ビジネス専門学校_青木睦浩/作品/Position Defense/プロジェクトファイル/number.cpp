//=============================================================================
//
// �i���o�[���� [number.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "number.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
// �w�i�̓ǂݍ���
//=============================================================================
HRESULT CNumber::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	                     // �f�o�C�X�ւ̃|�C���^
		                      "data/TEXTURE/number.png",	 // �ǂݍ��ރt�@�C����
		                      &m_pTexture);                  // �ǂݍ��ރ�����

	return S_OK;
}

//=============================================================================
// �w�i�̔j��
//=============================================================================
void CNumber::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �i���o�[�̐���
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �|�C���^
	CNumber *pNumber;

	// ���������m��
	pNumber = new CNumber;

	if (pNumber != NULL)
	{
		// Init��
		pNumber->Init(pos, fWidth, fHeight);
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pNumber;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	// �ϐ����N���A����
	m_pVtxBuff = NULL;
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// �i���o�[�̏���������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �����o�ɏ���n��
	m_pos = pos;
	m_size = D3DXVECTOR2(fWidth / 2, fHeight / 2);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,  // �m�ۂ���o�b�t�@�̃T�C�Y
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,          // ���_�t�H�[�}�b�g
		                        D3DPOOL_MANAGED,
		                        &m_pVtxBuff,            // ���_�o�b�t�@�ւ̃|�C���^
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �i���o�[�̏I������
//=============================================================================
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �i���o�[�̍X�V����
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
// �i���o�[�̕`�揈��
//=============================================================================
void CNumber::Draw(void)
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
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  // �v���~�e�B�u�̎��
		                   0,                    // �J�n���钸�_�̃C���f�b�N�X
		                   2);                   // �`�悷��v���~�e�B�u��
}

//=============================================================================
// �i���o�[�̐ݒ菈��
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �i���o�[�̐F�ݒ菈��
//=============================================================================
void CNumber::SetColor(int nColR, int nColG, int nColB, int nColA)
{
	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);
	pVtx[1].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);
	pVtx[2].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);
	pVtx[3].col = D3DCOLOR_RGBA(nColR, nColG, nColB, nColA);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
