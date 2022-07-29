//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//	�t�F�[�h�N���X
//*****************************************************************************
class CFade : public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// �t�F�[�h�Ȃ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_DIM,
		FADE_MAX
	} FADE;

	CFade(int nPriority = PRIORITY_FADE);	// �R���X�g���N�^
	~CFade();							// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE mode);		// ��������
	FADE GetFade(void);						// �t�F�[�h�擾
	void SetFade(CManager::MODE modenext);	// �t�F�[�h�̐ݒ�
	
private:
	CManager::MODE			m_mode;			// ���[�h�̎��
	D3DXCOLOR				m_color;		// �t�F�[�h�̓����x
	FADE					m_fade;			// �t�F�[�h�̎��
};
#endif