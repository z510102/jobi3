//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �o���b�g�N���X
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	// �e�̎��
	typedef enum
	{
		TYPE_HG = 0,	// �n���h�K��
		TYPE_AR,		// �A�T���g���C�t��
		TYPE_SG,		// �V���b�g�K��
		TYPE_SR,		// �X�i�C�p�[���C�t��
		TYPE_RL,		// ���P�b�g�����`���[
		TYPE_MAX,
	} BULLET_TYPE;

	CBullet(int nPriority = 3);																			// �f�t�H���g�R���X�g���N�^
	~CBullet();																							// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);																			// �e�N�X�`���ǂݍ���
	static void Unload(void);																			// �e�N�X�`���̔j��
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fAngle, BULLET_TYPE bullettype);	// ��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);													// ����������
	void Uninit(void);																					// �I������
	void Update(void);																					// �X�V����
	void Draw(void);																					// �`�揈��

	void Delete(void);																					// ��������

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_move;																					// �|���S���̈ړ���
	D3DXVECTOR3 m_pos;																					// �|���S���̈ʒu
	static LPDIRECT3DTEXTURE9 m_pTexture;																// �e�N�X�`���ւ̃|�C���^
	BULLET_TYPE m_type;																					// �e�̎��
	float m_fAngle;																						// �p�x
	int m_nDamage;																						// �_���[�W
	int m_nLife;																						// ���C�t
	bool m_bUse;																						// �g�p
	int m_nPassHG;																						// �n���h�K��
	int m_nPassAR;																						// �A�T���g���C�t��
	int m_nPassSG;																						// �V���b�g�K��
	int m_nPassSR;																						// �X�i�C�p�[���C�t��
	int m_nPassRL;																						// ���P�b�g�����`���[
	int m_nType;																						// �e�̎�ށi���l�j
};

#endif // !_SCENE2D_H_