//=============================================================================
//
// UI�N���X�̏��� [UI.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_SCORE (5)		// �X�R�A�̃P�^��
#define MAX_TIME (3)		// ���Ԃ̃P�^��
#define LIFE_WIDTH (150.0f)	// ���C�t�o�[�̕�
#define LIFE_HEIGHT (40.0f)	// ���C�t�o�[�̍���
#define LIFE_MAX (260)		// ���C�t�̏��
#define LIFE_DAMAGE (10.0f)	// ���C�t�o�[�̌����
#define STOP_PUSH (300.0f)	// PUSHSTART���~�܂�ʒu
#define MOVE_PUSH (2.0f)	// PUSHSTART�̑��x
#define MOVE_PICT (5.0f)	// ��̐l�̈ړ����x

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
//UI�̃N���X
//*****************************************************************************
class CUI : public CScene2D
{
public:

	CUI(int nPriority = PRIORITY_UI);	// �R���X�g���N�^
	~CUI();					// �f�X�g���N�^

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void AddLife(int nValue);	// ���C�t���Z
	int GetLife(void);			// ���C�t�擾

								// ��������
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, CTexture::TEXTURETYPE type);

private:
	CNumber						*m_apTime[MAX_TIME];	// �����̃C���X�^���X�i���ԁj
	CNumber						*m_apScore[MAX_SCORE];	// �����̃C���X�^���X�i�X�R�A�j
	D3DXCOLOR					m_col;					// �F
	D3DXVECTOR3					m_size;					// �傫��
	D3DXVECTOR3					m_Lifesize;				// ���C�t�Q�[�W�̑傫��
	D3DXVECTOR3					m_pos;					// �ʒu
	float						m_fPosV;				// �e�N�X�`�����WV
	float						m_fPosU;				// �e�N�X�`�����WU
	CTexture::TEXTURETYPE		m_type;					// UI�̃^�C�v
	bool						m_bBrinkFlag;			// PUSHSPACE�̓_�Ŕ���
	bool						m_bBrinkFlag2;			// �^�C�g���̎��̔�������
	bool						m_fade;					// �t�F�[�h�C������
	bool						m_bDisplay;				// ���S�����܂ō~�肽������					
	int							m_nLife;				// �c�胉�C�t
	DWORD						m_dwCurrentTime;		// �o�ߎ���
	DWORD						m_dwExecLastTime;		// ���݂̎���
	CManager::MODE				m_mode;					// ���[�h

};

#endif // !_TYTLEUI_H_