//=========================================================
//tmt[pause.cpp]
//Author:Yumika Matsushita
//=========================================================

//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "input.h"	//�L�[�{�[�h�̐錾�̕�����
#include "Pause.h"	//�Q�[����ʂ̐錾�̕�����
#include "player.h"
//#include "fade.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_POLYGON			(3)			//�|���S���̍ő吔
#define POLYGON_WIDTH		(150.0f)	//�I���o�����̃|���S���̉��̒���
#define POLYGON_HEIGHT		(100.0f)	//�I���o�����̃|���S���̏c�̒���
#define Brightness_POLYGON	(51)		//�|���S���̖��邳
#define POLYGON_MAXCOL		(255)		//�|���S���̕s�����x(255)
#define POLYGON_COL			(100)		//�|���S���̕s�����x(100)
#define MNPOLYGON_WIDTH		(300.0f)	//������@�̃|���S���̏c�̒���
#define MNPOLYGON_HEIGHT	(400.0f)	//������@�̃|���S���̉��̒���
#define MAX_PL				(4)			//�v���C���[�̍ő�l��

//=====================================
//�O���[�o���ϐ�
//=====================================

//�w�i
LPDIRECT3DTEXTURE9	g_pTexturePauseBG = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//������@(MN = menu)
LPDIRECT3DTEXTURE9	g_pTexturePauseMN = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseMN = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PauseMN g_pauseMN;										//������@�̃|���S���̍\����

//�I���ł�����
LPDIRECT3DTEXTURE9	g_pTexturePause[MAX_POLYGON] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPause = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Pause g_pause[MAX_POLYGON];								//Pause(�I���ł�����)�̃|���S���̍\����
int g_nCntChoose = 0;									//�I�����ꂽ�|���S�������点��ׂ̃J�E���g

//=====================================
//����������
//=====================================
void InitPause(void)
{
//==========================================================================================
//�������玟�̋�؂�܂ł̓|�[�Y��ʂ̔w�i�̃|���S���̏���

	int nCntPause = 0;									//for���̃J�E���g�̏�����

	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾

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

	VERTEX_2D* pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);

	//�e�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseBG->Unlock();

//==========================================================================================
//�������牺�܂ł͑�����@�̃|���S���̏���

	g_pauseMN.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_pauseMN.bUse = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_menu.png",
		&g_pTexturePauseMN);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMN,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMN->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);

	//�e�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//������@�̃|���S���ݒu
	SetPauseMenu(D3DXVECTOR3(900.0f, 300.0f, 0.0f));

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMN->Unlock();

//==========================================================================================
//�������牺�܂ł͑I���o����|���S���̏���

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pause[nCntPause].nType = 0;
		g_pause[nCntPause].bUse = false;
		g_pause[nCntPause].bColUse = false;
	}

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
		pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);

		//�e�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//�z�u���Ă���Ƃ�
	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPause(D3DXVECTOR3((SCREEN_WIDTH / 4), (nCntPause * 200.0f) + 250.0f, 0.0f));
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//=====================================
//�I������
//=====================================
void UninitPause(void)
{
//==================================================================================
//��؂��Ă���Ƃ���܂Ŕw�i�̃|���S���̏��� 
	
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
//��؂��Ă���Ƃ���܂ő�����@�̃|���S���̏���

	//�e�N�X�`���̔j��
	if (g_pTexturePauseMN != NULL)
	{
		g_pTexturePauseMN->Release();
		g_pTexturePauseMN = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseMN != NULL)
	{
		g_pVtxBuffPauseMN->Release();
		g_pVtxBuffPauseMN = NULL;
	}

//==================================================================================
//�������牺�܂ł͑I���o����|���S���̏��� 

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
	VERTEX_2D* pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//�\���̂̃t���O��S��false�ɂ���
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].bColUse = false;
	}

	//���L�[�����ꂽ��
	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP,0) == true)
	{
		g_nCntChoose--;		//�J�E���g���}�C�i�X����(��ɐi��)
	}

	//���L�[�����ꂽ��
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN,0) == true)
	{
		g_nCntChoose++;		//�J�E���g���v���X����(���ɐi��)
	}

	//�����J�E���g���g�p����Ă���|���S���������}�C�i�X�l�ɂȂ��Ă��܂�����
	if (g_nCntChoose <= -1)
	{
		g_nCntChoose = 2;	//�����I�ɃJ�E���g��2�ɂ���(retry����end�ɂƂ΂�)
	}

	//�����J�E���g���g�p����Ă���|���S���������v���X�l�ɂȂ��Ă��܂�����
	if (g_nCntChoose >= 3)
	{
		g_nCntChoose = 0;	//�����I�ɃJ�E���g��0�ɂ���(end����retry�ɂƂ΂�)
	}

	//�I�΂ꂽ�J�E���g�̒l�̃t���O��true�ɂ���
	g_pause[g_nCntChoose].bColUse = true;

	//�|���S���̐����񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�����I�΂ꂽ�|���S���̃t���O��false�̏ꍇ
		if (g_pause[nCntPause].bColUse == false)
		{//�s�����x��Ⴍ����
			//���_�J���[�̐ݒ�(false��)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		}

		//�����I�΂ꂽ�|���S���̃t���O��true�̏ꍇ
		if (g_pause[nCntPause].bColUse == true)
		{//�s�����x����������
			//���_�J���[�̐ݒ�(true��)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		}

		pVtx += 4;			//������
	}

	//�v���C���[�̐��Ԃ�񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_PL; nCntPause++)
	{
		//�����|���S����0�Ԃ��I�΂ꂽ�ꍇ
		if (g_pause[0].bColUse == true)
		{
			//��L�𓥂܂��������ł���A�{�^�����������ꍇ
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// �Q�[����ʂɖ߂鏈�����Ă�������
				//SetFade(MODE_GAME);
			}
		}

		//�����|���S����1�Ԃ��I�΂ꂽ�ꍇ
		if (g_pause[1].bColUse == true)
		{
			//��L�𓥂܂��������ł���A�{�^�����������ꍇ
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// �`���[�g���A����ʂɖ߂鏈�����Ă�������
				//SetFade(MODE_TUTORIAL);
			}
		}

		//�����|���S����2�Ԃ��I�΂ꂽ�ꍇ
		if (g_pause[2].bColUse == true)
		{
			//��L�𓥂܂��������ł���A�{�^�����������ꍇ
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// �^�C�g����ʂɖ߂鏈�����Ă�������
				//SetFade(MODE_TITLE);
			}
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
//==============================================================================================
//�������牺�̋�؂�܂Ŕw�i�̏���

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

//==============================================================================================
//�������牺�܂ł͑I���o����|���S���̏���
	
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�I���ł���|���S���̍ő吔���񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);		//�e�N�X�`���O������܂�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);		//�|���S���O������܂�
	}

//==============================================================================================
//��؂��Ă���Ƃ���܂ő�����@�̃|���S���̏���

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMN, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseMN);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//�I���ł���|���S���̐ݒ菈��
//=====================================
void SetPause(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//�I���ł���|���S���̍ő吔���񂵂Ă܂�
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

//=====================================
//������@�̃|���S���̐ݒ菈��
//=====================================
void SetPauseMenu(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMN->Lock(0, 0, (void**)&pVtx, 0);

	if (g_pauseMN.bUse == false)
	{
		g_pauseMN.pos = pos;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_pauseMN.pos.x - MNPOLYGON_WIDTH, g_pauseMN.pos.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_pauseMN.pos.x + MNPOLYGON_WIDTH, g_pauseMN.pos.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_pauseMN.pos.x - MNPOLYGON_WIDTH, g_pauseMN.pos.y + MNPOLYGON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_pauseMN.pos.x + MNPOLYGON_WIDTH, g_pauseMN.pos.y + MNPOLYGON_HEIGHT, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMN->Unlock();
}