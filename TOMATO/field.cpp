//=========================================================
//DirectXでの図形描画+α[Field.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "field.h"
//#include "Field1.h"
//#include "player.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_Field	(2)
#define MAX_CNT	(4)
#define MAX_SIZE	(400.0f)

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;	//テクスチャへのポインタ
D3DXVECTOR3 g_posField;	//位置
D3DXVECTOR3 g_rotField;	//向き
D3DXMATRIX g_mtxWorldField;	//ワールドマトリックス
//int g_x = 0;
//int g_y = 0;

//=====================================
//ポリゴンの初期化処理
//=====================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureField);

	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	VERTEX_3D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//==========================================
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE, 0.0f, MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(MAX_SIZE, 0.0f, MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-MAX_SIZE, 0.0f, -MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(MAX_SIZE, 0.0f, -MAX_SIZE);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffField->Unlock();

}

//=====================================
//ポリゴンの終了処理
//=====================================
void UninitField(void)
{
	//テクスチャの破棄
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=====================================
//ポリゴンの更新処理
//=====================================
void UpdateField()
{

}

//=====================================
//ポリゴンの描画処理
//=====================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureField);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
