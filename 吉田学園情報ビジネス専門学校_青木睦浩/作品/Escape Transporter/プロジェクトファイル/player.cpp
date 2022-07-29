//=============================================================================
//
// �v���C���[�N���X [player.h]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "model.h"
#include "keyboard.h"
#include "xinput_gamepad.h"
#include "camera.h"
#include "motion.h"
#include "stage.h"
#include "stage_data.h"
#include "billeffect.h"
#include "effect_straight.h"
#include "effect_speed.h"
#include "game.h"
#include "goal.h"
#include "fade.h"
#include "bullet.h"
#include "meshfield.h"
#include"time.h"
#include"sound.h"
#define RAND_POS (float(rand() % 200)- 100)

#define PI_QUARTER	(D3DX_PI / 4.0f)	// 3.14f��1/4�̒l	�΂߈ړ��̌����@45��
#define PI_HALF		(D3DX_PI / 2.0f)	// 3.14f��1/2�̒l	�΂߈ړ��̌����@90��
#define PLAYER_MOVESPEED		(5.5f)		// �X�s�[�h

#define CYCLE (float(rand() % 324) / 90.0f - float(rand() % 324) / 90.0f)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(m_pos, 0, sizeof(D3DXVECTOR3));			// �ʒu
	memset(m_move, 0, sizeof(D3DXVECTOR3));			// �ړ���
	m_nNumModel = 0;
	m_bJump = false;
	m_bLand = false;
	m_bGoal = false;
	m_bFade = false;
	m_bHitBullet = false;
	m_bDeathFrag = false;
	m_bMeshField = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	m_bJump = true;
	
	SetObjType(OBJTYPE_PLAYER);

	LoadPlayerFile(FILENAME_PLAYER);

	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0, 0, 0);

	// �����̐ݒ�
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_fGravitySpeed = GRAVITYSPEED;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Uninit();
		}
	}


	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	//�Q�[���p�b�h�̏����擾
	CXinputPad *pXinputPad = CManager::GetXinputPad();

	// �L�[�{�[�h�̏����擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̌������擾
	D3DXVECTOR3 cameraRot = pCamera->GetRot();

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();


	// �X�s�[�h�A�b�v	�G�t�F�N�g
#if 0
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		float fAngle = CYCLE;
		CEffectSpeed::Create(D3DXVECTOR3(m_pos.x + sinf(fAngle) * 100, m_pos.y, m_pos.z + cosf(fAngle) * 100), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 180, 27);
	}
#endif


	m_posOld = m_pos;


	//***********************************************************
	//	�ړ�����
	//***********************************************************
	
	// ���ړ�
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = (D3DX_PI * 3) / 4;
			m_move.x = sinf(0.75f) * -PLAYER_MOVESPEED;
			m_move.z = cosf(0.75f) * PLAYER_MOVESPEED;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			//�܂�
			m_rot.y = (-D3DX_PI *3) /4;
			m_move.x = sinf(-0.75f) * -PLAYER_MOVESPEED;
			m_move.z = cosf(-0.75f) * PLAYER_MOVESPEED;
		}
		else
		{
			m_rot.y = D3DX_PI;
			m_move.x = sinf(m_rot.y) * PLAYER_MOVESPEED;
			m_move.z = cosf(m_rot.y) * -PLAYER_MOVESPEED;
		}
	}
	// �O�ړ�
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_rot.y = (D3DX_PI * 7) / 4;
			m_move.x = sinf(0.50f) * PLAYER_MOVESPEED;
			m_move.z = cosf(0.50f) * -PLAYER_MOVESPEED;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_rot.y = -(D3DX_PI * 7) / 4;
			m_move.x = sinf(-0.50f) * PLAYER_MOVESPEED;
			m_move.z = cosf(-0.50f) * -PLAYER_MOVESPEED;
		}
		else
		{
			m_rot.y = 0;
			m_move.x = sinf(m_rot.y) * PLAYER_MOVESPEED;
			m_move.z = cosf(m_rot.y) * -PLAYER_MOVESPEED;
		}
	}
	// ���ړ�
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_rot.y = -D3DX_PI / 2;
		m_move.x = sinf(m_rot.y) * -PLAYER_MOVESPEED;
		m_move.z = cosf(m_rot.y) * PLAYER_MOVESPEED;
	}
	// �E�ړ�
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		m_rot.y = D3DX_PI / 2;
		m_move.x = sinf(m_rot.y) * -PLAYER_MOVESPEED;
		m_move.z = cosf(m_rot.y) * PLAYER_MOVESPEED;
	}
	else
	{
		m_move = D3DXVECTOR3(0, m_move.y, 0);
	}
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{
		m_bJump = true;
		m_move.y = 15.0f;
		pSound->Play(pSound->SOUND_LABEL_JUMP);
		pSound->SetVolume(pSound->SOUND_LABEL_JUMP, 0.8f);
	}
	if (m_bJump = true)
	{
		m_bLand = false;
		m_bJump = true;
	}


	if (m_fGravitySpeed > 0.0f)
	{
		m_move.y -= m_fGravitySpeed;
		m_pos.y += m_move.y;
	}

	//�������
	//if (m_pos.y <= 0.0f)
	//{
	//	m_pos.y = 0.0f;
	//	m_move.y = 0.0f;
	//	m_bJump = false;
	//}

	//�����蔻��
	CStage *pStage = CManager::GetGame()->GetStage();
	CGoal * pGoal = CManager::GetGame()->GetGoal();
	CMeshField *pMeshField = CManager::GetGame()->GetMeshField();

	//�V�[������X�e�[�W�f�[�^���擾
	CScene *pScene = CScene::GetScene(PRIORITY_MODEL);
	//�e���f��������
	while (pScene != NULL)
	{
		//�V�[������Ƃ��Ă����X�e�[�W�f�[�^��CStageData�ɃL���X�g
		CStageData *pStageData = (CStageData*)pScene;

		//�V�[���̎��̏��̊m��
		CScene *pSceneNext = CScene::GetNextScene(pScene);
		if (pStageData != NULL)
		{
			m_bLand = pStage->Collision(pStageData, &m_pos, &m_posOld, &m_move, m_fBackPos);
			m_bGoal = pGoal->Collision(pGoal, &m_pos, &m_posOld, &m_move, m_fBackPos);
			m_bMeshField = pMeshField->Collision(pMeshField, &m_pos, &m_posOld, &m_move, m_fBackPos);

			// ���u���b�N�̈ʒu���擾
			D3DXVECTOR3 blockpos = pStageData->GetPosition();

			//�n�ʓ��񂾂�
			if (m_bLand == true)
			{
				m_fGravitySpeed = blockpos.y;
				m_move.y = 0.0f;
				m_pos.y = m_fBackPos;
				m_bJump = false;
			}
			//�S�[�����񂾂�
			if (m_bGoal == true)
			{
				m_fGravitySpeed = 0.0f;
				m_move.y = 0.0f;
				m_pos.y = m_fBackPos;
				m_bGoal = false;
				// �t�F�[�h�̎擾
				CFade *pFade = CManager::GetFade();
				if (m_bFade == false)
				{
					// ��ʑJ�� / �t�F�[�h����
					pFade->SetFade(CManager::MODE_RESULT);
					m_bFade = true;
				}

			}
			//���b�V���t�B�[���h�̒��n����
			if (m_bMeshField == true)
			{
				m_bLand = true;
				m_fGravitySpeed = 0.0f;
				m_move.y = 0.0f;
				m_pos.y = m_fBackPos;
				m_bJump = false;
				m_bMeshField = false;
			}

			else
			{
				m_fGravitySpeed = GRAVITYSPEED;
			}

			//���̏��ɒu��������
			pScene = pSceneNext;

		}

	}
	//�e����������
	if (m_bHitBullet == true&& m_bFade==false)
	{
		m_bGoal = false;
		// �t�F�[�h�̎擾
		//CFade *pFade = CManager::GetFade();
		// ��ʑJ�� / �t�F�[�h����
		//pFade->SetFade(CManager::MODE_RESULT);
		//m_bFade = true;
		m_bHitBullet = false;
	}
	//���S�t���O���I����������
	if (m_bDeathFrag == true)
	{
		Uninit();
	}
	// �Q�[���I�[�o�[����
	if (m_pos.y <= -200.0f)
	{
		m_pos.y = -200.0f;

		// �t�@�C���Ăяo���̂��
		FILE *pFile;
		CTime *pTime = CGame::GetTime();

		//���Ԃ̃Z�[�u����
		pFile = fopen("data/SAVEDATA/newtime.txt", "w");
		if (pFile != NULL)
		{
			fprintf(pFile, "%d\n", 0);
		}
		else
		{
			printf("�t�@�C�����J���܂���ł���\n");
		}
		fclose(pFile);
		pTime->SetTime(0);

		// �t�F�[�h�̎擾
		CFade *pFade = CManager::GetFade();
		if (m_bFade == false)
		{
			// ��ʑJ�� / �t�F�[�h����
			pFade->SetFade(CManager::MODE_RESULT);
			m_bFade = true;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
}
//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
	}

	return pPlayer;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// ���f���t�@�C���ǂݍ���
//=============================================================================
void CPlayer::LoadPlayerFile(const char * pFileName)
{	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 pos;	// �ʒu�ۑ�
	D3DXVECTOR3 rot;	// �����ۑ�
	int nIndex = 0;
	int nParent = 0;	// �e���f��
	int nCntModel = 0;	// ���f����
	char aFile[256];	// ������ǂݍ���

	bool bCharacterSet = false;	// �L�����N�^�[�Z�b�g
	bool bPartsSet = false;		// �p�[�c�Z�b�g

	// �v���C���[�̃��f��/�I�t�Z�b�g�ǂݍ���
	FILE *pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{
				// ���f����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)
			{
				// ���f���̃p�X
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				m_pModel[nCntModel] = CModel::Create(&aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)
			{
				// �L�����N�^�[�Z�b�g
				nCntModel = 0;
				bCharacterSet = true;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)
			{
				// �L�����N�^�[�Z�b�g�I��
				bCharacterSet = false;
			}
			if (bCharacterSet == true)
			{
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{
					// �p�[�c�Z�b�g
					bPartsSet = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{
					// �p�[�c�Z�b�g�I��
					bPartsSet = false;
					nCntModel++;
				}
				if (bPartsSet == true)
				{
					// �e�q�֌W�ݒ�
					if (strcmp(&aFile[0], "PARENT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);

						// �e�q�֌W��-1�̏ꍇ�A�e���f����ݒ�
						if (nParent != -1)
						{
							m_pModel[nCntModel]->SetParent(m_pModel[nParent]);
						}
					}
					// �ʒu
					if (strcmp(&aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntModel]->SetPosition(pos);
					}
					// ����
					if (strcmp(&aFile[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntModel]->SetRotation(rot);
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// �ǂݍ��ݏI��
				break;
			}
		}
		fclose(pFile);
	}
}


