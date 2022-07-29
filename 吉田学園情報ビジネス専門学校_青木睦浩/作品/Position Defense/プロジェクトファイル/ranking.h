//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKING (6)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;

//*****************************************************************************
// �����L���O�N���X
//*****************************************************************************
class CRanking : public CScene
{
public:
	CRanking(int nPriority = 0);									// �f�t�H���g�R���X�g���N�^
	~CRanking();													// �f�X�g���N�^

	// �����o�֐�
	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);									// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

private:
	// �����o�ϐ�
	static CScore *m_apScore[MAX_RANKING];							// �����L���O�̃|�C���^�z��
	int m_aScore[MAX_RANKING];										// �X�R�A�̔z��
	int m_nScore;													// �X�R�A
	D3DXVECTOR3 m_pos;												// �ʒu
	D3DXVECTOR2 m_size;												// �T�C�Y
};

#endif // !_RANKING_H_