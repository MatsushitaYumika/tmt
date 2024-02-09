//=========================================================
//シューティングゲーム[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//インクルード
//=====================================
#include <stdio.h>
#include <string.h>
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "player.h"	//プレイヤーの宣言の複合体
#include "input.h"	//キーボードの宣言の複合体
#include "game.h"	//ゲーム画面の宣言の複合体
#include "camera.h"
#include "light.h"
#include "field.h"
#include "wall.h"
#include "time.h"
#include "fade.h"
#include "pause.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_TEXT	(8192)	//文字の最大数
#define MAX_MODEL	(128)	//敵の最大数

//=====================================
//グローバル変数
//=====================================
LPDIRECT3DTEXTURE9	g_pTextureGame = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffGame = NULL;	//頂点バッファへのポインタ
bool g_bPause = false;	//ポーズ中かどうか
bool g_Pause = false;	// ポーズフラグを無くす

//=====================================
//ゲーム画面の初期化処理
//=====================================
void InitGame(void)
{
	g_Pause = false;	// ポーズフラグを無くす

	InitCamera();

	InitLight();

	InitField();

	InitWall();

	//InitMeshfield();

	InitPlayer();
	InitPause();

	bool g_bPause = false;	//ポーズ解除
}

//=====================================
//ゲーム画面の終了処理
//=====================================
void UninitGame(void)
{
	UninitLight();

	UninitCamera();

	UninitField();

	UninitWall();

	UninitPlayer();
	UninitPause();
}

//=====================================
//ゲーム画面の更新処理
//=====================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_Pause = !g_Pause;
	}

	if (g_Pause)
	{ // ポーズ中のみ

		/*---【ここでUIの処理】---*/
		UpdatePause();



		return;	// 以下の処理は行わない
	}

		UpdateLight();

		UpdateCamera();

		UpdateField();

		UpdateWall();

		UpdatePlayer();
}

//=====================================
//ゲーム画面の描画処理
//=====================================
void DrawGame(void)
{
	SetCamera();

	DrawField();

	DrawWall();

	DrawPlayer();

	if (g_Pause)
	{ // ポーズ中のみ
		DrawPause();
	}

}

