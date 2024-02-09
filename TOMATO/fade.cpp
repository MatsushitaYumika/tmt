//=========================================================
//シューティングゲーム[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================
//=====================================
//インクルード
//=====================================
#include "fade.h"	//タイトル画面の宣言の複合体
#include "input.h"	//キーボードの宣言の複合体

//=====================================
//マクロ定義
//=====================================
#define FADE_SPEED	(5)

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureFade = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffFade = NULL;	//頂点バッファへのポインタ
int g_colorfade;
FADE g_fade/* = FADE_IN*/;	//現在のモード
MODE g_modeNext/* = MODE_NEXT*/;

//=====================================
//タイトル画面の初期化処理
//=====================================
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_fade = FADE_IN;
	g_colorfade = 0;
	

	//デバイスの取得
	pDevice = GetDevice();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\atamagaokasii.png",
	//	&g_pTextureTitle);

	//g_colorfade.nLife = 1.0f;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
}

//=====================================
//タイトル画面の終了処理
//=====================================
void UninitFade(void)
{
	//テクスチャの破棄
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=====================================
//タイトル画面の更新処理
//=====================================
void UpdateFade(void)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン
			g_colorfade -= FADE_SPEED;	//ポリゴンを透明にしていく

			if (g_colorfade <= 0)
			{
				g_colorfade = 0;
				g_fade = FADE_NONE;	//何もしてない
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト
			g_colorfade += FADE_SPEED;	//ポリゴンを不透明に

			if (g_colorfade >= 255)
			{
				g_colorfade = 255;
				g_fade = FADE_IN;	//フェードイン
				//モード設定(次の画面に移行)
				SetMode(g_modeNext);
			}
		}
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, g_colorfade);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
}

//=====================================
//描画処理
//=====================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//モードの設定
//=====================================
void SetFade(MODE ModeNext)
{
	g_modeNext = ModeNext;
	g_fade = FADE_OUT;
}

int GetFadeColor(void)
{
	return g_colorfade;
}

FADE GetFade(void)
{
	return g_fade;
}