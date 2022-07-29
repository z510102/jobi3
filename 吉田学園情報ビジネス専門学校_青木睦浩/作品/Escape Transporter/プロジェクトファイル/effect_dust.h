#include "billeffect.h"

class CEffectDust : public CBillEffect
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

	CEffectDust(int nPriority = 3);
	~CEffectDust();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CEffectDust *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int life, int nType);		//�G�t�F�N�g�̐���

private:
	D3DXVECTOR3 m_move;  //�ړ�
	D3DXVECTOR3 m_scale;  //�ړ�
	D3DXVECTOR3	m_rot;  // ����
	D3DXVECTOR3 m_Fastpos;	//�x�N�g����������悤

	float m_Vec;
	int m_nType;
	int m_nLife;		//����
	D3DCOLORVALUE m_colval;
	bool m_bUninit;		//�폜�t���O
	TYPE_SMOKECOLOR m_smokecol;
	int m_nFrameSmoke = 0;  //���̃t���[��
};
