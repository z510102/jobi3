//=============================================================================
//
// ���C�g�N���X [light.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "light.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{
	// �����o�ϐ��̃N���A
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLight::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

#if 1
	// ���C�g���N���A����
	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̕�����ݒ�
		// ���C�g�̊g�U���̐ݒ�
		m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		D3DXVec3Normalize(&m_vecDir, &m_vecDir);		// ���K������
		m_light[0].Direction = m_vecDir;

		// ���C�g�̊g�U���̐ݒ�
		m_vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
		D3DXVec3Normalize(&m_vecDir, &m_vecDir);		// ���K������
		m_light[1].Direction = m_vecDir;

		// ���C�g�̊g�U���̐ݒ�
		m_vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
		D3DXVec3Normalize(&m_vecDir, &m_vecDir);		// ���K������
		m_light[2].Direction = m_vecDir;

		// ���C�g��ݒ�
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
#endif
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CLight::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void CLight::Update(void)
{
}
//=============================================================================
// ��������
//=============================================================================
CLight *CLight::Create(void)
{
	CLight *pLight;
	pLight = new CLight;

	if (pLight != NULL)
	{
		pLight->Init();
		//pLight->m_type = type;
		//pLight->m_vecDirection = vecDir;
		//pLight->m_color = color;
	}

	return pLight;
}
