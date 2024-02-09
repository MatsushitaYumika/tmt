//=========================================================
//2D�A�N�V����[main.h]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�}�N����`
//=====================================
#ifndef _MAIN_H_	//���̃}�N����`������ĂȂ�������
#define _MAIN_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//=====================================
//�C���N���[�h
//=====================================
#include<Windows.h>
#include"d3dx9.h"	//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION	(0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include"dinput.h"	//���͏����ɕK�v
#include "dinput.h"	//���͏����ɕK�v
#include "Xinput.h"	//�W���C�p�b�g�����ɕK�v
#include "xaudio2.h"	//�T�E���h�����ɕK�v

//=====================================
//��ʃ��[�h�̎��
//=====================================
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_TUTORIAL,	//�`���[�g���A�����
	MODE_GAME,	//�Q�[�����
	//MODE_RESULT,	//���U���g���
	//MODE_RANKING,	//�����L���O���
	MODE_NEXT,
	MODE_MAX
}MODE;

//=====================================
//�v���g�^�C�v�錾
//=====================================
LPDIRECT3DDEVICE9	GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

//=====================================
//���C�u�����̃����N
//=====================================
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//�W���C�p�b�g�����ɕK�v

//=====================================
//�}�N����`
//=====================================
#define SCREEN_WIDTH	(1280)	//�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720)	//�E�B���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���_�t�H�[�}�b�g(���_���W[2D]/���_�J���[)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���_�t�H�[�}�b�g(���_���W[3D]/���_�J���[)

//=====================================
//���_���W[3D]�̍\���̂��`
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;	//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//=====================================
//���_���W[3D]�̍\���̂��`
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@��
	//float rhw;	//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

#endif