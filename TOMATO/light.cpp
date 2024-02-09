//=========================================================
//[light.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "light.h"
//#include "Light1.h"
//#include "player.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_LIGHT	(3)

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLight = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureLight = NULL;	//テクスチャへのポインタ
D3DXVECTOR3 g_posLight;	//位置
D3DXVECTOR3 g_rotLight;	//向き
D3DXMATRIX g_mtxWorldLight;	//ワールドマトリックス
D3DLIGHT9 g_light[MAX_LIGHT];	//ライトの情報


//=====================================
//ポリゴンの初期化処理
//=====================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecDir[MAX_LIGHT];	//設定用方向ベクトル

	//ライトの情報をクリアにする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	for (int nCntlight = 0; nCntlight < MAX_LIGHT; nCntlight++)
	{
		//ライトの種類を設定
		g_light[nCntlight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_light[nCntlight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		vecDir[1] = D3DXVECTOR3(-0.5f, -0.2f, -0.4f);
		vecDir[2] = D3DXVECTOR3(0.8f, 0.9f, 0.5f);

		D3DXVec3Normalize(&vecDir[nCntlight], &vecDir[nCntlight]);
	
		g_light[nCntlight].Direction = vecDir[nCntlight];	//ベクトルを正規化する

		//ライトを設定する
		pDevice->SetLight(nCntlight, &g_light[nCntlight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntlight, TRUE);
	}
}

//=====================================
//ポリゴンの終了処理
//=====================================
void UninitLight(void)
{

}

//=====================================
//ポリゴンの更新処理
//=====================================
void UpdateLight()
{

}
