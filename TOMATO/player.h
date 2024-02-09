//=========================================================
//DirectX�ł̐}�`�`��+��[Player.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�}�N����`
//=====================================
#ifndef _PLAYER_H_	//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//=====================================
//���f���\���̂��`
//=====================================
typedef struct
{	
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nMumMat;
	BYTE* pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	D3DXMATRIX mtxWorld;	//����͕`��ł�邩�珉�������Ȃ�
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 vtxMin;	//�����蔻��(Min�l)
	D3DXVECTOR3 vtxMax;	//�����蔻��(Max�l)
	D3DXVECTOR3 size;	//�����蔻��(���s)
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X(aModel[]�̔ԍ�)
}ModelParts;

//=====================================
//�v���C���[�\���̂��`
//=====================================
typedef struct
{	
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ʒu(�Â�)
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 move;	//����
	D3DXVECTOR3 vtxMin;	//�����蔻��(Min�l)
	D3DXVECTOR3 vtxMax;	//�����蔻��(Max�l)
	D3DXVECTOR3 size;	//�����蔻��(���s)
	ModelParts aModel[3];	//[]�̒��g�̓p�[�c��
	D3DXMATRIX mtxWorld;	//����͕`��ł�邩�珉�������Ȃ�
	int nCntType;	//model��carry_model�ŉ��Ԗڂ̃��f���������Ă��邩���肷�邽�߂̕ϐ�
	bool bIsLanding, bIsLandingCarry;
}Player;

//=====================================
//�v���g�^�C�v�錾(����)
//=====================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif
