//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �`���[�g���A���N���X
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial();								// �f�t�H���g�R���X�g���N�^
	~CTutorial();								// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);					// �e�N�X�`���ǂݍ���
	static void Unload(void);					// �e�N�X�`���̔j��
	static CTutorial *Create(void);				// ��������

	HRESULT Init(D3DXVECTOR3 pos);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	CScene2D *m_pScene2D;						// Scene2D�ւ̃|�C���^
	D3DXVECTOR3 m_Pos;							// �ʒu
};

#endif // !_TUTORIAL_H_