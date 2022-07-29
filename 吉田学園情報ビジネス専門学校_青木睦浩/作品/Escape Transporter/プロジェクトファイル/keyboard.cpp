//=============================================================================
//
//	�L�[�{�[�h�N���X [keyboard.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "keyboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyStatePress[0], 0, sizeof(m_aKeyStatePress));		// �v���X
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));	// �g���K�[
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));	// �����[�X
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < NUM_KEY_MAX; nKey++)
		{
			// �g���K�[���
			m_aKeyStateTrigger[nKey] = (m_aKeyStatePress[nKey] & aKeyState[nKey]) ^ aKeyState[nKey];

			// �����[�X���
			m_aKeyStateRelease[nKey] = (m_aKeyStatePress[nKey] | aKeyState[nKey]) ^ aKeyState[nKey];

			// �v���X���
			m_aKeyStatePress[nKey] = aKeyState[nKey];
		}
	}
	else
	{	// �A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}
//=============================================================================
// �v���X���
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �g���K�[���
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �����[�X���
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
