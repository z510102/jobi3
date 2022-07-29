//=============================================================================
//
// �L�[�{�[�h���� [input_keyboard.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256)

//*****************************************************************************
// �L�[�{�[�h�N���X
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// �f�t�H���g�R���X�g���N�^
	~CInputKeyboard();								// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����

	bool GetKeyboardPress(int nKey);				// �v���X���
	bool GetKeyboardTrigger(int nKey);				// �g���K�[���

private:
	// �����o�ϐ�
	BYTE m_aKeyStatePress[NUM_KEY_MAX];				// �v���X
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// �g���K�[
};

#endif // !_INPUT_KEYBOARD_H_