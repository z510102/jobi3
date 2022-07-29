//=============================================================================
//
// �O���l�[�h���������� [g_possession.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _G_POSSESSION_H_
#define _G_POSSESSION_H_

#include "scene2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �O���l�[�h�������N���X
//*****************************************************************************
class CG_Possession : public CScene
{
public:
	CG_Possession(int nPriority = 5);					// �f�t�H���g�R���X�g���N�^
	~CG_Possession();									// �f�X�g���N�^

	// �����o�֐�
	static CG_Possession *Create(D3DXVECTOR3 pos);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);						// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	void SetG_Ppssession(int nG_Ppssession);			// �O���l�[�h�������̐ݒ菈��
	void SubG_Ppssession(int nValue);					// �O���l�[�h�������̌��Z����
	int GetG_Ppssession(void);							// �O���l�[�h�������̎擾����
	void AddG_Ppssession(int nValue);					// �O���l�[�h�������̉��Z����

private:
	// �����o�ϐ�
	CNumber *m_pNumber;									// �O���l�[�h�������̃|�C���^
	int m_nG_Possession;								// ������
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR2 m_size;									// �T�C�Y
};

#endif // !_G_POSSESSION_H_