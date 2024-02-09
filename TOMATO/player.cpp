//=========================================================
//DirectX�ł̐}�`�`��+��[Player.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "Player.h"
#include"input.h"
#include "camera.h"

//#include "Player1.h"
//#include "player.h"

//=====================================
//�}�N����`
//=====================================
#define MAX_PLAYER	(3)
#define MAX_CNT	(4)
#define CAMERA_WIDTH	(100)
#define CAMERA_HEIGHT	(100)
#define MAX_SPEED	(5.0f)

//=====================================
//�O���[�o���ϐ�
//=====================================
//LPD3DXMESH g_pMeshPlayer[MAX_PLAYER] = {};	//���b�V��(���_���)�ւ̃|�C���^
//LPD3DXBUFFER g_pBuffMatPlayer[MAX_PLAYER] = {};	//�}�e���A���ւ̃|�C���^
//DWORD g_dwNumMatPlayer = 0;	//�}�e���A���̐�
//D3DXMATRIX g_mtxWorldPlayer;	//���[���h�}�g���b�N�X
Player g_Player;	//�v���C���[�̍\���̂̃O���[�o���ϐ�
int g_nldxShadow = -1;	//�Ώۂ̃C���f�b�N�X(�ԍ�)
float g_fJumpPlayer;
float g_fGravityPlayer;
bool g_bJumpPlayer;

