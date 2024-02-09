//=========================================================
//3Dgame[game.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//2重インクルード防止のマクロ定義

//=====================================
//インクルード
//=====================================
#include "main.h"

//=====================================
//プロトタイプ宣言(処理)
//=====================================
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif
