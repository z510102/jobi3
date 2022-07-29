#include "billeffect.h"

class CEffectStr : public CBillEffect
{
public:
	CEffectStr(int nPriority = 3);
	~CEffectStr();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, D3DXVECTOR3 move, int life,D3DCOLORVALUE colval);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	static CEffectStr *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, D3DXVECTOR3 move, int life, int nType, D3DCOLORVALUE colval);		//エフェクトの生成
	
private:
	D3DXVECTOR3 m_move;  //移動
	D3DXVECTOR3 m_scale;  //移動
	int m_nType;
	int m_nLife;		//寿命
	D3DCOLORVALUE m_colval;
	bool m_bUninit;		//削除フラグ

};