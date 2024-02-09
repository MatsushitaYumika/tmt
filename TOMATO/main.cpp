//=========================================================
//2Dアクション[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "player.h"	//プレイヤーの宣言の複合体
#include "input.h"	//キーボードの宣言の複合体
#include "camera.h"
#include "light.h"
#include "field.h"
#include "wall.h"
#include "game.h"
#include <stdio.h>
#include "title.h"
#include "fade.h"
#include "tutorial.h"

//=====================================
//マクロ定義
//=====================================
#define CLASS_NAME	"WindowClass"	//ウィンドウクラスの名前
#define WINDOW_NAME	"3D"	//ウィンドウの名前(キャプションに表示)
#define FPS	(1000 / 60)	//FPS

//=====================================
//プロトタイプ宣言
//=====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//=====================================
//グローバル変数
//=====================================
LPDIRECT3D9	g_pD3D = NULL;	//DirectX3Dオブジェへのポインタ
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//DirectX3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;	//フォントへのポインタ
int g_nCountFPS = 0;	//FPSカウンタ
MODE g_mode = MODE_TITLE;	//現在のモード

//=====================================
//メイン関数
//=====================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),	//WINDCLASSEXのメモリサイズ
		CS_CLASSDC,	//ウィンドウのスタイル
		WindowProc,	//ウィンドウプロシージャ
		0,	//0にする(通常はしない)
		0,	//0にする(通常はしない)
		hInstance,	//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),	//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),	//クライアント領域の背景色
		NULL,	//メニューバー
		CLASS_NAME,	//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),	//ファイルのアイコン
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//画面サイズの構造体

	HWND hWnd;	//ウィンドウハンドル(識別子)
	MSG msg;	//メッセージを格納する変数

	DWORD dwCurrentTime;	//現在時刻
	DWORD dwExecLastTime;	//最後に処理した時刻
	DWORD dwFrameCount;	//フレームカウント
	DWORD dwFPSLastTime;	//最後にFPSを計測した時刻

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
		CLASS_NAME,		//ウィンドウクラスの名前
		WINDOW_NAME,	//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
		CW_USEDEFAULT,	//ウィンドウの左上X座標
		CW_USEDEFAULT,	//ウィンドウの左上Y座標
		(rect.right - rect.left),	//ウィンドウの左上幅
		(rect.bottom - rect.top),	//ウィンドウの左上高さ
		NULL,	//親ウィンドウのハンドル
		NULL,	//メニューハンドルまたは子ウィンドウID
		hInstance,	// インスタンスハンドル
		NULL);	//ウィンドウ作成データ

	//初期化設定
	if (FAILED(Init(hInstance,hWnd,TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	timeBeginPeriod(1);	//分解能を設定
	dwCurrentTime = 0;	//初期化する
	dwExecLastTime = timeGetTime();	//現在時刻を取得
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);	//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);	//クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);	//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();	//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	//FPSを計測した時刻を保存

				dwFrameCount = 0;	//フレームカウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (FPS))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;	//処理開始の時刻[現在時刻]を保存

				//更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;	//フレームカウントを加算　
			}
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//=====================================
//ウィンドウプロシージャ
//=====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case	WM_CLOSE:	//閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//0を返さないと終了してしまう
		}
		break;

	case WM_DESTROY:	//ウィンドウ破棄のメッセージ
	//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case	WM_KEYDOWN:	//キー押下のメッセージ
		switch (wParam)
		{
		case	VK_ESCAPE:	//[ESC]キーが押された
		//メッセージBOXを表示
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{//「はい」を選択した場合
				//ウィンドウ破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//既定の処理を返す
}

//=====================================
//初期化処理
//=====================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)	//TRUE:ウィンドウ/FALSE:フルスクリーン
{
	D3DDISPLAYMODE d3ddm;	//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;	//バックバッファの形式
	d3dpp.BackBufferCount = 1;	//バッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;	//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//デプスバッファを16bit使う
	d3dpp.Windowed = bWindow;	//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理はハードウェア、頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			return E_FAIL;
		}
	}

	//デバッグ表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice,
	18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", & g_pFont);

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステート
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパットの初期化処理
	if (FAILED(InitJoyPad()))
	{
		return E_FAIL;
	}

	InitFade();
	 
	//タイトル画面の初期化処理
	InitTitle();

	//チュートリアル画面の初期化処理
	InitTutorial();

	//ゲーム画面の初期化処理
	InitGame();

	//モードの設定
	SetMode(g_mode);

	return S_OK;
}

//=====================================
//終了処理
//=====================================
void Uninit(void)
{
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面の終了処理
		UninitTitle();
	break;

	case MODE_TUTORIAL:	//チュートリアル画面の終了処理
		UninitTutorial();
		break;

	case MODE_GAME:	//ゲーム画面の終了処理
		UninitGame();
	break;

	//case MODE_RANKING:	//ランキング画面の終了処理
	//	UninitRanking();
	//	break;
	}



	//ゲーム画面の終了処理
	//UninitGame();

	//キーボードの終了処理
	UninitKeyboard();

	//ジョイパットの終了処理
	UninitJoyPad();

	//フェードの終了処理
	UninitFade();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=====================================
//更新処理
//=====================================
void Update(void)
{
	//フェードの更新処理
	UpdateFade();

	//ゲームの更新処理
	/*UpdateGame();*/

	//キーボードの更新処理
	UpdateKeyboard();

	//ジョイパットの更新処理
	UpdateJoyPad();

	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面の更新処理
		UpdateTitle();
		break;

	case MODE_TUTORIAL:	//チュートリアル画面の更新処理
		UpdateTutorial();
		break;

	case MODE_GAME:	//ゲーム画面の更新処理
		UpdateGame();
		break;
	}
}

//=====================================
//描画処理
//=====================================
void Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);	//画面クリア時の色(背景色)

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画が成功した場合
		//ゲームの描画処理
		/*DrawGame();*/

		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面の終了処理
			DrawTitle();
		break;

		case MODE_TUTORIAL:	//チュートリアル画面の終了処理
			DrawTutorial();
			break;

		case MODE_GAME:	//ゲーム画面の終了処理
			DrawGame();
		break;
		}


#ifdef _DEBUG
		//FPSの表示
		DrawFPS();
#endif

		//フェードの描画処理
		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=====================================
//モードの設定
//=====================================
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面の終了処理
		UninitTitle();
	break;

	case MODE_TUTORIAL:	//チュートリアル画面の終了処理
		UninitTutorial();
		break;

	case MODE_GAME:	//ゲーム画面の終了処理
		UninitGame();
	break;

	}

	//新しいの画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE:	//タイトル画面の初期化処理
		InitTitle();
	break;

	case MODE_TUTORIAL:	//チュートリアル画面の初期化処理
		InitTutorial();
		break;

	case MODE_GAME:	//ゲーム画面の初期化処理
		InitGame();
	break;

	}
	g_mode = mode;	//現在の画面(モード)を切り替える
}

//=====================================
//デバイスの取得
//=====================================
LPDIRECT3DDEVICE9	GetDevice(void)
{
	return g_pD3DDevice;
}

//=====================================
//モードの取得
//=====================================
MODE GetMode(void)
{
	return g_mode;
}

//=====================================
//FPSの表示
//=====================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n\n↑,↓:上下カメラ移動\nW,A,S,D:プレイヤーとカメラ追従移動\nR,F:視点移動\nT,G:注視点移動", g_nCountFPS);

	//テキストの描画処理
	g_pFont->DrawText(NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}