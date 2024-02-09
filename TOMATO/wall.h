//=========================================================
//DirectXでの図形描画+α[Wall.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _WALL_H_	//このマクロ定義がされていなかったら
#define _WALL_H_	//2重インクルード防止のマクロ定義

//=====================================
//インクルード
//=====================================
#include "main.h"

//=====================================
//カメラ構造体を定義
//=====================================
typedef struct
{
	int nType;
	D3DXVECTOR3 pos;	//
	D3DXVECTOR3 rot;	//
	D3DXVECTOR3 vtxMin;	//当たり判定(Min値)
	D3DXVECTOR3 vtxMax;	//当たり判定(Max値)
	BYTE* pVtxBuff;	//頂点バッファへのポインタ
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	int nNumVtx;	//頂点数
	bool bUse;
	//D3DXVECTOR3 vecU;	//
}Wall;

//=====================================
//プロトタイプ宣言(処理)
//=====================================
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif