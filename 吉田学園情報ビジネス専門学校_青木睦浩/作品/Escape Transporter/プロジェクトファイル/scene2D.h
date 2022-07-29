//=============================================================================
//
// 2D�|���S���N���X [scene2D.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "texture.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// ���_�t�H�[�}�b�g
#define NUM_VERTEX		4											// ���_��
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float		rhw; //1.0f�ŌŒ�
	D3DCOLOR    col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
//	2D�|���S���N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);			// �R���X�g���N�^
	~CScene2D();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nType);		// 2D�|���S���̐���

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; } // �e�N�X�`���̊��蓖��
	void SetVtxTexture(int nPatteernAnimU, float fAnimU, int nPatteernAnimV, float fAnimV, float fTexU, float fTexV);	// �e�N�X�`�����W�̐ݒ�
	D3DXVECTOR3 GetPosition(void);								// �ʒu���擾
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// �ʒu��ݒ�
	void SetTexPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float fPos);		// �ʒu��ݒ�
	D3DXVECTOR3 GetSize(void);									// �T�C�Y���擾
	void SetSize(D3DXVECTOR3 scale);							// �T�C�Y��ݒ�
	void SetColor(int nColr, int nColg, int nColb, int nCola);	// ���_�J���[�̐ݒ�
	void SetColor(D3DXCOLOR col);								// ���_�J���[�̐ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �ʒu
	D3DXVECTOR3				m_scale;				// �T�C�Y
	D3DXCOLOR				m_color;				// ���_�J���[
	int						m_nColor_r;				// ���_�J���[R
	int						m_nColor_g;				// ���_�J���[G
	int						m_nColor_b;				// ���_�J���[B
	int						m_nColor_a;				// ���_�J���[A

	int m_nNumTexture;
	//TEXTURE_TYPE m_type;
	int m_nType;
};
#endif //!_SCENE2D_H_