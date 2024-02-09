//=========================================================
//DirectX�ł̐}�`�`��+��[Field.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "field.h"
//#include "Field1.h"
//#include "player.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_Field	(2)
#define MAX_CNT	(4)
#define MAX_SIZE	(400.0f)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;	//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posField;	//�ʒu
D3DXVECTOR3 g_rotField;	//����
D3DXMATRIX g_mtxWorldField;	//���[���h�}�g���b�N�X
//int g_x = 0;
//int g_y = 0;

//=====================================
//�|���S���̏���������
//=====================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureField);

	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	VERTEX_3D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//==========================================
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE, 0.0f, MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(MAX_SIZE, 0.0f, MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-MAX_SIZE, 0.0f, -MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(MAX_SIZE, 0.0f, -MAX_SIZE);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffField->Unlock();

}

//=====================================
//�|���S���̏I������
//=====================================
void UninitField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=====================================
//�|���S���̍X�V����
//=====================================
void UpdateField()
{

}

//=====================================
//�|���S���̕`�揈��
//=====================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureField);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
