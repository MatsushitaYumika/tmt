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
#include "debugproc.h"
//#include "fade.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_POLYGON			(3)			//�|���S���̍ő吔
#define MAX_PL				(4)			//�v���C���[�̍ő�l��
#define Brightness_POLYGON	(51)		//�|���S���̖��邳
#define POLYGON_COL			(100)		//�|���S���̕s�����x(100)
#define POLYGON_MAXCOL		(255)		//�|���S���̕s�����x(255)
#define MA_WIDTH			(50.0f)		//���̃|���S���̉��̒���
#define MA_HEIGHT			(100.0f)	//���̃|���S���̏c�̒���
#define MD_WIDTH			(300.0f)	//�I���o�����̃|���S���̉��̒���
#define MD_HEIGHT			(200.0f)	//�I���o�����̃|���S���̏c�̒���
#define OI_WIDTH			(400.0f)	//������@�̃|���S���̏c�̒���
#define OI_HEIGHT			(700.0f)	//������@�̃|���S���̉��̒���

//=====================================
//�O���[�o���ϐ�
//=====================================

//�w�i(BackGround == BG)
LPDIRECT3DTEXTURE9	g_pTexturePauseBG = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//������@(OI == OperationInstructions)
LPDIRECT3DTEXTURE9	g_pTexturePauseOI = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseOI = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PauseOI g_pauseOI;										//������@�̃|���S���̍\����

//���(MA == MovingArrow)
LPDIRECT3DTEXTURE9	g_pTexturePauseMA = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseMA = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PauseMA g_pauseMA[MAX_POLYGON];							//���|���S���̍\����
int g_nCntChooseMA = 0;									//���̃|���S�������点��ׂ̃J�E���g
int g_Time = 0;											//���̃|���S�������炵�Ă������߂̃J�E���g
bool bg_MA = false;										//���̃|���S����h�炷���߂̃t���O

//�I���ł�����(MD == mode)
LPDIRECT3DTEXTURE9	g_pTexturePauseMD[MAX_POLYGON] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseMD = NULL;			//���_�o�b�t�@�ւ̃|�C���^
PauseMD g_pauseMD[MAX_POLYGON];								//Pause(�I���ł�����)�̃|���S���̍\����
int g_nCntChooseMD = 0;										//�I�����ꂽ�|���S�������点��ׂ̃J�E���g

//=====================================
//�w�i�̃|���S������������
//=====================================
void InitPauseBackGroundPolygon(void)
{
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
}

//=====================================
//������@�̃|���S������������
//=====================================
void InitPauseOperationInstructionsPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾

	g_pauseOI.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_pauseOI.bUse = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_menu.png",
		&g_pTexturePauseOI);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseOI,
		NULL);

	VERTEX_2D* pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseOI->Lock(0, 0, (void**)&pVtx, 0);

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
	SetPauseOperationInstructions(D3DXVECTOR3(1400.0f, 200.0f, 0.0f));

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseOI->Unlock();
}

//=====================================
//���[�h�I���̃|���S������������
//=====================================
void InitPauseModePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMD[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pauseMD[nCntPause].nType = 0;
		g_pauseMD[nCntPause].bUse = false;
		g_pauseMD[nCntPause].bColUse = false;
	}

	g_nCntChooseMD = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\retry.png",
		&g_pTexturePauseMD[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\continue.png",
		&g_pTexturePauseMD[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\end.png",
		&g_pTexturePauseMD[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMD,
		NULL);

	VERTEX_2D* pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMD->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
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
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPauseMode(D3DXVECTOR3((SCREEN_WIDTH / 3), (nCntPause * 300.0f) + 150.0f, 0.0f));
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMD->Unlock();
}

//=====================================
//�������̃|���S������������
//=====================================
void InitPauseMovingArrowPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_select.png",
		&g_pTexturePauseMA);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMA[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pauseMA[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pauseMA[nCntPause].nType = 0;
		g_pauseMA[nCntPause].bUse = false;
		g_pauseMA[nCntPause].bColUse = false;
	}

	g_nCntChooseMA = 0;
	g_Time = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMA,
		NULL);

	VERTEX_2D* pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMA->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
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
		pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);

		//�e�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//�z�u���Ă���Ƃ�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPauseMovingArrow(D3DXVECTOR3((SCREEN_WIDTH / 7), (nCntPause * 300.0f) + 210.0f, 0.0f));
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMA->Unlock();
}

