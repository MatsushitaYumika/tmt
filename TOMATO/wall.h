//=========================================================
//DirectX�ł̐}�`�`��+��[Wall.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�}�N����`
//=====================================
#ifndef _WALL_H_	//���̃}�N����`������Ă��Ȃ�������
#define _WALL_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//=====================================
//�C���N���[�h
//=====================================
#include "main.h"

//=====================================
//�J�����\���̂��`
//=====================================
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;	//
	D3DXVECTOR3 rot;	//
	D3DXVECTOR3 vtxMin;	//�����蔻��(Min�l)
	D3DXVECTOR3 vtxMax;	//�����蔻��(Max�l)
	BYTE* pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	int nNumVtx;	//���_��
	bool bUse;
	//D3DXVECTOR3 vecU;	//
}Wall;

//=====================================
//�v���g�^�C�v�錾(����)
//=====================================
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif