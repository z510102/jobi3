//=============================================================================
//
// 2D�|���S������ [scene2D.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)  //���_�t�H�[�}�b�g

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;  // ���_���W
	float       rhw;  // 1.0f�ŌŒ�
	D3DCOLOR    col;  // ���_�J���[
	D3DXVECTOR2 tex;  // �e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// 2D�|���S���N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);																							// �f�t�H���g�R���X�g���N�^
	~CScene2D();																											// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);																							// ����������
	void Uninit(void);																										// �I������
	void Update(void);																										// �X�V����
	void Draw(void);																										// �`�揈��

	static CScene2D *Create(D3DXVECTOR3 pos);																				// ��������

	void SetPosition(D3DXVECTOR3 pos);																						// �ݒ菈��
	D3DXVECTOR3 GetPosition(void);																							// �擾����
	void SetSize(float fWidth, float fHeight);																				// �T�C�Y�̐ݒ�
	D3DXVECTOR2 GetSize(void);																								// �T�C�Y�̎擾
	void SetColor(D3DXCOLOR col);																							// ���_�J���[�̐ݒ�
	void SetColor(int nColR, int nColG, int nColB, int nColA);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);																			// �e�N�X�`�������蓖�Ă�
	void SetVertexTexture(int nPatternAnimU, float fAnimU, int nPatternAnimV, float fAnimV, float fTexU, float fTexV);		// �e�N�X�`�����W�̐ݒ�

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9      m_pTexture;																						// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;																						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3             m_pos;																							// �|���S���̈ʒu
	D3DXVECTOR2             m_size;																							// �|���S���̃T�C�Y
	float m_fTexU;																											// �e�N�X�`����U���W
	float m_fTexV;																											// �e�N�X�`����V���W
	D3DXCOLOR m_color;																										// ���_�J���[
	int m_nColorR;																											// �J���[�i�ԁj
	int m_nColorG;																											// �J���[�i�΁j
	int m_nColorB;																											// �J���[�i�j
	int m_nColorA;																											// �J���[�i�����x�j
};

#endif // !_SCENE2D_H_