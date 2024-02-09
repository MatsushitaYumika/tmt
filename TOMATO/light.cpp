//=========================================================
//[light.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "light.h"
//#include "Light1.h"
//#include "player.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_LIGHT	(3)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLight = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureLight = NULL;	//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posLight;	//�ʒu
D3DXVECTOR3 g_rotLight;	//����
D3DXMATRIX g_mtxWorldLight;	//���[���h�}�g���b�N�X
D3DLIGHT9 g_light[MAX_LIGHT];	//���C�g�̏��


//=====================================
//�|���S���̏���������
//=====================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];	//�ݒ�p�����x�N�g��

	//���C�g�̏����N���A�ɂ���
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		//���C�g�̎�ނ�ݒ�
		g_light[nCntlight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		g_light[nCntlight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		vecDir[1] = D3DXVECTOR3(-0.5f, -0.2f, -0.4f);
		vecDir[2] = D3DXVECTOR3(0.8f, 0.9f, 0.5f);

		D3DXVec3Normalize(&vecDir[nCntlight], &vecDir[nCntlight]);
	
		g_light[nCntlight].Direction = vecDir[nCntlight];	//�x�N�g���𐳋K������

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntlight, &g_light[nCntlight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntlight, TRUE);
	}
}

//=====================================
//�|���S���̏I������
//=====================================
void UninitLight(void)
{

}

//=====================================
//�|���S���̍X�V����
//=====================================
void UpdateLight()
{

}
