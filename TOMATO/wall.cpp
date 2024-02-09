//=========================================================
//DirectXでの図形描画+α[Wall.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "wall.h"
//#include "Wall1.h"
//#include "player.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_WALL	(4)
#define MAX_CNT	(4)
#define MAX_SIZE	(400.0f)

//=====================================
//グローバル変数
//=====================================
LPD3DXMESH g_pMeshWall[MAX_WALL] = {};	//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatWall[MAX_WALL] = {};	//マテリアルへのポインタ
DWORD g_dwNumMatWall[MAX_WALL] = {};	//マテリアルの数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;	//テクスチャへのポインタ
//D3DXVECTOR3 g_posWall;	//位置
//D3DXVECTOR3 g_rotWall;	//向き
Wall g_wall[MAX_WALL];
D3DXMATRIX g_mtxWorldWall;	//ワールドマトリックス
//int g_x = 0;
//int g_y = 0;

//=====================================
//ポリゴンの初期化処理
//=====================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャの読み込み
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

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++/*,pVtx++*/)
	{
		//==========================================
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE, MAX_SIZE,0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_SIZE, MAX_SIZE,0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_SIZE,0.0f,0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_SIZE,0.0f,0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);


		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
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
//ポリゴンの終了処理
//=====================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=====================================
//ポリゴンの更新処理
//=====================================
void UpdateWall()
{

}

//=====================================
//ポリゴンの描画処理
//=====================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldWall);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCntWall].rot.y, g_wall[nCntWall].rot.x, g_wall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, g_wall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureWall);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}

//=====================================
//設定処理
//=====================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
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
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}