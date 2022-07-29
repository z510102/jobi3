//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_EFFECT (128)

//*****************************************************************************
// �G�t�F�N�g�N���X
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority);																	// �f�t�H���g�R���X�g���N�^
	~CEffect();																				// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos,
		                 int nColorR, int nColorG, int nColorB, int nColorA,
		                 int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA);	// ����������
	virtual void Uninit(void);																// �I������
	virtual void Update(void);																// �X�V����
	virtual void Draw(void);																// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;													// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;																		// �|���S���̈ʒu
	D3DXVECTOR2 m_size;																		// �|���S���̃T�C�Y
	D3DXCOLOR   m_color;																	// �|���S���̃J���[
	int m_nColorR;																			// �J���[�i�ԁj
	int m_nColorG;																			// �J���[�i�΁j
	int m_nColorB;																			// �J���[�i�j
	int m_nColorA;																			// �J���[�i�����x�j
	int m_nColorSubR;																		// �T�u�J���[�i�ԁj
	int m_nColorSubG;																		// �T�u�J���[�i�΁j
	int m_nColorSubB;																		// �T�u�J���[�i�j
	int m_nColorSubA;																		// �T�u�J���[�i�����x�j
};

#endif // !_EFFECT_H_