//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �G�l�~�[�N���X
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	// �G�̎��
	typedef enum
	{
		TYPE_0 = 0,		// �^�C�v0
		TYPE_1,			// �^�C�v1
		TYPE_2,			// �^�C�v2
		TYPE_3,			// �^�C�v3
		TYPE_4,			// �^�C�v4
		TYPE_5,			// �^�C�v5
		TYPE_6,			// �^�C�v6
		TYPE_MAX,
	} ENEMY_TYPE;

	CEnemy(int nPriority = 2);													// �f�t�H���g�R���X�g���N�^
	~CEnemy();																	// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`���̔j��
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY_TYPE type);	// ��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);							// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��

	void KnockDown(void);														// �G��|�������̏���

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];							// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move;															// �|���S���̈ړ���
	ENEMY_TYPE m_Type;															// �G�̎��
	D3DXVECTOR3 m_pos;															// �|���S���̈ʒu
	int m_nPatternAnimU;														// �A�j���[�V�����p�^�[���iU�j
	int m_nCounterAnim;															// �A�j���[�V�����J�E���^�[
	int m_nStop;																// �ړ���~
	bool m_bStop;																// ��~���Ă��邩�ǂ���
};

#endif // !_ENEMY_H_