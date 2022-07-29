//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�N���X
//*****************************************************************************
class CSound
{
public:
	CSound();   //�f�t�H���g�R���X�g���N�^
	~CSound();  //�f�X�g���N�^

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_TITLE_BGM = 0,		// �^�C�g��BGM
		SOUND_LABEL_TUTORIAL_BGM,		// �`���[�g���A��BGM
		SOUND_LABEL_GAME_BGM,			// �X�e�[�WBGM
		SOUND_LABEL_CLEAR_BGM,			// �Q�[���N���ABGM
		SOUND_LABEL_OVER_BGM,			// �Q�[���I�[�o�[BGM
		SOUND_LABEL_RANKING_BGM,		// �����L���OBGM

		SOUND_LABEL_BOMB,				// �O���l�[�h������
		SOUND_LABEL_BULLET_OUT,			// ���ˉ��i��j
		SOUND_LABEL_CANCEL,				// �L�����Z����
		SOUND_LABEL_COUNTDOWN_10,		// �^�C��10�b�O�̂Ƃ��̉�
		SOUND_LABEL_DECISION,			// ���艹
		SOUND_LABEL_FLASH_BOMB,			// �t���b�V���O���l�[�h������
		SOUND_LABEL_GRENADE,			// �O���l�[�h���ˉ�
		SOUND_LABEL_HG_SHOT,			// �n���h�K�����ˉ�
		SOUND_LABEL_RELOAD,				// �����[�h��
		SOUND_LABEL_RL_SHOT,			// ���P�b�g�����`���[���ˉ�
		SOUND_LABEL_SELECT,				// �I����
		SOUND_LABEL_SG_SHOT,			// �V���b�g�K�����ˉ�
		SOUND_LABEL_SR_SHOT,			// �X�i�C�p�[���C�t�����ˉ�
		SOUND_LABEL_WARNING,			// ���C�t�c��P�̂Ƃ��̉�
		SOUND_LABEL_ATTACK,				// �U����
		SOUND_LABEL_DAMAGE,				// �_���[�W��
		SOUND_LABEL_ITEM,				// �A�C�e���擾��
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//�����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	void SoundVolume(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }

private:
	//�p�����[�^�[�\����
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;  // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif // !_SOUND_H_