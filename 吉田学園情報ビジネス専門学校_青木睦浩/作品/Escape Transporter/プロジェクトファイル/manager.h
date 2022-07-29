//=============================================================================
//
// �}�l�[�W�� [manager.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CXinputPad;
class CSound;

class CTitle;
class CMenu;
class CTutorial;
class CSelect;
class CGame;
class CResult;
class CRanking;
class CRanking2;
class CFade;
class CLight;
class CCamera;
class CTexture;
class CModel;
//*****************************************************************************
//	�}�l�[�W���N���X
//*****************************************************************************
class CManager
{
public:
	// ���[�h�̎��
	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_MENU,		// �I��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_SELECT,	// ����Z���N�g
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	//���U���g
		MODE_RANKING,
		MODE_RANKING2,
		MODE_MAX		// �ő吔
	} MODE;

	CManager();										// �R���X�g���N�^
	~CManager();									// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CRenderer		*GetRenderer(void);		// �����_���[���擾
	static CInputKeyboard	*GetInputKeyboard(void);// �L�[�{�[�h���擾
	static CXinputPad		*GetXinputPad(void);	// �Q�[���p�b�h�擾
	static CSound			*GetSound(void);		// �T�E���h���擾
	static CTitle			*GetTitle(void); 		// �^�C�g���̃C���X�^���X
	static CMenu			*GetMenu(void); 		// ���j���[�̃C���X�^���X
	static CTutorial		*GetTutorial(void);		// �`���[�g���A���̃C���X�^���X
	static CSelect			*GetSelect(void);		// �Z���N�g�̃C���X�^���X
	static CGame			*GetGame(void);			// �Q�[���̃C���X�^���X
	static CResult			*GetResult(void);		// ���U���g�̃C���X�^���X
	static CRanking			*GetRanking(void);		// �����L���O�̃C���X�^���X
	static CRanking2		*GetRanking2(void);		// �����L���O�̃C���X�^���X
	static CFade			*GetFade(void);			// �t�F�[�h���擾
	static CLight			*GetLight(void); 		// ���C�g���擾
	static CCamera			*GetCamera(void);		// �J�������擾
	static CTexture			*GetTexture(void);		// �e�N�X�`�����擾
	static CModel			*GetModel(void); 		// ���f�����擾


	static void SetMode(MODE mode);	// ���[�h�̐ݒ�
	static MODE GetMode(void);		// ���[�h���擾


private:
	static CRenderer		*m_pRenderer;			// �����_���[�̃C���X�^���X
	static CInputKeyboard	*m_pInputKeyboard;		// �L�[�{�[�h�̃C���X�^���X
	static CXinputPad		*m_pXinputPad;			// �Q�[���p�b�h�̃C���X�^���X
	static CSound			*m_pSound;				// �T�E���h�̃C���X�^���X
	static CTitle			*m_pTitle;				// �^�C�g���̃C���X�^���X
	static CMenu			*m_pMenu;				// ���j���[�̃C���X�^���X
	static CTutorial		*m_pTutorial;			// �`���[�g���A���̃C���X�^���X
	static CSelect			*m_pSelect;				// �Z���N�g�̃C���X�^���X
	static CGame			*m_pGame;				// �Q�[���̃C���X�^���X
	static CResult			*m_pResult;				// ���U���g�̃C���X�^���X
	static CRanking			*m_pRanking;			// �����L���O�̃C���X�^���X
	static CRanking2			*m_pRanking2;			// �����L���O2�̃C���X�^���X
	static CFade			*m_pFade;				// �t�F�[�h�̃C���X�^���X
	static CLight			*m_pLight;				// ���C�g�̃C���X�^���X
	static CCamera			*m_pCamera;				// �J�����̃C���X�^���X
	static CTexture			*m_pTexture;			// �e�N�X�`���̃C���X�^���X
	static CModel			*m_pModel;			// ���f���̃C���X�^���X

	static MODE				m_mode;					// ��ʂ̃��[�h

};
#endif //!_MANAGER_H_