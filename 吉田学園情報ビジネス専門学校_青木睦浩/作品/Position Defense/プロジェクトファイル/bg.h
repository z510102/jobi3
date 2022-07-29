//=============================================================================
//
// �w�i���� [bg.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "scene2D.h"

//*****************************************************************************
// �w�i�N���X
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);					// �f�t�H���g�R���X�g���N�^
	~CBg();									// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);				// �e�N�X�`���ǂݍ���
	static void Unload(void);				// �e�N�X�`���̔j��
	static CBg *Create(void);				// ��������

	HRESULT Init(D3DXVECTOR3 pos);			// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	CScene2D *m_pScene2D;					// Scene2D�ւ̃|�C���^
	D3DXVECTOR3 m_Pos;						// �ʒu
	int m_nPriority;						// �D�揇��
};

#endif // !_BG_H_