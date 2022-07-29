#include "effect_smoke.h"
#include "camera.h"

#define RAND_Y (float(rand() % 3)+ 1)
#define CYCLE (float(rand() % 324) / 90.0f - float(rand() % 324) / 90.0f)

CEffectSmoke::CEffectSmoke(int nPriority) : CBillEffect(nPriority)
{

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

CEffectSmoke::~CEffectSmoke()
{

}

HRESULT CEffectSmoke::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life )
{
	CBillEffect::Init();
	m_move = move;
	m_nLife = life;
	m_scale = scale;


	CBillEffect::SetPosition(pos, scale);
	m_bUninit = false;

	return S_OK;
}

void CEffectSmoke::Uninit(void)
{
	CBillEffect::Uninit();
}

void CEffectSmoke::Update(void)
{
	m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	m_colval.r = 0.0f;
	m_colval.g = 255.0f;
	m_colval.b = 255.0f;
	m_colval.a = 255.0f;

	//“®‚«
	D3DXVECTOR3 pos = CBillEffect::GetPosition();
	m_move = D3DXVECTOR3(CYCLE * 1.0f, RAND_Y, CYCLE * 1.0f);
	//m_move = D3DXVECTOR3(0.5, 0.0f, 1);
	pos += m_move;
	//‚»‚Ì‘¼”X
	CBillEffect::SetPosition(pos, m_scale);
	CBillEffect::SetColVal(m_colval);
	CBillEffect::Update();

	if (m_bUninit == true)
	{
		Uninit();
	}
}

void CEffectSmoke::Draw(void)
{
	CBillEffect::Draw();
}

CEffectSmoke * CEffectSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life, int nType)
{
	CEffectSmoke *pEffectSmoke = NULL;
	if (pEffectSmoke == NULL)
	{
		pEffectSmoke = new CEffectSmoke;
		if (pEffectSmoke != NULL)
		{
			pEffectSmoke->Init(pos, scale, move, life);
			pEffectSmoke->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		}
	}
	return pEffectSmoke;

}

