//=============================================================================
//
// �^�C�g���N���X�̏��� [title.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PUSH_X (SCREEN_CENTER_X)			// PUSHSTART��X���W
#define PUSH_Y (200.0f + SCREEN_CENTER_Y)	// PUSHSTART��Y���W
#define PUSH_WIDTH (350.0f)					// PUSHSTART�̕�
#define PUSH_HEIGHT (100.0f)				// PUSHSTART�̍���
#define TITLE_X (SCREEN_CENTER_X)			// ���S��X���W
#define TITLE_Y (100.0f)					// ���S��Y���W
#define TITLE_WIDTH (550.0f)				// ���S�̕�
#define TITLE_HEIGHT (80.0f)				// ���S�̍���
#define HUMAN_X (0.0f)						// ��̃A����X���W
#define HUMAN_Y (50.0f)						// ��̃A����Y���W
#define HUMAN_WIDTH (60.0f)					// ��̃A���̕�
#define HUMAN_HEIGHT (50.0f)				// ��̃A���̍���

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �^�C�g���̃N���X
//*****************************************************************************
class CTitle : public CScene
{
public:
	CTitle();	// �R���X�g���N�^
	~CTitle();	// �f�X�g���N�^

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	static CTitle *Create(void);// ��������

private:
	bool m_fade;			//�t�F�[�h�C������
	DWORD m_dwCurrentTime;	//�N�����̎���
	DWORD m_dwExecLastTime;	//�o�ߎ���

};

#endif // !_TITLE_H_
