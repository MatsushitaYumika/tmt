//=========================================================
//�V���[�e�B���O�Q�[��[pause.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "input.h"	//�L�[�{�[�h�̐錾�̕�����
#include "Pause.h"	//�Q�[����ʂ̐錾�̕�����
#include "fade.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_POLYGON	(3)	//�|���S���̍ő吔
#define POLYGON_WIDTH	(150.0f)	//�|���S���̉��̒���
#define POLYGON_HEIGHT	(100.0f)	//�|���S���̏c�̒���
#define Brightness_POLYGON	(51)	//�|���S���̖��邳
#define POLYGON_COL (255)			//�|���S���̃J���[

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DTEXTURE9	g_pTexturePauseBG = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTexturePause[MAX_POLYGON] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPause = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Pause g_pause[MAX_POLYGON];
int nCntPauseCol = 100;
int g_nCntChoose = 0;

//=====================================
//����������
//=====================================
void InitPause(void)
{
	int nCntPause = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause.png",
		&g_pTexturePauseBG);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//==========================================
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);

	//�e�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseBG->Unlock();

	//==========================================================================================

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pause[nCntPause].nType = 0;
		g_pause[nCntPause].bUse = false;
		g_pause[nCntPause].bColUse = false;
	}

	nCntPauseCol = 100;
	g_nCntChoose = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\retry.png",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\continue.png",
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\end.png",
		&g_pTexturePause[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//==========================================
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);

		//�e�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPause(D3DXVECTOR3((SCREEN_WIDTH / 4), (nCntPause * 200.0f) + 100.0f, 0.0f));
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//=====================================
//�I������
//=====================================
void UninitPause(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}

	//==================================================================================

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=====================================
//�X�V����
//=====================================
void UpdatePause(void)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].bColUse = false;
	}

	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP,0) == true)
	{
		g_nCntChoose--;
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN,0) == true)
	{
		g_nCntChoose++;
	}
	if (g_nCntChoose <= -1)
	{
		g_nCntChoose = 2;
	}
	if (g_nCntChoose >= 3)
	{
		g_nCntChoose = 0;
	}

	g_pause[g_nCntChoose].bColUse = true;

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		if (g_pause[nCntPause].bColUse == false)
		{
			//���_�J���[�̐ݒ�(false��)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		}
		if (g_pause[nCntPause].bColUse == true)
		{
			//���_�J���[�̐ݒ�(true��)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
		}

		pVtx += 4;
	}

	if (g_pause[0].bColUse == true)
	{
		if (GetJoypadTrigger(JOYKEY_A,0) == true)
		{
			SetFade(MODE_GAME);
		}
	}
	if (g_pause[1].bColUse == true)
	{
		if (GetJoypadTrigger(JOYKEY_A,0) == true)
		{
			SetFade(MODE_TUTORIAL);
		}
	}
	if (g_pause[2].bColUse == true)
	{
		if (GetJoypadTrigger(JOYKEY_A,0) == true)
		{
			SetFade(MODE_TITLE);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//=====================================
//�`�揈��
//=====================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//==============================================================================================

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}

//=====================================
//�ݒ菈��
//=====================================
void SetPause(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		if (g_pause[nCntPause].bUse == false)
		{
			g_pause[nCntPause].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - POLYGON_WIDTH, g_pause[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + POLYGON_WIDTH, g_pause[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - POLYGON_WIDTH, g_pause[nCntPause].pos.y + POLYGON_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + POLYGON_WIDTH, g_pause[nCntPause].pos.y + POLYGON_HEIGHT, 0.0f);

			g_pause[nCntPause].bUse = true;
			g_pause[nCntPause].bColUse = false;

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}