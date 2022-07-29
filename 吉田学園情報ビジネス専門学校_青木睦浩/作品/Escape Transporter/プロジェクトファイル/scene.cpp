//=============================================================================
//
// �I�u�W�F�N�g�N���X [scene.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScene *CScene::m_apTop[PRIORITY_MAX] = {};		// �擪�I�u�W�F�N�g�̃|�C���^
CScene *CScene::m_apCur[PRIORITY_MAX] = {};		// ����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	// ���S�t���O�������Ă��Ȃ�
	m_bDeath = false;

	m_nPriority = nPriority;

	if (m_apCur[m_nPriority] == NULL &&
		m_apTop[m_nPriority] == NULL)		// ���݂̃I�u�W�F�N�g������Ƃ�
	{
		m_apTop[m_nPriority] = this;
		m_apCur[m_nPriority] = this;
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	else									// ���݂̃I�u�W�F�N�g���Ȃ��Ƃ�
	{
		m_pPrev = m_apCur[m_nPriority];
		m_apCur[m_nPriority]->m_pNext = this;
		m_apCur[m_nPriority] = this;
		m_pNext = NULL;
	}

	// �I�u�W�F�N�g�̎�ނ��N���A
	m_objType = OBJTYPE_NONE;

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (m_apTop[nCntPriority] == this && m_apCur[nCntPriority] == this)	/* �I�u�W�F�N�g�̃|�C���^������� */
		{
			// �擪����Ԍ��������������Ȃ�����S�Ė����Ȃ�
			m_apTop[nCntPriority] = NULL;
			m_apCur[nCntPriority] = NULL;
			m_pNext = NULL;
			m_pPrev = NULL;
		}
		else if (m_apTop[nCntPriority] == this)				/* �擪�I�u�W�F�N�g�̃|�C���^ */
		{
			// �擪�������Ȃ邩�玟�̃I�u�W�F�N�g��擪�I�u�W�F�N�g�ɂ���
			m_apTop[nCntPriority] = m_pNext;

			// �擪�I�u�W�F�N�g�������Ȃ������Ƃ�������
			this->m_apCur[nCntPriority]->m_pNext = NULL;
		}
		else if (m_apCur[nCntPriority] == this)				/* ���݂̃I�u�W�F�N�g�̃|�C���^ */
		{
			// ��Ԍ�낪�����Ȃ邩��O�̃I�u�W�F�N�g����Ԍ��̃I�u�W�F�N�g�ɂ���
			m_apCur[nCntPriority] = m_pPrev;

			// ��Ԍ��̃I�u�W�F�N�g�������Ȃ������Ƃ�������
			this->m_pPrev->m_pNext = NULL;
		}
		else									/* �O��̃I�u�W�F�N�g�̊Ԃɂ���I�u�W�F�N�g */
		{
			if (m_pNext != NULL)
			{
				// ���̃I�u�W�F�N�g�͈�O�̃I�u�W�F�N�g���O�̃I�u�W�F�N�g�ɂȂ�
				m_pNext->m_pPrev = this->m_pPrev;
			}
			if (m_pPrev != NULL)
			{
				// �O�̃I�u�W�F�N�g�͈��̃I�u�W�F�N�g�����̃I�u�W�F�N�g�ɂȂ�
				m_pPrev->m_pNext = this->m_pNext;
			}
		}
	}
}
//=============================================================================
// �S�ẴI�u�W�F�N�g�̔j��
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// �擪�I�u�W�F�N�g�̃|�C���^���擾
		CScene *pScene = m_apTop[nCntPriority];

		// pScene��NULL����Ȃ�������J��Ԃ�
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			if (nCntPriority != PRIORITY_FADE)
			{
				delete pScene;
				pScene = NULL;
			}

			// ���̃I�u�W�F�N�g�̃|�C���^���擾
			pScene = pSceneNext;
		}
	}
}
//=============================================================================
// �S�ẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// �擪�I�u�W�F�N�g�̃|�C���^���擾
		CScene *pScene = m_apTop[nCntPriority];

		// pScene��NULL����Ȃ�������J��Ԃ�
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;
			pScene->Update();

			if (pScene->m_bDeath == true)
			{
				delete pScene;
				pScene = NULL;
			}

			pScene = pSceneNext;
		}
	}
}
//=============================================================================
// �S�ẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// �擪�I�u�W�F�N�g�̃|�C���^���擾
		CScene *pScene = m_apTop[nCntPriority];

		// pScene��NULL����Ȃ�������J��Ԃ�
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}

}
//=============================================================================
// �I�u�W�F�N�g�̎�ނ�ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}
//=============================================================================
// �I�u�W�F�N�g�̎�ނ��擾
//=============================================================================
CScene::OBJTYPE CScene::GetobjType(void)
{
	return m_objType;
}
//=============================================================================
// �I�u�W�F�N�g���擾
//=============================================================================
CScene *CScene::GetScene(int nPriority)
{
	return m_apTop[nPriority];
}
//=============================================================================
// �I�u�W�F�N�g�̔j��
//=============================================================================
void CScene::Release(void)
{
	m_bDeath = true;
}