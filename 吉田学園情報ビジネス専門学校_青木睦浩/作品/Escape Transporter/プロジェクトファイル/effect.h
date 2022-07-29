//=============================================================================
//
// �G�t�F�N�g [effect.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "billboard.h"

//*****************************************************************************
//	�G�t�F�N�g�N���X
//*****************************************************************************
class CEffect : public CBillboard
{
public:
	CEffect();							// �R���X�g���N�^
	virtual~CEffect();								// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int nColr, int nColg, int nColb, int nCola,
		int nSubColr, int nSubColg, int nSubColb, int nSubCola, int nLife);			// ����������
	virtual void Uninit(void);						// �I������
	virtual void Update(void);						// �X�V����
	virtual void Draw(void);						// �`�揈��

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;	// ���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3	m_pos;						// �ʒu
	D3DXVECTOR3	m_rot;						// ����
	D3DXVECTOR3	m_move;						// �ړ���
	D3DXVECTOR2 m_size;						// �T�C�Y
	int			m_nColorR;					// ��
	int			m_nColorG;					// ��
	int			m_nColorB;					// ��
	int			m_nColorA;					// �����x
	int			m_nSubColorR;				// �Ԃ̌����l
	int			m_nSubColorG;				// �΂̌����l
	int			m_nSubColorB;				// �̌����l
	int			m_nSubColorA;				// �����x�̌����l

	int			m_nLife;					// ����
	float		m_fAlpha;					// ���l
	float		m_fRemove;					// �ړ��ʂ̌����l
};
#endif //!_EFFECT_H_