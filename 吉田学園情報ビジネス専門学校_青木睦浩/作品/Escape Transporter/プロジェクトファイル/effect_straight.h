#include "billeffect.h"

class CEffectStr : public CBillEffect
{
public:
	CEffectStr(int nPriority = 3);
	~CEffectStr();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, D3DXVECTOR3 move, int life,D3DCOLORVALUE colval);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CEffectStr *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, D3DXVECTOR3 move, int life, int nType, D3DCOLORVALUE colval);		//�G�t�F�N�g�̐���
	
private:
	D3DXVECTOR3 m_move;  //�ړ�
	D3DXVECTOR3 m_scale;  //�ړ�
	int m_nType;
	int m_nLife;		//����
	D3DCOLORVALUE m_colval;
	bool m_bUninit;		//�폜�t���O

};