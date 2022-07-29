//=============================================================================
//
// 3D�|���S���N���X [scene3D.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 3D ���_�t�H�[�}�b�g
#define NUM_VERTEX		4					// ���_��
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; // ���_���W
	D3DXVECTOR3 nor; // �@���x�N�g��
	D3DCOLOR    col; // ���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
//	3D�|���S���N���X
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 3);		// �R���X�g���N�^
	~CScene3D();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nType);		// 2D�|���S���̐���

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; } // �e�N�X�`���̊��蓖��
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// �ʒu��ݒ�
	D3DXVECTOR3 GetPosition(void);								// �ʒu���擾

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;					// �ʒu
	D3DXVECTOR3				m_rot;					// ����
	D3DXVECTOR3				m_scale;				// �T�C�Y
	int m_nType;

};
#endif //!_SCENE3D_H_