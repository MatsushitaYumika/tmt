//=========================================================
//DirectXでの8方向移動処理[light.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _LIGHT_H_	//このマクロ定義がされてなかったら
#define _LIGHT_H_	//2重インクルード防止のマクロ定義

//=====================================
//インクルード
//=====================================
#include "main.h"

//=====================================
//プロトタイプ宣言(処理)
//=====================================
void InitLight(void);
void UninitLight(void);
void UpdateLight(void);

#endif
