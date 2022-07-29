//=============================================================================
//
// �Q�[���I�[�o�[���� [over.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _OVER_H_
#define _OVER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �Q�[���I�[�o�[�N���X
//*****************************************************************************
class COver : public CScene
{
public:
	COver();									// �f�t�H���g�R���X�g���N�^
	~COver();									// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);					// �e�N�X�`���ǂݍ���
	static void Unload(void);					// �e�N�X�`���̔j��
	static COver *Create(void);					// ��������

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

#endif // !_OVER_H_