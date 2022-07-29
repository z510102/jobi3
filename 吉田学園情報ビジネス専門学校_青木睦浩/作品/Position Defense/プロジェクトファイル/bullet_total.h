//=============================================================================
//
// ���e������ [bullet_total.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _bullet_total_H_
#define _bullet_total_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLET_TOTAL (2)

//*****************************************************************************
// ���e���N���X
//*****************************************************************************
class CBulletTotal : public CScene
{
public:
	CBulletTotal(int nPriority = 5);											// �f�t�H���g�R���X�g���N�^
	~CBulletTotal();															// �f�X�g���N�^

	// �����o�֐�
	static CBulletTotal *Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type);	// ��������

	HRESULT Init(D3DXVECTOR3 pos);												// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��

	void SetBulletTotal(int nBulletNumber);										// ���e���̐ݒ菈��
	void SubBulletTotal(int nValue);											// ���e���̌��Z����
	int GetBulletTotal(void);													// ���e���̎擾����
	void AddBulletTotalHG(int nValue);											// �n���h�K���̑��e���̉��Z����
	void AddBulletTotalAR(int nValue);											// �A�T���g���C�t���̑��e���̉��Z����
	void AddBulletTotalSG(int nValue);											// �V���b�g�K���̑��e���̉��Z����
	void AddBulletTotalSR(int nValue);											// �X�i�C�p�[���C�t���̑��e���̉��Z����
	void AddBulletTotalRL(int nValue);											// ���P�b�g�����`���[�̑��e���̉��Z����

private:
	// �����o�ϐ�
	CNumber *m_apNumber[MAX_BULLET_TOTAL];										// �X�R�A�̃|�C���^�z��
	int m_nBulletNumber_HG_total;												// �n���h�K���̑��e��
	int m_nBulletNumber_AR_total;												// �A�T���g���C�t���̑��e��
	int m_nBulletNumber_SG_total;												// �V���b�g�K���̑��e��
	int m_nBulletNumber_SR_total;												// �X�i�C�p�[���C�t���̑��e��
	int m_nBulletNumber_RL_total;												// ���P�b�g�����`���[�̑��e��
	D3DXVECTOR2 m_size;															// �T�C�Y
	CBullet::BULLET_TYPE m_type_total;											// ���e���̎��
	int m_nTotalType;															// ���e���̎�ށi���l�j
	int m_nRemainingTotal;														// �c��̑��e��
	int m_nTotal;																// ���݂̑��e��
	int m_nPass;																// �}�K�W���̏���n��
};

#endif // !_BULLET_TOTAL_H_