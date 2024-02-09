//=========================================================
//DirectX�ł̐}�`�`��+��[Wall.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "wall.h"
//#include "Wall1.h"
//#include "player.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_WALL	(4)
#define MAX_CNT	(4)
#define MAX_SIZE	(400.0f)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPD3DXMESH g_pMeshWall[MAX_WALL] = {};	//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatWall[MAX_WALL] = {};	//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatWall[MAX_WALL] = {};	//�}�e���A���̐�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;	//�e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posWall;	//�ʒu
//D3DXVECTOR3 g_rotWall;	//����
Wall g_wall[MAX_WALL];
D3DXMATRIX g_mtxWorldWall;	//���[���h�}�g���b�N�X
//int g_x = 0;
//int g_y = 0;

//=====================================
//�|���S���̏���������
//=====================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].bUse = false;
	}

	/*g_rotWall.x += sinf(-D3DX_PI * 0.0f);
	g_rotWall.y += cosf(-D3DX_PI * 1.0f);*/

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++/*,pVtx++*/)
	{
		//==========================================
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE, MAX_SIZE,0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_SIZE, MAX_SIZE,0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_SIZE,0.0f,0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_SIZE,0.0f,0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);


		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	SetWall(D3DXVECTOR3(0.0f, 0.0f, MAX_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(-MAX_SIZE, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
	SetWall(D3DXVECTOR3(MAX_SIZE, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -MAX_SIZE), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

}

//=====================================
//�|���S���̏I������
//=====================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=====================================
//�|���S���̍X�V����
//=====================================
void UpdateWall()
{

}

//=====================================
//�|���S���̕`�揈��
//=====================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldWall);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCntWall].rot.y, g_wall[nCntWall].rot.x, g_wall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, g_wall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}

//=====================================
//�ݒ菈��
//=====================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_wall[nCntWall].bUse == false)
		{
			g_wall[nCntWall].pos = pos;
			g_wall[nCntWall].rot = rot;
			g_wall[nCntWall].bUse = true;
			
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}