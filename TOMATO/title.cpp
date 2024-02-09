//=========================================================
//�V���[�e�B���O�Q�[��[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "title.h"	//�^�C�g����ʂ̐錾�̕�����
#include "input.h"	//�L�[�{�[�h�̐錾�̕�����
#include "fade.h"

//=====================================
//�}�N����`
//=====================================
#define FEED_SPEED	(5)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureTitle = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTitle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
bool bTitleFeedOut = false;
int g_nCntTitle;

//=====================================
//�^�C�g����ʂ̏���������
//=====================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	g_nCntTitle = 0;
	bTitleFeedOut = false;

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//�e�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//=====================================
//�^�C�g����ʂ̏I������
//=====================================
void UninitTitle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=====================================
//�^�C�g����ʂ̍X�V����
//=====================================
void UpdateTitle(void)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	int fadecol = GetFadeColor();

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RETURN) == true && fadecol <= 0)
	{
		//bTitleFeedOut = true;
		SetFade(MODE_TUTORIAL);
	}
	/*if (bTitleFeedOut == true)
	{
		g_nCntTitle -= FEED_SPEED;
	}
	if(bTitleFeedOut == false)
	{
		g_nCntTitle += FEED_SPEED;
	}
	if (g_nCntTitle >= 255)
	{
		g_nCntTitle = 255;
	}*/
	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);
	//pVtx[1].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);
	//pVtx[2].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);
	//pVtx[3].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffTitle->Unlock();

	//if (g_nCntTitle <= 0)
	//{
	//	//���[�h�ݒ�(�Q�[����ʂɈڍs)
	//	SetMode(MODE_GAME);
	//}
}

//=====================================
//�`�揈��
//=====================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
	
}