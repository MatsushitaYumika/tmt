//=========================================================
//DirectX�ł�8�����ړ�����[input.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�C���N���[�h
//=====================================
#include "input.h"

//=====================================
//�}�N����`
//=====================================
#define NUM_KEY_MAX	(256)	//�L�[�̍ő吔
#define MAX_PRESS	(10)	//�L�[�{�[�h�̒���������(���s�[�g�p)

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECTINPUT8 g_pInput = NULL;  //DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];              //�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];       //�L�[�{�[�h�̃g���K�[���
XINPUT_STATE g_joyKeyState;	//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joyKeyStateTrigger;	//�W���C�p�b�h�̃v���X���
int g_nCntKeyTime = 0;	//�L�[�{�[�h�̃��s�[�g����

//=================================================================================================================
//�L�[�{�[�h

//=====================================
//�L�[�{�[�h�̏���������
//=====================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�f�o�C�X�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();
	return S_OK;

	g_nCntKeyTime = 0;
}

//=====================================
//�L�[�{�[�h�̏I������
//=====================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����l��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=====================================
//�L�[�{�[�h�̍X�V����
//=====================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̓��͏��
	int nCountKey;
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCountKey = 0; nCountKey < NUM_KEY_MAX; nCountKey++)
		{
			g_aKeyStateTrigger[nCountKey] = (g_aKeyState[nCountKey] ^ aKeyState[nCountKey]) & aKeyState[nCountKey]; //�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyState[nCountKey] = aKeyState[nCountKey]; //�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//=====================================
//�L�[�{�[�h�ւ̃v���X�����擾
//=====================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) != 0;
}

//=====================================
//�L�[�{�[�h�ւ̃g���K�[�����擾
//=====================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//===============================================================
//�L�[�{�[�h�̃��s�[�g�����擾
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
		g_nCntKeyTime++; //���������Ă��鎞�Ԃ����Z����
		if (g_nCntKeyTime >= MAX_PRESS)//��莞�Ԃ��o�߂�����
		{
			g_nCntKeyTime = 0;

			return true;
		}
	}

	return false;
}

//=================================================================================================================
//�W���C�p�b�g

//=====================================
//�W���C�p�b�g�̏���������
//=====================================
HRESULT InitJoyPad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));//�v���X�p

	//�������̃N���A
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));//�g���K�[�p

	//Xinput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//=====================================
//�W���C�p�b�g�̏I������
//=====================================
void UninitJoyPad(void)
{
	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//=====================================
//�W���C�p�b�g�̍X�V����
//=====================================
void UpdateJoyPad(void)
{
	XINPUT_STATE joyKeyState;	//�W���C�p�b�h�̓��͏��

	XINPUT_STATE joyKeyStateTrigger;

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;
		g_joyKeyStateTrigger.Gamepad.wButtons = ~OldButton & Button;
		g_joyKeyState = joyKeyState;	//�W���C�p�b�h�̃v���X����ۑ�

	}
}

//=====================================
//�W���C�p�b�g�ւ̃v���X�����擾
//=====================================
bool GetJoyPadPress(JOYKEY Key)
{
	return(g_joyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//===============================================================
//�W���C�p�b�h�̃g���K�[�����擾
//===============================================================
bool GetJoypadTrigger(JOYKEY key)
{
	return((g_joyKeyStateTrigger.Gamepad.wButtons) & (0x01 << key));
}

//===============================================================
//�W���C�p�b�h�̃��s�[�g�����擾
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
		g_nCntKeyTime++; //���������Ă��鎞�Ԃ����Z����
		if (g_nCntKeyTime >= MAX_PRESS)//��莞�Ԃ��o�߂�����
		{
			g_nCntKeyTime = 0;

			return true;
		}
	}

	return false;

}