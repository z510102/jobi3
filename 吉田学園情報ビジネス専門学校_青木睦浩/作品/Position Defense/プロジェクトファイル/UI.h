//=============================================================================
//
// UI���� [UI.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// UI�N���X
//*****************************************************************************
class CUI : public CScene2D
{
public:
	// UI�̎��
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_HIGH_SCORE,			// �n�C�X�R�A
		TYPE_SCORE,					// �X�R�A
		TYPE_TIME,					// �^�C��
		TYPE_LIFE,					// ���C�t
		TYPE_GRENADE,				// �O���l�[�h
		TYPE_FLASH_GRENADE,			// �t���b�V���O���l�[�h
		TYPE_WEAPON,				// ����
		TYPE_TUTORIAL_ANIMATION,	// �`���[�g���A���A�j���[�V����
		TYPE_SWITCHING,				// �y�[�W�؂�ւ�
		TYPE_TITLE,					// �^�C�g��
		TYPE_RELOAD,				// �����[�h
		TYPE_INFINITE,				// ��
		TYPE_RANKING_RANK,			// �����L���O����
		TYPE_GAME_CLEAR,			// �Q�[���N���A
		TYPE_GAME_OVER,				// �Q�[���I�[�o�[
		TYPE_START_GAME,			// �Q�[���X�^�[�g
		TYPE_TUTORIAL,				// �`���[�g���A��
		TYPE_RANKING,				// �����L���O
		TYPE_MAX,
	} UI_TYPE;

	CUI(int nPriority = 4);													// �f�t�H���g�R���X�g���N�^
	~CUI();																	// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);                                              // �e�N�X�`���ǂݍ���
	static void Unload(void);                                               // �e�N�X�`���̔j��
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, UI_TYPE type);	// ��������

	HRESULT Init(D3DXVECTOR3 pos);											// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];						// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;														// �ʒu
	D3DXVECTOR2 m_size;														// �T�C�Y
	UI_TYPE m_Type;															// UI�̎��
	int m_nPatternAnimU;													// �A�j���[�V�����p�^�[���iU�j
	D3DXCOLOR m_Color;														// �F
	int m_nType;															// ��ށi���l�j
	int m_nReloadHG;														// �n���h�K���̃����[�h����Ƃ��̐��l
	int m_nReloadAR;														// �A�T���g���C�t���̃����[�h����Ƃ��̐��l
	int m_nReloadSG;														// �V���b�g�K���̃����[�h����Ƃ��̐��l
	int m_nReloadSR;														// �X�i�C�p�[���C�t���̃����[�h����Ƃ��̐��l
	int m_nReloadRL;														// ���P�b�g�����`���[�̃����[�h����Ƃ��̐��l
	int m_nBulletType;														// �e�̎��
};

#endif // !_SCORE_H_