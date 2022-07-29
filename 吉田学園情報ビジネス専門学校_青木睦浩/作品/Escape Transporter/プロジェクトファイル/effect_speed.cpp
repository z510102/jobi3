#include "effect_speed.h"
#include "camera.h"

#define RAND_Y (float(rand() % 3)+ 1)
#define CYCLE (float(rand() % 324) / 90.0f - float(rand() % 324) / 90.0f)

CEffectSpeed::CEffectSpeed(int nPriority) : CBillEffect(nPriority)
{
	
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

CEffectSpeed::~CEffectSpeed()
{

}

HRESULT CEffectSpeed::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life)
{
	CBillEffect::Init();
	m_move = move;
	m_nLife = life;
	m_scale = scale;


	CBillEffect::SetPosition(pos, scale);
	m_bUninit = false;

	return S_OK;
}

void CEffectSpeed::Uninit(void)
{
	CBillEffect::Uninit();
}

void CEffectSpeed::Update(void)
{
	m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	m_colval.r = 255.0f;
	m_colval.g = 255.0f;
	m_colval.b = 0.0f;
	m_colval.a = 255.0f;



	//“®‚«
	D3DXVECTOR3 pos = CBillEffect::GetPosition();
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

void CEffectSpeed::Draw(void)
{
	CBillEffect::Draw();
}

CEffectSpeed * CEffectSpeed::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life, int nType)
{
	CEffectSpeed *pEffectSpeed = NULL;
	if (pEffectSpeed == NULL)
	{
		pEffectSpeed = new CEffectSpeed;
		if (pEffectSpeed != NULL)
		{
			pEffectSpeed->Init(pos, scale, move, life);
			pEffectSpeed->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		}
	}
	return pEffectSpeed;

}