//=====================================
//�|���S���̏���������
//=====================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	g_Player.pos = D3DXVECTOR3(40.0f, 0.0f, 0.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nCntType = -1;
	g_Player.bIsLanding = false;
	g_Player.bIsLandingCarry = false;

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		g_Player.aModel[nCntModel].pMesh = NULL;
		g_Player.aModel[nCntModel].pBuffMat = NULL;
		g_Player.aModel[nCntModel].nMumMat = NULL;
		g_Player.aModel[nCntModel].nIdxModelParent = NULL;
		g_Player.aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aModel[nCntModel].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aModel[nCntModel].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aModel[nCntModel].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_Player.aModel[0].nIdxModelParent = -1;
	g_Player.aModel[1].nIdxModelParent = 0;
	g_Player.aModel[2].nIdxModelParent = 1;
	g_fGravityPlayer = 2.0f;
	g_fJumpPlayer = -6.0f;
	g_bJumpPlayer = false;


	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\3Dplayer.x", 
		D3DXMESH_SYSTEMMEM, 
		pDevice, 
		NULL, 
		&g_Player.aModel[0].pBuffMat,
		NULL, 
		&g_Player.aModel[0].nMumMat,
		&g_Player.aModel[0].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\3Dplayer_reg.R.x", 
		D3DXMESH_SYSTEMMEM, 
		pDevice, 
		NULL, 
		&g_Player.aModel[1].pBuffMat,
		NULL, 
		&g_Player.aModel[1].nMumMat,
		&g_Player.aModel[1].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\3Dplayer_reg.L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[2].pBuffMat,
		NULL,
		&g_Player.aModel[2].nMumMat,
		&g_Player.aModel[2].pMesh);

	g_Player.aModel[1].pos = D3DXVECTOR3(10.0f, 5.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(1.57f, 0.0f, 1.57f);
	g_Player.aModel[2].pos = D3DXVECTOR3(-7.0f, 5.0f, 0.0f);
	g_Player.aModel[2].rot = D3DXVECTOR3(-1.57f, 0.0f, 1.57f);

	for (int nCntBuff = 0; nCntBuff < MAX_PLAYER; nCntBuff++)
	{
		//���_���̎擾
		g_Player.aModel[nCntBuff].nNumVtx = g_Player.aModel[nCntBuff].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		g_Player.aModel[nCntBuff].sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntBuff].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_Player.aModel[nCntBuff].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Player.aModel[nCntBuff].pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < g_Player.aModel[nCntBuff].nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Player.aModel[nCntBuff].pVtxBuff;

			if (vtx.x > g_Player.aModel[nCntBuff].vtxMax.x)
			{
				g_Player.aModel[nCntBuff].vtxMax.x = vtx.x;
			}
			else if(vtx.x < g_Player.aModel[nCntBuff].vtxMin.x)
			{
				g_Player.aModel[nCntBuff].vtxMin.x = vtx.x;
			}

			if (vtx.y > g_Player.aModel[nCntBuff].vtxMax.y)
			{
				g_Player.aModel[nCntBuff].vtxMax.y = vtx.y;
			}
			else if (vtx.y < g_Player.aModel[nCntBuff].vtxMin.y)
			{
				g_Player.aModel[nCntBuff].vtxMin.y = vtx.y;
			}

			if (vtx.z > g_Player.aModel[nCntBuff].vtxMax.z)
			{
				g_Player.aModel[nCntBuff].vtxMax.z = vtx.z;
			}
			else if (vtx.z < g_Player.aModel[nCntBuff].vtxMin.z)
			{
				g_Player.aModel[nCntBuff].vtxMin.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			g_Player.aModel[nCntBuff].pVtxBuff += g_Player.aModel[nCntBuff].sizeFVF;

		}

		//���_�o�b�t�@�̃A�����b�N
		g_Player.aModel[nCntBuff].pMesh->UnlockVertexBuffer();

	}

	//�v���C���[�̍ŏ��ő�����߂�
	for (int nCntBuff = 0; nCntBuff < MAX_PLAYER; nCntBuff++)
	{
		if (g_Player.vtxMax.x < g_Player.aModel[nCntBuff].vtxMax.x)
		{
			g_Player.vtxMax.x = g_Player.aModel[nCntBuff].vtxMax.x;
		}
		else if (g_Player.vtxMin.x > g_Player.aModel[nCntBuff].vtxMin.x)
		{
			g_Player.vtxMin.x = g_Player.aModel[nCntBuff].vtxMin.x;
		}

		if (g_Player.vtxMax.y < g_Player.aModel[nCntBuff].vtxMax.y)
		{
			g_Player.vtxMax.y = g_Player.aModel[nCntBuff].vtxMax.y;
		}
		else if (g_Player.vtxMin.y > g_Player.aModel[nCntBuff].vtxMin.y)
		{
			g_Player.vtxMin.y = g_Player.aModel[nCntBuff].vtxMin.y;
		}

		if (g_Player.vtxMax.z < g_Player.aModel[nCntBuff].vtxMax.z)
		{
			g_Player.vtxMax.z = g_Player.aModel[nCntBuff].vtxMax.z;
		}
		else if (g_Player.vtxMin.z > g_Player.aModel[nCntBuff].vtxMin.z)
		{
			g_Player.vtxMin.z = g_Player.aModel[nCntBuff].vtxMin.z;
		}
	}

	//�v���C���[�̃T�C�Y�����߂�
	g_Player.size = g_Player.vtxMax - g_Player.vtxMin;
	
	////�e��ݒ�
	//g_nldxShadow = SetShadow();
}

//=====================================
//�|���S���̏I������
//=====================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		//�e�N�X�`���̔j��
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}


}

