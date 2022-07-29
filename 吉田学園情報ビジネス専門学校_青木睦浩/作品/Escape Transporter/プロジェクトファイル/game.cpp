//=============================================================================
//
// �Q�[����� [game.cpp]
// Author : ���}���@�V��
// Author : �쑺�@�D�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"
#include "keyboard.h"
//#include "xinput_gamepad.h"
#include "fade.h"

#include "scene2D.h"
#include "scene3D.h"
#include "stage.h"

#include "meshfield.h"
#include "texture.h"

#include "light.h"
#include "camera.h"
#include "model.h"
#include "player.h"
//#include "bg.h"
//#include "bg_board.h"
//#include "player.h"
#include "enemy.h"
#include "score.h"
#include "time.h"
#include "ui.h"
//#include "move.h"
//#include "select.h"
//#include "ui_select.h"
#include "sound.h"
#include "billboard.h"
#include "billeffect.h"
#include "effect_straight.h"
#include "effect_smoke.h"
#include "effect_dust.h"
#include "goal.h"
#include "bullet.h"

#define CYCLE (float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f)
#define SPEED 2

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer	*CGame::m_pPlayer = NULL;
CScore *CGame::m_pScore = NULL;
CTime *CGame::m_pTime = NULL;
CStage *CGame::m_pStage = NULL;
CGoal *CGame::m_pGoal = NULL;
CBullet *CGame::m_pBullet = NULL;
CMeshField *CGame::m_pMeshField = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_bFade = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{

	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetPositionR(D3DXVECTOR3(0.0f, GAZE_Y, -GAZE_Z));	// �����_
	pCamera->SetPositionV(D3DXVECTOR3(0.0f, VIEW_Y, -VIEW_Z));	// ���_

	// ���b�V���t�B�[���h
	//m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, -200.0f, 500.0f), D3DXVECTOR3(7000.0f, 0.0f, 7000.0f), CTexture::TEXTURETYPE_MAX);
	
	// �v���[���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_GAME);
	pSound->SetVolume(pSound->SOUND_LABEL_GAME, 0.5f);

	// UI�̐���
	CUI::Create(D3DXVECTOR3(150.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 40.0f, 0.0f), CTexture::TEXTURETYPE_HPBG);
	CUI::Create(D3DXVECTOR3(132.0f, 658.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(112.0f, 15.0f, 0.0f), CTexture::TEXTURETYPE_HPHONTAI);

	// �X�e�[�W�̐���
	m_pStage = CStage::Create();
	//�S�[���̐���
	m_pGoal = CGoal::Create();

	// �G�̐���
	//CEnemy::Create(D3DXVECTOR3(0, 0, 300), D3DXVECTOR3(0, 0, 0));

	// UI �^�C�}�[�ƃX�R�A�@���ݒu
	m_pTime = CTime::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(35.0f, 47.0f, 0.0f), 60, false);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	// �t�@�C���Ăяo���̂��
	FILE *pFile;

	// �I��������̎��Ԃ��L�^
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_GAME);

	//���Ԃ̃Z�[�u����
	pFile = fopen("data/SAVEDATA/newtime.txt", "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", nTime);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	//// �I������Ƃ��̃X�R�A���Z�[�u
	//CScore *pScore = CGame::GetScore();
	//int nScore = pScore->GetScore();
	////�Z�[�u����
	//pFile = fopen("data/SAVEDATA/newscore.txt", "w");
	//if (pFile != NULL)
	//{
	//	fprintf(pFile, "%d\n", nScore);
	//}
	//else
	//{
	//	printf("�t�@�C�����J���܂���ł���\n");
	//}
	//fclose(pFile);

	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	//// ���U���g�s��
	//if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true )
	//{
	//	if (m_bFade == false)
	//	{
	//		// ��ʑJ�� / �t�F�[�h����
	//		pFade->SetFade(CManager::MODE_RESULT);
	//		m_bFade = true;
	//	}
	//}

	//// �Ƃ肠�������̓X�y�[�X�������ςŃX�R�A������悤��
	//CScore *pScore = CGame::GetScore();
	//if (CManager::GetInputKeyboard()->GetPress(DIK_SPACE) == true)
	//{
 //		pScore->AddScore(1);
	//}

	// �G�t�F�N�g/�p�[�e�B�N��
#if 1
	//��
	if (CManager::GetInputKeyboard()->GetPress(DIK_K) == true)
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			CEffectSmoke::Create(D3DXVECTOR3(0, 50, 0),
				D3DXVECTOR3(10.0f, 10.0f, 0.0f),
				D3DXVECTOR3(0, 0, 0),
				60, 26);
		}
	}

	//����
	if (CManager::GetInputKeyboard()->GetPress(DIK_L) == true)
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			CEffectDust::Create(D3DXVECTOR3(0, 70, 0),
				D3DXVECTOR3(10.0f, 10.0f, 0.0f),
				D3DXVECTOR3(sinf(CYCLE) * SPEED, 1.0f, cosf(CYCLE) * SPEED),
				120, 26);
		}
	}


//�r�[��
	if (CManager::GetInputKeyboard()->GetPress(DIK_J) == true)
	{
		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			CEffectDust::Create(D3DXVECTOR3(0, 70, 0),
				D3DXVECTOR3(10.0f, 10.0f, 0.0f),
				D3DXVECTOR3(sinf(CYCLE) * 5, cosf(CYCLE) * 5, 1.5f),
				420, 26);
		}
		CEffectStr::Create(D3DXVECTOR3(0, 70, 0),
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(0.0f, 0.0f, 5.0f),
			120, 26,
			m_colval);
	}
		//test
	if (CManager::GetInputKeyboard()->GetPress(DIK_O) == true)
	{
		CBullet::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(BULLET_SCALE_X, BULLET_SCALE_Y, BULLET_SCALE_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 240, 28);	// �r���{�[�h�̏�����
	}

	CScene *pSceneBullet = CScene::GetScene(PRIORITY_BULLET);

	//�e�̓����蔻��
	while (pSceneBullet != NULL)
	{
		//�V�[����e�̃N���X�ɃL���X�g
		CBullet *pBullet = (CBullet*)pSceneBullet;
		//�V�[���̎��̃I�u�W�F�N�g���i�[
		CScene *pNext = CScene::GetNextScene(pSceneBullet);
		if (pBullet != NULL)
		{
			pBullet->Collision(pBullet, &m_pPlayer->GetPos());
		}
		//�V�[�������ɂ���
		pSceneBullet = pNext;
	}

#endif

}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}
//=============================================================================
// �Q�[����ʂ̐���
//=============================================================================
CGame *CGame::Create(void)
{
	// �^�C�g���̃C���X�^���X����
	CGame *pGame = new CGame;
	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �^�C���̎擾
//=============================================================================
CTime * CGame::GetTime(void)
{
	return m_pTime;
}

CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}
CStage *CGame::GetStage(void)
{
	return m_pStage;
}

CGoal *CGame::GetGoal(void)
{
	return m_pGoal;
}

CBullet *CGame::GetBullet(void)
{
	return m_pBullet;
}

CMeshField *CGame::GetMeshField(void)
{
	return m_pMeshField;
}