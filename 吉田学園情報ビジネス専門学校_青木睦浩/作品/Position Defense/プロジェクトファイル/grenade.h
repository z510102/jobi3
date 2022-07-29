//=============================================================================
//
// �O���l�[�h���� [grenade.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �O���l�[�h�N���X
//*****************************************************************************
class CGrenade : public CScene2D
{
public:
	CGrenade(int nPriority = 3);									// �f�t�H���g�R���X�g���N�^
	~CGrenade();													// �f�X�g���N�^

	// �����o�֐�
	static CGrenade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// ��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static HRESULT Load(void);										// �e�N�X�`���ǂݍ���
	static void Unload(void);										// �e�N�X�`���̔j��
	void NotUse(void);												// �O���l�[�h���g�p��������

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_move;												// �ړ���
	D3DXVECTOR3 m_pos;												// �ʒu
	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	bool m_bUse;													// �g�p
	int m_nPassG;													// �O���l�[�h�������̏������炤
};

#endif // !_GRENADE_H_