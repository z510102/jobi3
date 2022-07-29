//=============================================================================
//
// �������� [explosion.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �����N���X
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	// �����̎��
	typedef enum
	{
		TYPE_SG = 0,		// �V���b�g�K��
		TYPE_G,				// �O���l�[�h
		TYPE_KNOCK,			// �G��|�����Ƃ�
		TYPE_APPEARANCE,	// �G�̏o��
		TYPE_RL,			// ���P�b�g�����`���[
		TYPE_MAX,
	} EXPLOSION_TYPE;

	CExplosion(int nPriority = 3);																			// �f�t�H���g�R���X�g���N�^
	~CExplosion();																							// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);																				// �e�N�X�`���ǂݍ���
	static void Unload(void);																				// �e�N�X�`���̔j��
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR color, EXPLOSION_TYPE type);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);																			// ����������
	void Uninit(void);																						// �I������
	void Update(void);																						// �X�V����
	void Draw(void);																						// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;																	// �e�N�X�`���ւ̃|�C���^
	int m_nCounterAnim;																						// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;																						// �A�j���[�V�����p�^�[��
	D3DXVECTOR3 m_pos;																						// �ʒu
	D3DXCOLOR   m_color;																					// �F
	D3DXVECTOR2 m_size;																						// �T�C�Y
	EXPLOSION_TYPE m_Type;																					// �����̎��
};

#endif // !_EXPLOSION_H_