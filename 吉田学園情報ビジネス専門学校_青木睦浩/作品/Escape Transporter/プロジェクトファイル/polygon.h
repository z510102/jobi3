//=============================================================================
//
// �|���S���N���X [polygon.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================

//*****************************************************************************
//	�v���C���[�N���X
//*****************************************************************************
class CPolygon : public CScene2D
{
public:
	CPolygon();			// �R���X�g���N�^
	~CPolygon();			// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);		// ��������

	static HRESULT Load(void);				// �e�N�X�`���̓ǂݍ���
	static void Unload(void);				// �e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// ���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3					m_pos;			// �ʒu
	D3DXVECTOR3					m_rot;			// ����
	D3DXVECTOR3					m_scale;		// �傫��
	D3DXVECTOR3					m_move;			// �ړ���
	D3DXCOLOR					m_color;		// �F
	bool						m_bUninit;		// �j��
};
#endif //!_POLYGON_H_