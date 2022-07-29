//=============================================================================
//
// �G�N���X [enemy.h]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"
#include "model.h"
#include "keyboard.h"
#include "camera.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(m_pos, 0, sizeof(D3DXVECTOR3));			// �ʒu
	memset(m_move, 0, sizeof(D3DXVECTOR3));			// �ړ���
	m_nNumModel = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(void)
{

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
#if 1
	char aFile[256];	// ������ǂݍ���
	D3DXVECTOR3 pos;	// �ʒu�ۑ�
	D3DXVECTOR3 rot;	// �����ۑ�
	int nCntModel = 0;	// ���f����
	int nParent = 0;	// �e���f��
	bool bCharacterSet = false;	// �L�����N�^�[�Z�b�g
	bool bPartsSet = false;		// �p�[�c�Z�b�g

								// �v���C���[�̃��f��/�I�t�Z�b�g�ǂݍ���
	FILE *pFile = fopen(FILENAME_LEG, "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{
				// ���f����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)
			{
				// ���f���̃p�X
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				m_pModel[nCntModel] = CModel::Create(&aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)
			{
				// �L�����N�^�[�Z�b�g
				nCntModel = 0;
				bCharacterSet = true;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)
			{
				// �L�����N�^�[�Z�b�g�I��
				bCharacterSet = false;
			}
			if (bCharacterSet == true)
			{
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{
					// �p�[�c�Z�b�g
					bPartsSet = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{
					// �p�[�c�Z�b�g�I��
					bPartsSet = false;
					nCntModel++;
				}
				if (bPartsSet == true)
				{
					// �e�q�֌W�ݒ�
					if (strcmp(&aFile[0], "PARENT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);

						// �e�q�֌W��-1�̏ꍇ�A�e���f����ݒ�
						if (nParent != -1)
						{
							m_pModel[nCntModel]->SetParent(m_pModel[nParent]);
						}
					}
					// �ʒu
					if (strcmp(&aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntModel]->SetPosition(pos);
					}
					// ����
					if (strcmp(&aFile[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntModel]->SetRotation(rot);
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
	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0);

	// �����̐ݒ�
	m_rot = D3DXVECTOR3(0, 0, 0);

#if 0
	//���_���W�̎擾
	int nNumVtx;  //���_��
	DWORD sizeFVF;  //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;  //���_�ւ̃|�C���^

					 //���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//�S�Ă̒��_���r���ă��f���̍ŏ��l�A�ő�l�𔲂��o��
		//�ő�l
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}

		//�ŏ��l
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		//g_aBuilding[g_nCntBuilding].fWidth = g_aBuilding[g_nCntBuilding].vtxMax.x - g_aBuilding[g_nCntBuilding].vtxMin.x;
		//g_aBuilding[g_nCntBuilding].fHeight = g_aBuilding[g_nCntBuilding].vtxMax.y - g_aBuilding[g_nCntBuilding].vtxMin.y;
		//g_aBuilding[g_nCntBuilding].fDepth = g_aBuilding[g_nCntBuilding].vtxMax.z - g_aBuilding[g_nCntBuilding].vtxMin.z;

		pVtxBuff += sizeFVF;
	}
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Uninit();
		}
	}


	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxRot, mtxTrans;

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
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
}
//=============================================================================
// �v���C���[�̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		pEnemy->Init();
		pEnemy->m_pos = pos;
		pEnemy->m_rot = rot;
	}

	return pEnemy;
}
//=============================================================================
// �ʏ�̓����蔻��
//=============================================================================
void CEnemy::Collision(void)
{
	// �I�u�W�F�N�g�����擾
	CScene *pScene = CScene::GetScene(0);

	bool bLand = false;

	// ��I�u�W�F�N�g���珇�ɒT��
	while (pScene)
	{
		// �I�u�W�F�N�g�̎�ނ��擾
		OBJTYPE objtype = CScene::GetobjType();

		// �I�u�W�F�N�g�̎�ނ��z�u���f���̏ꍇ
		if (objtype == CScene::OBJTYPE_MODEL)
		{
			// �I�u�W�F�N�g�̈ʒu�Ƒ傫�����擾
			D3DXVECTOR3 pos = ((CModel*)pScene)->GetPosition();
			D3DXVECTOR3 scale = ((CModel*)pScene)->GetScale();

			if (m_pos.x < pos.x + scale.x && m_pos.x > pos.x - scale.x &&
				m_pos.y < pos.y + scale.y && m_posOld.y <= pos.y)
			{
				m_pos.y = pos.y;
				bLand = true;
			}
			else if (m_pos.x < pos.x + scale.x && m_pos.x > pos.x - scale.x &&
				m_pos.y < pos.y + scale.y && m_posOld.y >= pos.y + scale.y)
			{
				m_pos.y = pos.y + scale.y;
			}
			if (m_pos.y < pos.y + scale.y && m_pos.y > pos.y &&
				m_pos.x < pos.x - scale.x && m_posOld.x <= pos.x)
			{
				m_pos.x = pos.x - scale.x;
			}
			else if (m_pos.y < pos.y + scale.y && m_pos.y > pos.y &&
				m_pos.x < pos.x && m_posOld.x >= pos.x + scale.x)
			{
				m_pos.x = pos.x + scale.x;
			}

		}
	}
}
