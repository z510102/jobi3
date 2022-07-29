//=============================================================================
//
// ���C�g�N���X [light.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//	���C�g�N���X
//*****************************************************************************
class CLight
{
public:
	typedef enum
	{
		LIGHT_0 = 0,
		LIGHT_1,
		LIGHT_2,
		LIGHT_MAX
	} LIGHT_TYPE;

	CLight();			// �R���X�g���N�^
	~CLight();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����

	static CLight *Create(void);	// ��������

private:
	D3DLIGHT9 m_light[3];	// ���C�g���
	D3DXVECTOR3 m_vecDir;			// �ݒ�p�����x�N�g��
	D3DXVECTOR3 m_vecDirection;
	D3DLIGHTTYPE m_type;
	D3DXCOLOR m_color;

};
#endif //!_LIGHT_H_