//=============================================================================
//
// ���͏��� [input.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �C���v�b�g�N���X
//*****************************************************************************
class CInput
{
public:
	CInput();												// �f�t�H���g�R���X�g���N�^
	virtual ~CInput();										// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	virtual void Uninit(void);								// �I������

protected:
	//�����o�ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevice;							// ���̓f�o�C�X�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;							// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
};

#endif // !_INPUT_H_