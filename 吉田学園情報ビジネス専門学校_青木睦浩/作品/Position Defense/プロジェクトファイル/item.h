//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �A�C�e���N���X
//*****************************************************************************
class CItem : public CScene2D
{
public:
	// �A�C�e���̎��
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_AR,		//�@�A�T���g���C�t���̒e
		TYPE_SG,		//�@�V���b�g�K���̒e
		TYPE_SR,		//�@�X�i�C�p�[���C�t���̒e
		TYPE_RL,		//�@���P�b�g�����`���[�̒e
		TYPE_G,			//�@�O���l�[�h
		TYPE_FG,		//�@�t���b�V���O���l�[�h
		TYPE_TIME,		//�@�^�C��
		TYPE_MAX,
	} ITEM_TYPE;

	CItem(int nPriority = 4);													// �f�t�H���g�R���X�g���N�^
	~CItem();																	// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`���̔j��
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ITEM_TYPE type);	// ��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);							// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];							// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move;															// �|���S���̈ړ���
	ITEM_TYPE m_type;															// �A�C�e���̎��
	D3DXVECTOR3 m_pos;															// �|���S���̈ʒu
};

#endif // !_ITEM_H_