//=============================================================================
//
// �X�e�[�W�Ǘ��N���X [goal.h]
// Author : �y���@��P
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "goal.h"
#include "model.h"
#include "camera.h"
#include "keyboard.h"
#include "stage_data.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CModel *CGoal::m_apModel[MODEL_MAX] = {};
CStageData *CGoal::m_pStageData = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoal::CGoal(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(m_pos, 0, sizeof(D3DXVECTOR3));			// �ʒu
	memset(m_move, 0, sizeof(D3DXVECTOR3));			// �ړ���
	m_bUninit = false;								// �j��
	m_nNumModel = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGoal::~CGoal()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGoal::Init(void)
{
	SetObjType(CScene::OBJTYPE_MODEL);

#if 1
	//m_nNumModel = 2;
	m_pModel = CModel::Create("data/MODEL/FLOOR/Floor_Green.x");
	m_pModel->SetPosition(D3DXVECTOR3(-30.0f, 20.0f, 6500.0f));
	m_pModel->SetRotation(D3DXVECTOR3(0, 0, 0));

	//m_pModel[1] = CModel::Create("data/MODEL/building01.x");
	//m_pModel[1]->SetPosition(D3DXVECTOR3(120, 0, 100));
	//m_pModel[1]->SetRotation(D3DXVECTOR3(0, 0, 0));

#endif

	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0);

	// �����̐ݒ�
	m_rot = D3DXVECTOR3(0, 0, 0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGoal::Uninit(void)
{
	// ���f���̔j��
		if (m_pModel != NULL)
		{
			m_pModel->Uninit();
		}


	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGoal::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CGoal::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

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

	// ���f���̕`��
		if (m_pModel != NULL)
		{
			m_pModel->Draw();
		}

}
//=============================================================================
// �ʏ�̓����蔻��
//=============================================================================
bool CGoal::Collision(CGoal *pGoal,D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	//���f�������擾
	CModel *pModel = pGoal->GetModel();

	if (pModel != NULL)
	{
		D3DXVECTOR3 pos = pModel->GetPosition();
		D3DXVECTOR3 scale = pModel->GetScale();

		if (pPos->y <= pos.y&&pPosOld->y >= pos.y)
		{
			if (pPos->x >= pos.x - scale.x + 10.0f && pPos->z <= pos.z + scale.z + 10.0f&&
				pPos->x <= pos.x + scale.x + 10.0f  && pPos->z >= pos.z - scale.z + 10.0f)
			{
				pPos->y = pos.y;
				BackPos = pos.y;
				return true;
			}
		}

	}

	return false;
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CGoal *CGoal::Create(void)
{
	CGoal *pGoal;
	pGoal = new CGoal;

	if (pGoal != NULL)
	{
		pGoal->Init();
	}

	return pGoal;
}


CModel *CGoal::GetModel(void)
{
	return m_pModel;
}

D3DXVECTOR3 CGoal::GetPosition(void)
{
	return m_pos;
}

