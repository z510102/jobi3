//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドクラス
//*****************************************************************************
class CSound
{
public:
	CSound();   //デフォルトコンストラクタ
	~CSound();  //デストラクタ

	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_TITLE_BGM = 0,		// タイトルBGM
		SOUND_LABEL_TUTORIAL_BGM,		// チュートリアルBGM
		SOUND_LABEL_GAME_BGM,			// ステージBGM
		SOUND_LABEL_CLEAR_BGM,			// ゲームクリアBGM
		SOUND_LABEL_OVER_BGM,			// ゲームオーバーBGM
		SOUND_LABEL_RANKING_BGM,		// ランキングBGM

		SOUND_LABEL_BOMB,				// グレネード爆発音
		SOUND_LABEL_BULLET_OUT,			// 発射音（空）
		SOUND_LABEL_CANCEL,				// キャンセル音
		SOUND_LABEL_COUNTDOWN_10,		// タイム10秒前のときの音
		SOUND_LABEL_DECISION,			// 決定音
		SOUND_LABEL_FLASH_BOMB,			// フラッシュグレネード爆発音
		SOUND_LABEL_GRENADE,			// グレネード発射音
		SOUND_LABEL_HG_SHOT,			// ハンドガン発射音
		SOUND_LABEL_RELOAD,				// リロード音
		SOUND_LABEL_RL_SHOT,			// ロケットランチャー発射音
		SOUND_LABEL_SELECT,				// 選択音
		SOUND_LABEL_SG_SHOT,			// ショットガン発射音
		SOUND_LABEL_SR_SHOT,			// スナイパーライフル発射音
		SOUND_LABEL_WARNING,			// ライフ残り１のときの音
		SOUND_LABEL_ATTACK,				// 攻撃音
		SOUND_LABEL_DAMAGE,				// ダメージ音
		SOUND_LABEL_ITEM,				// アイテム取得音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	void SoundVolume(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }

private:
	//パラメーター構造体
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;  // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

																// 各音素材のパラメータ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif // !_SOUND_H_