//=====================================
//�w�i�̃|���S���̏I������
//=====================================
void UninitPauseBackGroundPolygon(void)
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
}

//=====================================
//������@�̃|���S���̏I������
//=====================================
void UninitPauseOperationInstructionsPolygon(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseOI != NULL)
	{
		g_pTexturePauseOI->Release();
		g_pTexturePauseOI = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseOI != NULL)
	{
		g_pVtxBuffPauseOI->Release();
		g_pVtxBuffPauseOI = NULL;
	}
}

//=====================================
//���[�h�I���̃|���S���̏I������
//=====================================
void UninitPauseModePolygon(void)
{
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePauseMD[nCntPause] != NULL)
		{
			g_pTexturePauseMD[nCntPause]->Release();
			g_pTexturePauseMD[nCntPause] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseMD != NULL)
	{
		g_pVtxBuffPauseMD->Release();
		g_pVtxBuffPauseMD = NULL;
	}
}

//=====================================
//�������̏I������
//=====================================
void UninitPauseMovingArrowPolygon(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseMA != NULL)
	{
		g_pTexturePauseMA->Release();
		g_pTexturePauseMA = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseMA != NULL)
	{
		g_pVtxBuffPauseMA->Release();
		g_pVtxBuffPauseMA = NULL;
	}
}

//=====================================
//�w�i�̃|���S���X�V����(��)
//=====================================
void UpdatePauseBackGroundPolygon(void)
{

}

//=====================================
//������@�̃|���S���X�V����(��)
//=====================================
void UpdatePauseOperationInstructionsPolygon(void)
{

}

//=====================================
//���[�h�I���̃|���S���X�V����
//=====================================
void UpdatePauseModePolygon(void)
{
	VERTEX_2D* pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMD->Lock(0, 0, (void**)&pVtx, 0);

	//�I���o����|���S���̍\���̂̃t���O��S��false�ɂ���
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMD[nCntPause].bColUse = false;
	}

	//���L�[�����ꂽ��
	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP, 0) == true)
	{
		g_nCntChooseMD--;		//�J�E���g���}�C�i�X����(��ɐi��)
		g_nCntChooseMA--;	//��L�Ɠ���(������͖��̂���)
	}

	//���L�[�����ꂽ��
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN, 0) == true)
	{
		g_nCntChooseMD++;		//�J�E���g���v���X����(���ɐi��)
		g_nCntChooseMA++;	//��L�Ɠ���(������͖��̂���)
	}

	//�����J�E���g���g�p����Ă���|���S���������}�C�i�X�l�ɂȂ��Ă��܂�����
	if (g_nCntChooseMD <= -1)
	{
		g_nCntChooseMD = 2;	//�����I�ɃJ�E���g��2�ɂ���(retry����end�ɂƂ΂�)
		g_nCntChooseMA = 2;	//��L�Ɠ���(������͖��̂���)
	}

	//�����J�E���g���g�p����Ă���|���S���������v���X�l�ɂȂ��Ă��܂�����
	if (g_nCntChooseMD >= 3)
	{
		g_nCntChooseMD = 0;	//�����I�ɃJ�E���g��0�ɂ���(end����retry�ɂƂ΂�)
		g_nCntChooseMA = 0;	//��L�Ɠ���(������͖��̂���)
	}

	//�I�΂ꂽ�J�E���g�̒l�̃t���O��true�ɂ���
	g_pauseMD[g_nCntChooseMD].bColUse = true;		//�I���o����|���S��

	//�I���ł���|���S���̐����񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�����I�΂ꂽ�|���S���̃t���O��false�̏ꍇ
		if (g_pauseMD[nCntPause].bColUse == false)
		{//�s�����x��Ⴍ����
			//���_�J���[�̐ݒ�(false��)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		}

		//�����I�΂ꂽ�|���S���̃t���O��true�̏ꍇ
		if (g_pauseMD[nCntPause].bColUse == true)
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
	for (int nCntPause = 0; nCntPause < MAX_PL; nCntPause++)	//�^�C�g���őI�������Q���l����Ԃ����̂�MAX_PL�̂Ƃ��ɂ���Ă�������
	{
		//�����|���S����0�Ԃ��I�΂ꂽ�ꍇ
		if (g_pauseMD[0].bColUse == true)
		{
			//��L�𓥂܂��������ł���A�{�^�����������ꍇ
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// �Q�[����ʂɖ߂鏈�����Ă�������
				//SetFade(MODE_GAME);
			}
		}

		//�����|���S����1�Ԃ��I�΂ꂽ�ꍇ
		if (g_pauseMD[1].bColUse == true)
		{
			//��L�𓥂܂��������ł���A�{�^�����������ꍇ
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// �`���[�g���A����ʂɖ߂鏈�����Ă�������
				//SetFade(MODE_TUTORIAL);
			}
		}

		//�����|���S����2�Ԃ��I�΂ꂽ�ꍇ
		if (g_pauseMD[2].bColUse == true)
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
	g_pVtxBuffPauseMD->Unlock();
}

