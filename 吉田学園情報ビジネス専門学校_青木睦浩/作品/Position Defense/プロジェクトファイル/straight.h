//=============================================================================
//
// �G�t�F�N�g�̋O�Տ��� [straight.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _STRAIGHT_H_
#define _STRAIGHT_H_

#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STRAIGHT (128)

//*****************************************************************************
// �G�t�F�N�g�O�ՃN���X
//*****************************************************************************
class CStraight : public CEffect
{
public:
	CStraight(int nPriority = 4);																// �f�t�H���g�R���X�g���N�^
	~CStraight();																				// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);																	// �e�N�X�`���ǂݍ���
	static void Unload(void);																	// �e�N�X�`���̔j��
	static CStraight *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,
		                     int nColorR, int nColorG, int nColorB, int nColorA,
		                     int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
		                     int nLife);														// ��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size,
		                 int nColorR, int nColorG, int nColorB, int nColorA,
		                 int nColorSubR, int nColorSubG, int nColorSubB, int nColorSubA,
		                 int nLife);															// ����������
	virtual void Uninit(void);																	// �I������
	virtual void Update(void);																	// �X�V����
	virtual void Draw(void);																	// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;														// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;																			// �|���S���̈ʒu
	D3DXVECTOR2 m_size;																			// �|���S���̃T�C�Y
	D3DXCOLOR   m_color;																		// �|���S���̃J���[
	int m_nLife;																				// ����
	int m_nColorR;																				// �F�i�ԁj
	int m_nColorG;																				// �F�i�΁j
	int m_nColorB;																				// �F�i�j
	int m_nColorA;																				// �F�i�����x�j
	int m_nColorSubR;																			// �T�u�F�i�ԁj
	int m_nColorSubG;																			// �T�u�F�i�΁j
	int m_nColorSubB;																			// �T�u�F�i�j
	int m_nColorSubA;																			// �T�u�F�i�����x�j
};

#endif // !_STRAIGHT_H_