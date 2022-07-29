//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

//*****************************************************************************
// �t�F�[�h�N���X
//*****************************************************************************
class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// �t�F�[�h�Ȃ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_MAX,
	} FADE;

	CFade(int nPriority = 9);														// �f�t�H���g�R���X�g���N�^
	~CFade();																		// �f�X�g���N�^

	// �����o�֐�
	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CManager::MODE mode);	// ��������

	HRESULT Init(D3DXVECTOR3 pos);													// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void Draw(void);																// �`�揈��

	void SetFade(CManager::MODE modenext);											// �ݒ菈��
	FADE GetFade(void);																// �擾����

private:
	// �����o�ϐ�
	FADE m_Fade;																	// �t�F�[�h�̎��
	CManager::MODE m_Mode;															// ��ʂ̃��[�h
	D3DXCOLOR m_Color;																// �J���[
};

#endif // !_FADE_H_