//=============================================================================
//
// ���C�t���� [life.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "scene2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// ���C�t�N���X
//*****************************************************************************
class CLife : public CScene
{
public:
	CLife(int nPriority = 0);					// �f�t�H���g�R���X�g���N�^
	~CLife();									// �f�X�g���N�^

	// �����o�֐�
	static CLife *Create(D3DXVECTOR3 pos);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	void SetLife(int nLife);					// �X�R�A�̐ݒ菈��
	void AddLife(int nValue);					// �X�R�A�̉��Z����
	void SubLife(int nValue);					// �X�R�A�̌��Z����
	int GetLife(void);							// �X�R�A�̎擾����

private:
	// �����o�ϐ�
	CNumber *m_pNumber;							// �X�R�A�̃|�C���^�z��
	int m_nLife;								// ���C�t
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR2 m_size;							// �T�C�Y
	bool m_bUse;								// �g�p
};

#endif // !_LIFE_H_