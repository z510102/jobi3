//=============================================================================
//
// �Q�[������ [game.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "bg.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CSound;
class CEnemy;
class CScore;
class CEffect;
class CPosition;
class CHighScore;
class CUI;
class CTime;
class CLife;
class CG_Possession;
class CF_G_Possession;
class CBulletMagazine;
class CBulletTotal;
class CExplosion;
class CItem;
class CFlash;

//*****************************************************************************
// �Q�[���N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();											// �f�t�H���g�R���X�g���N�^
	~CGame();											// �f�X�g���N�^

	// �����o�֐�
	static CGame *Create(void);							// ��������
	void Clear(void);									// �Q�[���N���A����
	void Over(void);									// �Q�[���I�[�o�[����

	HRESULT Init(D3DXVECTOR3 pos);						// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CEnemy *GetEnemy(void);						// �G�l�~�[�̎擾����
	static CScore *GetScore(void);						// �X�R�A�̎擾����
	static CPosition *GetPosition(void);				// �|�W�V�����̎擾����
	static CUI *GetUI(void);							// UI�̎擾����
	static CTime *GetTime(void);						// �^�C���̎擾����
	static CLife *GetLife(void);						// ���C�t�̎擾����
	static CG_Possession *GetG_Possession(void);		// �O���l�[�h�������̎擾����
	static CF_G_Possession *GetF_G_Possession(void);	// �t���b�V���O���l�[�h�������̎擾����
	static CBulletMagazine *GetBulletMagazine(void);	// �}�K�W���̒e���̎擾����
	static CBulletTotal *GetBulletTotal(void);			// ���e���̎擾����
	static CExplosion *GetExplosion(void);				// �����̎擾����
	static CFlash *GetFlash(void);						// �M���̎擾����

private:
	HRESULT Load(void);									// �e�N�X�`���ǂݍ���
	void Unload(void);									// �e�N�X�`���j��

	// �����o�ϐ�
	static CBg *m_pBg;									// �w�i�ւ̃|�C���^
	static CPlayer *m_pPlayer;							// �v���C���[�ւ̃|�C���^
	static CEnemy *m_pEnemy;							// �G�l�~�[�ւ̃|�C���^
	static CScore *m_pScore;							// �X�R�A�ւ̃|�C���^
	static CPosition *m_pPosition;						// �|�W�V�����ւ̃|�C���^
	static CHighScore *m_pHighScore;					// �n�C�X�R�A�ւ̃|�C���^
	static CUI *m_pUI;									// UI�ւ̃|�C���^
	static CTime *m_pTime;								// �^�C���ւ̃|�C���^
	static CLife *m_pLife;								// ���C�t�ւ̃|�C���^
	static CG_Possession *m_pG_Possession;				// �O���l�[�h�������ւ̃|�C���^
	static CF_G_Possession *m_pF_G_Possession;			// �t���b�V���O���l�[�h�������ւ̃|�C���^
	static CBulletMagazine *m_pBulletMagazine;			// �}�K�W���̒e���ւ̃|�C���^
	static CBulletTotal *m_pBulletTotal;				// ���e���ւ̃|�C���^
	static CExplosion *m_pExplosion;					// �����ւ̃|�C���^
	static CItem *m_pItem;								// �A�C�e���ւ̃|�C���^
	static CFlash *m_pFlash;							// �M���ւ̃|�C���^
	int m_nSpawn;										// �G�̃X�|�[���l
	int m_nSpawn2;										// �G�̃X�|�[���l�Q
	int m_nSpawn3;										// �G�̃X�|�[���l�R
	int m_nSpawn4;										// �G�̃X�|�[���l�S
	int m_nSpawn5;										// �G�̃X�|�[���l�T
	int m_nSpawn6;										// �G�̃X�|�[���l�U
	int m_nSpawn7;										// �G�̃X�|�[���l�V
	int m_nCntSpawn;									// �G7�̏o���Ԋu�𒲐�����
	int m_nCntLife;										// ���C�t�����J�E���g
};

#endif // !_GAME_H_