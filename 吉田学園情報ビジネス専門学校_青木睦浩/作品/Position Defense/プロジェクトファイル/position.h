//=============================================================================
//
// �|�W�V�������� [position.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _POSITION_H_
#define _POSITION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �|�W�V�����N���X
//*****************************************************************************
class CPosition : public CScene2D
{
public:
	CPosition(int nPriority = 1);									// �f�t�H���g�R���X�g���N�^
	~CPosition();													// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);										// �e�N�X�`���ǂݍ���
	static void Unload(void);										// �e�N�X�`���̔j��
	static CPosition *Create(D3DXVECTOR3 pos, D3DXCOLOR color);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);									// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	D3DXCOLOR   m_color;											// �|���S���̃J���[
};

#endif // !_POSITION_H_