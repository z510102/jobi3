//=============================================================================
//
// �T�E���h�N���X [sound.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "xaudio2.h"//XAudio2�֘A�̃w�b�_�[
#include"manager.h"

//*****************************************************************************
// �T�E���h�N���X�̒�`
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	//�T�E���h�t�@�C���̍\����
	typedef enum
	{
		SOUND_LABEL_GAME = 0,	// �^�C�g��BGM
		SOUND_LABEL_TADA,		// �e�e�[��
		SOUND_LABEL_TAIKODON,	// ���ۃh��
		SOUND_LABEL_RESULT,		// ���U���g
		SOUND_LABEL_MENU,		// ���j���[
		SOUND_LABEL_TITLE,		// �^�C�g��
		SOUND_LABEL_KETTEI,
		SOUND_LABEL_MOVE,
		SOUND_LABEL_JUMP,
		SOUND_LABEL_MAX
	}SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	void SetVolume(SOUND_LABEL label, float fVolume)
	{
		m_apSourceVoice[label]->SetVolume(fVolume);
	}

private:
	//�p�����[�^�\����
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2				*m_pXAudio2 = NULL;						// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};	// �I�[�f�B�I�f�[�^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};		// �I�[�f�B�I�f�[�^�T�C�Y

																	// �e���f�ނ̃p�����[�^
	PARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data//SOUND//game.wav", -1 },	// �T���v��BGM
		{ "data//SOUND//tada.wav", 0 },		// �e�e�[��
		{ "data//SOUND//taikodon.wav", 0 },	// ���ۃh��
		{ "data//SOUND//result.wav", -1 },	// ���U���g
		{ "data//SOUND//menu.wav", -1 },		// ���j���[
		{ "data//SOUND//title.wav", -1 },		// �^�C�g��
		{ "data//SOUND//���艹.wav", 0 },		// �e�e�[��
		{ "data//SOUND//�J�[�\���ړ�.wav", 0 },		// �e�e�[��
		{ "data//SOUND//jump.wav", 0 },		// �e�e�[��
	};

};

#endif // !_SOUND_H_
