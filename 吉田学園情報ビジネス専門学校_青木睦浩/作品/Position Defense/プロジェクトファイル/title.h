//=============================================================================
//
// �^�C�g������ [title.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �^�C�g���N���X
//*****************************************************************************
class CTitle : public CScene
{
public:

	//�I�����ڂ̎��
	typedef enum
	{
		TYPE_START_GAME = 0,	// �X�^�[�g�Q�[��
		TYPE_TUTORIAL,			// �`���[�g���A��
		TYPE_RANKING,			// �����L���O
		TYPE_MAX
	} SELECT_TYPE;

	CTitle();									// �f�t�H���g�R���X�g���N�^
	~CTitle();									// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);					// �e�N�X�`���ǂݍ���
	static void Unload(void);					// �e�N�X�`���̔j��
	static CTitle *Create(void);				// ��������

	HRESULT Init(D3DXVECTOR3 pos);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static int GetSelect(void);					// �I�����ڂ̎擾����

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	CScene2D *m_pScene2D;						// Scene2D�ւ̃|�C���^
	D3DXVECTOR3 m_Pos;							// �ʒu
	static int m_nSelect;						// �I������
};

#endif // !_TITLE_H_