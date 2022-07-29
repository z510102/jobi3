//=============================================================================
//
// �^�C������ [time.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TIME (3)

//*****************************************************************************
// �^�C���N���X
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime(int nPriority = 5);					// �f�t�H���g�R���X�g���N�^
	~CTime();									// �f�X�g���N�^

	// �����o�֐�
	static CTime *Create(D3DXVECTOR3 pos);		// ��������

	HRESULT Init(D3DXVECTOR3 pos);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	void SetTime(int nScore);					// �X�R�A�̐ݒ菈��
	void AddTime(int nValue);					// �X�R�A�̉��Z����
	int GetTime(void);							// �X�R�A�̎擾����

private:
	// �����o�ϐ�
	CNumber *m_apNumber[MAX_TIME];				// �X�R�A�̃|�C���^�z��
	int m_nTime;								// �^�C��
	int m_nCntTimer;							// �^�C�}�[�̃J�E���g
	D3DXVECTOR2 m_size;							// �T�C�Y
	bool m_bUse;								// �g�p
};

#endif // !_SCORE_H_