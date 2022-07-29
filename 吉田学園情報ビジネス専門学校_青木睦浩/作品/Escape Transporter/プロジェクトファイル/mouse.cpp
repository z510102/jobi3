//=============================================================================
//
//	�}�E�X�N���X [mouse.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mouse.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
DIMOUSESTATE CMouse::m_CurrentMouseState;		// �}�E�X�̌��݂̓��͏��
DIMOUSESTATE CMouse::m_PrevMouseState;			// �}�E�X�̈�t���[���O�̓��͏��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMouse::CMouse()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMouse::~CMouse()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
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

	// �|�[�����O���J�n
	m_pDevice->Poll();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CMouse::Update(void)
{
	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	m_PrevMouseState = m_CurrentMouseState;

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState)))
	{
		// �A�N�Z�X���̎擾
		m_pDevice->Acquire();

		// �ŐV�̃}�E�X�̏�Ԃ��X�V
		m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);
	}
}

bool CMouse::ButtonDown(int nButton)
{
	if (!(m_PrevMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX) &&
		m_CurrentMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX)
	{
		return true;
	}

	return false;
}

bool CMouse::ButtonUp(int nButton)
{
	if (m_PrevMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX &&
		!(m_CurrentMouseState.rgbButtons[nButton] & NUM_BUTTON_MAX))
	{
		return true;
	}

	return false;
}