//=====================================
//�������̃|���S���X�V����
//=====================================
void UpdatePauseMovingArrowPolygon(void)
{
	VERTEX_2D* pVtx;		//���_���ւ̃|�C���^

	g_Time++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMA->Lock(0, 0, (void**)&pVtx, 0);

	//���̃|���S���̍\���̂̃t���O��false�ɂ���
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMA[nCntPause].bColUse = false;
	}

	//�I�΂ꂽ�J�E���g�̒l�̃t���O��true�ɂ���
	g_pauseMA[g_nCntChooseMA].bColUse = true;		//���̃|���S��

	//���̃|���S���̐����񂵂Ă܂�
	for (int nCntPauseSL = 0; nCntPauseSL < MAX_POLYGON; nCntPauseSL++)
	{
		//�����I�΂ꂽ�|���S���̃t���O��false�̏ꍇ
		if (g_pauseMA[nCntPauseSL].bColUse == false)
		{//�s�����x��Ⴍ����
			//���_�J���[�̐ݒ�(false��)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
		}

		//�����I�΂ꂽ�|���S���̃t���O��true�̏ꍇ
		if (g_pauseMA[nCntPauseSL].bColUse == true)
		{//�s�����x����������
			//���_�J���[�̐ݒ�(true��)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		}

		if (g_Time % 60 == 0)
		{
			bg_MA = bg_MA ? false : true;
		}

		if (bg_MA == true)
		{
			g_pauseMA[nCntPauseSL].move.x = 1.0f;
		}
		if (bg_MA == false)
		{
			g_pauseMA[nCntPauseSL].move.x = -1.0f;
		}

		g_pauseMA[nCntPauseSL].pos += g_pauseMA[nCntPauseSL].move;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x - MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x + MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x - MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y + MA_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x + MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y + MA_HEIGHT, 0.0f);


		pVtx += 4;			//������
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMA->Unlock();
}

//=====================================
//�w�i�̃|���S���̕`�揈��
//=====================================
void DrawPauseBackGroundPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//������@�̃|���S���̕`�揈��
//=====================================
void DrawPauseOperationInstructionsPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseOI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseOI);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//���[�h�I���̃|���S���̕`�揈��
//=====================================
void DrawPauseModePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMD, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�I���ł���|���S���̍ő吔���񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseMD[nCntPause]);		//�e�N�X�`���O������܂�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);		//�|���S���O������܂�
	}
}

