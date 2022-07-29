//=============================================================================
//
// �t���b�V���O���l�[�h���������� [f_g_possession.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _F_G_POSSESSION_H_
#define _F_G_POSSESSION_H_

#include "scene2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �t���b�V���O���l�[�h�������N���X
//*****************************************************************************
class CF_G_Possession : public CScene
{
public:
	CF_G_Possession(int nPriority = 5);					// �f�t�H���g�R���X�g���N�^
	~CF_G_Possession();									// �f�X�g���N�^

	// �����o�֐�
	static CF_G_Possession *Create(D3DXVECTOR3 pos);	// ��������

	HRESULT Init(D3DXVECTOR3 pos);						// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	void SetF_G_Ppssession(int nG_Ppssession);			// �t���b�V���O���l�[�h�������̐ݒ菈��
	void SubF_G_Ppssession(int nValue);					// �t���b�V���O���l�[�h�������̌��Z����
	int GetF_G_Ppssession(void);						// �t���b�V���O���l�[�h�������̎擾����
	void AddF_G_Ppssession(int nValue);					// �t���b�V���O���l�[�h�������̉��Z����

private:
	// �����o�ϐ�
	CNumber *m_pNumber;									// �i���o�[�̃|�C���^
	int m_nF_G_Possession;								// �t���b�V���O���l�[�h������
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR2 m_size;									// �T�C�Y
};

#endif // !_F_G_POSSESSION_H_