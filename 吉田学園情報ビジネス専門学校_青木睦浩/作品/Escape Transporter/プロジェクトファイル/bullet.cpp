#include "bullet.h"
#include "camera.h"
#include "player.h"
#include "game.h"

#define RAND_Y (float(rand() % 3)+ 1)
#define CYCLE (float(rand() % 324) / 90.0f - float(rand() % 324) / 90.0f)

CBullet::CBullet(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

CBullet::~CBullet()
{

}

HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life)
{
	CBillboard::Init();
	m_pos = pos;
	m_move = move;
	m_nLife = life;
	m_scale = scale;
	CBillboard::SetPosition(pos, scale);
	m_bUninit = false;

	return S_OK;
}

void CBullet::Uninit(void)
{
	CBillboard::Uninit();
}

void CBullet::Update(void)
{
	//m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	//����
	D3DXVECTOR3 pos = CBillboard::GetPosition();
	pos += m_move;
	//���̑����X
	CBillboard::SetPosition(pos, m_scale);
	CBillboard::Update();

	if (m_bUninit == true)
	{
		Uninit();
	}
}

void CBullet::Draw(void)
{
	CBillboard::Draw();
}

CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life, int nType)
{
	CBullet *pEffectSmoke = NULL;
	if (pEffectSmoke == NULL)
	{
		pEffectSmoke = new CBullet(CScene::PRIORITY_BULLET);
		if (pEffectSmoke != NULL)
		{
			pEffectSmoke->Init(pos, scale, move, life);
			pEffectSmoke->BindTexture(CManager::GetTexture()->SetTextureType(nType));
		}
	}
	return pEffectSmoke;

}

bool CBullet::Collision(CBullet *pBullet, D3DXVECTOR3 * pPos)
{
	////���f�������擾
	//CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		CPlayer *pPlayer = CManager::GetGame()->GetPlayer();
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();  //�v���C���[
		D3DXVECTOR3 pos = m_pos;  //�����i�e�j
		D3DXVECTOR3 Vec = PlayerPos - pos;
		float VecPos = sqrtf(Vec.x * Vec.x) + (Vec.z * Vec.z);
		//�v���C���[���e�̍�����艺��������
		if (PlayerPos.y <= m_pos.y+ m_scale.y)
		{
			if (VecPos <= m_scale.x + 25.0f)
			{
				//�v���C���[�ɓ����������Ƃ�Ԃ�
				pPlayer->SetbHitBullet(true);
				m_bUninit = true;
			}

		}
		
	}

	return false;
}


