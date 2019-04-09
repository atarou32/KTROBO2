#include "KTRoboInputGamePad.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#include "KTRoboLog.h"
#include <wbemidl.h>
using namespace KTROBO;

InputGamePad::InputGamePad()
{
}


InputGamePad::~InputGamePad()
{
}
bool                    bFilterOutXinputDevices = true;
XINPUT_DEVICE_NODE*     pXInputDeviceList = NULL;
void InputGamePad::CleanupForIsXInputDevice()
{
	// Cleanup linked list
	XINPUT_DEVICE_NODE* pNode = pXInputDeviceList;
	while (pNode)
	{
		XINPUT_DEVICE_NODE* pDelete = pNode;
		pNode = pNode->pNext;
		SAFE_DELETE(pDelete);
	}
}

bool IsXInputDevice(const GUID* pGuidProductFromDirectInput);

BOOL CALLBACK    EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext) {
	HWND hDlg = (HWND)pContext;

	static int nSliderCount = 0;  // Number of returned slider controls
	static int nPOVCount = 0;     // Number of returned POV controls

	// For axes that are returned, set the DIPROP_RANGE property for the
	// enumerated axis in order to scale min/max values.
	if (pdidoi->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType; // Specify the enumerated axis
		diprg.lMin = -1000;
		diprg.lMax = +1000;
		LPDIRECTINPUTDEVICE8 pj = InputGamePad::getInstance()->getPJOYSTICK();
		// Set the range for the axis
		if (FAILED(pj->SetProperty(DIPROP_RANGE, &diprg.diph)))
			return DIENUM_STOP;

	}

	/*
	// Set the UI to reflect what objects the joystick supports
	if (pdidoi->guidType == GUID_XAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_X_AXIS), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_X_AXIS_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_YAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Y_AXIS), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Y_AXIS_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_ZAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Z_AXIS), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Z_AXIS_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_RxAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_X_ROT), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_X_ROT_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_RyAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Y_ROT), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Y_ROT_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_RzAxis)
	{
		EnableWindow(GetDlgItem(hDlg, IDC_Z_ROT), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_Z_ROT_TEXT), TRUE);
	}
	if (pdidoi->guidType == GUID_Slider)
	{
		switch (nSliderCount++)
		{
		case 0:
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER0), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER0_TEXT), TRUE);
			break;

		case 1:
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER1), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_SLIDER1_TEXT), TRUE);
			break;
		}
	}
	if (pdidoi->guidType == GUID_POV)
	{
		switch (nPOVCount++)
		{
		case 0:
			EnableWindow(GetDlgItem(hDlg, IDC_POV0), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV0_TEXT), TRUE);
			break;

		case 1:
			EnableWindow(GetDlgItem(hDlg, IDC_POV1), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV1_TEXT), TRUE);
			break;

		case 2:
			EnableWindow(GetDlgItem(hDlg, IDC_POV2), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV2_TEXT), TRUE);
			break;

		case 3:
			EnableWindow(GetDlgItem(hDlg, IDC_POV3), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_POV3_TEXT), TRUE);
			break;
		}
	}*/

	return DIENUM_CONTINUE;
}

BOOL CALLBACK    EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext) {

	DI_ENUM_CONTEXT* pEnumContext = (DI_ENUM_CONTEXT*)pContext;
	HRESULT hr;

	if ( bFilterOutXinputDevices && IsXInputDevice(&pdidInstance->guidProduct))
		return DIENUM_CONTINUE;

	// Skip anything other than the perferred joystick device as defined by the control panel.  
	// Instead you could store all the enumerated joysticks and let the user pick.
	if (pEnumContext->bPreferredJoyCfgValid &&
		!IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
		return DIENUM_CONTINUE;

	// Obtain an interface to the enumerated joystick.
	LPDIRECTINPUTDEVICE8 pj = InputGamePad::getInstance()->getPJOYSTICK();
	hr = InputGamePad::getInstance()->getPDI()->CreateDevice(pdidInstance->guidInstance, &pj, NULL);
	InputGamePad::getInstance()->setPJOYSTICK(pj);
	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr))
		return DIENUM_CONTINUE;

	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.
	return DIENUM_STOP;

}

