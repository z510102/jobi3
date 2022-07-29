#include "effect_straight.h"

CEffectStr::CEffectStr(int nPriority) : CBillEffect(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
}

CEffectStr::~CEffectStr()
{

}

HRESULT CEffectStr::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, D3DXVECTOR3 move, int life, D3DCOLORVALUE colval)
{
	CBillEffect::Init();
	m_move = move;
	m_nLife = life;
	m_scale = scale;
	m_colval = colval;
	CBillEffect::SetPosition(pos,scale);
	m_bUninit = false;

	return S_OK;
}

void CEffectStr::Uninit(void)
{
	CBillEffect::Uninit();
}

void CEffectStr::Update(void)
{
	m_colval.r = 0.0f;
	m_colval.g = 255.0f;
	m_colval.b = 255.0f;
	m_colval.a = 255.0f;


	m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	D3DXVECTOR3 pos = CBillEffect::GetPosition();
	pos += m_move;

	CBillEffect::SetPosition(pos, m_scale);
	CBillEffect::SetColVal(m_colval);
	CBillEffect::Update();

	if (m_bUninit == true)
	{
		Uninit();
	}
}

void CEffectStr::Draw(void)
{
	CBillEffect::Draw();
}

CEffectStr * CEffectStr::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, D3DXVECTOR3 move, int life, int nType, D3DCOLORVALUE colval)
{
	CEffectStr *pEffectStr = NULL;
	if (pEffectStr == NULL)
	{
		pEffectStr = new CEffectStr;
		if (pEffectStr != NULL)
		{
			pEffectStr->Init(pos,scale,rot,move, life,colval);
			pEffectStr->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		}
	}
	return pEffectStr;

}

