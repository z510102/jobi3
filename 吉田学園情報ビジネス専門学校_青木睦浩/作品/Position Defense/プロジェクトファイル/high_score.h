//=============================================================================
//
// �n�C�X�R�A���� [high_score.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _HIGH_SCORE_H_
#define _HIGH_SCORE_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_HIGH_SCORE (5)

//*****************************************************************************
// �n�C�X�R�A�N���X
//*****************************************************************************
class CHighScore : public CScene
{
public:
	CHighScore(int nPriority = 5);					// �f�t�H���g�R���X�g���N�^
	~CHighScore();									// �f�X�g���N�^

	// �����o�֐�
	static CHighScore *Create(D3DXVECTOR3 pos);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);					// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	void SetScore(int nScore);						// �X�R�A�̐ݒ菈��
	void AddScore(int nValue);						// �X�R�A�̉��Z����
	int GetScore(void);								// �X�R�A�̎擾����

private:
	// �����o�ϐ�
	CNumber *m_apNumber[MAX_HIGH_SCORE];			// �X�R�A�̃|�C���^�z��
	int m_nScore;									// �X�R�A
	D3DXVECTOR2 m_size;								// �T�C�Y
	int m_nHighScore;								// �n�C�X�R�A
};

#endif // !_HIGH_SCORE_H_