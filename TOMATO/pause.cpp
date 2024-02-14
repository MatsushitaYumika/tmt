//=========================================================
//シューティングゲーム[pause.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "input.h"	//キーボードの宣言の複合体
#include "Pause.h"	//ゲーム画面の宣言の複合体
#include "fade.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_POLYGON	(3)	//ポリゴンの最大数
#define POLYGON_WIDTH	(150.0f)	//ポリゴンの横の長さ
#define POLYGON_HEIGHT	(100.0f)	//ポリゴンの縦の長さ
#define Brightness_POLYGON	(51)	//ポリゴンの明るさ
#define POLYGON_COL (255)			//ポリゴンのカラー

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DTEXTURE9	g_pTexturePauseBG = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseBG = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9	g_pTexturePause[MAX_POLYGON] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPause = NULL;	//頂点バッファへのポインタ
Pause g_pause[MAX_POLYGON];
int nCntPauseCol = 100;
int g_nCntChoose = 0;

//=====================================
//初期化処理
//=====================================
void InitPause(void)
{
	int nCntPause = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause.png",
		&g_pTexturePauseBG);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 120);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseBG->Unlock();

	//==========================================================================================

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pause[nCntPause].nType = 0;
		g_pause[nCntPause].bUse = false;
		g_pause[nCntPause].bColUse = false;
	}

	nCntPauseCol = 100;
	g_nCntChoose = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\retry.png",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\continue.png",
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\end.png",
		&g_pTexturePause[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//==========================================
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);

		//テスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPause(D3DXVECTOR3((SCREEN_WIDTH / 4), (nCntPause * 200.0f) + 100.0f, 0.0f));
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//=====================================
//終了処理
//=====================================
void UninitPause(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}

	//==================================================================================

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=====================================
//更新処理
//=====================================
void UpdatePause(void)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].bColUse = false;
	}

	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP,0) == true)
	{
		g_nCntChoose--;
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN,0) == true)
	{
		g_nCntChoose++;
	}
	if (g_nCntChoose <= -1)
	{
		g_nCntChoose = 2;
	}
	if (g_nCntChoose >= 3)
	{
		g_nCntChoose = 0;
	}

	g_pause[g_nCntChoose].bColUse = true;

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		if (g_pause[nCntPause].bColUse == false)
		{
			//頂点カラーの設定(false時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, 100);
		}
		if (g_pause[nCntPause].bColUse == true)
		{
			//頂点カラーの設定(true時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_COL, POLYGON_COL, POLYGON_COL, POLYGON_COL);
		}

		pVtx += 4;
	}

	if (g_pause[0].bColUse == true)
	{
		if (GetJoypadTrigger(JOYKEY_A,0) == true)
		{
			SetFade(MODE_GAME);
		}
	}
	if (g_pause[1].bColUse == true)
	{
		if (GetJoypadTrigger(JOYKEY_A,0) == true)
		{
			SetFade(MODE_TUTORIAL);
		}
	}
	if (g_pause[2].bColUse == true)
	{
		if (GetJoypadTrigger(JOYKEY_A,0) == true)
		{
			SetFade(MODE_TITLE);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//=====================================
//描画処理
//=====================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスへのポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//==============================================================================================

		//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}

//=====================================
//設定処理
//=====================================
void SetPause(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		if (g_pause[nCntPause].bUse == false)
		{
			g_pause[nCntPause].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - POLYGON_WIDTH, g_pause[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + POLYGON_WIDTH, g_pause[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - POLYGON_WIDTH, g_pause[nCntPause].pos.y + POLYGON_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + POLYGON_WIDTH, g_pause[nCntPause].pos.y + POLYGON_HEIGHT, 0.0f);

			g_pause[nCntPause].bUse = true;
			g_pause[nCntPause].bColUse = false;

			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}