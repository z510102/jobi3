//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputGamepad;
class CSound;
class CTitle;
class CTutorial;
class CGame;
class CClear;
class COver;
class CResult;
class CFade;

//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:

	// ��ʂ̃��[�h�̎��
	typedef enum
	{
		MODE_TITLE = 0,		// �^�C�g��
		MODE_TUTORIAL,		// �`���[�g���A��
		MODE_GAME,			// �Q�[��
		MODE_CLEAR,			// �N���A
		MODE_OVER,			// �I�[�o�[
		MODE_RESULT,		// ���U���g
		MODE_MAX,
	} MODE;

	CManager();														// �f�t�H���g�R���X�g���N�^
	~CManager();													// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static void SetMode(MODE mode);									// ���[�h�̐ݒ菈��
	static MODE GetMode(void);										// ���[�h�̎擾����

	static CRenderer *GetRenderer(void);							// �����_�����O�N���X�̎擾
	static CInputKeyboard *GetInputKeyboard(void);					// �L�[�{�[�h�N���X�̎擾
	static CInputGamepad *GetInputGamepad(void);					// �Q�[���p�b�h�N���X�̎擾
	static CFade *GetFade(void);									// �t�F�[�h�N���X�̎擾
	static CSound *GetSound(void);									// �T�E���h�N���X�̎擾

private:
	// �����o�ϐ�
	static CTitle *m_pTitle;										// �^�C�g���̃C���X�^���X
	static CTutorial *m_pTutorial;									// �`���[�g���A���̃C���X�^���X
	static CGame *m_pGame;											// �Q�[���̃C���X�^���X
	static CClear *m_pClear;										// �N���A�̃C���X�^���X
	static COver *m_pOver;											// �I�[�o�[�̃C���X�^���X
	static CResult *m_pResult;										// ���U���g�̃C���X�^���X
	static MODE m_mode;												// ���[�h�̃C���X�^���X
	static CSound *m_pSound;										// �T�E���h�̃C���X�^���X
	static CRenderer *m_pRenderer;									// �����_�����O�N���X�̃C���X�^���X
	static CInputKeyboard *m_pInputKeyboard;						// �L�[�{�[�h�N���X�̃C���X�^���X
	static CInputGamepad *m_pInputGamepad;							// �Q�[���p�b�h�N���X�̃C���X�^���X
	static CFade *m_pFade;											// �t�F�[�h�N���X�̃C���X�^���X
};

#endif // !_MANAGER_H_