//=============================================================================
//
// �G�N���X [enemy.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "motion.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define FILENAME_HUMAN "data/SCRIPT/ENEMY/motion_human.txt"
#define FILENAME_LEG "data/SCRIPT/ENEMY/motion_leg.txt"
#define MAX_ENEMY_MODEL 20
#define MAX_ENEMY_PARTS 20
//=============================================================================
// �O���錾
//=============================================================================
class CModel;
//*****************************************************************************
//	�G�N���X
//*****************************************************************************
class CEnemy : public CScene
{
public:

	CEnemy(int nPriority = PRIORITY_ENEMY);	// �R���X�g���N�^
	~CEnemy();					// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ��������

	void LoadXFile(const char *pFileName);		// �ǂݍ��ރt�@�C����ݒ�
	void Collision(void);						// �ʏ�̓����蔻��
	void VectorCollision(void);					// �x�N�g���̓����蔻��

private:
	D3DXMATRIX							m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3							m_pos;						// �ʒu
	D3DXVECTOR3							m_posOld;					// �O�̈ʒu
	D3DXVECTOR3							m_rot;						// ����
	D3DXVECTOR3							m_move;						// �ړ���
	CModel								*m_pModel[MAX_ENEMY_MODEL];	// ���f���ւ̃|�C���^
	LPD3DXMESH							m_pMesh[MAX_ENEMY_PARTS];	// ���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER						m_pBuffMa[MAX_ENEMY_PARTS];	// �}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD								m_nNumMat[MAX_ENEMY_PARTS];	// �}�g���b�N�X��
	D3DXVECTOR3							m_vtxMin[8];				// ���f���̍ŏ��l
	D3DXVECTOR3							m_vtxMax[8];				// ���f���̍ő�l
	int									m_nNumModel;				// ���f���̑���

};
#endif //!_ENEMY_H_