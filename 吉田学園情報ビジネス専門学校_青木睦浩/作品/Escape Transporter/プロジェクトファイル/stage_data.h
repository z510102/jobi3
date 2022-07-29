//=============================================================================
//
// ステージデータクラス [stage_data.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _STAGE_DATA_H_
#define _STAGE_DATA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "stage.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CModel;

//*****************************************************************************
//	ステージデータクラス
//*****************************************************************************
class CStageData : public CScene
{
public:

	CStageData(int nPriority = PRIORITY_MODEL);	// コンストラクタ
	~CStageData();					// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CStageData *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int nIndex);		// 生成処理
	static void LoadXFile(const char *pModelFileName, int nIndex);					// Stageクラスで読み込みんだ情報を保存
	void SetModel(int nIndex);						// モデルの番号をポインタに保存
	void SetPosition(D3DXVECTOR3 pos);				// 生成したモデルの位置を保存
	D3DXVECTOR3 GetPosition(void);
	void SetRotation(D3DXVECTOR3 rot);				// 生成したモデルの向きを保存
	D3DXVECTOR3 GetRotation(void);
	void SetScale(D3DXVECTOR3 scale);
	D3DXVECTOR3 GetScale(void);
	CModel *GetModel(int nIndex) { return m_apModel[nIndex]; }//モデルの情報を取得
	CModel *GetModel(void) { return m_pModel; }//モデルの情報を取得

private:
	static CModel				*m_apModel[MODEL_MAX];	// 読み込んだモデルを保存

	CModel						*m_pModel;				// 保存したポインタのモデル情報を設定
	D3DXVECTOR3					m_pos;			// 位置
	D3DXVECTOR3					m_rot;			// 向き
	D3DXVECTOR3					m_scale;		// 大きさ

};
#endif //!_STAGE_DATA_H_