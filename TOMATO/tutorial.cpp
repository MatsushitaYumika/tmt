//=========================================================
//シューティングゲーム[tutorial.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "tutorial.h"	//タイトル画面の宣言の複合体
#include "input.h"	//キーボードの宣言の複合体
#include "fade.h"

//=====================================
//マクロ定義
//=====================================
#define FEED_SPEED	(5)

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureTutorial[2] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTutorial = NULL;	//頂点バッファへのポインタ
bool bTutorialFeedOut = false;
int g_nCntTutorial;

//=====================================
//初期化処理
//=====================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial000.png",
		&g_pTextureTutorial[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial001.png",
		&g_pTextureTutorial[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	g_nCntTutorial = 0;
	bTutorialFeedOut = false;

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//==========================================
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

//=====================================
//終了処理
//=====================================
void UninitTutorial(void)
{
	for (int nCntTutorial = 0; nCntTutorial < 2; nCntTutorial++)
	{
		//テクスチャの破棄
		if (g_pTextureTutorial[nCntTutorial] != NULL)
		{
			g_pTextureTutorial[nCntTutorial]->Release();
			g_pTextureTutorial[nCntTutorial] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}


}

//=====================================
//更新処理
//=====================================
void UpdateTutorial(void)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	int fadecol = GetFadeColor();

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RIGHT) == true )
	{
		g_nCntTutorial = 1;
	}
	if (GetKeyboardTrigger(DIK_LEFT) == true )
	{
		g_nCntTutorial = 0;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && fadecol <= 0)
	{
		/*bTutorialFeedOut = true;*/
		SetFade(MODE_GAME);
	}
	/*if (bTutorialFeedOut == true)
	{
		g_nCntTutorial -= FEED_SPEED;
	}
	if(bTutorialFeedOut == false)
	{
		g_nCntTutorial += FEED_SPEED;
	}
	if (g_nCntTutorial >= 255)
	{
		g_nCntTutorial = 255;
	}*/
	////頂点カラーの設定
	//pVtx[0].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);
	//pVtx[1].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);
	//pVtx[2].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);
	//pVtx[3].col = D3DCOLOR_RGBA(g_nCntTutorial, g_nCntTutorial, g_nCntTutorial, g_nCntTutorial);

	////頂点バッファをアンロックする
	//g_pVtxBuffTutorial->Unlock();

	//if (g_nCntTutorial <= 0)
	//{
	//	//モード設定(ゲーム画面に移行)
	//	SetMode(MODE_GAME);
	//}
}

//=====================================
//描画処理
//=====================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_nCntTutorial == 0)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial[0]);
	}
	if (g_nCntTutorial == 1)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial[1]);
	}
	

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}