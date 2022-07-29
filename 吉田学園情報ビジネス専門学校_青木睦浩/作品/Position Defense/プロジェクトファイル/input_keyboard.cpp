//=============================================================================
//
// ���͏��� [input_keyboard.cpp]
// Author : �ؖr�_
//
//=============================================================================

#include "input_keyboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyStatePress[0], 0, sizeof(m_aKeyStatePress));      //�v���X
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));  //�g���K�[
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �}�E�X�Ƃ��͂����ɑ��₵�Ă���


	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CInputKeyboard::Update(void)
{
	// �L�[�{�[�h�̓��͏��
	BYTE aKeyState[NUM_KEY_MAX];

	// �J�E���g�p�̕ϐ�
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		// �L�[�{�[�h�̓��͏��ۑ�
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//�g���K�[�L�[
			m_aKeyStateTrigger[nCntKey] = (m_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			m_aKeyStatePress[nCntKey] = aKeyState[nCntKey];
		}
	}

	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
		m_pDevice->Acquire();
	}
}

//=============================================================================
//�L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}