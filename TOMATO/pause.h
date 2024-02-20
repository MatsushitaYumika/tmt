//=========================================================
//�|�[�Y�̏����E�w�b�_�t�@�C��[pause.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�}�N����`
//=====================================
#ifndef _PAUSE_H_	//���̃}�N����`������ĂȂ�������
#define _PAUSE_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//=====================================
//�C���N���[�h
//=====================================
#include "main.h"

//=====================================
//�|�[�Y��ʂ̃��[�h�I��(MD == Mode)�|���S���̍\����
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//����(����)
	int nType;			//���[�h�̎��
	bool bUse;			//�g�p�̗L��
	bool bColUse;		//�|���S���̃J���[�̗L��
}PauseMD;

//=====================================
//�|�[�Y��ʂ̑�����@(OI == OperationInstructions)�|���S���̍\����
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//����(����)
	bool bUse;			//�g�p�̗L��
}PauseOI;

//=====================================
//�|�[�Y��ʂ̖��(MA == MovingArrow)�|���S���̍\����
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu(����)
	D3DXVECTOR3 move;	//����(����)
	int nType;			//���[�h�̎��
	bool bUse;			//�g�p�̗L��
	bool bColUse;		//�|���S���̃J���[�̗L��
}PauseMA;

//=====================================
//�}�N����`
//=====================================


//=====================================
//�v���g�^�C�v�錾(����)
//=====================================
void InitPauseBackGroundPolygon(void);					//�w�i�̃|���S���̏���������
void InitPauseOperationInstructionsPolygon(void);		//������@�̃|���S���̏���������
void InitPauseModePolygon(void);						//���[�h�I���̃|���S���̏���������
void InitPauseMovingArrowPolygon(void);					//�������̃|���S���̏���������
void UninitPauseBackGroundPolygon(void);				//�w�i�̃|���S���̏I������
void UninitPauseOperationInstructionsPolygon(void);		//������@�̃|���S���̏I������
void UninitPauseModePolygon(void);						//���[�h�I���̃|���S���̏I������
void UninitPauseMovingArrowPolygon(void);				//�������̃|���S���̏I������
void UpdatePauseBackGroundPolygon(void);				//�w�i�̃|���S���̍X�V����
void UpdatePauseOperationInstructionsPolygon(void);		//������@�̃|���S���̍X�V����
void UpdatePauseModePolygon(void);						//���[�h�I���̃|���S���̍X�V����
void UpdatePauseMovingArrowPolygon(void);				//�������̃|���S���̍X�V����
void DrawPauseBackGroundPolygon(void);					//�w�i�̃|���S���̕`�揈��
void DrawPauseOperationInstructionsPolygon(void);		//������@�̃|���S���̕`�揈��
void DrawPauseModePolygon(void);						//���[�h�I���̃|���S���̕`�揈��
void DrawPauseMovingArrowPolygon(void);					//�������̃|���S���̕`�揈��
void SetPauseMode(D3DXVECTOR3 pos);						//���[�h�I���̃|���S���̐ݒu����
void SetPauseOperationInstructions(D3DXVECTOR3 pos);	//������@�̃|���S���̐ݒu����
void SetPauseMovingArrow(D3DXVECTOR3 pos);				//�������̃|���S���̐ݒu����
void InitPause(void);									//��������Ă�Init�̏���
void UninitPause(void);									//��������Ă�Uninit�̏���
void UpdatePause(void);									//��������Ă�Update�̏���
void DrawPause(void);									//��������Ă�Draw�̏���

#endif