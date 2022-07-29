#include "billboard.h"


CBillboard::CBillboard(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CBillboard::~CBillboard()
{

}


HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

					  //���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, m_pos.z + 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, m_pos.z + 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y,  m_pos.z + 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y,  m_pos.z + 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//�I������
void CBillboard::Uninit(void)
{
	////�e�N�X�`���̔j��
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//�X�V����
void CBillboard::Update(void)
{
	
	VERTEX_3D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, + m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_scale.x, + m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x, - m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_scale.x, - m_scale.y, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}

void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxView, mtxTrans;

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);  //�t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;


	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));  //���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_3D); //���_�t�H�[�}�b�g�̐ݒ�

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

}

CBillboard * CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType)
{
	

		CBillboard *pBillboard = NULL;
		if (pBillboard == NULL)
		{
			pBillboard = new CBillboard;
			if (pBillboard != NULL)
			{
				pBillboard->Init();
				pBillboard->m_pos = pos;
				pBillboard->m_scale = scale;
				pBillboard->BindTexture(CManager::GetTexture()->SetTextureType(nType));
			}
		}
		return pBillboard;
	
}

void CBillboard::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_pos = pos;
	m_scale = scale;

	VERTEX_3D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x, -m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_scale.x, -m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x, +m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_scale.x, +m_scale.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
D3DXVECTOR3 CBillboard::GetPosition(void)
{
	return m_pos;
}

void CBillboard::SetColVal(D3DCOLORVALUE colval)
{
	VERTEX_3D *pVtx;  //���_���ւ̃|�C���^

	m_colval = colval;

	//���_���W�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].col = D3DCOLOR_RGBA((int)m_colval.r, (int)m_colval.g, (int)m_colval.b, (int)m_colval.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)m_colval.r, (int)m_colval.g, (int)m_colval.b, (int)m_colval.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)m_colval.r, (int)m_colval.g, (int)m_colval.b, (int)m_colval.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)m_colval.r, (int)m_colval.g, (int)m_colval.b, (int)m_colval.a);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}



