//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"
#include "bullet.h"

//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer(int nPriority = 2);					// �f�t�H���g�R���X�g���N�^
	~CPlayer();									// �f�X�g���N�^

	// �����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos);	// ��������

	HRESULT Init(D3DXVECTOR3 pos);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static HRESULT Load(void);					// �e�N�X�`���ǂݍ���
	static void Unload(void);					// �e�N�X�`���̔j��
	static int GetBulletType(void);				// �e�̎�ޏ��擾����

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;							// �ʒu
	CBullet::BULLET_TYPE m_type;				// �e�̎��
	static int m_nBullet;						// �e�̎�ނ̏������炤�i���l�j
	int m_nPatternAnimU;						// �A�j���[�V�����p�^�[���iU�j
	int m_nCounterAnim;							// �A�j���[�V�����J�E���^�[
	int m_nBulletNumber_HG_magazine;			// �n���h�K���̃}�K�W���̒e��
	int m_nBulletNumber_AR_magazine;			// �A�T���g���C�t���̃}�K�W���̒e��
	int m_nBulletNumber_SG_magazine;			// �V���b�g�K���̃}�K�W���̒e��
	int m_nBulletNumber_SR_magazine;			// �X�i�C�p�[���C�t���̃}�K�W���̒e��
	int m_nBulletNumber_RL_magazine;			// ���P�b�g�����`���[�̃}�K�W���̒e��
	int m_nRapidSpeedHG;						// �n���h�K���̒e�̔��ˊԊu
	int m_nRapidSpeedAR;						// �A�T���g���C�t���̒e�̔��ˊԊu
	int m_nRapidSpeedSG;						// �V���b�g�K���̒e�̔��ˊԊu
	int m_nRapidSpeedSR;						// �X�i�C�p�[���C�t���̒e�̔��ˊԊu
	int m_nRapidSpeedRL;						// ���P�b�g�����`���[�̒e�̔��ˊԊu
};

#endif // !_PLAYER_H_