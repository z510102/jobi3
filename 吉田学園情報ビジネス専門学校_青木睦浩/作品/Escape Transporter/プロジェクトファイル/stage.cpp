//=============================================================================
//
// �X�e�[�W�Ǘ��N���X [stage.h]
// Author : ���}���@�V��
// Author : �ؖr�_
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stage.h"
#include "model.h"
#include "camera.h"
#include "keyboard.h"
#include "stage_data.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CStageData *CStage::m_pStageData = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage::CStage(int nPriority) : CScene(nPriority)
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
CStage::~CStage()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CStage::Init(void)
{
	SetObjType(CScene::OBJTYPE_MODEL);
#if 1
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	char aFile[256];	// ������ǂݍ���
	D3DXVECTOR3 pos;	// �ʒu�ۑ�
	D3DXVECTOR3 rot;	// �����ۑ�
	D3DXVECTOR3 scale;	// �傫���ۑ�
	int nCntModel = 0;	// ���f�����J�E���g
	int nModelType = 0;	// ���f���̎��
	bool bModelSet = false;		// ���f���Z�b�g
	bool bStageSet = false;		// �X�e�[�W�Z�b�g

	// ���f���̔z�u���ǂݍ���
	FILE *pFile = fopen(MODEL_FILENAME, "r");

	if (pFile != NULL)
	{
		while (true)
		{
			// ������ǂݍ��݊J�n
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{
				// ���f���̎�ސ�
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nModelType);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)
			{
				// ���f���̃p�X
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				CStageData::LoadXFile(&aFile[0], nModelType);
				nModelType++;
			}
			if (strcmp(&aFile[0], "STAGESET") == 0)
			{
				// �X�e�[�W�Z�b�g
				m_nNumModel = 0;
				bStageSet = true;
			}
			if (strcmp(&aFile[0], "END_STAGESET") == 0)
			{
				// �X�e�[�W�Z�b�g�̏I��
				bStageSet = false;
			}
			// �X�e�[�W�Z�b�g
			if (bStageSet == true)
			{
				if (strcmp(&aFile[0], "MODELSET") == 0)
				{
					// ���f���Z�b�g
					bModelSet = true;
				}
				if (strcmp(&aFile[0], "END_MODELSET") == 0)
				{
					// ���f���Z�b�g�̏I��
					bModelSet = false;

					// ���f���̏���ݒ�
					m_pStageData = CStageData::Create(pos, rot, scale, nModelType);
					// ���f���̐��𑝂₷
					m_nNumModel++;
				}
				// ���f���Z�b�g
				if (bModelSet == true)
				{
					// ���f���̎��
					if (strcmp(&aFile[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nModelType);
					}
					// �ʒu
					if (strcmp(&aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					}
					// ����
					if (strcmp(&aFile[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					}
					// �傫��
					if (strcmp(&aFile[0], "SCALE") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &scale.x, &scale.y, &scale.z);
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// �ǂݍ��ݏI��
				break;
			}
		}
		fclose(pFile);
	}


#endif

#if 0
	m_nNumModel = 2;
	m_pModel[0] = CModel::Create("data/MODEL/building00.x");
	m_pModel[0]->SetPosition(D3DXVECTOR3(-120, 0, -100));
	m_pModel[0]->SetRotation(D3DXVECTOR3(0, 0, 0));

	m_pModel[1] = CModel::Create("data/MODEL/building01.x");
	m_pModel[1]->SetPosition(D3DXVECTOR3(120, 0, 100));
	m_pModel[1]->SetRotation(D3DXVECTOR3(0, 0, 0));

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
void CStage::Uninit(void)
{
	// ���f���̔j��
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Uninit();
		}
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CStage::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CStage::Draw(void)
{
}

//=============================================================================
// �ʏ�̓����蔻��
//=============================================================================
bool CStage::Collision(CStageData *pStage, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos)
{
	//���f�������擾
	CModel *pModel = pStage->GetModel();

	// pModel��NULL����Ȃ�������
	if (pModel != NULL)
	{
		// ����n��
		D3DXVECTOR3 pos = pStage->GetPosition();
		D3DXVECTOR3 scale = pModel->GetScale();

		// pPos.y�̒l��pos.y�̒l�ȉ�����pPosOld.y�̒l��pos.y�̒l�ȏ�̏ꍇ
		if (pPos->y <= pos.y && pPosOld->y >= pos.y)
		{
			// pPos.x�̒l���v�Z�����l�ȏォ�� pPos.z�̒l���v�Z�����l�ȉ����� pPos.x�̒l���v�Z�����l�ȉ����� pPos.z�̒l���v�Z�����l�ȏ�̏ꍇ
			if (pPos->x >= pos.x - scale.x + 15.0f  && pPos->z <= pos.z + scale.z + 15.0f &&
				pPos->x <= pos.x + scale.x + 15.0f  && pPos->z >= pos.z - scale.z + 15.0f)
			{
				// ����n��
				pPos->y = pos.y;
				BackPos = pos.y;

				// true��Ԃ�
				return true;
			}
			
		}

	}

	// false��Ԃ�
	return false;
}

//=============================================================================
// �X�e�[�W�̐���
//=============================================================================
CStage *CStage::Create(void)
{
	// �|�C���^
	CStage *pStage;

	// ���������m��
	pStage = new CStage;

	if (pStage != NULL)
	{
		// ������
		pStage->Init();
	}

	// �|�C���^��߂�l�֕Ԃ�
	return pStage;
}

//=============================================================================
// �X�e�[�W�f�[�^�̎擾
//=============================================================================
CStageData *CStage::GetStageData(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_pStageData;
}
