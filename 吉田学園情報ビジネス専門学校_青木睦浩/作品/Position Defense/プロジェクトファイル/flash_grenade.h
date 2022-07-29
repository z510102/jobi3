//=============================================================================
//
// �t���b�V���O���l�[�h���� [flash_grenade.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _FLASH_GRENADE_H_
#define _FLASH_GRENADE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �t���b�V���O���l�[�h�N���X
//*****************************************************************************
class CFlashGrenade : public CScene2D
{
public:
	CFlashGrenade(int nPriority = 3);									// �f�t�H���g�R���X�g���N�^
	~CFlashGrenade();													// �f�X�g���N�^

	// �����o�֐�
	static CFlashGrenade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	// ��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);					// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	static HRESULT Load(void);											// �e�N�X�`���ǂݍ���
	static void Unload(void);											// �e�N�X�`���̔j��

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_move;													// �|���S���̈ړ���
	D3DXVECTOR3 m_pos;													// �|���S���̈ʒu
	static LPDIRECT3DTEXTURE9 m_pTexture;								// �e�N�X�`���ւ̃|�C���^
	bool m_bUse;														// �g�p
};

#endif // !_FLASH_GRENADE_H_