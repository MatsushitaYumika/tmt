//=========================================================
//tmt[pause.cpp]
//Author:Yumika Matsushita
//=========================================================

//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "input.h"	//キーボードの宣言の複合体
#include "Pause.h"	//ゲーム画面の宣言の複合体
#include "player.h"
//#include "fade.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_POLYGON			(3)			//ポリゴンの最大数
#define POLYGON_WIDTH		(150.0f)	//選択出来るやつのポリゴンの横の長さ
#define POLYGON_HEIGHT		(100.0f)	//選択出来るやつのポリゴンの縦の長さ
#define Brightness_POLYGON	(51)		//ポリゴンの明るさ
#define POLYGON_MAXCOL		(255)		//ポリゴンの不透明度(255)
#define POLYGON_COL			(100)		//ポリゴンの不透明度(100)
#define MNPOLYGON_WIDTH		(300.0f)	//操作方法のポリゴンの縦の長さ
#define MNPOLYGON_HEIGHT	(400.0f)	//操作方法のポリゴンの横の長さ
#define MAX_PL				(4)			//プレイヤーの最大人数

//=====================================
//グローバル変数
//=====================================

//背景
LPDIRECT3DTEXTURE9	g_pTexturePauseBG = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseBG = NULL;		//頂点バッファへのポインタ

//操作方法(MN = menu)
LPDIRECT3DTEXTURE9	g_pTexturePauseMN = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseMN = NULL;		//頂点バッファへのポインタ
PauseMN g_pauseMN;										//操作方法のポリゴンの構造体

//選択できるやつ
LPDIRECT3DTEXTURE9	g_pTexturePause[MAX_POLYGON] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPause = NULL;			//頂点バッファへのポインタ
Pause g_pause[MAX_POLYGON];								//Pause(選択できるやつ)のポリゴンの構造体
int g_nCntChoose = 0;									//選択されたポリゴンを光らせる為のカウント

//=====================================
//初期化処理
//=====================================
void InitPause(void)
{
//==========================================================================================
//ここから次の区切りまではポーズ画面の背景のポリゴンの処理

	int nCntPause = 0;									//for文のカウントの初期化

	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得

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

	VERTEX_2D* pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseBG->Unlock();

//==========================================================================================
//ここから下までは操作方法のポリゴンの処理

	g_pauseMN.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_pauseMN.bUse = false;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_menu.png",
		&g_pTexturePauseMN);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMN,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMN->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//操作方法のポリゴン設置
	SetPauseMenu(D3DXVECTOR3(900.0f, 300.0f, 0.0f));

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMN->Unlock();

//==========================================================================================
//ここから下までは選択出来るポリゴンの処理

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pause[nCntPause].nType = 0;
		g_pause[nCntPause].bUse = false;
		g_pause[nCntPause].bColUse = false;
	}

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
		pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);

		//テスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//配置しているとこ
	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPause(D3DXVECTOR3((SCREEN_WIDTH / 4), (nCntPause * 200.0f) + 250.0f, 0.0f));
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//=====================================
//終了処理
//=====================================
void UninitPause(void)
{
//==================================================================================
//区切られているところまで背景のポリゴンの処理 
	
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
//区切られているところまで操作方法のポリゴンの処理

	//テクスチャの破棄
	if (g_pTexturePauseMN != NULL)
	{
		g_pTexturePauseMN->Release();
		g_pTexturePauseMN = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseMN != NULL)
	{
		g_pVtxBuffPauseMN->Release();
		g_pVtxBuffPauseMN = NULL;
	}

//==================================================================================
//ここから下までは選択出来るポリゴンの処理 

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
	VERTEX_2D* pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//構造体のフラグを全てfalseにする
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pause[nCntPause].bColUse = false;
	}

	//↑キー押されたら
	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP,0) == true)
	{
		g_nCntChoose--;		//カウントをマイナスする(上に進む)
	}

	//↓キー押されたら
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN,0) == true)
	{
		g_nCntChoose++;		//カウントをプラスする(下に進む)
	}

	//もしカウントが使用されているポリゴン数よりもマイナス値になってしまった時
	if (g_nCntChoose <= -1)
	{
		g_nCntChoose = 2;	//強制的にカウントを2にする(retryからendにとばす)
	}

	//もしカウントが使用されているポリゴン数よりもプラス値になってしまった時
	if (g_nCntChoose >= 3)
	{
		g_nCntChoose = 0;	//強制的にカウントを0にする(endからretryにとばす)
	}

	//選ばれたカウントの値のフラグをtrueにする
	g_pause[g_nCntChoose].bColUse = true;

	//ポリゴンの数分回してます
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//もし選ばれたポリゴンのフラグがfalseの場合
		if (g_pause[nCntPause].bColUse == false)
		{//不透明度を低くする
			//頂点カラーの設定(false時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		}

		//もし選ばれたポリゴンのフラグがtrueの場合
		if (g_pause[nCntPause].bColUse == true)
		{//不透明度を高くする
			//頂点カラーの設定(true時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		}

		pVtx += 4;			//いつもの
	}

	//プレイヤーの数ぶん回してます
	for (int nCntPause = 0; nCntPause < MAX_PL; nCntPause++)
	{
		//もしポリゴンの0番が選ばれた場合
		if (g_pause[0].bColUse == true)
		{
			//上記を踏まえたうえでもしAボタンを押した場合
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// ゲーム画面に戻る処理してください
				//SetFade(MODE_GAME);
			}
		}

		//もしポリゴンの1番が選ばれた場合
		if (g_pause[1].bColUse == true)
		{
			//上記を踏まえたうえでもしAボタンを押した場合
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// チュートリアル画面に戻る処理してください
				//SetFade(MODE_TUTORIAL);
			}
		}

		//もしポリゴンの2番が選ばれた場合
		if (g_pause[2].bColUse == true)
		{
			//上記を踏まえたうえでもしAボタンを押した場合
			if (GetJoypadTrigger(JOYKEY_A, nCntPause) == true)
			{
				// タイトル画面に戻る処理してください
				//SetFade(MODE_TITLE);
			}
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
//==============================================================================================
//ここから下の区切りまで背景の処理

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

//==============================================================================================
//ここから下までは選択出来るポリゴンの処理
	
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//選択できるポリゴンの最大数分回してます
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);		//テクスチャ三個分あります

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);		//ポリゴン三つ分あります
	}

//==============================================================================================
//区切られているところまで操作方法のポリゴンの処理

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMN, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseMN);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//選択できるポリゴンの設定処理
//=====================================
void SetPause(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//選択できるポリゴンの最大数分回してます
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

//=====================================
//操作方法のポリゴンの設定処理
//=====================================
void SetPauseMenu(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMN->Lock(0, 0, (void**)&pVtx, 0);

	if (g_pauseMN.bUse == false)
	{
		g_pauseMN.pos = pos;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_pauseMN.pos.x - MNPOLYGON_WIDTH, g_pauseMN.pos.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_pauseMN.pos.x + MNPOLYGON_WIDTH, g_pauseMN.pos.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_pauseMN.pos.x - MNPOLYGON_WIDTH, g_pauseMN.pos.y + MNPOLYGON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_pauseMN.pos.x + MNPOLYGON_WIDTH, g_pauseMN.pos.y + MNPOLYGON_HEIGHT, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMN->Unlock();
}