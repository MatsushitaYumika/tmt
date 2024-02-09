//=========================================================
//シューティングゲーム[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "title.h"	//タイトル画面の宣言の複合体
#include "input.h"	//キーボードの宣言の複合体
#include "fade.h"

//=====================================
//マクロ定義
//=====================================
#define FEED_SPEED	(5)

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureTitle = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTitle = NULL;	//頂点バッファへのポインタ
bool bTitleFeedOut = false;
int g_nCntTitle;

//=====================================
//タイトル画面の初期化処理
//=====================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	g_nCntTitle = 0;
	bTitleFeedOut = false;

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//=====================================
//タイトル画面の終了処理
//=====================================
void UninitTitle(void)
{
	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=====================================
//タイトル画面の更新処理
//=====================================
void UpdateTitle(void)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	int fadecol = GetFadeColor();

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RETURN) == true && fadecol <= 0)
	{
		//bTitleFeedOut = true;
		SetFade(MODE_TUTORIAL);
	}
	/*if (bTitleFeedOut == true)
	{
		g_nCntTitle -= FEED_SPEED;
	}
	if(bTitleFeedOut == false)
	{
		g_nCntTitle += FEED_SPEED;
	}
	if (g_nCntTitle >= 255)
	{
		g_nCntTitle = 255;
	}*/
	////頂点カラーの設定
	//pVtx[0].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);
	//pVtx[1].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);
	//pVtx[2].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);
	//pVtx[3].col = D3DCOLOR_RGBA(g_nCntTitle, g_nCntTitle, g_nCntTitle, g_nCntTitle);

	////頂点バッファをアンロックする
	//g_pVtxBuffTitle->Unlock();

	//if (g_nCntTitle <= 0)
	//{
	//	//モード設定(ゲーム画面に移行)
	//	SetMode(MODE_GAME);
	//}
}

//=====================================
//描画処理
//=====================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
	
}