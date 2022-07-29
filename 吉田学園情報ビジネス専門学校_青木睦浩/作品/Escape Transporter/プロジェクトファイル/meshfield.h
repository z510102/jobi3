//
// ���b�V���t�B�[���h�N���X [meshfield.h]
// Author : �؁@�r�_
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene3D.h"

//=============================================================================
// �}�N����`
//=============================================================================

//*****************************************************************************
//	���b�V���t�B�[���h�N���X
//*****************************************************************************
class CMeshField : public CScene3D
{
public:
	CMeshField(int nPriority = PRIORITY_MODEL);																				// �R���X�g���N�^
	~CMeshField();																											// �f�X�g���N�^

	HRESULT Init(void);																										// ����������
	void Uninit(void);																										// �I������
	void Update(void);																										// �X�V����
	void Draw(void);																										// �`�揈��

	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nType);												// ��������
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }												// �e�N�X�`���̊��蓖��

	D3DXVECTOR3 GetPosition(void);																							// �ʒu�̎擾
	D3DXVECTOR3 GetScale(void);																								// �傫���̎擾
	bool Collision(CMeshField *pMeshField, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float& BackPos);	// �����蔻��

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;																					// ���b�V���t�B�[���h�̒��_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff;																					// ���b�V���t�B�[���h�̃C���f�b�N�X�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture;																					// ���L�e�N�X�`���̃|�C���^
	D3DXMATRIX					m_mtxWorld;																					//	���[���h�}�g���b�N�X
	D3DXVECTOR3					m_move;																						// �ړ���
	D3DXVECTOR3					m_pos;																						// �ʒu
	D3DXVECTOR3					m_rot;																						// ����
	D3DXVECTOR3					m_scale;																					// �傫��
	D3DXCOLOR					m_color;																					// �F
	bool						m_bUninit;																					// �j��
	int m_nType;
};
#endif //!_MESHFIELD_H_