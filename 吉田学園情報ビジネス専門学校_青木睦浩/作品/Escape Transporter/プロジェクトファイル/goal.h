//=============================================================================
//
// �X�e�[�W�Ǘ��N���X [goal.h]
// Author : �y����P
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MODEL_FILENAME "data/SCRIPT/model.txt"
#define MODELTYPE_MAX 5
#define MODEL_MAX 20
#define MAX_TEX 20
//=============================================================================
// �O���錾
//=============================================================================
class CModel;
class CStageData;
//*****************************************************************************
//	�X�e�[�W�N���X
//*****************************************************************************
class CGoal : public CScene
{
public:

	CGoal(int nPriority = 0);	// �R���X�g���N�^
	~CGoal();					// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CGoal *Create(void);		// ��������
	int GetNumModel(void) { return m_nNumModel; }
	CModel *GetModel(void);
	D3DXVECTOR3 GetPosition(void);

	bool Collision(CGoal *pGoal,D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);		// �ʏ�̓����蔻��

private:
	static CModel				*m_apModel[MODEL_MAX];
	D3DXMATRIX					m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;			// �ʒu
	D3DXVECTOR3					m_rot;			// ����
	D3DXVECTOR3					m_move;			// �ړ���
	CModel						*m_pModel;	// ���f���ւ̃|�C���^
	D3DXCOLOR					m_color;		// �F
	bool						m_bUninit;		// �j��
	int							m_nNumModel;
	int							m_nModelType;
	LPD3DXMESH					m_pMesh[20];	// ���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER				m_pBuffMat[20];	// �}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD						m_nNumMat[20];	// �}�g���b�N�X��

	static CStageData			*m_pStageData;
};
#endif //!_STAGE_H_
