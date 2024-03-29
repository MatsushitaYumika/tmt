//=========================================================
//DirectXでの図形描画+α[Field.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _FIELD_H_	//このマクロ定義がされていなかったら
#define _FIELD_H_	//2重インクルード防止のマクロ定義

//=====================================
//プロトタイプ宣言(処理)
//=====================================
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

#endif


