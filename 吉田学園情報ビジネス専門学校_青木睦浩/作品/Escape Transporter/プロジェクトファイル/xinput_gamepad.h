//=============================================================================
//
//	�Q�[���p�b�h�N���X [xinput_gamepad.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _XINPUT_GAMEPAD_H_
#define _XINPUT_GAMEPAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

//*****************************************************************************
//	�Q�[���p�b�h�N���X
//*****************************************************************************
class CXinputPad : public CInput
{
public:
	// �V�����_�[�g���K�[�̗�
	typedef enum
	{
		SHOULDERTYPE_RIGHT = 0,
		SHOULDERTYPE_LEFT,
		SHOULDERTYPE_MAX
	} SHOULDER_TRIGGER;

	// �X�e�B�b�N�̕�����
	typedef enum
	{
		STICKTYPE_UP = 0,
		STICKTYPE_RIGHT,
		STICKTYPE_LEFT,
		STICKTYPE_DOWN,
		STICKTYPE_MAX
	} STICKTYPE;

	CXinputPad();			//�R���X�g���N�^
	~CXinputPad();			//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����

	bool GetButtonPress(int nButton);				// �{�^���̃v���X����
	bool GetButtonTrigger(int nButton);				// �{�^���̃g���K�[����
	bool GetButtonRelease(int nButton);				// �{�^���̃����[�X����

	bool GetShoulder(int nShoulderTrigger);			// �V�����_�[�g���K�[�̃v���X����
	bool GetShoulderTrigger(int nShoulderTrigger);	// �V�����_�[�g���K�[�̃g���K�[����
	bool GetShoulderRelease(int nShoulderTrigger);	// �V�����_�[�g���K�[�̃����[�X����

	bool GetLeftStick(int nLstick);							// ���X�e�B�b�N�̊�{����
	bool GetLeftStickTrigger(int nLstick);					// ���X�e�B�b�N�̃g���K�[����
	bool GetLeftStickRelease(int nLstick);					// ���X�e�B�b�N�̃����[�X����

	bool GetRightStick(int nRstick);						// �E�X�e�B�b�N�̊�{����
	void SetVibration(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond);	// �R���g���[���̐U���@�\�ݒ�(�o�C�u���[�V�����@�\)

private:
	XINPUT_STATE		m_state;			// �R���g���[���[�̏��
	XINPUT_STATE		m_stateLast;		// �R���g���[���[�̏�ԕۑ�
	XINPUT_VIBRATION	m_vibration;		// �R���g���[���̐U���@�\(�o�C�u���[�V�����@�\)
	bool				m_bConnect;			// �R���g���[���[�̐ڑ�����
	bool				m_bVibration;		// �R���g���[���̐U���@�\(�o�C�u���[�V�����@�\)�̎g�p����
	int					m_nCntVibration;	// �R���g���[���̐U���@�\(�o�C�u���[�V�����J�E���^�[)
};
#endif //!_GAMEPAD_H_