//=====================================
//�������̃|���S���̕`�揈��
//=====================================
void DrawPauseMovingArrowPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMA, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�I���ł���|���S���̍ő吔���񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseMA);		//�e�N�X�`��1������܂�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);		//�|���S���O������܂�
	}
}

//=====================================
//���[�h�I���̃|���S���̐ݒ菈��
//=====================================
void SetPauseMode(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMD->Lock(0, 0, (void**)&pVtx, 0);

	//�I���ł���|���S���̍ő吔���񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		if (g_pauseMD[nCntPause].bUse == false)
		{
			g_pauseMD[nCntPause].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x - MD_WIDTH, g_pauseMD[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x + MD_WIDTH, g_pauseMD[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x - MD_WIDTH, g_pauseMD[nCntPause].pos.y + MD_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x + MD_WIDTH, g_pauseMD[nCntPause].pos.y + MD_HEIGHT, 0.0f);

			g_pauseMD[nCntPause].bUse = true;
			g_pauseMD[nCntPause].bColUse = false;

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMD->Unlock();
}

//=====================================
//������@�̃|���S���̐ݒ菈��
//=====================================
void SetPauseOperationInstructions(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseOI->Lock(0, 0, (void**)&pVtx, 0);

	if (g_pauseOI.bUse == false)
	{
		g_pauseOI.pos = pos;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_pauseOI.pos.x - OI_WIDTH, g_pauseOI.pos.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_pauseOI.pos.x + OI_WIDTH, g_pauseOI.pos.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_pauseOI.pos.x - OI_WIDTH, g_pauseOI.pos.y + OI_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_pauseOI.pos.x + OI_WIDTH, g_pauseOI.pos.y + OI_HEIGHT, 0.0f);

		g_pauseOI.bUse = true;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseOI->Unlock();
}

//=====================================
//�������̃|���S���̐ݒ菈��
//=====================================
void SetPauseMovingArrow(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMA->Lock(0, 0, (void**)&pVtx, 0);

	//�I���ł���|���S���̍ő吔���񂵂Ă܂�
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		if (g_pauseMA[nCntPause].bUse == false)
		{
			g_pauseMA[nCntPause].pos = pos;
			g_pauseMA[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x - MA_WIDTH, g_pauseMA[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x + MA_WIDTH, g_pauseMA[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x - MA_WIDTH, g_pauseMA[nCntPause].pos.y + MA_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x + MA_WIDTH, g_pauseMA[nCntPause].pos.y + MA_HEIGHT, 0.0f);

			g_pauseMA[nCntPause].bUse = true;
			g_pauseMA[nCntPause].bColUse = false;

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMA->Unlock();
}

//=====================================
//��������Ă�Init�̏���
//=====================================
void InitPause(void)
{
	InitPauseBackGroundPolygon();
	InitPauseOperationInstructionsPolygon();
	InitPauseModePolygon();
	InitPauseMovingArrowPolygon();
}

//=====================================
//��������Ă�Uninit�̏���
//=====================================
void UninitPause(void)
{
	UninitPauseBackGroundPolygon();
	UninitPauseOperationInstructionsPolygon();
	UninitPauseModePolygon();
	UninitPauseMovingArrowPolygon();
}

//=====================================
//��������Ă�Update�̏���
//=====================================
void UpdatePause(void)
{
	UpdatePauseBackGroundPolygon();
	UpdatePauseOperationInstructionsPolygon();
	UpdatePauseModePolygon();
	UpdatePauseMovingArrowPolygon();
}

//=====================================
//��������Ă�Draw�̏���
//=====================================
void DrawPause(void)
{
	DrawPauseBackGroundPolygon();
	DrawPauseOperationInstructionsPolygon();
	DrawPauseModePolygon();
	DrawPauseMovingArrowPolygon();
}