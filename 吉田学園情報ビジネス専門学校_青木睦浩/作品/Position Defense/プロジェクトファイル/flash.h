//=============================================================================
//
// �M������ [flash.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _FLASH_H_
#define _FLASH_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �M���N���X
//*****************************************************************************
class CFlash : public CScene2D
{
public:
	CFlash(int nPriority = 3);									// �f�t�H���g�R���X�g���N�^
	~CFlash();													// �f�X�g���N�^

	//�����o�֐�
	static HRESULT Load(void);                                  // �e�N�X�`���ǂݍ���
	static void Unload(void);                                   // �e�N�X�`���̔j��
	static CFlash *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// ��������

	HRESULT Init(D3DXVECTOR3 pos);								// ����������
	void Uninit(void);                                          // �I������
	void Update(void);                                          // �X�V����
	void Draw(void);                                            // �`�揈��

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;						// �e�N�X�`���ւ̃|�C���^
	int m_nCounterAnim;											// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;											// �A�j���[�V�����p�^�[��
	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR2 m_size;											// �T�C�Y
};

#endif // !_EXPLOSION_H_