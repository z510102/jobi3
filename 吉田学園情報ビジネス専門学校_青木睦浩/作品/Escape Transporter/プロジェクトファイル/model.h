//=============================================================================
//
// ���f���N���X [model.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//	�v���C���[�N���X
//*****************************************************************************
class CModel
{
public:
	CModel();	// �R���X�g���N�^
	~CModel();					// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	void DrawObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);		// �X�e�[�W�Z�b�g�̃I�u�W�F�N�g�`�揈��

	static CModel *Create(const char *pModelFileName);	// ��������

	void SetParent(CModel *pModel);						// �e���f����ݒ�
	D3DXMATRIX GetMtxWorld(void);						// ���[���h�}�g���b�N�X���擾
	void LoadXFile(const char *pModelFileName);			// X�t�@�C���ǂݍ���
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// �p�[�c�̈ʒu��ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// �p�[�c�̈ʒu���擾
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }			// �p�[�c�̌�����ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_pos; }			// �p�[�c�̌������擾
	D3DXVECTOR3 GetMove(void);			// �ړ��ʂ��擾
	D3DXVECTOR3 GetScale(void);


private:
	LPDIRECT3DTEXTURE9	m_pTexture[5];	// �e�N�X�`���̃|�C���^
	LPD3DXMESH					m_pMesh;		// ���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER				m_pBuffMat;		// �}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD						m_nNumMat;		// �}�g���b�N�X��
	CModel						*m_pParent;		// �e���f���ւ̃|�C���^
	int							m_nIdxParent;	// �e���f���̃C���f�b�N�X
	D3DXMATRIX					m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;			// �ʒu
	D3DXVECTOR3					m_rot;			// ����
	D3DXVECTOR3					m_scale;		// �傫���̔{��
	D3DXVECTOR3					m_size;			// �傫��
	D3DXVECTOR3					m_move;			// �ړ���
	D3DXVECTOR3					m_vtxMin;		// ���_�̍ŏ��l
	D3DXVECTOR3					m_vtxMax;		// ���_�̍ő�l
};
#endif //!_MODEL_H_