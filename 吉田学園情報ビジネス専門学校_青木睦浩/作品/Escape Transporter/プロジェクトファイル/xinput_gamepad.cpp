//=============================================================================
//
//	�Q�[���p�b�h�N���X [Xinput_gamepad.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "Xinput_gamepad.h"
#include "input.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXinputPad::CXinputPad()
{
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));			// �R���g���[���[�̏��
	ZeroMemory(&m_stateLast, sizeof(XINPUT_STATE));		// �R���g���[���[�̏�ԕۑ�
	ZeroMemory(&m_vibration, sizeof(XINPUT_VIBRATION));	// �R���g���[���̐U���@�\�̃��[�^�[���x���x��
	m_bVibration = false;								// �R���g���[���̐U���@�\�̎g�p����
	m_nCntVibration = 0;								// �R���g���[���̐U���@�\(�o�C�u���[�V�����J�E���^�[)
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXinputPad::~CXinputPad()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CXinputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CXinputPad::Uninit(void)
{
	// ������false�̏ꍇ�F���ݍĐ����̃o�C�u���[�V�����G�t�F�N�g���~
	XInputEnable(false);

	CInput::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CXinputPad::Update(void)
{
	// �R���g���[���[�̏��
	XINPUT_STATE state;

	// XInput����R���g���[���[�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// �R���g���[���[�Ɛڑ����Ă���
		m_bConnect = true;
	}
	else
	{
		// �R���g���[���[�Ɛڑ����Ă��Ȃ�
		m_bConnect = false;
	}

	// ���X�e�B�b�N����
	// �T���X�e�B�b�N���f�b�h�]�[�����ɂ���ꍇ�͒l���[��
	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}

	// �E�X�e�B�b�N����
	// �T���X�e�B�b�N���f�b�h�]�[�����ɂ���ꍇ�͒l���[��
	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}

	// �U���@�\(�o�C�u���[�V����)�̃J�E���g�_�E��
	if (m_nCntVibration > 0)
	{
		m_nCntVibration--;
	}
	// �J�E���g���I������ƐU���@�\(�o�C�u���[�V����)���I��
	if (m_nCntVibration <= 0 && m_bVibration == true)
	{
		SetVibration(0, 0, 0);
		m_bVibration = false;
	}

	// �R���g���[���[�̓��͏�Ԃ�ۑ�
	m_stateLast = m_state;
	m_state = state;
}
//=======================================================================
// �{�^���̃v���X����
//=======================================================================
bool CXinputPad::GetButtonPress(int nButton)
{
	return m_state.Gamepad.wButtons & nButton ? true : false;
}
//=======================================================================
// �{�^���̃g���K�[����
//=======================================================================
bool CXinputPad::GetButtonTrigger(int nButton)
{
	return (((m_stateLast.Gamepad.wButtons & nButton) == false) && (m_state.Gamepad.wButtons & nButton)) ? true : false;
}
//=============================================================================
// �����[�X���
//=============================================================================
bool CXinputPad::GetButtonRelease(int nButton)
{
	return (((m_stateLast.Gamepad.wButtons & nButton) == false) && (m_state.Gamepad.wButtons & nButton)) ? true : false;
}

//=======================================================================
// �V�����_�[�g���K�[�̃v���X����
//=======================================================================
bool CXinputPad::GetShoulder(int nShoulderTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nShoulderTrigger)
	{
	case SHOULDERTYPE_RIGHT:
		return m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case SHOULDERTYPE_LEFT:
		return m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}

}
//=======================================================================
// �V�����_�[�g���K�[�̃g���K�[����
//=======================================================================
bool CXinputPad::GetShoulderTrigger(int nShoulderTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nShoulderTrigger)
	{
	case SHOULDERTYPE_RIGHT:
		return (((m_stateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case SHOULDERTYPE_LEFT:
		return (((m_stateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// �V�����_�[�g���K�[�̃����[�X����
//=======================================================================
bool CXinputPad::GetShoulderRelease(int nShoulderTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nShoulderTrigger)
	{
	case SHOULDERTYPE_RIGHT:
		return (((m_stateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case SHOULDERTYPE_LEFT:
		return (((m_stateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=======================================================================
// ���X�e�B�b�N�̃v���X����
//=======================================================================
bool CXinputPad::GetLeftStick(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// ���X�e�B�b�N�̃g���K�[����
//=======================================================================
bool CXinputPad::GetLeftStickTrigger(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return (((m_stateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return (((m_stateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_LEFT:
		return (((m_stateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_DOWN:
		return (((m_stateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// ���X�e�B�b�N�̃����[�X����
//=======================================================================
bool CXinputPad::GetLeftStickRelease(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return (((m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return (((m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_LEFT:
		return (((m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_DOWN:
		return (((m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
// �E�X�e�B�b�N�̃v���X����
//=======================================================================
bool CXinputPad::GetRightStick(int nRstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nRstick)
	{
	case STICKTYPE_UP:
		return m_state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return m_state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return m_state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return m_state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}
//=======================================================================
//�o�C�u���[�V�����ݒ�
//=======================================================================
void CXinputPad::SetVibration(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond)
{
	m_vibration.wLeftMotorSpeed = nLeftMotorSpeed;		// �����[�^�[�̑��x�F�L���Ȓl��0�`65,535�͈̔�

	m_vibration.wRightMotorSpeed = nRightMotorSpeed;	// �E���[�^�[�̑��x�F�L���Ȓl��0�`65,535�͈̔�

	XInputSetState(0, &m_vibration);			// �U���@�\(�o�C�u���[�V����)�ݒ�

	m_nCntVibration = nSecond;					// �U���@�\(�o�C�u���[�V����)�̎g�p�J�E���g

	m_bVibration = true;						// �U���@�\(�o�C�u���[�V����)���g�p
}