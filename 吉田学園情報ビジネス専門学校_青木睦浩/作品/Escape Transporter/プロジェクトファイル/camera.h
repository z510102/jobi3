//=============================================================================
//
// カメラクラス [camera.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define VIEW_Y (900)	// 視点の高さ
#define VIEW_Z (500)	// 視点の奥行
#define GAZE_Y (100)	// 注視点の高さ
#define GAZE_Z (0)	// 注視点の奥行
//*****************************************************************************
//	カメラクラス
//*****************************************************************************
class CCamera
{
public:
	CCamera();			// コンストラクタ
	~CCamera();			// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void SetCamera(void);	// 設定処理

	static CCamera *Create(void);	// 生成処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPositionV(D3DXVECTOR3 posV) { m_posV = posV; }	// 視点を設定
	void SetPositionR(D3DXVECTOR3 posR) { m_posR = posR; }	// 注視点を設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// 向きを設定

	D3DXVECTOR3 GetPosR(void) { return m_posR; }				// 現在の視点を取得
	D3DXVECTOR3 GetPosV(void) { return m_posV; }				// 現在の注視点を取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }				// 向きを取得
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posV;					//現在の視点
	D3DXVECTOR3 m_posR;					//現在の注視点
	D3DXVECTOR3 m_vecU;					//法線ベクトル
	D3DXVECTOR3 m_rot;					//カメラの向き
										//D3DXVECTOR3 m_posVDest;			//目的の視点
										//D3DXVECTOR3 m_posRDest;			//目的の注視点
										//D3DXVECTOR3 m_move;				//カメラの移動量

	D3DXMATRIX	m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX	m_mtxView;			//ビューマトリックス
	D3DVIEWPORT9 m_viewport;		//ビューポート
};
#endif //!_CAMERA_H_