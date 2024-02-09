//=========================================================
//DirectXでの図形描画+α[Player.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "Player.h"
#include"input.h"
#include "camera.h"

//#include "Player1.h"
//#include "player.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_PLAYER	(3)
#define MAX_CNT	(4)
#define CAMERA_WIDTH	(100)
#define CAMERA_HEIGHT	(100)
#define MAX_SPEED	(5.0f)

//=====================================
//グローバル変数
//=====================================
//LPD3DXMESH g_pMeshPlayer[MAX_PLAYER] = {};	//メッシュ(頂点情報)へのポインタ
//LPD3DXBUFFER g_pBuffMatPlayer[MAX_PLAYER] = {};	//マテリアルへのポインタ
//DWORD g_dwNumMatPlayer = 0;	//マテリアルの数
//D3DXMATRIX g_mtxWorldPlayer;	//ワールドマトリックス
Player g_Player;	//プレイヤーの構造体のグローバル変数
int g_nldxShadow = -1;	//対象のインデックス(番号)
float g_fJumpPlayer;
float g_fGravityPlayer;
bool g_bJumpPlayer;

//=====================================
//ポリゴンの初期化処理
//=====================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

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


	//xファイルの読み込み
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
		//頂点数の取得
		g_Player.aModel[nCntBuff].nNumVtx = g_Player.aModel[nCntBuff].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		g_Player.aModel[nCntBuff].sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntBuff].pMesh->GetFVF());

		//頂点バッファのロック
		g_Player.aModel[nCntBuff].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Player.aModel[nCntBuff].pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < g_Player.aModel[nCntBuff].nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
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

			//頂点フォーマットのサイズ分ポインタを進める
			g_Player.aModel[nCntBuff].pVtxBuff += g_Player.aModel[nCntBuff].sizeFVF;

		}

		//頂点バッファのアンロック
		g_Player.aModel[nCntBuff].pMesh->UnlockVertexBuffer();

	}

	//プレイヤーの最小最大を求める
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

	//プレイヤーのサイズを求める
	g_Player.size = g_Player.vtxMax - g_Player.vtxMin;
	
	////影を設定
	//g_nldxShadow = SetShadow();
}

//=====================================
//ポリゴンの終了処理
//=====================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		//テクスチャの破棄
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		//頂点バッファの破棄
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}


}

//=====================================
//ポリゴンの更新処理
//=====================================
void UpdatePlayer()
{
	Camera* pCamera = GetCamera();	//カメラ情報のポインタ
	g_Player.posOld = g_Player.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI) * MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * -D3DX_PI) - (pCamera->rot.y * D3DX_PI)) * 0.5f;

		if (GetKeyboardPress(DIK_A) == true || GetJoyPadPress(JOYKEY_LEFT) == true)
		{//左上移動
			//g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
			//g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
			//g_Player.rot.y = ((pCamera->rot.y * D3DX_PI - (D3DX_PI)) + (pCamera->rot.y * D3DX_PI - (D3DX_PI / 2))) * 0.25f;
		}
	}
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (D3DX_PI / 2)) + (pCamera->rot.y * D3DX_PI + (D3DX_PI / 2))) * -0.5f;

		if (GetKeyboardPress(DIK_S) == true || GetJoyPadPress(JOYKEY_DOWN) == true)
		{//左下移動
		/*	g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (D3DX_PI / 2)) * -MAX_SPEED;
			g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * -MAX_SPEED;
			g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI/ 2)) + (pCamera->rot.y * D3DX_PI + (D3DX_PI))) * 0.75f;*/

			//移動量を更新
			/*g_player.move.x += sinf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;
			g_player.move.y += cosf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;*/
		}
	}
	if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI) * -MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * -MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI)) + (pCamera->rot.y * D3DX_PI + (-D3DX_PI))) * -0.5f;

		if (GetKeyboardPress(DIK_D) == true || GetJoyPadPress(JOYKEY_RIGHT) == true)
		{//右下移動
		/*	g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
			g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;*/
			//g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2)) + (pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2))) * -0.5f;
			
			//移動量を更新
			/*g_player.move.x += sinf(D3DX_PI * 1.0) * MOVE_MIN_LONG;
			g_player.move.y += cosf(D3DX_PI * 1.0) * MOVE_MIN_LONG;*/
		}
	}
	if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
		g_Player.rot.y = ((pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2)) + (pCamera->rot.y * D3DX_PI + (-D3DX_PI / 2))) * -0.5f;

		if (GetKeyboardPress(DIK_W) == true || GetJoyPadPress(JOYKEY_UP) == true)
		{//右上移動
		/*	g_Player.move.x = sinf(pCamera->rot.y * -D3DX_PI + (-D3DX_PI / 2)) * -MAX_SPEED;
			g_Player.move.z = cosf(pCamera->rot.y * -D3DX_PI) * MAX_SPEED;
			g_Player.rot.y = ((pCamera->rot.y * D3DX_PI - (D3DX_PI)) + (pCamera->rot.y * D3DX_PI - (D3DX_PI / 2))) * -0.25f;*/

			//移動量を更新
			/*g_player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;*/
		}
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{//Qキーが押された
		g_Player.rot.y += 0.05f;
	}
	if (GetKeyboardPress(DIK_E) == true)
	{//Eキーが押された
		g_Player.rot.y -= 0.05f;
	}
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{//LSHIFTキーが押された
		g_Player.rot.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{//RSHIFTキーが押された
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

	//GameModel* pModel = GetModel();	//モデル(持てる)情報のポインタ
	//CarryModel* pCarryModel = GetCarryModel();	//モデル(持てない)情報のポインタ

	//移動量を更新(減衰させる)
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.5f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.5f;

	////影の位置を設定
	//SetPositionShadow(g_nldxShadow, g_Player.pos);

	//StopSound(SOUND_LABEL_SE_SHOT);
}

//=====================================
//ポリゴンの描画処理
//=====================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;	//現在のマテリアル保管用
	D3DXMATERIAL* pMat;	//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		//位置を反映
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

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nMumMat; nCntMat++)
		{
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデル(パーツ)の描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=====================================
//モデルの取得
//=====================================
Player* GetPlayer(void)
{
	return &g_Player;
}
