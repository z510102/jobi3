//=============================================================================
//
// ���Ԍo�߂̃N���X [time.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene.h"
#include "manager.h"
//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_TIME (3)			// �����̃P�^��
#define SPACE_TIME (56)			// �����̊Ԋu
#define REDUCE_TIME (1000)		// ���b�Ń^�C�����炷��
#define TIMEUP_WIDTH (500.0f)	// �^�C���A�b�v�\���̕�
#define TIMEUP_HEIGHT (100.0f)	// �^�C���A�b�v�\���̍���
#define INTERVAL_TIME (100)		// �^�C���A�b�v�\�����o�Ă����ʑJ�ڂ܂ł̎���

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime(int nPriority = PRIORITY_UI);// �R���X�g���N�^
	~CTime();				 // �f�X�g���N�^

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void AddTime(int nValue);	//���Ԃ̉��Z
	int GetTime(void);			//���Ԃ̎擾
	void SetTime(int nTime);

								//���Ԃ̐���
	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time, bool bStop);

private:
	CNumber		*m_apNumber[MAX_TIME];// �����̃C���X�^���X
	int			m_nTime;			  // ����
	int			m_IntervalTime;		  // �^�C���A�b�v��̊�
	D3DXVECTOR3 m_size;				  // �傫��
	D3DXVECTOR3 m_pos;				  // �ʒu
	D3DXCOLOR	m_col;				  // �F
	bool		m_fade;				  // �t�F�[�h����
	bool		m_bStop;			  // ���U���g�̂Ƃ��͎��Ԓ�~
	bool		m_bflag;			  // �^�C���A�b�v����������o�������Ȃ��p
	DWORD		m_dwCurrentTime;	  // �o�ߎ���
	DWORD		m_dwExecLastTime;	  // ���݂̎���
	CManager::MODE			m_mode;

};

#endif // !_TIME_H_
