//=============================================================================
//
// �w�i�̃N���X [bg.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_X (SCREEN_CENTER_X)		// �w�i��X���W
#define BG_Y (SCREEN_CENTER_Y)		// �w�i��Y���W
#define BG_WIDTH (SCREEN_WIDTH / 2)	// �w�i�̕�
#define BG_HEIGHT (SCREEN_HEIGHT / 2)// �w�i�̍���

//*****************************************************************************
// �w�i�̃N���X�̒�`
//*****************************************************************************
class CBg : public CScene2D
{
public:
	CBg(int nPriority = PRIORITY_BG);	// �R���X�g���N�^
	~CBg();					// �f�X�g���N�^

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	static HRESULT	Load(void);		//�e�̃e�N�X�`�����[�h
	static void		Unload(void);	//�e�̃e�N�X�`���A�����[�h

	//�w�i�̐���
	static CBg	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);

private:
	D3DXVECTOR3					m_pos;			//�ړ���
	float						m_fPosV;		//�e�N�X�`�����W
	int							m_nPriority;	//�D�揇��
	int							m_nType;		//���

};

#endif // !_BG_H_
