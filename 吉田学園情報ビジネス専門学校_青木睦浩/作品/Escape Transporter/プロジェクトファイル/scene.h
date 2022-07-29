//=============================================================================
//
// �I�u�W�F�N�g�N���X [scene.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE		(40)		// �e�N�X�`���̍ő吔

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,	// �Ȃ�
		OBJTYPE_BG,			// �w�i
		OBJTYPE_MODEL,
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_ENEMY,		// �G
		OBJTYPE_BOSS,
		OBJTYPE_ITEM,		// �A�C�e��
		OBJTYPE_BULLET,		// �e
		OBJTYPE_SPECIAL,
		OBJTYPE_ENEMYBULLET,// �G�e
		OBJTYPE_EXPLOSION,	// ����
		OBJTYPE_EFFECT,		// �G�t�F�N�g
		OBJTYPE_UI,			// �c�@
		OBJTYPE_FADE,		// �t�F�[�h
		OBJTYPE_MAX			// �ő吔
	} OBJTYPE;

	// �`��̗D�揇��
	typedef enum
	{
		PRIORITY_BG = 0,		// �w�i
		PRIORITY_MODEL,
		PRIORITY_ENEMY,			// �G
		PRIORITY_BOSS,			// �{�X
		PRIORITY_PLAYER,		// �v���C���[
		PRIORITY_ITEM,			// �A�C�e��
		PRIORITY_BGBOARD,		// �T�C�h�{�[�h
		PRIORITY_BULLET,		// �e
		PRIORITY_EFFECT,		// �G�t�F�N�g
		PRIORITY_EXPLOSION,		// ����
		PRIORITY_UI,			// UI
		PRIORITY_FADE,			// �t�F�[�h
		PRIORITY_MAX			// �ő吔
	} PRIORITY_TYPE;

	CScene(int nPriority = OBJTYPE_NONE);				// �R���X�g���N�^
	virtual ~CScene();						// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;				// ����������
	virtual void Uninit(void) = 0;				// �I������
	virtual void Update(void) = 0;				// �X�V����
	virtual void Draw(void) = 0;				// �`�揈��

	static void ReleaseAll(void);				// �S�ẴI�u�W�F�N�g�̔j��
	static void UpdateAll(void);				// �S�ẴI�u�W�F�N�g�̍X�V����
	static void DrawAll(void);					// �S�ẴI�u�W�F�N�g�̕`�揈��

	void SetObjType(OBJTYPE objType);			// �I�u�W�F�N�g�̎�ނ�ݒ�
	OBJTYPE GetobjType(void);					// �I�u�W�F�N�g�̎�ނ��擾
	static CScene *GetScene(int nPriority);		// �񋓌^�ƈ�v����I�u�W�F�N�g���擾
	static CScene *GetNextScene(CScene *pScene) { return pScene->m_pNext; };

protected:
	void Release(void);							// �I�u�W�F�N�g�̔j��

private:
	OBJTYPE			m_objType;					// �I�u�W�F�N�g�̎��

												// ���X�g�\��
	static CScene *m_apTop[PRIORITY_MAX];		// �擪�I�u�W�F�N�g�̃|�C���^
	static CScene *m_apCur[PRIORITY_MAX];		// ����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev;			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;			// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;				// ���S�t���O
	int m_nPriority;

};
#endif //!_SCENE_H_