//=========================================================
//DirectX�ł�8�����ړ�����[camera.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�}�N����`
//=====================================
#ifndef _CAMERA_H_	//���̃}�N����`������ĂȂ�������
#define _CAMERA_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//=====================================
//�C���N���[�h
//=====================================
#include "main.h"

//=====================================
//�J�����\���̂��`
//=====================================
typedef struct
{
	D3DXVECTOR3 posV;	//���_
	D3DXVECTOR3 posR;	//�����_
	D3DXVECTOR3 vecU;	//������x�N�g��
	D3DXVECTOR3 move;	//�ړ�
	D3DXVECTOR3 rot;	//��]
	float fDistance;	//����
	bool bUsePosV;
	bool bUsePosR;
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;	//�r���[�}�g���b�N�X
}Camera;

//=====================================
//�v���g�^�C�v�錾(����)
//=====================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera* GetCamera(void);
#endif
