//=========================================================
//[camera.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "camera.h"
#include "input.h"
#include "player.h"
//#include "Camera1.h"
//#include "player.h"

//=====================================
//�}�N����`
//=====================================
#define CAMERA_WIDTH	(100)
#define CAMERA_HEIGHT	(100)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCamera = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCamera = NULL;	//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posCamera;	//�ʒu
D3DXVECTOR3 g_rotCamera;	//����
D3DXMATRIX g_mtxWorldCamera;	//���[���h�}�g���b�N�X
Camera g_camera;	//�J�����̏��
float g_fLengthCamera;	//�Ίp���̒���
float g_fAngleCamera;	//�Ίp���̊p�x


//=====================================
//�|���S���̏���������
//=====================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 250.0f, 0.0f);
	g_camera.posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = 270.0f;
	g_camera.bUsePosV = false;
	g_camera.bUsePosR = false;

	//�Ίp���̒������Z�o����
	g_fLengthCamera = sqrtf(CAMERA_WIDTH * CAMERA_WIDTH + CAMERA_HEIGHT * CAMERA_HEIGHT) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAngleCamera = atan2f(CAMERA_WIDTH, CAMERA_HEIGHT);
}

//=====================================
//�|���S���̏I������
//=====================================
void UninitCamera(void)
{
	
}

