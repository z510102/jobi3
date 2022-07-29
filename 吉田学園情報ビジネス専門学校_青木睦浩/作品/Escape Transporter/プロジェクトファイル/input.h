//=============================================================================
//
// �C���v�b�g�N���X [input.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//	�C���v�b�g�N���X
//*****************************************************************************
class CInput
{
public:
	CInput();										// �R���X�g���N�^
	virtual ~CInput();								// �f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	virtual void Uninit(void);								// �I������
	virtual void Update(void) = 0;							// �X�V����

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;							// ���̓f�o�C�X�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;							// DirectInput�I�u�W�F�N�g�̃|�C���^
};
#endif //!_INPUT_H_