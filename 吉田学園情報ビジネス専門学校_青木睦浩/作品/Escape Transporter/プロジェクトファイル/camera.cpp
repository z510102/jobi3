//=============================================================================
//
// カメラクラス [camea.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include "game.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	memset(&m_pos, 0, sizeof(m_pos));
	memset(&m_posV, 0, sizeof(m_posV));
	memset(&m_posR, 0, sizeof(m_posR));
	memset(&m_vecU, 0, sizeof(m_vecU));
}
//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, VIEW_Y, -VIEW_Z);	// 視点
	m_posR = D3DXVECTOR3(0.0f, GAZE_Y, -GAZE_Z);	// 注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// 法線ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// カメラの向き

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}
//=============================================================================
// 更新処理
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
	//m_posV.y = VIEW_Y;	// 視点
	//m_posR.y = GAZE_Y;	// 注視点

	//=============================================
	//				カメラの移動処理
	//=============================================
	if (CManager::GetInputKeyboard()->GetPress(DIK_UP) == true)
	{// 前移動
		m_posV.x += sinf(m_rot.y) * (4.0f);
		m_posV.z += cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);	// sinf X軸の決定
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);	// cosf Z軸の決定
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_DOWN) == true)
	{// 後移動
		m_posV.x -= sinf(m_rot.y) * (4.0f);
		m_posV.z -= cosf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_LEFT) == true)
	{// 左移動
		m_posV.x -= cosf(m_rot.y) * (4.0f);
		m_posV.z += sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_RIGHT) == true)
	{// 右移動
		m_posV.x += cosf(m_rot.y) * (4.0f);
		m_posV.z -= sinf(m_rot.y) * (4.0f);
		m_posR.x = m_posV.x + sinf(m_rot.y) * (VIEW_Z);
		m_posR.z = m_posV.z + cosf(m_rot.y) * (VIEW_Z);
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_U) == true)
	{// 視点と注視点の距離
		m_posV.z += 4.0f;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_M) == true)
	{// 視点と注視点の距離
		m_posV.z -= 4.0f;
	}

	//=============================================
	//					視点操作
	//=============================================
#if 0
	if (CManager::GetInputKeyboard()->GetPress(DIK_Y) == true || CManager::GetMouse()->ButtonUp(VK_LBUTTON) == true)
	{// 上移動
		m_posV.y += 4.0f;

		if (m_posV.y >= 900.0f)
		{
			m_posV.y = 900.0f;
		}

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_N) == true)
	{// 下移動
		m_posV.y -= 4.0f;

		if (m_posV.y <= 200.0f)
		{
			m_posV.y = 200.0f;
		}

	}
#endif
	else if (CManager::GetInputKeyboard()->GetPress(DIK_C) == true)
	{// 左旋回
		if (m_rot.y < D3DX_PI)
		{// -3.14fより小さくなったときに値を3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_Z) == true)
	{// 右旋回
		if (m_rot.y > D3DX_PI)
		{// 3.14fより大きくなったときに値を-3.14fにする
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * VIEW_Z;
		m_posV.z = m_posR.z - cosf(m_rot.y) * VIEW_Z;
	}

	//=============================================
	//					注視点操作
	//=============================================
	if (CManager::GetInputKeyboard()->GetPress(DIK_T) == true)
	{// 上移動
		m_posR.y += 2.0f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_B) == true)
	{// 下移動
		m_posR.y -= 2.0f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_Q) == true)
	{// 左旋回
		if (m_rot.y < D3DX_PI)
		{// -3.14fより小さくなったとき3.14fにする
			m_rot.y += D3DX_PI * 2.0f;
		}
		m_rot.y -= 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_E) == true)
	{// 右旋回
		if (m_rot.y > D3DX_PI)
		{// 3.14fより大きくなったとき-3.14fにする
			m_rot.y -= D3DX_PI * 2.0f;
		}
		m_rot.y += 0.03f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * VIEW_Z;
		m_posR.z = m_posV.z + cosf(m_rot.y) * VIEW_Z;
	}

}
//=============================================================================
// 設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						// 画角 360度
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// 画面比率
		10.0f,										// 手前の位置
		40000.0f);									// 奥の位置	数値変更で描画範囲を広くする

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
// 生成処理
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


