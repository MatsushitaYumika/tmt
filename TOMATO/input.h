//=========================================================
//DirectXでの8方向移動処理[input.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _INPUT_H_	//このマクロ定義がされてなかったら
#define _INPUT_H_	//2重インクルード防止のマクロ定義

//=====================================
//インクルード
//=====================================
#include "main.h"

//=====================================
//ジョイパット構造体を定義
//=====================================
typedef enum
{
	JOYKEY_UP = 0,	//十字キー(↑)
	JOYKEY_DOWN,	//十字キー(↓)
	JOYKEY_LEFT,	//十字キー(←)
	JOYKEY_RIGHT,	//十字キー(→)
	JOYKEY_A,	//A
	JOYKEY_B,	//B
	JOYKEY_Y,	//Y
	JOYKEY_X,	//X
	JOYKEY_RT,	//RT
	JOYKEY_LT,	//LT
	JOYKEY_START,	//スタートボタン
	JOYKEY_BACK,	//バックボタン
	JOYKEY_LEFT_THUMB,	//左スティック(押し込み)
	JOYKEY_RIGHT_THUMB,	//右スティック(押し込み)
	JOYKEY_AUTO,			//オートボタン
	JOYKEY_CLEAR,			//クリアボタン
	JOYKEY_ZR,	   //右トリガー
	JOYKEY_MAX
}JOYKEY;

//=====================================
//プロトタイプ宣言(処理)
//=====================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化処理
void UninitKeyboard(void);	//キーボードの終了処理
void UpdateKeyboard(void);	//キーボードの更新処理
bool GetKeyboardPress(int nKey);	//キーボードのプレス処理
bool GetKeyboardTrigger(int nKey);	//キーボードのトリガー処理
bool GetKeyboardRepeat(int nKey);	//キーボードのリピート処理

HRESULT InitJoyPad(void);	//ジョイパッドの初期化処理
void UninitJoyPad(void);	//ジョイパッドの終了処理
void UpdateJoyPad(void);	//ジョイパッドの更新処理
bool GetJoyPadPress(JOYKEY Key);	//ジョイパッドのプレス情報
bool GetJoypadTrigger(JOYKEY key);	//ジョイパッドのトリガー情報
bool GetJoypadRepeat(JOYKEY key);	//ジョイパッドのリピート情報

#endif