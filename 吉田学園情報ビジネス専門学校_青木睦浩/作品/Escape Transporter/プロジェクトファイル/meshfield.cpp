//=============================================================================
//
// ���b�V���t�B�[���h�N���X [meshfield.h]
// Author : �؁@�r�_
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "meshfield.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(int nPriority) : CScene3D(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(m_pos, 0, sizeof(m_pos));			// �ʒu
	memset(m_rot, 0, sizeof(m_rot));			// ����
	memset(m_move, 0, sizeof(m_move));			// �ړ���
	memset(m_scale, 0, sizeof(m_scale));		// �傫��

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(OBJTYPE_MODEL);

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	//���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y, m_pos.z + m_scale.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x			 , m_pos.y, m_pos.z + m_scale.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y, m_pos.z + m_scale.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y, m_pos.z			   );
	pVtx[4].pos = D3DXVECTOR3(m_pos.x			 , m_pos.y, m_pos.z			   );
	pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y, m_pos.z			   );
	pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y, m_pos.z - m_scale.z);
	pVtx[7].pos = D3DXVECTOR3(m_pos.x			 , m_pos.y, m_pos.z - m_scale.z);
	pVtx[8].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y, m_pos.z - m_scale.z);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(5.0f, 5.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 5.0f);
	pVtx[2].tex = D3DXVECTOR2(5.0f, 5.0f);
	pVtx[3].tex = D3DXVECTOR2(5.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(5.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(5.0f, 5.0f);
	pVtx[7].tex = D3DXVECTOR2(0.0f, 5.0f);
	pVtx[8].tex = D3DXVECTOR2(5.0f, 5.0f);


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
							   D3DUSAGE_WRITEONLY,
							   D3DFMT_INDEX16,
							   D3DPOOL_MANAGED,
							   &m_pIdxBuff,
							   NULL);

	// �C���f�b�N�X���ւ̃|�C���^
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;

	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;

	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;

	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;


	// ���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

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

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->SetTexture(0, m_pTexture);

	// �C���f�b�N�X�̃v���~�e�B�u
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NUM_VERTEX, 0, 12);
}
//=============================================================================
// ���b�V���t�B�[���h�̐���
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nType)
{
	// �|�C���^
	CMeshField *pMeshField;

	// ���������m��
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		// �����o�ϐ��֏���n���E���ꂼ��̏�����
		pMeshField->m_pos = pos;
		pMeshField->m_scale = scale;
		pMeshField->Init();
		pMeshField->BindTexture(CManager::GetTexture()->SetTextureType(nType));
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pMeshField;
}
//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CMeshField::GetPosition(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pos;
}
//=============================================================================
// �傫���̎擾
//=============================================================================
D3DXVECTOR3 CMeshField::GetScale(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_scale;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CMeshField::Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	// pMeshField��NULL����Ȃ�������
	if (pMeshField != NULL)
	{
		// ����n��
		D3DXVECTOR3 pos = pMeshField->GetPosition();
		D3DXVECTOR3 scale = pMeshField->GetScale();

		// pPos.y�̒l��pos.y�̒l�ȉ�����pPosOld.y�̒l��pos.y�̒l�ȏ�̏ꍇ
		if (pPos->y <= pos.y && pPosOld->y >= pos.y)
		{
			// pPos.x�̒l���v�Z�����l�ȏォ�� pPos.z�̒l���v�Z�����l�ȉ����� pPos.x�̒l���v�Z�����l�ȉ����� pPos.z�̒l���v�Z�����l�ȏゾ�����ꍇ
			if (pPos->x >= pos.x - m_scale.x + 10.0f && pPos->z <= pos.z + m_scale.z + 10.0f&&
				pPos->x <= pos.x + m_scale.x + 10.0f && pPos->z >= pos.z - m_scale.z + 10.0f)
			{
				// �l������
				pPos->y = pos.y;
				BackPos = pos.y;

				// true��߂�l�֕Ԃ�
				return true;
			}
		}
	}

	// false��߂�l�֕Ԃ�
	return false;
}
