//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCENE (1280)
#define PRIORITY_MAX (15)
#define MOVE_MAX (800)
#define MOVE_MIN (115)

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,			// �v���C���[
		OBJTYPE_ENEMY,			// �G
		OBJTYPE_BULLET,			// �e
		OBJTYPE_GRENADE,		// ��֒e
		OBJTYPE_FLASH_GRENADE,	// �M����֒e
		OBJTYPE_EXPLOSION,		// ����
		OBJTYPE_LIFE,			// �̗�
		OBJTYPE_EFFECT,			// �G�t�F�N�g
		OBJTYPE_POSITION,		// �|�W�V����
		OBJTYPE_UI,				// UI
		OBJTYPE_BG,				// �w�i
		OBJTYPE_ITEM,			// �A�C�e��
		OBJTYPE_FLASH,			// �M��
		OBJTYPE_MAX
	} OBJTYPE;

	// �v���C�I���e�B�̎��
	typedef enum
	{
		PRIORITY_BG = 0,
		PRIORITY_POSITION,
		PRIORITY_CHARA,
		PRIORITY_ANIM_EFFECT,
		PRIORITY_SCREEN,
		PRIORITY_UI,
		PRIORITY_NUMBER,
		PRIORITY_BULLET,
		PRIORITY_GRENADE,
		PRIORITY_ITEM,
		PRIORITY_EFFECT,
		PRIORITY_FADE,
		PRIORITY,
	} PRIORITY_TYPE;

	CScene(int nPriority = 3);								// �f�t�H���g�R���X�g���N�^
	virtual ~CScene();										// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;				// ����������
	virtual void Uninit(void) = 0;							// �I������
	virtual void Update(void) = 0;							// �X�V����
	virtual void Draw(void) = 0;							// �`�揈��

	static void ReleaseAll(void);							// �S�ẴI�u�W�F�N�g�̔j��
	static void UpdateAll(void);							// �S�ẴI�u�W�F�N�g�̍X�V����
	static void DrawAll(void);								// �S�ẴI�u�W�F�N�g�̕`�揈��

	void SetObjType(OBJTYPE objType);						// �I�u�W�F�N�g�̐ݒ菈��
	OBJTYPE GetObjType(void);								// �I�u�W�F�N�g�̎�ނ̎擾����
	static CScene *GetScene(int nPriority, int nIndex);		// �I�u�W�F�N�g�̎擾����

protected:
	void Release(void);										// �I�u�W�F�N�g�̔j��

private:
	// �����o�ϐ�
	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];		// �I�u�W�F�N�g�̃|�C���^�z��
	static int m_nNumAll;									// �I�u�W�F�N�g�̑���
	int m_nID;												// �i�[��̔ԍ�
	OBJTYPE m_objType;										// �I�u�W�F�N�g�̎��
	int m_nPriority;										// �D�揇�ʂ̔ԍ�
};

#endif // !_SCENE_H_