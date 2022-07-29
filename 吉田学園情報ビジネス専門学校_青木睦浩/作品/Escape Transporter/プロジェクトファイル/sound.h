//=============================================================================
//
// サウンドクラス [sound.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "xaudio2.h"//XAudio2関連のヘッダー
#include"manager.h"

//*****************************************************************************
// サウンドクラスの定義
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	//サウンドファイルの構造体
	typedef enum
	{
		SOUND_LABEL_GAME = 0,	// タイトルBGM
		SOUND_LABEL_TADA,		// テテーン
		SOUND_LABEL_TAIKODON,	// 太鼓ドン
		SOUND_LABEL_RESULT,		// リザルト
		SOUND_LABEL_MENU,		// メニュー
		SOUND_LABEL_TITLE,		// タイトル
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
	//パラメータ構造体
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2				*m_pXAudio2 = NULL;						// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;				// マスターボイス
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};	// オーディオデータ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};		// オーディオデータサイズ

																	// 各音素材のパラメータ
	PARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data//SOUND//game.wav", -1 },	// サンプルBGM
		{ "data//SOUND//tada.wav", 0 },		// テテーン
		{ "data//SOUND//taikodon.wav", 0 },	// 太鼓ドン
		{ "data//SOUND//result.wav", -1 },	// リザルト
		{ "data//SOUND//menu.wav", -1 },		// メニュー
		{ "data//SOUND//title.wav", -1 },		// タイトル
		{ "data//SOUND//決定音.wav", 0 },		// テテーン
		{ "data//SOUND//カーソル移動.wav", 0 },		// テテーン
		{ "data//SOUND//jump.wav", 0 },		// テテーン
	};

};

#endif // !_SOUND_H_
