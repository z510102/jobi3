//=============================================================================
//
//	�L�[�{�[�h�N���X [inputkeyboard.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//	�L�[�{�[�h�N���X
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// �R���X�g���N�^
	~CInputKeyboard();								// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����

	bool GetPress(int nKey);						// �v���X���
	bool GetTrigger(int nKey);						// �g���K�[���
	bool GetRelease(int nKey);						// �����[�X���

private:
	BYTE m_aKeyStatePress[NUM_KEY_MAX];				// �v���X
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// �g���K�[
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			// �����[�X

};
#endif //!_INPUT_KEYBOARD_H_