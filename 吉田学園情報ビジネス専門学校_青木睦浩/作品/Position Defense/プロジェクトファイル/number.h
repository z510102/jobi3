//=============================================================================
//
// �i���o�[���� [number.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//*****************************************************************************
// �i���o�[�N���X
//*****************************************************************************
class CNumber
{
public:
	CNumber();																// �f�t�H���g�R���X�g���N�^
	~CNumber();																// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);                                              // �e�N�X�`���ǂݍ���
	static void Unload(void);                                               // �e�N�X�`���̔j��
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// ��������

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	void SetNumber(int nNumber);											// �i���o�[�̐ݒ菈��
	void SetColor(int nColR, int nColG, int nColB, int nColA);				// �F�ݒ菈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;									// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;														// �ʒu
	D3DXVECTOR2 m_size;														// �T�C�Y
};

#endif // !_NUMBER_H_