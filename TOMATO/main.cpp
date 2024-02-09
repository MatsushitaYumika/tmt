//=========================================================
//2D�A�N�V����[main.cpp]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//�C���N���[�h
//=====================================
#include "main.h"	//Windows�A�v���P�[�V�������̐錾�̕�����
#include "player.h"	//�v���C���[�̐錾�̕�����
#include "input.h"	//�L�[�{�[�h�̐錾�̕�����
#include "camera.h"
#include "light.h"
#include "field.h"
#include "wall.h"
#include "game.h"
#include <stdio.h>
#include "title.h"
#include "fade.h"
#include "tutorial.h"

//=====================================
//�}�N����`
//=====================================
#define CLASS_NAME	"WindowClass"	//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME	"3D"	//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define FPS	(1000 / 60)	//FPS

//=====================================
//�v���g�^�C�v�錾
//=====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//=====================================
//�O���[�o���ϐ�
//=====================================
LPDIRECT3D9	g_pD3D = NULL;	//DirectX3D�I�u�W�F�ւ̃|�C���^
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//DirectX3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;	//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;	//FPS�J�E���^
MODE g_mode = MODE_TITLE;	//���݂̃��[�h

//=====================================
//���C���֐�
//=====================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),	//WINDCLASSEX�̃������T�C�Y
		CS_CLASSDC,	//�E�B���h�E�̃X�^�C��
		WindowProc,	//�E�B���h�E�v���V�[�W��
		0,	//0�ɂ���(�ʏ�͂��Ȃ�)
		0,	//0�ɂ���(�ʏ�͂��Ȃ�)
		hInstance,	//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),	//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),	//�N���C�A���g�̈�̔w�i�F
		NULL,	//���j���[�o�[
		CLASS_NAME,	//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),	//�t�@�C���̃A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//��ʃT�C�Y�̍\����

	HWND hWnd;	//�E�B���h�E�n���h��(���ʎq)
	MSG msg;	//���b�Z�[�W���i�[����ϐ�

	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;	//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME,		//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,	//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,	//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,	//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),	//�E�B���h�E�̍��㕝
		(rect.bottom - rect.top),	//�E�B���h�E�̍��㍂��
		NULL,	//�e�E�B���h�E�̃n���h��
		NULL,	//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,	// �C���X�^���X�n���h��
		NULL);	//�E�B���h�E�쐬�f�[�^

	//�������ݒ�
	if (FAILED(Init(hInstance,hWnd,TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	timeBeginPeriod(1);	//����\��ݒ�
	dwCurrentTime = 0;	//����������
	dwExecLastTime = timeGetTime();	//���ݎ������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);	//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();	//���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	//FPS���v������������ۑ�

				dwFrameCount = 0;	//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (FPS))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;	//�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;	//�t���[���J�E���g�����Z�@
			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//=====================================
//�E�B���h�E�v���V�[�W��
//=====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case	WM_CLOSE:	//����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_DESTROY:	//�E�B���h�E�j���̃��b�Z�[�W
	//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case	WM_KEYDOWN:	//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case	VK_ESCAPE:	//[ESC]�L�[�������ꂽ
		//���b�Z�[�WBOX��\��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{//�u�͂��v��I�������ꍇ
				//�E�B���h�E�j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//����̏�����Ԃ�
}

//=====================================
//����������
//=====================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)	//TRUE:�E�B���h�E/FALSE:�t���X�N���[��
{
	D3DDISPLAYMODE d3ddm;	//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;	//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;	//�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;	//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�f�v�X�o�b�t�@��16bit�g��
	d3dpp.Windowed = bWindow;	//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			return E_FAIL;
		}
	}

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice,
	18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", & g_pFont);

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�g�̏���������
	if (FAILED(InitJoyPad()))
	{
		return E_FAIL;
	}

	InitFade();
	 
	//�^�C�g����ʂ̏���������
	InitTitle();

	//�`���[�g���A����ʂ̏���������
	InitTutorial();

	//�Q�[����ʂ̏���������
	InitGame();

	//���[�h�̐ݒ�
	SetMode(g_mode);

	return S_OK;
}

//=====================================
//�I������
//=====================================
void Uninit(void)
{
	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g����ʂ̏I������
		UninitTitle();
	break;

	case MODE_TUTORIAL:	//�`���[�g���A����ʂ̏I������
		UninitTutorial();
		break;

	case MODE_GAME:	//�Q�[����ʂ̏I������
		UninitGame();
	break;

	//case MODE_RANKING:	//�����L���O��ʂ̏I������
	//	UninitRanking();
	//	break;
	}



	//�Q�[����ʂ̏I������
	//UninitGame();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�W���C�p�b�g�̏I������
	UninitJoyPad();

	//�t�F�[�h�̏I������
	UninitFade();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=====================================
//�X�V����
//=====================================
void Update(void)
{
	//�t�F�[�h�̍X�V����
	UpdateFade();

	//�Q�[���̍X�V����
	/*UpdateGame();*/

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�W���C�p�b�g�̍X�V����
	UpdateJoyPad();

	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g����ʂ̍X�V����
		UpdateTitle();
		break;

	case MODE_TUTORIAL:	//�`���[�g���A����ʂ̍X�V����
		UpdateTutorial();
		break;

	case MODE_GAME:	//�Q�[����ʂ̍X�V����
		UpdateGame();
		break;
	}
}

//=====================================
//�`�揈��
//=====================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);	//��ʃN���A���̐F(�w�i�F)

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`�悪���������ꍇ
		//�Q�[���̕`�揈��
		/*DrawGame();*/

		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g����ʂ̏I������
			DrawTitle();
		break;

		case MODE_TUTORIAL:	//�`���[�g���A����ʂ̏I������
			DrawTutorial();
			break;

		case MODE_GAME:	//�Q�[����ʂ̏I������
			DrawGame();
		break;
		}


#ifdef _DEBUG
		//FPS�̕\��
		DrawFPS();
#endif

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=====================================
//���[�h�̐ݒ�
//=====================================
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g����ʂ̏I������
		UninitTitle();
	break;

	case MODE_TUTORIAL:	//�`���[�g���A����ʂ̏I������
		UninitTutorial();
		break;

	case MODE_GAME:	//�Q�[����ʂ̏I������
		UninitGame();
	break;

	}

	//�V�����̉��(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g����ʂ̏���������
		InitTitle();
	break;

	case MODE_TUTORIAL:	//�`���[�g���A����ʂ̏���������
		InitTutorial();
		break;

	case MODE_GAME:	//�Q�[����ʂ̏���������
		InitGame();
	break;

	}
	g_mode = mode;	//���݂̉��(���[�h)��؂�ւ���
}

//=====================================
//�f�o�C�X�̎擾
//=====================================
LPDIRECT3DDEVICE9	GetDevice(void)
{
	return g_pD3DDevice;
}

//=====================================
//���[�h�̎擾
//=====================================
MODE GetMode(void)
{
	return g_mode;
}

//=====================================
//FPS�̕\��
//=====================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n\n��,��:�㉺�J�����ړ�\nW,A,S,D:�v���C���[�ƃJ�����Ǐ]�ړ�\nR,F:���_�ړ�\nT,G:�����_�ړ�", g_nCountFPS);

	//�e�L�X�g�̕`�揈��
	g_pFont->DrawText(NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}