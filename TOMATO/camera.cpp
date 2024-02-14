//=========================================================
//[camera.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "camera.h"
#include "input.h"
#include "player.h"
//#include "Camera1.h"
//#include "player.h"

//=====================================
//マクロ定義
//=====================================
#define CAMERA_WIDTH	(100)
#define CAMERA_HEIGHT	(100)

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCamera = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCamera = NULL;	//テクスチャへのポインタ
D3DXVECTOR3 g_posCamera;	//位置
D3DXVECTOR3 g_rotCamera;	//向き
D3DXMATRIX g_mtxWorldCamera;	//ワールドマトリックス
Camera g_camera;	//カメラの情報
float g_fLengthCamera;	//対角線の長さ
float g_fAngleCamera;	//対角線の角度


//=====================================
//ポリゴンの初期化処理
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

	//対角線の長さを算出する
	g_fLengthCamera = sqrtf(CAMERA_WIDTH * CAMERA_WIDTH + CAMERA_HEIGHT * CAMERA_HEIGHT) / 2.0f;

	//対角線の角度を算出する
	g_fAngleCamera = atan2f(CAMERA_WIDTH, CAMERA_HEIGHT);
}

//=====================================
//ポリゴンの終了処理
//=====================================
void UninitCamera(void)
{
	
}

//=====================================
//ポリゴンの更新処理
//=====================================
void UpdateCamera()
{
	Player* pPlayer = GetPlayer();	//プレイヤー情報のポインタ

	//カメラ平行移動(Dまで同じ)
	if (GetKeyboardPress(DIK_UP) == true)
	{//↑キーが押された
		g_camera.posV.y += 3.0f;
		g_camera.posR.y += 3.0f;

		//移動量を更新
		/*g_player.move.x += sinf(D3DX_PI * 1.0) * 0.1f;*/
		/*g_player.move.y += cosf(D3DX_PI * 1.0) * MOVE_MAX_LONG;*/
	
		//if (GetKeyboardPress(DIK_A) == true || GetJoyPadPress(JOYKEY_LEFT) == true)
		//{//左上移動
		//	g_camera.posV.y += 1.0f;
		//	g_camera.posR.y += 1.0f;

		//	//移動量を更新
		//	/*g_player.move.x += sinf(-D3DX_PI * 0.75) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(-D3DX_PI * 0.75) * MOVE_MIN_LONG;*/
		//}
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//←キーが押された
		g_camera.posV.x -= 3.0f;
		//g_camera.posR.x -= 3.0f;

		//移動量を更新
		/*g_player.move.x += sinf(-D3DX_PI * 0.5) * MOVE_MAX_LONG;*/
		/*g_player.move.y += cosf(D3DX_PI * 1.0) * 5.0f;*/

		//if (GetKeyboardPress(DIK_S) == true || GetJoyPadPress(JOYKEY_DOWN) == true)
		//{//左下移動
		//	g_camera.posV.x += sinf(-D3DX_PI * 0.25f) * -2.5f;
		//	g_camera.posV.y += cosf(-D3DX_PI * 0.25f) * -2.5f;

		//	//移動量を更新
		//	/*g_player.move.x += sinf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(-D3DX_PI * 0.25) * MOVE_MIN_LONG;*/
		//}
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{//↓キーが押された
		g_camera.posV.y -= 3.0f;
		g_camera.posR.y -= 3.0f;

		//移動量を更新
		//g_player.move.x += sinf(-D3DX_PI * 0.5) * 5.0f;
		//g_player.move.y += cosf(-D3DX_PI * 1.0) * MOVE_MINUS_MAX_LONG;

		//if (GetKeyboardPress(DIK_D) == true || GetJoyPadPress(JOYKEY_RIGHT) == true)
		//{//右下移動
		//	g_camera.posV.x += sinf(D3DX_PI * 0.25f) * -2.5f;
		//	g_camera.posV.y += cosf(D3DX_PI * 0.25f) * -2.5f;

		//	//移動量を更新
		//	/*g_player.move.x += sinf(D3DX_PI * 1.0) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(D3DX_PI * 1.0) * MOVE_MIN_LONG;*/
		//}
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{//→キーが押された
		g_camera.posV.x += 3.0f;
		//g_camera.posR.x += 3.0f;

		//移動量を更新
		/*g_player.move.x += sinf(D3DX_PI * 0.5f) * MOVE_MAX_LONG;*/
		/*g_player.move.y += cosf(D3DX_PI * 1.0f) * 5.0f;*/

		//if (GetKeyboardPress(DIK_W) == true || GetJoyPadPress(JOYKEY_UP) == true)
		//{//右上移動
		//	g_camera.posV.x += sinf(D3DX_PI * 0.75f) * -2.5f;
		//	g_camera.posV.y += cosf(D3DX_PI * 0.75f) * -2.5f;

		//	//移動量を更新
		//	/*g_player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;
		//	g_player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_MIN_LONG;*/
		//}
	}
	//視点(上昇:R,下降:F)
	if (GetKeyboardPress(DIK_R) == true)
	{//Rキーが押された
		g_camera.posV.y += 3.0f;
		//g_camera.posR.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_F) == true)
	{//Fキーが押された
		g_camera.posV.y -= 3.0f;
		//g_camera.posR.y += 1.0f;
	}
	//注視点(上昇:T,下降:G)
	if (GetKeyboardPress(DIK_T) == true)
	{//Tキーが押された
		//g_camera.posV.y += 1.0f;
		g_camera.posR.y += 3.0f;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//Gキーが押された
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
	//ズームイン/アウト(ズームイン:Y,ズームアウト:H)
	//if (GetKeyboardPress(DIK_Y) == true)
	//{//Yキーが押された
	//	g_camera.posV.y -= 0.5f;
	//	//g_camera.posR.y += 1.0f;
	//}
	//視点旋回(左回り:Z,右回り:C)
	if (GetKeyboardPress(DIK_Z) == true)
	{//Zキーが押された
		g_camera.rot.y += 0.005f;
		g_camera.bUsePosV = true;
	}
	if (GetKeyboardPress(DIK_C) == true)
	{//Cキーが押された
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
//ポリゴンの描画処理
//=====================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f),(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 8000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIsIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=====================================
//カメラの取得
//=====================================
Camera* GetCamera(void)
{
	return &g_camera;
}