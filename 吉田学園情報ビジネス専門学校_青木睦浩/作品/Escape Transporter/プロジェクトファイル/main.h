//=============================================================================
//
// ���C������ [main.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>								// Windows
#include "d3dx9.h"									// �`��ɕK�v
#define DIRECTINPUT_VERSION (0x0800)				//�r���h���̌x���Ώ��p�}�N��
#include <dinput.h>									// directinput
#include "xaudio2.h"								// XAudio2�֘A�̃w�b�_�[
#include <stdio.h>									// rand�֐��g�p
#include <time.h>									// time�֐��g�p
#include <XInput.h>									// Xinput

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")					// �`��ɕK�v
#pragma comment (lib, "d3dx9.lib")					// [d3dx9, lib]�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")					// DirectX�R���|�[�l���g(���i)�ɕK�v
#pragma comment (lib, "dinput8.lib")				// DInput���͂ɕK�v
#pragma comment (lib, "xinput.lib")					// XInput���͂ɕK�v
#pragma comment (lib, "winmm.lib")					// FPS�\������

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Escape Transporter"	// �E�C���h�E�̃L���v�V������
#define SCREEN_WIDTH (1280)							// �E�B���h�E�̕�
#define SCREEN_HEIGHT (720)							// �E�B���h�E�̍���	

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int GetFPS(void);									// FPS�擾����
#endif