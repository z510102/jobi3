//=============================================================================
//
// 2D�|���S���N���X [billboard.h]
// Author : �y���@��P
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

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

//*****************************************************************************
//	2D�|���S���N���X
//*****************************************************************************
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = PRIORITY_EFFECT);			// �R���X�g���N�^
	~CBillboard();		// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int nType);		// 2D�|���S���̐���
																									//LPDIRECT3DTEXTURE9 SetTextureType(int nType);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	D3DXVECTOR3 GetPosition(void);
	void SetColVal(D3DCOLORVALUE colval);


	//void SetPosition(D3DXVECTOR3 pos,D3DXVECTOR3 scale);
	//D3DXVECTOR3 GetPosition(void);
	//void SetCol(D3DCOLORVALUE colval);


private:
	// ���L�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �ʒu
	D3DXVECTOR3				m_scale;				// �T�C�Y
	D3DXMATRIX				m_mtxWorld;
	D3DXCOLOR				m_color;				// ���_�J���[
	D3DCOLORVALUE		    m_colval;
	int m_nType;
};
#endif //!_SCENE2D_H_
