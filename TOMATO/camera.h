//=========================================================
//DirectXでの8方向移動処理[camera.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _CAMERA_H_	//このマクロ定義がされてなかったら
#define _CAMERA_H_	//2重インクルード防止のマクロ定義

//=====================================
//インクルード
//=====================================
#include "main.h"

//=====================================
//カメラ構造体を定義
//=====================================
typedef struct
{
	D3DXVECTOR3 posV;	//視点
	D3DXVECTOR3 posR;	//注視点
	D3DXVECTOR3 vecU;	//上方向ベクトル
	D3DXVECTOR3 move;	//移動
	D3DXVECTOR3 rot;	//回転
	float fDistance;	//距離
	bool bUsePosV;
	bool bUsePosR;
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;	//ビューマトリックス
}Camera;

//=====================================
//プロトタイプ宣言(処理)
//=====================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera* GetCamera(void);
#endif
