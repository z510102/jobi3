#ifndef _BULLET_H_
#define _BULLET_H_
#include "billboard.h"

#define BULLET_SCALE_X 50.0f
#define BULLET_SCALE_Y 50.0f
#define BULLET_SCALE_Z 50.0f

class CModel;

class CBullet : public CBillboard
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_WHITE,
		TYPE_RED,
		TYPE_BLUE,
		TYPE_YELLOW,
		TYPE_MAX
	} TYPE_SMOKECOLOR;

	CBullet(int nPriority = CScene::PRIORITY_BULLET);
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life, int nType);		//�G�t�F�N�g�̐���
	bool Collision(CBullet *pBullet, D3DXVECTOR3 *pPos);		// �ʏ�̓����蔻��


private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;  //�ړ�
	D3DXVECTOR3 m_scale;  //�ړ�
	D3DXVECTOR3	m_rot;  // ����
	CModel	*m_pModel;
	int m_nType;
	int m_nLife;		//����
	D3DCOLORVALUE m_colval;
	bool m_bUninit;		//�폜�t���O
	TYPE_SMOKECOLOR m_smokecol;
	int m_nFrameSmoke = 0;  //���̃t���[��
};
#endif
