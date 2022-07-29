//=============================================================================
//
// �����L���O�N���X [rankingdata.h]
// Author : �쑺�@�D�l
//
//=============================================================================

#ifndef _RANKINGDATA_H_
#define _RANKINGDATA_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_RANKING (6)
#define RANKING_TEXT ("data/SAVEDATA/ranking.txt")
#define SCORE_TEXT ("data/SAVEDATA/newtime.txt")
#define NUMBER_WIDTH (42.0f)
#define NUMBER_HEIGHT (47.0f)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CTime;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CRankingData : public CScene
{
public:
	CRankingData(int nPriority = 4);// �R���X�g���N�^
	~CRankingData();				// �f�X�g���N�^

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	static CRankingData *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bFlag);	// ��������

private:
	int	m_nTime[MAX_RANKING];				// �X�R�A�i�[
	D3DXVECTOR3 m_size;						// �傫��
	D3DXVECTOR3 m_pos;						// �ʒu
	static CTime	*m_pTime[MAX_RANKING];	// �X�R�A�̃C���X�^���X
	CTime *m_pNowTime;					// ���݂̃X�R�A
	bool m_bFlag;							// ���j���[���Q�[�������񂾂��̔���

};

#endif //!_RANKINGDATA_H_