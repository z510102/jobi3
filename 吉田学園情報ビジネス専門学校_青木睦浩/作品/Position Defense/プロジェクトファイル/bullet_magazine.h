//=============================================================================
//
// �}�K�W������ [bullet_magazine.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _bullet_magazine_H_
#define _bullet_magazine_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLET_MAGAZINE (2)
#define MAX_BULLET_HG_MAGAZINE (10)
#define MAX_BULLET_AR_MAGAZINE (30)
#define MAX_BULLET_SG_MAGAZINE (8)
#define MAX_BULLET_SR_MAGAZINE (6)
#define MAX_BULLET_RL_MAGAZINE (1)

//*****************************************************************************
// �}�K�W���N���X
//*****************************************************************************
class CBulletMagazine : public CScene
{
public:
	CBulletMagazine(int nPriority = 5);												// �f�t�H���g�R���X�g���N�^
	~CBulletMagazine();																// �f�X�g���N�^

	// �����o�֐�
	static CBulletMagazine *Create(D3DXVECTOR3 pos, CBullet::BULLET_TYPE type);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);													// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void Draw(void);																// �`�揈��

	void SubBulletMagazine(int nValue);												// �e���̌��Z����
	int GetBulletMagazineHG(void);													// �n���h�K���e���̎擾����
	int GetBulletMagazineAR(void);													// �A�T���g���C�t���e���̎擾����
	int GetBulletMagazineSG(void);													// �V���b�g�K���e���̎擾����
	int GetBulletMagazineSR(void);													// �X�i�C�p�[���C�t���e���̎擾����
	int GetBulletMagazineRL(void);													// ���P�b�g�����`���[�e���̎擾����
	int GetBulletType(void);														// �e�̎�ނ̎擾����

private:
	// �����o�ϐ�
	CNumber *m_apNumber[MAX_BULLET_MAGAZINE];										// �X�R�A�̃|�C���^�z��
	int m_nBulletNumber_HG_magazine;												// �n���h�K���̃}�K�W���̒e��
	int m_nBulletNumber_AR_magazine;												// �A�T���g���C�t���̃}�K�W���̒e��
	int m_nBulletNumber_SG_magazine;												// �V���b�g�K���̃}�K�W���̒e��
	int m_nBulletNumber_SR_magazine;												// �X�i�C�p�[���C�t���̃}�K�W���̒e��
	int m_nBulletNumber_RL_magazine;												// ���P�b�g�����`���[�̃}�K�W���̒e��
	D3DXVECTOR2 m_size;																// �T�C�Y
	CBullet::BULLET_TYPE m_type_magajine;											// �}�K�W���̎��
	int m_nMagazineType;															// �}�K�W���̎�ށi���l�j
	int m_nMagazine;																// �e�̍ő吔���猻�݂̒e�����������e�̐�
	int m_nTotal_Magazine;															// ���e���̏������炤
};

#endif // !_BULLET_MAGAZINE_H_