//=====================================
//�|���S���̍X�V����
//=====================================
void UpdatePlayer()
{
	Camera* pCamera = GetCamera();	//�J�������̃|�C���^
	g_Player.posOld = g_Player.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI) * MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * -D3DX_PI) - (pCamera->rot.y * D3DX_PI)) * 0.5f;

		if (GetKeyboardPress(DIK_A) == true || GetJoyPadPress(JOYKEY_LEFT) == true)
		{//����ړ�
			//g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
			//g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
			//g_Player.rot.y = ((pCamera->rot.y * D3DX_PI - (D3DX_PI)) + (pCamera->rot.y * D3DX_PI - (D3DX_PI / 2))) * 0.25f;
		}
	}
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (D3DX_PI / 2)) + (pCamera->rot.y * D3DX_PI + (D3DX_PI / 2))) * -0.5f;

		if (GetKeyboardPress(DIK_S) == true || GetJoyPadPress(JOYKEY_DOWN) == true)
		{//�����ړ�
		/*	g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
			g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * -MAX_SPEED;
			g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI/ 2)) + (pCamera->rot.y * D3DX_PI + (D3DX_PI))) * 0.75f;*/

			//�ړ��ʂ��X�V
			/*g_player.move.x += sinf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;
			g_player.move.y += cosf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;*/
		}
	}
	if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI) * -MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * -MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI)) + (pCamera->rot.y * D3DX_PI + (-D3DX_PI))) * -0.5f;

		if (GetKeyboardPress(DIK_D) == true || GetJoyPadPress(JOYKEY_RIGHT) == true)
		{//�E���ړ�
		/*	g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
			g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;*/
			//g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2)) + (pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2))) * -0.5f;
			
			//�ړ��ʂ��X�V
			/*g_player.move.x += sinf(D3DX_PI * 1.0) * MOVE_MIN_LONG;
			g_player.move.y += cosf(D3DX_PI * 1.0) * MOVE_MIN_LONG;*/
		}
	}
	if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2)) + (pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2))) * -0.5f;

		if (GetKeyboardPress(DIK_W) == true || GetJoyPadPress(JOYKEY_UP) == true)
		{//�E��ړ�
		/*	g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
			g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * MAX_SPEED;
			g_Player.rot.y = ((pCamera->rot.y * D3DX_PI - (D3DX_PI)) + (pCamera->rot.y * D3DX_PI - (D3DX_PI / 2))) * -0.25f;*/

			//�ړ��ʂ��X�V
			/*g_player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;*/
		}
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{//Q�L�[�������ꂽ
		g_Player.rot.y += 0.05f;
	}
	if (GetKeyboardPress(DIK_E) == true)
	{//E�L�[�������ꂽ
		g_Player.rot.y -= 0.05f;
	}
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{//LSHIFT�L�[�������ꂽ
		g_Player.rot.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//RSHIFT�L�[�������ꂽ
		g_Player.rot.y -= 1.0f;
	}
	if (GetKeyboardTrigger(DIK_SPACE) == true && g_bJumpPlayer == false)
	{
		/*SetBullet(g_Player.pos, g_Player.rot, 500);*/
		/*g_Player.move.y -= g_fJumpPlayer;
		g_bJumpPlayer = true;*/
	}

	//PlaySound(SOUND_LABEL_SE_SHOT);

	if (g_Player.pos.z >= 380.0f)
	{
		g_Player.pos.z = 380.0f;
	}
	else if(g_Player.pos.z <= -380.0f)
	{
		g_Player.pos.z = -380.0f;
	}

	if (g_Player.pos.x >= 380.0f)
	{
		g_Player.pos.x = 380.0f;
	}
	else if (g_Player.pos.x <= -380.0f)
	{
		g_Player.pos.x = -380.0f;
	}

	g_Player.pos += g_Player.move;

	//g_Player.bIsLanding = bCollisionModel(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.size);
	//
	//g_Player.bIsLandingCarry = bCollisionCarryModel(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.size);

	//GameModel* pModel = GetModel();	//���f��(���Ă�)���̃|�C���^
	//CarryModel* pCarryModel = GetCarryModel();	//���f��(���ĂȂ�)���̃|�C���^

	//�ړ��ʂ��X�V(����������)
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.5f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.5f;

	////�e�̈ʒu��ݒ�
	//SetPositionShadow(g_nldxShadow, g_Player.pos);

	//StopSound(SOUND_LABEL_SE_SHOT);
}

//=====================================
//�|���S���̕`�揈��
//=====================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۊǗp
	D3DXMATERIAL* pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		D3DXMATRIX mtxParent;
		if (g_Player.aModel[nCntModel].nIdxModelParent == - 1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aModel[0].mtxWorld;
		}

		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nMumMat; nCntMat++)
		{
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f��(�p�[�c)�̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=====================================
//���f���̎擾
//=====================================
Player* GetPlayer(void)
{
	return &g_Player;
}
