//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCORE (5)

//*****************************************************************************
// �X�R�A�N���X
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = 5);									// �f�t�H���g�R���X�g���N�^
	~CScore();													// �f�X�g���N�^

	// �����o�֐�
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// ��������

	HRESULT Init(D3DXVECTOR3 pos);								// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void SetScore(int nScore);									// �X�R�A�̐ݒ菈��
	void AddScore(int nValue);									// �X�R�A�̉��Z����
	int GetScore(void);											// �X�R�A�̎擾����

private:
	// �����o�ϐ�
	CNumber *m_apNumber[MAX_SCORE];								// �X�R�A�̃|�C���^�z��
	int m_nScore;												// �X�R�A
	D3DXVECTOR2 m_size;											// �T�C�Y
};

#endif // !_SCORE_H_