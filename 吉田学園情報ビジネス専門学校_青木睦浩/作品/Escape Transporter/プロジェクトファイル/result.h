//=============================================================================
//
// ���U���g��ʂ̏��� [result.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_BG (24)							 // �w�i�̃e�N�X�`���ԍ�
#define NOWSCORE_X (100.0f)						 // ���̃X�R�A��X���W
#define NOWSCORE_Y (200.0f)						 // ���̃X�R�A��Y���W
#define NOWSCORE_WIDTH (45.0f)					 // ���̃X�R�A�̕�
#define NOWSCORE_HEIGHT (47.0f)					 // ���̃X�R�A�̍���
#define NOWTIME_X (SCREEN_CENTER_X - 100.0f)	 // ���̎��Ԃ�X���W
#define NOWTIME_Y (250.0f)						 // ���̎��Ԃ�Y���W
#define NOWTIME_WIDTH (35.0f)					 // ���̎��Ԃ̕�
#define NOWTIME_HEIGHT (47.0f)					 // ���̎��Ԃ̍���
#define RANK_X (SCREEN_CENTER_X)				 // �����N��X���W
#define RANK_Y (600.0f)							 // �����N��Y���W
#define RANK_WIDTH (100.0f)						 // �����N�̕�
#define RANK_HEIGHT (100.0f)					 // �����N�̍���
#define PLUS_X (SCREEN_CENTER_X + 65.0f)		 // �v���X�\����X���W
#define PLUS_Y (550.0f)							 // �v���X�\����Y���W
#define PLUS_WIDTH (30.0f)						 // �v���X�\���̕�
#define PLUS_HEIGHT (30.0f)						 // �v���X�\���̍���
#define FILE_TIME ("data/SAVEDATA/newtime.txt")	 // �^�C���ǂݍ��ݗp�t�@�C��
#define FILE_SCORE ("data/SAVEDATA/newscore.txt")// �X�R�A�ǂݍ��ݗp�t�@�C��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;
class CTime;
class CScore;

//*****************************************************************************
// ���U���g�̃N���X
//*****************************************************************************
class CResult : public CScene
{
public:
	CResult();			// �R���X�g���N�^
	~CResult();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	static CResult *Create(void);	// ��������

private:
	bool			m_fade;		 // �t�F�[�h�C������
	bool			m_bflag1;	 // �t�F�[�h�C������
	bool			m_bflag2;	 // �t�F�[�h�C������
	bool			m_bflag3;	 // �t�F�[�h�C������
	static CScore	*m_pScore;	 // �X�R�A�̃C���X�^���X
	static CTime	*m_pTime;	 // �^�C���̃C���X�^���X
	CScore			*m_pNowScore;// ���̃X�R�A
	int				m_nNewdata;
	int				m_nTime;
	DWORD		m_dwCurrentTime;	  // �o�ߎ���
	DWORD		m_dwExecLastTime;	  // ���݂̎���

};

#endif // !_RESULT_H_
