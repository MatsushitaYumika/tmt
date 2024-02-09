//=========================================================
//�V���[�e�B���O�Q�[��[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�C���N���[�h
//=====================================
#include <stdio.h>
#include <string.h>
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "player.h"	//�v���C���[�̐錾�̕�����
#include "input.h"	//�L�[�{�[�h�̐錾�̕�����
#include "game.h"	//�Q�[����ʂ̐錾�̕�����
#include "camera.h"
#include "light.h"
#include "field.h"
#include "wall.h"
#include "time.h"
#include "fade.h"
#include "pause.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_TEXT	(8192)	//�����̍ő吔
#define MAX_MODEL	(128)	//�G�̍ő吔

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureGame = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffGame = NULL;	//���_�o�b�t�@�ւ̃|�C���^
bool g_bPause = false;	//�|�[�Y�����ǂ���
bool g_Pause = false;	// �|�[�Y�t���O�𖳂���

//=====================================
//�Q�[����ʂ̏���������
//=====================================
void InitGame(void)
{
	g_Pause = false;	// �|�[�Y�t���O�𖳂���

	InitCamera();

	InitLight();

	InitField();

	InitWall();

	//InitMeshfield();

	InitPlayer();
	InitPause();

	bool g_bPause = false;	//�|�[�Y����
}

//=====================================
//�Q�[����ʂ̏I������
//=====================================
void UninitGame(void)
{
	UninitLight();

	UninitCamera();

	UninitField();

	UninitWall();

	UninitPlayer();
	UninitPause();
}

//=====================================
//�Q�[����ʂ̍X�V����
//=====================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_Pause = !g_Pause;
	}

	if (g_Pause)
	{ // �|�[�Y���̂�

		/*---�y������UI�̏����z---*/
		UpdatePause();



		return;	// �ȉ��̏����͍s��Ȃ�
	}

		UpdateLight();

		UpdateCamera();

		UpdateField();

		UpdateWall();

		UpdatePlayer();
}

//=====================================
//�Q�[����ʂ̕`�揈��
//=====================================
void DrawGame(void)
{
	SetCamera();

	DrawField();

	DrawWall();

	DrawPlayer();

	if (g_Pause)
	{ // �|�[�Y���̂�
		DrawPause();
	}

}