void InputGamePad::SetUpForIsXInputDevice() {
	IWbemServices* pIWbemServices = NULL;
	IEnumWbemClassObject* pEnumDevices = NULL;
	IWbemLocator* pIWbemLocator = NULL;
	IWbemClassObject* pDevices[20] = { 0 };
	BSTR bstrDeviceID = NULL;
	BSTR bstrClassName = NULL;
	BSTR bstrNamespace = NULL;
	DWORD uReturned = 0;
	bool bCleanupCOM = false;
	UINT iDevice = 0;
	VARIANT var;
	HRESULT hr;

	// CoInit if needed
	hr = CoInitialize(NULL);
	bCleanupCOM = SUCCEEDED(hr);

	// Create WMI
	hr = CoCreateInstance(__uuidof(WbemLocator),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWbemLocator),
		(LPVOID*)&pIWbemLocator);
	if (FAILED(hr) || pIWbemLocator == NULL)
		goto LCleanup;

	// Create BSTRs for WMI
	bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2"); if (bstrNamespace == NULL) goto LCleanup;
	bstrDeviceID = SysAllocString(L"DeviceID");           if (bstrDeviceID == NULL)  goto LCleanup;
	bstrClassName = SysAllocString(L"Win32_PNPEntity");    if (bstrClassName == NULL) goto LCleanup;

	// Connect to WMI 
	hr = pIWbemLocator->ConnectServer(bstrNamespace, NULL, NULL, 0L,
		0L, NULL, NULL, &pIWbemServices);
	if (FAILED(hr) || pIWbemServices == NULL)
		goto LCleanup;

	// Switch security level to IMPERSONATE
	CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0);

	// Get list of Win32_PNPEntity devices
	hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, NULL, &pEnumDevices);
	if (FAILED(hr) || pEnumDevices == NULL)
		goto LCleanup;

	// Loop over all devices
	for (; ; )
	{
		// Get 20 at a time
		hr = pEnumDevices->Next(10000, 20, pDevices, &uReturned);
		if (FAILED(hr))
			goto LCleanup;
		if (uReturned == 0)
			break;

		for (iDevice = 0; iDevice < uReturned; iDevice++)
		{
			// For each device, get its device ID
			hr = pDevices[iDevice]->Get(bstrDeviceID, 0L, &var, NULL, NULL);
			if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != NULL)
			{
				// Check if the device ID contains "IG_".  If it does, then it’s an XInput device
				// Unfortunately this information can not be found by just using DirectInput 
				if (wcsstr(var.bstrVal, L"IG_"))
				{
					// If it does, then get the VID/PID from var.bstrVal
					DWORD dwPid = 0, dwVid = 0;
					WCHAR* strVid = wcsstr(var.bstrVal, L"VID_");
					if (strVid && swscanf(strVid, L"VID_%4X", &dwVid) != 1)
						dwVid = 0;
					WCHAR* strPid = wcsstr(var.bstrVal, L"PID_");
					if (strPid && swscanf(strPid, L"PID_%4X", &dwPid) != 1)
						dwPid = 0;

					DWORD dwVidPid = MAKELONG(dwVid, dwPid);

					// Add the VID/PID to a linked list
					XINPUT_DEVICE_NODE* pNewNode = new XINPUT_DEVICE_NODE;
					if (pNewNode)
					{
						pNewNode->dwVidPid = dwVidPid;
						pNewNode->pNext = pXInputDeviceList;
						pXInputDeviceList = pNewNode;
					}
				}
			}
			SAFE_RELEASE(pDevices[iDevice]);
		}
	}

