//=========================================================
//DirectX�ł�8�����ړ�����[input.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�}�N����`
//=====================================
#ifndef _INPUT_H_	//���̃}�N����`������ĂȂ�������
#define _INPUT_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//=====================================
//�C���N���[�h
//=====================================
#include "main.h"

//=====================================
//�W���C�p�b�g�\���̂��`
//=====================================
typedef enum
{
	JOYKEY_UP = 0,	//�\���L�[(��)
	JOYKEY_DOWN,	//�\���L�[(��)
	JOYKEY_LEFT,	//�\���L�[(��)
	JOYKEY_RIGHT,	//�\���L�[(��)
	JOYKEY_A,	//A
	JOYKEY_B,	//B
	JOYKEY_Y,	//Y
	JOYKEY_X,	//X
	JOYKEY_RT,	//RT
	JOYKEY_LT,	//LT
	JOYKEY_START,	//�X�^�[�g�{�^��
	JOYKEY_BACK,	//�o�b�N�{�^��
	JOYKEY_LEFT_THUMB,	//���X�e�B�b�N(��������)
	JOYKEY_RIGHT_THUMB,	//�E�X�e�B�b�N(��������)
	JOYKEY_AUTO,			//�I�[�g�{�^��
	JOYKEY_CLEAR,			//�N���A�{�^��
	JOYKEY_ZR,	   //�E�g���K�[
	JOYKEY_MAX
}JOYKEY;

//=====================================
//�v���g�^�C�v�錾(����)
//=====================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[�{�[�h�̏���������
void UninitKeyboard(void);	//�L�[�{�[�h�̏I������
void UpdateKeyboard(void);	//�L�[�{�[�h�̍X�V����
bool GetKeyboardPress(int nKey);	//�L�[�{�[�h�̃v���X����
bool GetKeyboardTrigger(int nKey);	//�L�[�{�[�h�̃g���K�[����
bool GetKeyboardRepeat(int nKey);	//�L�[�{�[�h�̃��s�[�g����

HRESULT InitJoyPad(void);	//�W���C�p�b�h�̏���������
void UninitJoyPad(void);	//�W���C�p�b�h�̏I������
void UpdateJoyPad(void);	//�W���C�p�b�h�̍X�V����
bool GetJoyPadPress(JOYKEY Key);	//�W���C�p�b�h�̃v���X���
bool GetJoypadTrigger(JOYKEY key);	//�W���C�p�b�h�̃g���K�[���
bool GetJoypadRepeat(JOYKEY key);	//�W���C�p�b�h�̃��s�[�g���

#endif