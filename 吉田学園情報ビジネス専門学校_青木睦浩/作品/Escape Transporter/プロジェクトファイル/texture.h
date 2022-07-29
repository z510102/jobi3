//=============================================================================
//
// �e�N�X�`���N���X [texture.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FILENAME_TEX "data/SCRIPT/texture.txt"

//*****************************************************************************
//	�e�N�X�`���N���X
//*****************************************************************************
class CTexture
{
public:
	//�e�N�X�`���̎��
	typedef enum
	{
		TEXTURETYPE_PUSH = 0,
		TEXTURETYPE_NAME,
		TEXTURETYPE_WITCH,
		TEXTURETYPE_TITLEBG,
		TEXTURETYPE_GAMEBG,
		TEXTURETYPE_GAMEWOOD,
		TEXTURETYPE_CLEAR,
		TEXTURETYPE_MENUBG,
		TEXTURETYPE_PLAYICON,
		TEXTURETYPE_HELPICON,
		TEXTURETYPE_RANKICON,
		TEXTURETYPE_BACKICON,
		TEXTURETYPE_PLAYTEXT,
		TEXTURETYPE_HELPTEXT,
		TEXTURETYPE_RANKTEXT,
		TEXTURETYPE_BACKTEXT,
		TEXTURETYPE_PLAY,
		TEXTURETYPE_HELP,
		TEXTURETYPE_RANK,
		TEXTURETYPE_BACK,
		TEXTURETYPE_SCORE,
		TEXTURETYPE_TIME,
		TEXTURETYPE_HPBG,
		TEXTURETYPE_HPHONTAI,
		TEXTURETYPE_RESULTBG,
		TEXTURETYPE_TIMEUP,
		TEXTURETYPE_GRANK,
		TEXTURETYPE_FRANK,
		TEXTURETYPE_ERANK,
		TEXTURETYPE_DRANK,
		TEXTURETYPE_CRANK,
		TEXTURETYPE_BRANK,
		TEXTURETYPE_ARANK,
		TEXTURETYPE_SRANK,
		TEXTURETYPE_PLUS,
		TEXTURETYPE_TUTORIAL1,
		TEXTURETYPE_TUTORIAL2,
		TEXTURETYPE_TUTORIAL3,
		TEXTURETYPE_CLEAR2,
		TEXTURETYPE_MAX
	} TEXTURETYPE;

	CTexture();						// �R���X�g���N�^
	~CTexture();					// �f�X�g���N�^

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	static CTexture *Create(void);		// ��������
	LPDIRECT3DTEXTURE9 SetTextureType(int nType);				// �e�N�X�`���̎�ނ�ݒ�

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];		// �e�N�X�`���̃|�C���^
	static int m_nType;
	int m_nNumTexture;
	int m_nTextType;


};
#endif //!_TEXTURE_H_