LCleanup:
	if (bstrNamespace)
		SysFreeString(bstrNamespace);
	if (bstrDeviceID)
		SysFreeString(bstrDeviceID);
	if (bstrClassName)
		SysFreeString(bstrClassName);
	for (iDevice = 0; iDevice < 20; iDevice++)
		SAFE_RELEASE(pDevices[iDevice]);
	SAFE_RELEASE(pEnumDevices);
	SAFE_RELEASE(pIWbemLocator);
	SAFE_RELEASE(pIWbemServices);

	return;

}
bool IsXInputDevice(const GUID* pGuidProductFromDirectInput)
{
	// Check each xinput device to see if this device's vid/pid matches
	XINPUT_DEVICE_NODE* pNode = pXInputDeviceList;
	while (pNode)
	{
		if (pNode->dwVidPid == pGuidProductFromDirectInput->Data1)
			return true;
		pNode = pNode->pNext;
	}

	return false;
}
HRESULT InputGamePad::InitDirectInput(HWND hDlg) {
	HRESULT hr;
	InitCommonControls();
	bFilterOutXinputDevices = true;
	pXInputDeviceList = NULL;
	// Register with the DirectInput subsystem and get a pointer
	// to a IDirectInput interface we can use.
	// Create a DInput object
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&pDI, NULL)))
		return hr;


	if (bFilterOutXinputDevices)
		SetUpForIsXInputDevice();

	DIJOYCONFIG PreferredJoyCfg = { 0 };
	DI_ENUM_CONTEXT enumContext;
	enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
	enumContext.bPreferredJoyCfgValid = false;

	IDirectInputJoyConfig8* pJoyConfig = NULL;
	if (FAILED(hr = pDI->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig)))
		return hr;

	PreferredJoyCfg.dwSize = sizeof(PreferredJoyCfg);
	if (SUCCEEDED(pJoyConfig->GetConfig(0, &PreferredJoyCfg, DIJC_GUIDINSTANCE))) // This function is expected to fail if no joystick is attached
		enumContext.bPreferredJoyCfgValid = true;
	SAFE_RELEASE(pJoyConfig);

	// Look for a simple joystick we can use for this sample program.
	if (FAILED(hr = pDI->EnumDevices(DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		&enumContext, DIEDFL_ATTACHEDONLY)))
		return hr;

	if (bFilterOutXinputDevices)
		CleanupForIsXInputDevice();

	// Make sure we got a joystick
	if (NULL == pJoystick)
	{
		//MessageBox(NULL, TEXT("Joystick not found. The sample will now exit."),
			//TEXT("DirectInput Sample"),
	//		MB_ICONERROR | MB_OK);
		//EndDialog(hDlg, 0);

		mylog::writelog(KTROBO::INFO, "there is no gamepad\n");

		return S_OK;
	}

	// Set the data format to "simple joystick" - a predefined data format 
	//
	// A data format specifies which controls on a device we are interested in,
	// and how they should be reported. This tells DInput that we will be
	// passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
	if (FAILED(hr = pJoystick->SetDataFormat(&c_dfDIJoystick2)))
		return hr;

	// Set the cooperative level to let DInput know how this device should
	// interact with the system and with other DInput applications.
	if (FAILED(hr = pJoystick->SetCooperativeLevel(hDlg, DISCL_EXCLUSIVE |
		DISCL_FOREGROUND)))
		return hr;

	// Enumerate the joystick objects. The callback function enabled user
	// interface elements for objects that are found, and sets the min/max
	// values property for discovered axes.
	if (FAILED(hr = pJoystick->EnumObjects(EnumObjectsCallback,
		(VOID*)hDlg, DIDFT_ALL)))
		return hr;

	return S_OK;

}
VOID InputGamePad::FreeDirectInput() {
	// Unacquire the device one last time just in case 
   // the app tried to exit while the device is still acquired.
	if (pJoystick)
		pJoystick->Unacquire();

	// Release any DirectInput objects.
	SAFE_RELEASE(pJoystick);
	SAFE_RELEASE(pDI);
}
HRESULT InputGamePad::UpdateInputState(HWND hDlg) {

	HRESULT hr;
	TCHAR strText[512] = { 0 }; // Device state text
	          // DInput joystick state 

	if (NULL == pJoystick)
		return S_OK;

	// Poll the device to read the current state
	hr = pJoystick->Poll();
	if (FAILED(hr))
	{
		// DInput is telling us that the input stream has been
		// interrupted. We aren't tracking any state between polls, so
		// we don't have any special reset that needs to be done. We
		// just re-acquire and try again.
		hr = pJoystick->Acquire();
	//	while (hr == DIERR_INPUTLOST)
	//		hr = pJoystick->Acquire();

		// hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
		// may occur when the app is minimized or in the process of 
		// switching, so just try again later 
		return S_OK;
	}

	// Get the input's device state
	if (FAILED(hr = pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &js)))
		return hr; // The device should have been acquired during the Poll()

	// Display joystick state to dialog

	// Axes
	/*
	StringCchPrintf(strText, 512, TEXT("%ld"), js.lX);
	SetWindowText(GetDlgItem(hDlg, IDC_X_AXIS), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.lY);
	SetWindowText(GetDlgItem(hDlg, IDC_Y_AXIS), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.lZ);
	SetWindowText(GetDlgItem(hDlg, IDC_Z_AXIS), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.lRx);
	SetWindowText(GetDlgItem(hDlg, IDC_X_ROT), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.lRy);
	SetWindowText(GetDlgItem(hDlg, IDC_Y_ROT), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.lRz);
	SetWindowText(GetDlgItem(hDlg, IDC_Z_ROT), strText);

	// Slider controls
	StringCchPrintf(strText, 512, TEXT("%ld"), js.rglSlider[0]);
	SetWindowText(GetDlgItem(hDlg, IDC_SLIDER0), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.rglSlider[1]);
	SetWindowText(GetDlgItem(hDlg, IDC_SLIDER1), strText);

	// Points of view
	StringCchPrintf(strText, 512, TEXT("%ld"), js.rgdwPOV[0]);
	SetWindowText(GetDlgItem(hDlg, IDC_POV0), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.rgdwPOV[1]);
	SetWindowText(GetDlgItem(hDlg, IDC_POV1), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.rgdwPOV[2]);
	SetWindowText(GetDlgItem(hDlg, IDC_POV2), strText);
	StringCchPrintf(strText, 512, TEXT("%ld"), js.rgdwPOV[3]);
	SetWindowText(GetDlgItem(hDlg, IDC_POV3), strText);


	// Fill up text with which buttons are pressed
	StringCchCopy(strText, 512, TEXT(""));
	for (int i = 0; i < 128; i++)
	{
		if (js.rgbButtons[i] & 0x80)
		{
			TCHAR sz[128];
			StringCchPrintf(sz, 128, TEXT("%02d "), i);
			StringCchCat(strText, 512, sz);
		}
	}

	SetWindowText(GetDlgItem(hDlg, IDC_BUTTONS), strText);
	*/
	return S_OK;




}