//=============================================================================
//
// �X�e�[�W�f�[�^�N���X [stage_data.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _STAGE_DATA_H_
#define _STAGE_DATA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "stage.h"
//=============================================================================
// �O���錾
//=============================================================================
class CModel;

//*****************************************************************************
//	�X�e�[�W�f�[�^�N���X
//*****************************************************************************
class CStageData : public CScene
{
public:

	CStageData(int nPriority = PRIORITY_MODEL);	// �R���X�g���N�^
	~CStageData();					// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CStageData *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nIndex);		// ��������
	static void LoadXFile(const char *pModelFileName, int nIndex);					// Stage�N���X�œǂݍ��݂񂾏���ۑ�
	void SetModel(int nIndex);						// ���f���̔ԍ����|�C���^�ɕۑ�
	void SetPosition(D3DXVECTOR3 pos);				// �����������f���̈ʒu��ۑ�
	D3DXVECTOR3 GetPosition(void);
	void SetRotation(D3DXVECTOR3 rot);				// �����������f���̌�����ۑ�
	D3DXVECTOR3 GetRotation(void);
	void SetScale(D3DXVECTOR3 scale);
	D3DXVECTOR3 GetScale(void);
	CModel *GetModel(int nIndex) { return m_apModel[nIndex]; }//���f���̏����擾
	CModel *GetModel(void) { return m_pModel; }//���f���̏����擾

private:
	static CModel				*m_apModel[MODEL_MAX];	// �ǂݍ��񂾃��f����ۑ�

	CModel						*m_pModel;				// �ۑ������|�C���^�̃��f������ݒ�
	D3DXVECTOR3					m_pos;			// �ʒu
	D3DXVECTOR3					m_rot;			// ����
	D3DXVECTOR3					m_scale;		// �傫��

};
#endif //!_STAGE_DATA_H_