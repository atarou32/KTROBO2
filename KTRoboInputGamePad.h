#ifndef KTROBO_INPUT_GAME_PAD_H
#define KTROBO_INPUT_GAME_PAD_H


#define STRICT
#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_DEPRECATE
#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif



#pragma once
#include <Windows.h>
#include <CommCtrl.h>
#include <basetsd.h>
#include <dinput.h>
#include <dinputd.h>
#include <assert.h>
#include <OleAuto.h>
#include <shellapi.h>
#include <strsafe.h>


namespace KTROBO {

	struct XINPUT_DEVICE_NODE
	{
		DWORD dwVidPid;
		XINPUT_DEVICE_NODE* pNext;
	};

	struct DI_ENUM_CONTEXT
	{
		DIJOYCONFIG* pPreferredJoyCfg;
		bool bPreferredJoyCfgValid;
	};

//BOOL CALLBACK    EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);
//BOOL CALLBACK    EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);

class InputGamePad
{
private:
	LPDIRECTINPUT8 pDI;
	LPDIRECTINPUTDEVICE8 pJoystick;
public:
	DIJOYSTATE2 js;
private:
	
public:
	
private:
	InputGamePad();
	InputGamePad(InputGamePad& pa);
public:

	LPDIRECTINPUT8 getPDI() { return pDI; };
	LPDIRECTINPUTDEVICE8 getPJOYSTICK() { return pJoystick; };
	void setPJOYSTICK(LPDIRECTINPUTDEVICE8 m) { pJoystick = m; };
	void acquire() { if (pJoystick) { pJoystick->Acquire(); } };

	static InputGamePad* getInstance() {
		static InputGamePad instance;
		return &instance;
	}
	~InputGamePad();

	//bool IsXInputDevice(const GUID* pGuidProductFromDirectInput);
	void CleanupForIsXInputDevice();
	void SetUpForIsXInputDevice();
	HRESULT InitDirectInput(HWND hDlg);
	VOID FreeDirectInput();
	HRESULT UpdateInputState(HWND hDlg);




};

}
#endif