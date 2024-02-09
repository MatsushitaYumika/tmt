//=========================================================
//�V���[�e�B���O�Q�[��[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "fade.h"	//�^�C�g����ʂ̐錾�̕�����
#include "input.h"	//�L�[�{�[�h�̐錾�̕�����

//=====================================
//�}�N����`
//=====================================
#define FADE_SPEED	(5)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureFade = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^
int g_colorfade;
FADE g_fade/* = FADE_IN*/;	//���݂̃��[�h
MODE g_modeNext/* = MODE_NEXT*/;

//=====================================
//�^�C�g����ʂ̏���������
//=====================================
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_fade = FADE_IN;
	g_colorfade = 0;
	

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\atamagaokasii.png",
	//	&g_pTextureTitle);

	//g_colorfade.nLife = 1.0f;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);

	//�e�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//=====================================
//�^�C�g����ʂ̏I������
//=====================================
void UninitFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=====================================
//�^�C�g����ʂ̍X�V����
//=====================================
void UpdateFade(void)
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C��
			g_colorfade -= FADE_SPEED;	//�|���S���𓧖��ɂ��Ă���

			if (g_colorfade <= 0)
			{
				g_colorfade = 0;
				g_fade = FADE_NONE;	//�������ĂȂ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g
			g_colorfade += FADE_SPEED;	//�|���S����s������

			if (g_colorfade >= 255)
			{
				g_colorfade = 255;
				g_fade = FADE_IN;	//�t�F�[�h�C��
				//���[�h�ݒ�(���̉�ʂɈڍs)
				SetMode(g_modeNext);
			}
		}
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//=====================================
//�`�揈��
//=====================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//���[�h�̐ݒ�
//=====================================
void SetFade(MODE ModeNext)
{
	g_modeNext = ModeNext;
	g_fade = FADE_OUT;
}

int GetFadeColor(void)
{
	return g_colorfade;
}

FADE GetFade(void)
{
	return g_fade;
}