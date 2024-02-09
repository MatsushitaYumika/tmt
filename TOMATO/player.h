//=========================================================
//DirectXでの図形描画+α[Player.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _PLAYER_H_	//このマクロ定義がされていなかったら
#define _PLAYER_H_	//2重インクルード防止のマクロ定義

//=====================================
//モデル構造体を定義
//=====================================
typedef struct
{	
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nMumMat;
	BYTE* pVtxBuff;	//頂点バッファへのポインタ
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	D3DXMATRIX mtxWorld;	//これは描画でやるから初期化しない
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 vtxMin;	//当たり判定(Min値)
	D3DXVECTOR3 vtxMax;	//当たり判定(Max値)
	D3DXVECTOR3 size;	//当たり判定(奥行)
	int nIdxModelParent;	//親モデルのインデックス(aModel[]の番号)
}ModelParts;

//=====================================
//プレイヤー構造体を定義
//=====================================
typedef struct
{	
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//位置(古い)
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 move;	//動き
	D3DXVECTOR3 vtxMin;	//当たり判定(Min値)
	D3DXVECTOR3 vtxMax;	//当たり判定(Max値)
	D3DXVECTOR3 size;	//当たり判定(奥行)
	ModelParts aModel[3];	//[]の中身はパーツ数
	D3DXMATRIX mtxWorld;	//これは描画でやるから初期化しない
	int nCntType;	//modelとcarry_modelで何番目のモデルを持っているか判定するための変数
	bool bIsLanding, bIsLandingCarry;
}Player;

//=====================================
//プロトタイプ宣言(処理)
//=====================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif
