//=============================================================================
//
// ���[�V�����N���X [motion.h]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "motion.h"
#include "model.h"
#include "keyboard.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{
	// �����o�ϐ��̃N���A
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMotion::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMotion::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CMotion::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMotion::Draw(void)
{

}
//=============================================================================
// �v���C���[�̐���
//=============================================================================
CMotion *CMotion::Create(void)
{
	CMotion *pMotion;
	pMotion = new CMotion;

	if (pMotion != NULL)
	{
		pMotion->Init();
	}

	return pMotion;
}
//=============================================================================
// ���[�V�����Đ�
//=============================================================================
void CMotion::PlayMotion(const int nNumModel, CModel **apModel, MOTION_TYPE& motiontype, MOTION_TYPE& motiontypelast)
{

	//*******************************************************
	//�@�ʒu�Ɖ�]�����v�Z���邽�߂̃��[�J���ϐ�
	//*******************************************************
	float fPosXDiff[MOTION_KEY_MAX];	// �ʒu���X�̍���
	float fPosYDiff[MOTION_KEY_MAX];	// �ʒu���Y�̍���
	float fPosZDiff[MOTION_KEY_MAX];	// �ʒu���Z�̍���
	float fRotXDiff[MOTION_KEY_MAX];	// ��]���X�̍���
	float fRotYDiff[MOTION_KEY_MAX];	// ��]���Y�̍���
	float fRotZDiff[MOTION_KEY_MAX];	// ��]���Z�̍���

	float fPosXAsk[MOTION_KEY_MAX];		// ���߂�l�̈ʒuX
	float fPosYAsk[MOTION_KEY_MAX];		// ���߂�l�̈ʒuY
	float fPosZAsk[MOTION_KEY_MAX];		// ���߂�l�̈ʒuZ
	float fRotXAsk[MOTION_KEY_MAX];		// ���߂�l�̉�]X
	float fRotYAsk[MOTION_KEY_MAX];		// ���߂�l�̉�]Y
	float fRotZAsk[MOTION_KEY_MAX];		// ���߂�l�̉�]Z

	// ���[�V�������ς�����Ƃ�
	if (motiontypelast != motiontype)
	{
		m_nNumKey = 0;
	}

	// ���݂̃��[�V�����^�C�v��ۑ�
	motiontypelast = motiontype;

	// �ő�̃L�[�ɐi�ނ܂ł̏���
	// ���݂̃��[�V�����L�[�����[�V�����L�[�̍ő吔��菬�����Ƃ�
	if (m_nNumKey < m_aMotionInfo[motiontype].nNumMaxKey - 1)
	{
		while (1)
		{
			// �p�[�c�����[�v������
			for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
			{
				// �ʒu�̍���(���̃L�[�ƌ��݂̃L�[�̍���)
				fPosXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX;
				fPosYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY;
				fPosZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ;

				// �����̍���(���̃L�[�ƌ��݂̃L�[�̍���)
				fRotXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX;
				fRotYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY;
				fRotZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ;

				// ���߂��ʒu�E���� = ���݂̈ʒu + ���� * ((float�ŃL���X�g)���[�V�����J�E���^�[ / (float�ŃL���X�g)�ő�̃t���[��)�@��float�^�Œl�𐳊m�Ɏ擾���邽��
				fPosXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fPosYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fPosZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);

				fRotXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fRotYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);
				fRotZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame);

				// ���߂��ʒu�E������ݒ�
				apModel[nCntModel]->SetPosition(D3DXVECTOR3(fPosXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fPosYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fPosZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
				apModel[nCntModel]->SetRotation(D3DXVECTOR3(fRotXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fRotYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fRotZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
			}

			// ���[�V�����J�E���^�[�����Z����
			m_nMotionCounter++;

			// ���[�V�����̃t���[���ő吔���t���[���J�E���^�[���z������
			if (m_nMotionCounter >= m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame)
			{
				m_nMotionCounter = 0;	// ���[�V�����J�E���^�[��������

				// ���̃L�[�ɐi��
				m_nNumKey++;
			}
			else
			{
				break;
			}
		}
	}

	// ���[�V�������[�v�̏���
	// ���݂̃L�[�ƍő�̃L�[�������Ƃ�
	if (m_nNumKey == m_aMotionInfo[motiontype].nNumMaxKey - 1)
	{
		// ���[�v����ꍇ
		if (m_aMotionInfo[motiontype].bLoop == true)
		{
			while (1)
			{

				for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
				{
					// �ʒu�̍���(���̃L�[�ƌ��݂̃L�[�̍���)
					fPosXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fPosX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX;
					fPosYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fPosY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY;
					fPosZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fPosZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ;

					// �����̍���(���̃L�[�ƌ��݂̃L�[�̍���)
					fRotXDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fRotX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX;
					fRotYDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fRotY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY;
					fRotZDiff[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[0].aKey[nCntModel].fRotZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ;

					// ���߂�ʒu�E���� = ���݂̈ʒu + ���� * ((float�ŃL���X�g)���[�V�����J�E���^�[ / (float�ŃL���X�g)�ő�̃t���[��)�@��float�^�Œl�𐳊m�Ɏ擾���邽��
					fPosXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fPosYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY + fPosYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fPosZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ + fPosZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);

					fRotXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX + fRotXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fRotYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY + fRotYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);
					fRotZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ + fRotZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[motiontype].aKeyInfo[nCntModel].nFrame);

					// ���߂��ʒu�E������ݒ�
					apModel[nCntModel]->SetPosition(D3DXVECTOR3(fPosXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fPosYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fPosZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
					apModel[nCntModel]->SetRotation(D3DXVECTOR3(fRotXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fRotYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fRotZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
				}

				// ���[�V�����J�E���^�[��1�t���[�����ɉ��Z
				m_nMotionCounter++;

				// ���[�V�����̃t���[���ő吔���t���[���J�E���^�[���z������
				if (m_nMotionCounter > m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].nFrame)
				{
					// ���[�V�����J�E���^�[��������
					m_nMotionCounter = 0;

					// �L�[�������[�v������
					m_nNumKey = 0;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			while (1)
			{
				for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
				{
					// �ʒu�̍���
					fPosXDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosX;
					fPosYDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosY;
					fPosZDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fPosZ;

					// �����̍���
					fRotXDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotX - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotX;
					fRotYDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotY - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotY;
					fRotZDiff[nCntModel] = m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotZ - m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey].aKey[nCntModel].fRotZ;

					// ���߂��ʒu�E���� = ���݂̈ʒu + ���� * ((float�ŃL���X�g)���[�V�����J�E���^�[ / (float�ŃL���X�g)�ő�̃t���[��)
					fPosXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosX + fPosXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fPosYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosY + fPosYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fPosZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fPosZ + fPosZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);

					fRotXAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotX + fRotXDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fRotYAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotY + fRotYDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);
					fRotZAsk[nCntModel] = m_aMotionInfo[motiontype].aKeyInfo[m_nNumKey + 1].aKey[nCntModel].fRotZ + fRotZDiff[nCntModel] * ((float)m_nMotionCounter / (float)m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[0].nFrame);

					// ���߂��ʒu�E������ݒ�
					apModel[nCntModel]->SetPosition(D3DXVECTOR3(fPosXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fPosYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fPosZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
					apModel[nCntModel]->SetRotation(D3DXVECTOR3(fRotXAsk[nCntModel] + apModel[nCntModel]->GetPosition().x, fRotYAsk[nCntModel] + apModel[nCntModel]->GetPosition().y, fRotZAsk[nCntModel] + apModel[nCntModel]->GetPosition().z));
				}

				// ���[�V�����J�E���^�[�����Z
				m_nMotionCounter++;

				// ���[�V�����̃t���[���ő吔���t���[���J�E���^�[���z������
				if (m_nMotionCounter >= m_aMotionInfo[MOTION_NEUTRAL].aKeyInfo[m_nNumKey].nFrame)
				{
					// ���[�V�����J�E���^�[��������
					m_nMotionCounter = 0;

					// ���̃L�[�ɐi��
					m_nNumKey++;

					// �L�[�����j���[�g�������[�V�����ɕύX
					motiontype = MOTION_NEUTRAL;
				}
				else
				{
					break;
				}
			}
		}
	}

}
//=============================================================================
// ���[�V�����t�@�C���̓ǂݍ���
//=============================================================================
void CMotion::LoadMotion(const char *pMotionFileName)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	int nLoop = 0;			// ���[�V�������[�v
	int nNumKey = 0;		// �L�[�̑���
	int nCntKey = 0;		// �L�[��
	int nCntParts = 0;		// �p�[�c��
	int nCntMotion = 0;		// ���[�V������
	bool bMotionSet = false;	// ���[�V�����̃Z�b�g
	bool bKeySet = false;	// ���[�V�����L�[�̃Z�b�g
	bool bKey = false;		// �L�[�p�[�c�̃Z�b�g
	D3DXVECTOR3 pos;		// �p�[�c�̈ʒu
	D3DXVECTOR3 rot;		// �p�[�c�̌���
	char aFile[256];		// ������ǂݍ���
	FILE *pFile = fopen(pMotionFileName, "r");	// �X�N���v�g�t�@�C���ǂݍ���

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "MOTIONSET") == 0)
			{
				bMotionSet = true;
			}
			if (bMotionSet == true)
			{
				if (strcmp(&aFile[0], "LOOP") == 0)
				{
					// ���[�V�������[�v�̐ݒ�
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);

					if (nLoop == 0)
					{
						m_aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0)
				{
					// ���[�V�����L�[�̑���
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNumMaxKey);
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)
				{
					// ���[�V�����L�[�̃Z�b�g
					bKeySet = true;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)
				{
					// ���[�V�����L�[�̃Z�b�g�I��
					bKeySet = false;
					nCntKey++;
				}
				if (bKeySet == true)
				{
					if (strcmp(&aFile[0], "FRAME") == 0)
					{
						// �L�[�t���[���̐ݒ�
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "KEY") == 0)
					{
						// �L�[�p�[�c�̃Z�b�g
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)
					{
						// �L�[�p�[�c�̃Z�b�g�I��
						bKey = false;
						nCntParts++;
					}
					if (bKey == true)
					{
						// �ʒu
						if (strcmp(&aFile[0], "POS") == 0)
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);

						}
						// ����
						if (strcmp(&aFile[0], "ROT") == 0)
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
						}
					}
				}
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)
			{
				// ���[�V�����^�C�v�̉��Z
				nCntMotion++;
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