//=====================================
//�|���S���̍X�V����
//=====================================
void UpdateCamera()
{
	Player* pPlayer = GetPlayer();	//�v���C���[���̃|�C���^

	//�J�������s�ړ�(D�܂œ���)
	if (GetKeyboardPress(DIK_UP) == true)
	{//���L�[�������ꂽ
		g_camera.posV.y += 3.0f;
		g_camera.posR.y += 3.0f;

		//�ړ��ʂ��X�V
		/*g_player.move.x += sinf(D3DX_PI * 1.0) * 0.1f;*/
		/*g_player.move.y += cosf(D3DX_PI * 1.0) * MOVE_MAX_LONG;*/
	
		//if (GetKeyboardPress(DIK_A) == true || GetJoyPadPress(JOYKEY_LEFT) == true)
		//{//����ړ�
		//	g_camera.posV.y += 1.0f;
		//	g_camera.posR.y += 1.0f;

		//	//�ړ��ʂ��X�V
		//	/*g_player.move.x += sinf(-D3DX_PI * 0.75) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(-D3DX_PI * 0.75) * MOVE_MIN_LONG;*/
		//}
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//���L�[�������ꂽ
		g_camera.posV.x -= 3.0f;
		//g_camera.posR.x -= 3.0f;

		//�ړ��ʂ��X�V
		/*g_player.move.x += sinf(-D3DX_PI * 0.5) * MOVE_MAX_LONG;*/
		/*g_player.move.y += cosf(D3DX_PI * 1.0) * 5.0f;*/

		//if (GetKeyboardPress(DIK_S) == true || GetJoyPadPress(JOYKEY_DOWN) == true)
		//{//�����ړ�
		//	g_camera.posV.x += sinf(-D3DX_PI * 0.25f) * -2.5f;
		//	g_camera.posV.y += cosf(-D3DX_PI * 0.25f) * -2.5f;

		//	//�ړ��ʂ��X�V
		//	/*g_player.move.x += sinf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;*/
		//}
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//���L�[�������ꂽ
		g_camera.posV.y -= 3.0f;
		g_camera.posR.y -= 3.0f;

		//�ړ��ʂ��X�V
		//g_player.move.x += sinf(-D3DX_PI * 0.5) * 5.0f;
		//g_player.move.y += cosf(-D3DX_PI * 1.0) * MOVE_MINUS_MAX_LONG;

		//if (GetKeyboardPress(DIK_D) == true || GetJoyPadPress(JOYKEY_RIGHT) == true)
		//{//�E���ړ�
		//	g_camera.posV.x += sinf(D3DX_PI * 0.25f) * -2.5f;
		//	g_camera.posV.y += cosf(D3DX_PI * 0.25f) * -2.5f;

		//	//�ړ��ʂ��X�V
		//	/*g_player.move.x += sinf(D3DX_PI * 1.0) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(D3DX_PI * 1.0) * MOVE_MIN_LONG;*/
		//}
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//���L�[�������ꂽ
		g_camera.posV.x += 3.0f;
		//g_camera.posR.x += 3.0f;

		//�ړ��ʂ��X�V
		/*g_player.move.x += sinf(D3DX_PI * 0.5f) * MOVE_MAX_LONG;*/
		/*g_player.move.y += cosf(D3DX_PI * 1.0f) * 5.0f;*/

		//if (GetKeyboardPress(DIK_W) == true || GetJoyPadPress(JOYKEY_UP) == true)
		//{//�E��ړ�
		//	g_camera.posV.x += sinf(D3DX_PI * 0.75f) * -2.5f;
		//	g_camera.posV.y += cosf(D3DX_PI * 0.75f) * -2.5f;

		//	//�ړ��ʂ��X�V
		//	/*g_player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;*/
		//}
	}
	//���_(�㏸:R,���~:F)
	if (GetKeyboardPress(DIK_R) == true)
	{//R�L�[�������ꂽ
		g_camera.posV.y += 3.0f;
		//g_camera.posR.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_F) == true)
	{//F�L�[�������ꂽ
		g_camera.posV.y -= 3.0f;
		//g_camera.posR.y += 1.0f;
	}
	//�����_(�㏸:T,���~:G)
	if (GetKeyboardPress(DIK_T) == true)
	{//T�L�[�������ꂽ
		//g_camera.posV.y += 1.0f;
		g_camera.posR.y += 3.0f;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//G�L�[�������ꂽ
		//g_camera.posV.y += 1.0f;
		g_camera.posR.y -= 3.0f;
	}
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_camera.posV.z += 3.0f;
		g_camera.posR.z += 3.0f;
	}
	if (GetKeyboardPress(DIK_H) == true)
	{
		g_camera.posV.z -= 3.0f;
		g_camera.posR.z -= 3.0f;
	}
	//�Y�[���C��/�A�E�g(�Y�[���C��:Y,�Y�[���A�E�g:H)
	//if (GetKeyboardPress(DIK_Y) == true)
	//{//Y�L�[�������ꂽ
	//	g_camera.posV.y -= 0.5f;
	//	//g_camera.posR.y += 1.0f;
	//}
	//���_����(�����:Z,�E���:C)
	if (GetKeyboardPress(DIK_Z) == true)
	{//Z�L�[�������ꂽ
		g_camera.rot.y += 0.005f;
		g_camera.bUsePosV = true;
	}
	if (GetKeyboardPress(DIK_C) == true)
	{//C�L�[�������ꂽ
		g_camera.rot.y -= 0.005f;
		g_camera.bUsePosV = true;
	}
	
	g_camera.posR = pPlayer->pos;
	/*if (g_camera.bUsePosV == true)
	{*/
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y * D3DX_PI) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y * D3DX_PI) * g_camera.fDistance;
	/*}*/
	
	if (g_camera.bUsePosR == true)
	{
		g_camera.posR.x = sinf(g_camera.rot.z + D3DX_PI) * sqrtf(CAMERA_WIDTH * CAMERA_WIDTH + CAMERA_HEIGHT * CAMERA_HEIGHT) / 2.0f;
		g_camera.posR.z = cosf(g_camera.rot.z + D3DX_PI) * sqrtf(CAMERA_WIDTH * CAMERA_WIDTH + CAMERA_HEIGHT * CAMERA_HEIGHT) / 2.0f;
	}

}

//=====================================
//�|���S���̕`�揈��
//=====================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f),(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 8000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIsIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=====================================
//�J�����̎擾
//=====================================
Camera* GetCamera(void)
{
	return &g_camera;
}