#include "effect_dust.h"
#include "camera.h"

#define RAND_Y (float(rand() % 3)+ 1)
#define CYCLE (float(10+rand() % 324) / 50.0f - float(10+rand() % 324) / 50.0f)


CEffectDust::CEffectDust(int nPriority) : CBillEffect(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

CEffectDust::~CEffectDust()
{

}

HRESULT CEffectDust::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale,D3DXVECTOR3 move, int life)
{
	CBillEffect::Init();
	m_move = move;
	m_nLife = life;
	m_scale = scale;
	m_Fastpos = pos;
	m_Vec = 0;
	CBillEffect::SetPosition(pos, scale);
	m_bUninit = false;

	return S_OK;
}

void CEffectDust::Uninit(void)
{
	CBillEffect::Uninit();
}

void CEffectDust::Update(void)
{
	//êFïœçX
	m_colval.r = 0.0f;
	m_colval.g = 255.0f;
	m_colval.b = 255.0f;
	m_colval.a = 255.0f;

	m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	//ìÆÇ´
	D3DXVECTOR3 pos = CBillEffect::GetPosition();
	D3DXVECTOR3 Vecpos = pos - m_Fastpos;


	pos += m_move;

	m_Vec = sqrtf(Vecpos.x * Vecpos.x + Vecpos.y * Vecpos.y + Vecpos.z * Vecpos.z);

	if (m_Vec >= 75.0f)
	{
		m_bUninit = true;
	}
	//ÇªÇÃëºèîÅX
	CBillEffect::SetPosition(pos, m_scale);
	CBillEffect::SetColVal(m_colval);
	CBillEffect::Update();

	if (m_bUninit == true)
	{
		Uninit();
	}
}

void CEffectDust::Draw(void)
{
	CBillEffect::Draw();
}

CEffectDust * CEffectDust::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life, int nType)
{
	CEffectDust *pEffectDust = NULL;
	if (pEffectDust == NULL)
	{
		pEffectDust = new CEffectDust;
		if (pEffectDust != NULL)
		{
			pEffectDust->Init(pos, scale, move, life);
			pEffectDust->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		}
	}
	return pEffectDust;

}

