//=============================================================================
//
// �J�����N���X [camera.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define VIEW_Y (900)	// ���_�̍���
#define VIEW_Z (500)	// ���_�̉��s
#define GAZE_Y (100)	// �����_�̍���
#define GAZE_Z (0)	// �����_�̉��s
//*****************************************************************************
//	�J�����N���X
//*****************************************************************************
class CCamera
{
public:
	CCamera();			// �R���X�g���N�^
	~CCamera();			// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void SetCamera(void);	// �ݒ菈��

	static CCamera *Create(void);	// ��������
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPositionV(D3DXVECTOR3 posV) { m_posV = posV; }	// ���_��ݒ�
	void SetPositionR(D3DXVECTOR3 posR) { m_posR = posR; }	// �����_��ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// ������ݒ�

	D3DXVECTOR3 GetPosR(void) { return m_posR; }				// ���݂̎��_���擾
	D3DXVECTOR3 GetPosV(void) { return m_posV; }				// ���݂̒����_���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// �������擾
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posV;					//���݂̎��_
	D3DXVECTOR3 m_posR;					//���݂̒����_
	D3DXVECTOR3 m_vecU;					//�@���x�N�g��
	D3DXVECTOR3 m_rot;					//�J�����̌���
										//D3DXVECTOR3 m_posVDest;			//�ړI�̎��_
										//D3DXVECTOR3 m_posRDest;			//�ړI�̒����_
										//D3DXVECTOR3 m_move;				//�J�����̈ړ���

	D3DXMATRIX	m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;			//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;		//�r���[�|�[�g
};
#endif //!_CAMERA_H_