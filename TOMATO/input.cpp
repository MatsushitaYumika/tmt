//=========================================================
//DirectXでの8方向移動処理[input.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//インクルード
//=====================================
#include "input.h"

//=====================================
//マクロ定義
//=====================================
#define NUM_KEY_MAX	(256)	//キーの最大数
#define MAX_PRESS	(10)	//キーボードの長押し時間(リピート用)

//=====================================
//グローバル変数
//=====================================
LPDIRECTINPUT8 g_pInput = NULL;  //DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];              //キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];       //キーボードのトリガー情報
XINPUT_STATE g_joyKeyState;	//ジョイパッドのプレス情報
XINPUT_STATE g_joyKeyStateTrigger;	//ジョイパッドのプレス情報
int g_nCntKeyTime = 0;	//キーボードのリピート処理

//=================================================================================================================
//キーボード

//=====================================
//キーボードの初期化処理
//=====================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputデバイスオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマット
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();
	return S_OK;

	g_nCntKeyTime = 0;
}

//=====================================
//キーボードの終了処理
//=====================================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //キーボードへのアクセス権を獲得
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=====================================
//キーボードの更新処理
//=====================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //キーボードの入力情報
	int nCountKey;
	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCountKey = 0; nCountKey < NUM_KEY_MAX; nCountKey++)
		{
			g_aKeyStateTrigger[nCountKey] = (g_aKeyState[nCountKey] ^ aKeyState[nCountKey]) & aKeyState[nCountKey]; //キーボードのトリガー情報を保存
			g_aKeyState[nCountKey] = aKeyState[nCountKey]; //キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //キーボードのアクセス権を獲得
	}
}

//=====================================
//キーボードへのプレス情報を取得
//=====================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) != 0;
}

//=====================================
//キーボードへのトリガー情報を取得
//=====================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//===============================================================
//キーボードのリピート情報を取得
//===============================================================
bool GetKeyboardRepeat(int nKey)
{

	if (GetKeyboardPress(nKey))
	{
		if (GetKeyboardTrigger(nKey))
		{
			g_nCntKeyTime = 0;
			return true;
		}
		g_nCntKeyTime++; //長押ししている時間を加算する
		if (g_nCntKeyTime >= MAX_PRESS)//一定時間が経過したら
		{
			g_nCntKeyTime = 0;

			return true;
		}
	}

	return false;
}

//=================================================================================================================
//ジョイパット

//=====================================
//ジョイパットの初期化処理
//=====================================
HRESULT InitJoyPad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));//プレス用

	//メモリのクリア
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));//トリガー用

	//Xinputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//=====================================
//ジョイパットの終了処理
//=====================================
void UninitJoyPad(void)
{
	//XInputのステートを設定(無効にする)
	XInputEnable(false);
}

//=====================================
//ジョイパットの更新処理
//=====================================
void UpdateJoyPad(void)
{
	XINPUT_STATE joyKeyState;	//ジョイパッドの入力情報

	XINPUT_STATE joyKeyStateTrigger;

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;
		g_joyKeyStateTrigger.Gamepad.wButtons = ~OldButton & Button;
		g_joyKeyState = joyKeyState;	//ジョイパッドのプレス情報を保存

	}
}

//=====================================
//ジョイパットへのプレス情報を取得
//=====================================
bool GetJoyPadPress(JOYKEY Key)
{
	return(g_joyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//===============================================================
//ジョイパッドのトリガー情報を取得
//===============================================================
bool GetJoypadTrigger(JOYKEY key)
{
	return((g_joyKeyStateTrigger.Gamepad.wButtons) & (0x01 << key));
}

//===============================================================
//ジョイパッドのリピート情報を取得
//===============================================================
bool GetJoypadRepeat(JOYKEY key)
{
	if (GetJoyPadPress(key))
	{
		if (GetJoypadTrigger(key))
		{
			g_nCntKeyTime = 0;
			return true;
		}
		g_nCntKeyTime++; //長押ししている時間を加算する
		if (g_nCntKeyTime >= MAX_PRESS)//一定時間が経過したら
		{
			g_nCntKeyTime = 0;

			return true;
		}
	}

	return false;

}