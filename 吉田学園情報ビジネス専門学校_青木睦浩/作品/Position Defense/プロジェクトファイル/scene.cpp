//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "scene.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	// MAX_SCENE�̐���
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		// m_apScene��NULL��������
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;

			// �����̔ԍ���ݒ�
			m_nID = nCntScene;

			// ����n��
			m_nPriority = nPriority;

			// ���Z����
			m_nNumAll++;

			// ������
			break;
		}
	}

	// �I�u�W�F�N�g�̎�ނ��Ȃ��ɂ���
	m_objType = OBJTYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̔j��
//=============================================================================
void CScene::ReleaseAll(void)
{
	// PRIORITY_MAX�̐���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// MAX_SCENE�̐���
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// m_apScene��NULL����Ȃ�������
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// nCntPriority��9����Ȃ�������
				if (nCntPriority != 9)
				{
					// 2D�|���S���̏I������
					m_apScene[nCntPriority][nCntScene]->Uninit();
				}
			}
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	// PRIORITY_MAX�̐���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// MAX_SCENE�̐���
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// m_apScene��NULL����Ȃ�������
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// 2D�|���S���̍X�V����
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	// PRIORITY_MAX�̐���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// MAX_SCENE�̐���
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// m_apScene��NULL����Ȃ�������
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// 2D�|���S���̕`�揈��
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̐ݒ菈��
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	// �����o�֏���n��
	m_objType = objType;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̎擾����
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	// �����o��߂�l�֕Ԃ�
	return m_objType;
}

//=============================================================================
// �I�u�W�F�N�g�̎擾����
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nIndex)
{
	// �|�C���^�z���߂�l�֕Ԃ�
	return m_apScene[nPriority][nIndex];
}

//=============================================================================
// �I�u�W�F�N�g�̔j��
//=============================================================================
void CScene::Release(void)
{
	// m_apScene��NULL����Ȃ�������
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		// �C���X�^���X�̔j��
		int nID = m_nID;
		
		// �����o�̏���n��
		int nPriority = m_nPriority;

		// �|�C���^�z����������
		delete m_apScene[nPriority][nID];

		// m_apScene��NULL�ɂ���
		m_apScene[nPriority][nID] = NULL;

		// m_nNumAll�����Z����
		m_nNumAll--;
	}
}