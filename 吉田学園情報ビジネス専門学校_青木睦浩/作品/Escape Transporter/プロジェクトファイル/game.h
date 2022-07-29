//=============================================================================
//
// �Q�[���N���X [game.h]
// Author : ���}���@�V��
// Author : �쑺�@�D�l
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene2D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CPlayer;
class CScore;
class CTime;
class CStage;
class CGoal;
class CBullet;
class CMeshField;
//*****************************************************************************
//	�Q�[���N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();			// �R���X�g���N�^
	~CGame();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	static CGame	*Create(void);	// ��������

	static CPlayer	*GetPlayer(void); 	// �v���C���[���̎擾
	static CScore	*GetScore(void);//�X�R�A���̎擾
	static CTime	*GetTime(void);	//�^�C�����̎擾
	static CStage	*GetStage(void);	//�^�C�����̎擾
	static CGoal	*GetGoal(void);		//�S�[�����̎擾
	static CBullet	*GetBullet(void);	//�e���̎擾
	static CMeshField *GetMeshField(void);

private:
	static CPlayer	*m_pPlayer;	// �v���C���[�̃C���X�^���X
	static CScore	*m_pScore;	// �X�R�A�̃C���X�^���X
	static CTime	*m_pTime;	// �^�C���̃C���X�^���X

	bool			m_bFade;	// �t�F�[�h����
	D3DCOLORVALUE m_colval;
	static CStage  *m_pStage;
	static CMeshField	*m_pMeshField;
	static CGoal	*m_pGoal;
	static CBullet	*m_pBullet;
};
#endif //!_GAME_H_