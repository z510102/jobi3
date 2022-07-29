//=============================================================================
//
// �v���C���[�N���X [player.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "motion.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define FILENAME_PLAYER "data/SCRIPT/PLAYER/motion.txt"
#define MAX_PLAYER_MODEL 20
#define MAX_PARTS 20
#define GRAVITYSPEED (0.5)
//=============================================================================
// �O���錾
//=============================================================================
class CModel;
//*****************************************************************************
//	�v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = PRIORITY_PLAYER);	// �R���X�g���N�^
	~CPlayer();					// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ��������

	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3	GetPos(void);		//
	//void SetDeath(bool bDeath) {m_bDeathFrag = bDeath;}
	//bool GetDeath(void) { return m_bDeathFrag; }
	void SetbHitBullet(bool bHitBullet) { m_bHitBullet = bHitBullet; }
	void LoadPlayerFile(const char *pFileName);

private:
	CModel								*m_pModel[MAX_PLAYER_MODEL];	// ���f���ւ̃|�C���^
	D3DXMATRIX							m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3							m_pos;						// �ʒu
	D3DXVECTOR3							m_posOld;					// �O�̈ʒu
	D3DXVECTOR3							m_rot;						// ����
	D3DXVECTOR3							m_scale;						// �傫��
	D3DXVECTOR3							m_move;						// �ړ���

	int									m_nNumModel;				// ���f���̑���
	float								m_fGravitySpeed;			//�d�͉����x
	float								m_fBackPos;					//�v���C���[�����n����ʒu
	bool								m_bJump;
	bool								m_bLand;
	bool								m_bGoal;
	bool								m_bFade;	//�t�F�[�h
	bool								m_bHitBullet;  //�e�̓����蔻��p
	bool								m_bDeathFrag;
	bool								m_bMeshField;

};
#endif //!_PLAYER_H_