//=========================================================
//�V���[�e�B���O�Q�[��[tutorial.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "tutorial.h"	//�^�C�g����ʂ̐錾�̕�����
#include "input.h"	//�L�[�{�[�h�̐錾�̕�����
#include "fade.h"

//=====================================
//�}�N����`
//=====================================
#define FEED_SPEED	(5)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureTutorial[2] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTutorial = NULL;	//���_�o�b�t�@�ւ̃|�C���^
bool bTutorialFeedOut = false;
int g_nCntTutorial;

//=====================================
//����������
//=====================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial000.png",
		&g_pTextureTutorial[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial001.png",
		&g_pTextureTutorial[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	g_nCntTutorial = 0;
	bTutorialFeedOut = false;

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

//=====================================
//�I������
//=====================================
void UninitTutorial(void)
{
	for (int nCntTutorial = 0; nCntTutorial < 2; nCntTutorial++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTutorial[nCntTutorial] != NULL)
		{
			g_pTextureTutorial[nCntTutorial]->Release();
			g_pTextureTutorial[nCntTutorial] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}


}

//=====================================
//�X�V����
//=====================================
void UpdateTutorial(void)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	int fadecol = GetFadeColor();

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RIGHT) == true )
	{
		g_nCntTutorial = 1;
	}
	if (GetKeyboardTrigger(DIK_LEFT) == true )
	{
		g_nCntTutorial = 0;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && fadecol <= 0)
	{
		/*bTutorialFeedOut = true;*/
		SetFade(MODE_GAME);
	}
	/*if (bTutorialFeedOut == true)
	{
		g_nCntTutorial -= FEED_SPEED;
	}
	if(bTutorialFeedOut == false)
	{
		g_nCntTutorial += FEED_SPEED;
	}
	if (g_nCntTutorial >= 255)
	{
		g_nCntTutorial = 255;
	}*/
	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);
	//pVtx[1].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);
	//pVtx[2].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);
	//pVtx[3].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffTutorial->Unlock();

	//if (g_nCntTutorial <= 0)
	//{
	//	//���[�h�ݒ�(�Q�[����ʂɈڍs)
	//	SetMode(MODE_GAME);
	//}
}

//=====================================
//�`�揈��
//=====================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_nCntTutorial == 0)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[0]);
	}
	if (g_nCntTutorial == 1)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[1]);
	}
	

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}