//=============================================================================
//
// �J�����N���X [camea.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include "game.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	memset(&m_pos, 0, sizeof(m_pos));
	memset(&m_posV, 0, sizeof(m_posV));
	memset(&m_posR, 0, sizeof(m_posR));
	memset(&m_vecU, 0, sizeof(m_vecU));
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, VIEW_Y, -VIEW_Z);	// ���_
	m_posR = D3DXVECTOR3(0.0f, GAZE_Y, -GAZE_Z);	// �����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// �@���x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �J�����̌���

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{

	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 posR = pPlayer->GetMove();
		D3DXVECTOR3 posV = pPlayer->GetMove();
		m_posR.x += posR.x;
		m_posV.x += posV.x;
		m_posR.z += posR.z;
		m_posV.z += posV.z;
	}
	//m_posV.y = VIEW_Y;	// ���_
	//m_posR.y = GAZE_Y;	// �����_

	//=============================================
	//				�J�����̈ړ�����
	//=============================================
	if (CManager::GetInputKeyboard()->GetPress(DIK_UP) == true)
	{// �O�ړ�
		m_posV.x += sinf(m_rot.y) * (4.0f);
		m_posV.z += cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);	// sinf X���̌���
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);	// cosf Z���̌���
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_DOWN) == true)
	{// ��ړ�
		m_posV.x -= sinf(m_rot.y) * (4.0f);
		m_posV.z -= cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_LEFT) == true)
	{// ���ړ�
		m_posV.x -= cosf(m_rot.y) * (4.0f);
		m_posV.z += sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_RIGHT) == true)
	{// �E�ړ�
		m_posV.x += cosf(m_rot.y) * (4.0f);
		m_posV.z -= sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_U) == true)
	{// ���_�ƒ����_�̋���
		m_posV.z += 4.0f;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_M) == true)
	{// ���_�ƒ����_�̋���
		m_posV.z -= 4.0f;
	}

	//=============================================
	//					���_����
	//=============================================
#if 0
	if (CManager::GetInputKeyboard()->GetPress(DIK_Y) == true || CManager::GetMouse()->ButtonUp(VK_LBUTTON) == true)
	{// ��ړ�
		m_posV.y += 4.0f;

		if (m_posV.y >= 900.0f)
		{
			m_posV.y = 900.0f;
		}

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_N) == true)
	{// ���ړ�
		m_posV.y -= 4.0f;

		if (m_posV.y <= 200.0f)
		{
			m_posV.y = 200.0f;
		}

	}
#endif
	else if (CManager::GetInputKeyboard()->GetPress(DIK_C) == true)
	{// ������
		if (m_rot.y < D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ��ɒl��3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_Z) == true)
	{// �E����
		if (m_rot.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��ɒl��-3.14f�ɂ���
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}

	//=============================================
	//					�����_����
	//=============================================
	if (CManager::GetInputKeyboard()->GetPress(DIK_T) == true)
	{// ��ړ�
		m_posR.y += 2.0f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_B) == true)
	{// ���ړ�
		m_posR.y -= 2.0f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_Q) == true)
	{// ������
		if (m_rot.y < D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ�3.14f�ɂ���
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_E) == true)
	{// �E����
		if (m_rot.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ�-3.14f�ɂ���
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}

}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						// ��p 360�x
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// ��ʔ䗦
		10.0f,										// ��O�̈ʒu
		40000.0f);									// ���̈ʒu	���l�ύX�ŕ`��͈͂��L������

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
// ��������
//=============================================================================
CCamera *CCamera::Create(void)
{
	CCamera *pCamera;
	pCamera = new CCamera;

	if (pCamera != NULL)
	{
		pCamera->Init();
	}

	return pCamera;
}

//D3DXVECTOR3 CCamera::GetPositionR(void)
//{
//	return D3DXVECTOR3();
//}
//
//D3DXVECTOR3 CCamera::GetPositionV(void)
//{
//	return D3DXVECTOR3();
//}
//
//D3DXVECTOR3 CCamera::GetVectorU(void)
//{
//	return D3DXVECTOR3();
//}
//
//D3DXVECTOR3 CCamera::GetMove(void)
//{
//	return D3DXVECTOR3();
//}


