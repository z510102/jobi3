//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "game.h"
#include "player.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	// �����o�ϐ��̃N���A
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pFont = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�o�C�X�̐���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O���s��Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ� (��Ԑݒ�)
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ� (��Ԑݒ�)

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// 2�Ԗڂ̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	// �S�ẴI�u�W�F�N�g�̍X�V����
	CScene::UpdateAll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �S�ẴI�u�W�F�N�g�̕`�揈��
		CScene::DrawAll();

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
		DrawTXT();
#endif
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
// �A���t�@�u�����f�B���O(�A���t�@�e�X�g)�̐ݒ�
//=============================================================================
void CRenderer::SetAddSynthesis(bool bUse)
{
	if (bUse == true)
	{
		// ���u�����f�B���O�����Z�����ɐݒ�
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	}
	else
	{
		// ���u�����f�B���O��ʏ퍇���ɐݒ�
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	}
}
//=============================================================================
// ���Z�����̐ݒ�
//=============================================================================
void CRenderer::SetSubSynthesis(bool bUse)
{
	if (bUse == true)
	{
		// ���u�����f�B���O�����Z�����ɐݒ�
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else
	{
		// ���u�����f�B���O��ʏ퍇���ɐݒ�
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

}
//=============================================================================
// Z�e�X�g��ݒ�
//=============================================================================
void CRenderer::SetZTest(bool bUse)
{
	if (bUse == true)
	{
		// Z�e�X�g��K�p
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	}
	else
	{
		// �W���ɖ߂�
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

}
#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	int nCountFPS;

	nCountFPS = GetFPS();	// FPS���擾

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", nCountFPS);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
#ifdef _DEBUG
//=============================================================================
//�e�L�X�g�̕`��
//=============================================================================
void CRenderer::DrawTXT(void)
{

	RECT rect = { 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT };	//	�\���͈�
	char aStr[1024];	//	������̊i�[

	CCamera *pCamera = CManager::GetCamera();	//	�J�����̏��擾
	D3DXVECTOR3 posR = pCamera->GetPosR();
	D3DXVECTOR3 posV = pCamera->GetPosV();


	int nNum = sprintf(&aStr[0], "[�J�����̎��_�@�@�@�@�@�F( %.2f : %.2f : %.2f )]\n", posV.x, posV.y, posV.z); //	�\��������������̏��
	nNum += sprintf(&aStr[nNum], "[�J�����̒����_�@�@�@�@�F( %.2f : %.2f : %.2f )]\n", posR.x, posR.y, posR.z);
	//nNum += sprintf(&aStr[nNum], "[�ړ���		 �@�@�@�@�F( %.2f : %.2f : %.2f )]\n", move.x, move.y, move.z);

	//nNum += sprintf(&aStr[nNum], "[���_�ƒ����_�̋����@�@�F( %.2f )]\n\n", pCamera->posV.z);

	//nNum += sprintf(&aStr[nNum], "[���f���̍ő�l�@�@�F( %.2f : %.2f : %.2f )]\n", pPlayer->vtxMaxPlayer.x, pPlayer->vtxMaxPlayer.y, pPlayer->vtxMaxPlayer.z);
	//nNum += sprintf(&aStr[nNum], "[���f���̍ŏ��l�@�@�F( %.2f : %.2f : %.2f )]\n", pPlayer->vtxMinPlayer.x, pPlayer->vtxMinPlayer.y, pPlayer->vtxMinPlayer.z);

	m_pFont->DrawText(NULL, aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));	//	�e�L�X�g�̕`��
}
#endif

