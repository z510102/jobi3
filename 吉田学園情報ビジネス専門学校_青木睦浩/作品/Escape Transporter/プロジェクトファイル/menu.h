//=============================================================================
//
// ���j���[�̏��� [menu.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_UI (12)							// UI�̍ő吔
#define UITEXT_X (250.0f)					// �A����X���W
#define UITEXT_WIDTH (250.0f)				// �A���̕�
#define UITEXT_HEIGHT (50.0f)				// �A���̍���
#define UIICON_X (SCREEN_CENTER_X + 250.0f)	// �A�C�R����X���W
#define UIICON_Y (SCREEN_CENTER_Y - 50.0f)	// �A�C�R����Y���W
#define UIICON_WIDTH (250.0f)				// �A�C�R���̕�
#define UIICON_HEIGHT (250.0f)				// �A�C�R���̍���
#define UIINFO_Y (SCREEN_CENTER_Y + 250.0f)	// ��������X���W
#define UIINFO_WIDTH (350.0f)				// �������̕�
#define UIINFO_HEIGHT (80.0f)				// �������̍���

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;
class CUI;

//*****************************************************************************
// ���U���g�̃N���X
//*****************************************************************************
class CMenu : public CScene
{
public:
	// �I�����̗�
	typedef enum
	{
		SELECT_PLAY = 0,		// �I���i�v���C�j
		SELECT_TUTORIAL,		// �I���i�`���[�g���A���j
		SELECT_RANKING,			// �I���i�����L���O�j
		SELECT_QUIT,			// �I���i�߂�j
		SELECT_MAX
	} SELECTTYPE;

	CMenu();		// �R���X�g���N�^
	~CMenu();		// �f�X�g���N�^

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	static CMenu *Create(void);	// ��������

private:
	bool		m_fade;			// �t�F�[�h�C������
	static CUI	*m_pUI[12];		// UI�̃C���X�^���X
	int			m_nCntSelect;	// �ǂ���I��ł邩�̂��

};

#endif // !_RESULT_H_
