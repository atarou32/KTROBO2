#include "KTRoboInput.h"
#include "mmsystem.h"
#include "windowsx.h"

#include "KTRoboCS.h"
#include "KTRoboInputGamePad.h"
#include "KTRoboLog.h"
#include "MyTokenAnalyzer.h"

using namespace KTROBO;

DWORD Input::now_time=0;
DWORD Input::last_time=0;

Input::Input(void)
{
	
	
}


Input::~Input(void)
{
}


void Input::Init(HWND hwnd) {
	now_time = timeGetTime();
	last_time = now_time;
	nagaosi_start_time = now_time;
	for (int i=0;i<256;i++) {
		keystate[i] = 0;
		b_keystate[i] = 0;
	}

	for (int i=0;i<INPUTJYOUTAI_FRAME_MAX;i++) {
		input_jyoutai_idou[i] = 0;
		input_jyoutai_koudou[i] = 0;
	}

	command_key[INPUTJYOUTAI_KEY_INDEX_BACK] = INPUTJYOUTAI_KEY_DEFAULT_BACK;
	command_key[INPUTJYOUTAI_KEY_INDEX_FORWARD] = INPUTJYOUTAI_KEY_DEFAULT_FORWARD;
	command_key[INPUTJYOUTAI_KEY_INDEX_FRIEND] = INPUTJYOUTAI_KEY_DEFAULT_FRIEND;
	command_key[INPUTJYOUTAI_KEY_INDEX_JUMP] = INPUTJYOUTAI_KEY_DEFAULT_JUMP;
	command_key[INPUTJYOUTAI_KEY_INDEX_JYAKU_KICK] = INPUTJYOUTAI_KEY_DEFAULT_JYAKU_KICK;
	command_key[INPUTJYOUTAI_KEY_INDEX_KYOU_KICK] = INPUTJYOUTAI_KEY_DEFAULT_KYOU_KICK;
	command_key[INPUTJYOUTAI_KEY_INDEX_JYAKU_PUNCH] = INPUTJYOUTAI_KEY_DEFAULT_JYAKU_PUNCH;
	command_key[INPUTJYOUTAI_KEY_INDEX_KYOU_PUNCH] = INPUTJYOUTAI_KEY_DEFAULT_KYOU_PUNCH;
	command_key[INPUTJYOUTAI_KEY_INDEX_KAMAE] = INPUTJYOUTAI_KEY_DEFAULT_KAMAE;
	command_key[INPUTJYOUTAI_KEY_INDEX_KOKYUU] = INPUTJYOUTAI_KEY_DEFAULT_KOKYUU;

	command_key[INPUTJYOUTAI_KEY_INDEX_LEFT] = INPUTJYOUTAI_KEY_DEFAULT_LEFT;
	command_key[INPUTJYOUTAI_KEY_INDEX_PICK] = INPUTJYOUTAI_KEY_DEFAULT_PICK;
	command_key[INPUTJYOUTAI_KEY_INDEX_RIGHT] = INPUTJYOUTAI_KEY_DEFAULT_RIGHT;
	command_key[INPUTJYOUTAI_KEY_INDEX_SHAGAMI] = INPUTJYOUTAI_KEY_DEFAULT_SHAGAMI;



	#ifndef HID_USAGE_PAGE_GENERIC
    #define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
    #endif
    #ifndef HID_USAGE_GENERIC_MOUSE
    #define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
    #endif
    RAWINPUTDEVICE Rid[1];
    Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
    Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
    Rid[0].dwFlags = RIDEV_INPUTSINK;   
    Rid[0].hwndTarget = hwnd;
    RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	HRESULT hr = InputGamePad::getInstance()->InitDirectInput(hwnd);
	if (FAILED(hr)) throw GameError(KTROBO::FATAL_ERROR, "no gamepad");



}
void Input::Del() {

	InputGamePad::getInstance()->FreeDirectInput();



}
LRESULT CALLBACK Input::myWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {

   PAINTSTRUCT ps;
   HDC hdc;
   static BYTE keys[256];
   memset(keys,0,256);
   static unsigned char exclude_keys[] = {0xF0,0xF3,0xF6,0xFB};
   static int ek_len = 4;
    switch( message )
    {
	case WM_CREATE:
		SetTimer(hWnd, 0, 1000 / 30, NULL);
		break;





	case WM_ACTIVATE:
		if (WA_INACTIVE != wParam)
		{
			// Make sure the device is acquired, if we are gaining focus.
			InputGamePad::getInstance()->acquire();
		}
		break;

	case WM_TIMER:
		// Update the input device every timer message
		CS::instance()->enter(CS_MESSAGE_CS, "enter message make");
		if (FAILED(InputGamePad::getInstance()->UpdateInputState(hWnd)))
		{
	//		KillTimer(hDlg, 0);
	//		MessageBox(NULL, TEXT("Error Reading Input State. ") \
				TEXT("The sample will now exit."), TEXT("DirectInput Sample"),
	//			MB_ICONERROR | MB_OK);
	//		EndDialog(hDlg, TRUE);
			mylog::writelog(KTROBO::INFO, "update input gamepad failed\n");

		}
		for (int i = 0; i < KTROBO_GAMEPAD_BUTTON_MAX; i++) {
			BYTE state = InputGamePad::getInstance()->js.rgbButtons[i];

			if ((state & 0x80)) {
				// 押されている
				Input::gamepad_state.button[i] |= KTROBO_INPUT_BUTTON_PRESSED;
			}
			if ((state & 0x80) && !(b_gamepad_state.button[i] & KTROBO_INPUT_BUTTON_PRESSED)) {
				// 押された瞬間
				Input::gamepad_state.button[i] |= KTROBO_INPUT_BUTTON_DOWN;

			}
			if (!(state & 0x80) && (b_gamepad_state.button[i] & KTROBO_INPUT_BUTTON_PRESSED)) {
				Input::gamepad_state.button[i] |= KTROBO_INPUT_BUTTON_UP;
				Input::gamepad_state.button[i] &= ~KTROBO_INPUT_BUTTON_PRESSED;
			}
		}
		
		
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_X_AXIS]  = (int)InputGamePad::getInstance()->js.lX;
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_Y_AXIS] = (int)InputGamePad::getInstance()->js.lY;
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_Z_AXIS] = (int)InputGamePad::getInstance()->js.lZ;
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_X_ROT] = (int)InputGamePad::getInstance()->js.lRx;
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_Y_ROT] = (int)InputGamePad::getInstance()->js.lRy;
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_Z_ROT] = (int)InputGamePad::getInstance()->js.lRz;
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_SLIDER_0] = (int)InputGamePad::getInstance()->js.rglSlider[0];// lY;
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_SLIDER_1] = (int)InputGamePad::getInstance()->js.rglSlider[1];
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_0] = (int)InputGamePad::getInstance()->js.rgdwPOV[0];
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_1] = (int)InputGamePad::getInstance()->js.rgdwPOV[1];
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_2] = (int)InputGamePad::getInstance()->js.rgdwPOV[2];
		Input::gamepad_state.axisrotsliderpov[KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_3] = (int)InputGamePad::getInstance()->js.rgdwPOV[3];

		for (int i = 0; i < KTROBO_GAMEPAD_CONFIG_STATE_MAX; i++) {
			if ((Input::gamepad_state.rules[i].is_button == true) && (Input::gamepad_state.rules[i].index == KTROBO_GAMEPAD_BUTTON_NOUSE)) continue;
			if (Input::gamepad_state.rules[i].is_button) {
				Input::gamepad_state.config_state[i] = Input::gamepad_state.button[Input::gamepad_state.rules[i].index];
			} else {
				if ((Input::gamepad_state.rules[i].index >= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_START) && (Input::gamepad_state.rules[i].index <= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_END)) {
				// pov なら　valueと一致したときに　セットする
					if (Input::gamepad_state.rules[i].pov_value == Input::gamepad_state.axisrotsliderpov[Input::gamepad_state.rules[i].index]) {
						Input::gamepad_state.config_state[i] = Input::gamepad_state.rules[i].pov_value;
					}
					else {
						// 違ったら反応してたのを消す
						Input::gamepad_state.config_state[i] = KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_DEFAULT;
					}
				
				
				}
				else {
					Input::gamepad_state.config_state[i] = Input::gamepad_state.axisrotsliderpov[Input::gamepad_state.rules[i].index];
				}
			}
		}

		CS::instance()->leave(CS_MESSAGE_CS, "enter message make");
		InputMessageDispatcher::messageMake();

		break;






		case WM_IME_SETCONTEXT:
		case WM_IME_STARTCOMPOSITION:
		case WM_IME_COMPOSITION:
		case WM_IME_ENDCOMPOSITION:
		case WM_IME_NOTIFY:
		lParam = 0;
		break;
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;
		case WM_INPUT:
			{
			 UINT dwSize;
      
			 GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
			 unsigned char* lpb = new unsigned char[dwSize];
			 if (lpb == NULL)
			{
				// エラー
				break;
			}

			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			{
				// エラー
				delete[] lpb;
				break;
			}

			RAWINPUT* raw = (RAWINPUT*)lpb;

		    if (raw->header.dwType == RIM_TYPEMOUSE) 
            {
				Input::mouse_state.mouse_rawx = raw->data.mouse.lLastX;
				Input::mouse_state.mouse_rawy = raw->data.mouse.lLastY;
				Input::mouse_state.mouse_rawdx = mouse_state.mouse_rawx - b_mousestate.mouse_rawx;
				Input::mouse_state.mouse_rawdy = mouse_state.mouse_rawy - b_mousestate.mouse_rawy;
				Input::mouse_state.mouse_button = raw->data.mouse.ulButtons;
				if (raw->data.mouse.ulButtons & KTROBO_MOUSESTATE_R_UP) {
					Input::mouse_state.mouse_r_button_pressed = false;
				}
				if (raw->data.mouse.ulButtons & KTROBO_MOUSESTATE_R_DOWN) {
					Input::mouse_state.mouse_r_button_pressed = true;
				}
				if (raw->data.mouse.ulButtons & KTROBO_MOUSESTATE_L_UP) {
					Input::mouse_state.mouse_l_button_pressed = false;
				}
				if (raw->data.mouse.ulButtons & KTROBO_MOUSESTATE_L_DOWN) {
					Input::mouse_state.mouse_l_button_pressed = true;
				}


		/*		char test[256];
				memset(test,0,256);
				_itoa_s(Input::mouse_state.mouse_rawx,test,10);
				OutputDebugStringA(test);
				OutputDebugStringA(";");
				memset(test,0,256);
				_itoa_s(raw->data.mouse.ulButtons,test,10);
				OutputDebugStringA(test);
				OutputDebugStringA("\n");*/
			}

			delete[] lpb; 
			}

			InputMessageDispatcher::messageMake();
			break;
		case WM_KEYUP:
			if (GetKeyboardState(keys)) {
			for (int i=0;i<256;i++) {
				bool e = false;
				for (int k = 0;k<ek_len;k++) {
					if ((unsigned char)i == exclude_keys[k]) {
						e = true;
					}
				}
				if (e) continue;

				BYTE state = keys[i];
				if ((state & 0x80)) {
					// 押されている
					Input::keystate[i] |= KTROBO_INPUT_BUTTON_PRESSED;
				}
				if ((state & 0x80) && !(b_keystate[i] & KTROBO_INPUT_BUTTON_PRESSED)) {
					// 押された瞬間
					Input::keystate[i] |= KTROBO_INPUT_BUTTON_DOWN;
				}
				if (!(state & 0x80) && (b_keystate[i] & KTROBO_INPUT_BUTTON_PRESSED)) {
					Input::keystate[i] |= KTROBO_INPUT_BUTTON_UP;
					Input::keystate[i] &= ~KTROBO_INPUT_BUTTON_PRESSED;
				}
			}
			}
			InputMessageDispatcher::messageMake();
			break;
		case WM_KEYDOWN:
			if (GetKeyboardState(keys)) {
			for (int i=0;i<256;i++) {
				bool e = false;
				for (int k = 0;k<ek_len;k++) {
					if ((unsigned char)i == exclude_keys[k]) {
						e = true;
					}
				}
				if (e) continue;

				BYTE state = keys[i];
				if ((state & 0x80)) {
					// 押されている
					Input::keystate[i] |= KTROBO_INPUT_BUTTON_PRESSED;
				}
				if ((state & 0x80) && !(b_keystate[i] & KTROBO_INPUT_BUTTON_PRESSED)) {
					// 押された瞬間
					Input::keystate[i] |= KTROBO_INPUT_BUTTON_DOWN;
				
				}
				if (!(state & 0x80) && (b_keystate[i] & KTROBO_INPUT_BUTTON_PRESSED)) {
					Input::keystate[i] |= KTROBO_INPUT_BUTTON_UP;
					Input::keystate[i] &= ~KTROBO_INPUT_BUTTON_PRESSED;
				}
			}
			}
			InputMessageDispatcher::messageMake();
			break;

		case WM_MOUSEMOVE:
			{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam);
			Input::mouse_state.mouse_x = xPos;
			Input::mouse_state.mouse_y = yPos;
			Input::mouse_state.mouse_dx = xPos - b_mousestate.mouse_x;
			Input::mouse_state.mouse_dy = yPos - b_mousestate.mouse_y;

			InputMessageDispatcher::messageMake();
			}
			break;
			
        case WM_DESTROY:
			KillTimer(hWnd, 0);
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}



INPUTGETBYMESSAGESTRUCT InputMessageDispatcher::message_getter_structs[KTROBO_INPUTGETMESSAGESTRUCT_SIZE];
volatile DWORD InputMessageDispatcher::now_time=0;
MYINPUTMESSAGESTRUCT InputMessageDispatcher::message_structs[KTROBO_INPUTMESSAGESTRUCT_SIZE];
int InputMessageDispatcher::now_message_index=0; 

void InputMessageDispatcher::Init() {
	now_time = timeGetTime();
	before_time = now_time;
	dt = 0;
	rootinputget = registerImpl(&getinputdonone, NULL,NULL);
}



void InputMessageDispatcher::_messageDispatch(MYINPUTMESSAGESTRUCT* message, INPUTGETBYMESSAGESTRUCT* get_input, DWORD time) {

	if (get_input->handleMessage(message->getMSGID(), (void*)message, time)) {
	
		return;
	}

	if(get_input->child) {
		InputMessageDispatcher::_messageDispatch(message, get_input->child, time);
	}


}


void InputMessageDispatcher::messageDispatch() {
	// 外部で複数スレッドをロックしてこの関数を呼び出す
	// MESSAGE_CS でロックする
	
	DWORD time = timeGetTime();
	CS::instance()->enter(CS_MESSAGE_CS, "enter message dispatch");

	int mes_index = (InputMessageDispatcher::now_message_index+1)% KTROBO_INPUTMESSAGESTRUCT_SIZE;
	for (int i=0;i<KTROBO_INPUTMESSAGESTRUCT_SIZE;i++) {
		int index = (mes_index + i) % KTROBO_INPUTMESSAGESTRUCT_SIZE;
		MYINPUTMESSAGESTRUCT* s = &InputMessageDispatcher::message_structs[index];
		if (s->getISUSE()) {
			// 処理を行う
			for (int k=0;k<KTROBO_INPUTGETMESSAGESTRUCT_SIZE;k++) {
				if (!InputMessageDispatcher::message_getter_structs[k].getParent() && message_getter_structs[k].getIsUse()) {					
					_messageDispatch(s, &message_getter_structs[k], time);
				}
			}

			s->setISUSE(false);
		}
	}


	CS::instance()->leave(CS_MESSAGE_CS, "leave message dispatch");
}



void InputMessageDispatcher::messageMakeMouseRawStateChanged(DWORD n_time) {
	MYINPUTMESSAGESTRUCT* s = &InputMessageDispatcher::message_structs[now_message_index];
	s->setSENDER(KTROBO_INPUT_MESSAGE_SENDER_INPUTSYSTEM);
	s->setMSGID(KTROBO_INPUT_MESSAGE_ID_MOUSERAWSTATE);
	s->setTIME(n_time);
	s->setKEYSTATE(Input::keystate);
	s->setMOUSESTATE(&Input::mouse_state);
	s->setGAMEPADSTATE(&Input::gamepad_state);
	s->setISUSE(true);
	Input::b_mousestate.mouse_dx = 0;
	Input::b_mousestate.mouse_dy = 0;
	Input::mouse_state.mouse_dx = 0;
	Input::mouse_state.mouse_dy = 0;
	Input::mouse_state.mouse_button = 0;
	InputMessageDispatcher::now_message_index = (InputMessageDispatcher::now_message_index +1) % KTROBO_INPUTMESSAGESTRUCT_SIZE;
}


bool InputMessageDispatcher::_commandHantei(MyCommand* com, int k) {

	int now_index = 0;
	int idou_max = 0;
	int koudou_max = 0;
	for (int t = INPUT_MYCOMMAND_FRAME_MAX-1;t >=0; t--) {
		if (Input::input_jyoutai_idou[t]) {
			idou_max = t;
			break;
		}
	}

	for (int t = INPUT_MYCOMMAND_FRAME_MAX-1;t >=0; t--) {
		if (Input::input_jyoutai_koudou[t]) {
			koudou_max = t;
			break;
		}
	}



	for (int i=k;i<k+com->frame && now_index < INPUT_MYCOMMAND_FRAME_MAX;i++) {
		int inde = i % INPUTJYOUTAI_FRAME_MAX;
		if (Input::input_jyoutai_idou[inde]) {
			if ((com->idou[now_index] & Input::input_jyoutai_idou[inde]) == com->idou[now_index]) {
				if (Input::input_jyoutai_koudou[inde]) {
						if ((Input::input_jyoutai_koudou[inde] & com->koudou[now_index]) == com->koudou[now_index]) {
							now_index++;
						}
				} else {
					now_index++;
				}
			}
		} else {
		
			if (Input::input_jyoutai_koudou[inde]) {
				if ((Input::input_jyoutai_koudou[inde] & com->koudou[now_index]) == com->koudou[now_index]) {
					now_index++;
				}
			} else {
				now_index++;
			}
		}

		if (now_index > idou_max && now_index > koudou_max) {
			return true;
		}
	}


	return false;
}

void InputMessageDispatcher::commandMake(DWORD time) {


	for (int p=0;p<15;p++) {
		for (int i=0;i<KTROBO_INPUTCOMMAND_SIZE;i++) {
			MyCommand* com = &command[i];
			if (com->is_use) {
				if (com->priority == p) {
					// 一致判定を行う
					int j_index = (1+Input::input_jyoutai_index) % INPUTJYOUTAI_FRAME_MAX;
					int j_max_index = j_index + INPUTJYOUTAI_FRAME_MAX;
					for (int k = j_index; k < j_max_index - com->frame;k++) {
						if (_commandHantei(com, k)) {
							if (com->is_reset) {
								// 全部input_jyoutai をクリアする
								for (int t = 0; t < INPUTJYOUTAI_FRAME_MAX;t++) {
									Input::input_jyoutai_idou[t] = 0;
									Input::input_jyoutai_koudou[t] = 0;
								}
							}
							// メッセージを作ってリターンする
							MYINPUTMESSAGESTRUCT* s = &InputMessageDispatcher::message_structs[now_message_index];
							s->setSENDER(KTROBO_INPUT_MESSAGE_SENDER_INPUTSYSTEM);
							s->setMSGID(KTROBO_INPUT_MESSAGE_ID_COMMAND);
							s->setDataINT(com->command);
							s->setTIME(time);
							s->setKEYSTATE(Input::keystate);
							s->setMOUSESTATE(&Input::mouse_state);
							s->setGAMEPADSTATE(&Input::gamepad_state);
							s->setISUSE(true);
							InputMessageDispatcher::now_message_index = (InputMessageDispatcher::now_message_index +1) % KTROBO_INPUTMESSAGESTRUCT_SIZE;
							return;
						}
					}
				}
			}
		}
	}
}

void InputMessageDispatcher::messageMakeButtonDown(int i, DWORD time) {

	MYINPUTMESSAGESTRUCT* s = &InputMessageDispatcher::message_structs[now_message_index];
	s->setSENDER(KTROBO_INPUT_MESSAGE_SENDER_INPUTSYSTEM);
	s->setMSGID(KTROBO_INPUT_MESSAGE_ID_KEYDOWN);
	s->setTIME(time);
	s->setKEYSTATE(Input::keystate);
	s->setMOUSESTATE(&Input::mouse_state);
	s->setGAMEPADSTATE(&Input::gamepad_state);
	s->setISUSE(true);
	InputMessageDispatcher::now_message_index = (InputMessageDispatcher::now_message_index +1) % KTROBO_INPUTMESSAGESTRUCT_SIZE;

}


void InputMessageDispatcher::messageMakeGamePad(int i, DWORD time) {

	MYINPUTMESSAGESTRUCT* s = &InputMessageDispatcher::message_structs[now_message_index];
	s->setSENDER(KTROBO_INPUT_MESSAGE_SENDER_INPUTSYSTEM);
	s->setMSGID(KTROBO_INPUT_MESSAGE_ID_GAMEPAD);
	s->setTIME(time);
	s->setKEYSTATE(Input::keystate);
	s->setMOUSESTATE(&Input::mouse_state);
	s->setGAMEPADSTATE(&Input::gamepad_state);
	s->setISUSE(true);
	InputMessageDispatcher::now_message_index = (InputMessageDispatcher::now_message_index + 1) % KTROBO_INPUTMESSAGESTRUCT_SIZE;

}


void InputMessageDispatcher::messageMakeButtonUp(int i, DWORD time) {

	MYINPUTMESSAGESTRUCT* s = &InputMessageDispatcher::message_structs[now_message_index];
	s->setSENDER(KTROBO_INPUT_MESSAGE_SENDER_INPUTSYSTEM);
	s->setMSGID(KTROBO_INPUT_MESSAGE_ID_KEYUP);
	s->setTIME(time);
	s->setKEYSTATE(Input::keystate);
	s->setMOUSESTATE(&Input::mouse_state);
	s->setGAMEPADSTATE(&Input::gamepad_state);
	s->setISUSE(true);
	InputMessageDispatcher::now_message_index = (InputMessageDispatcher::now_message_index +1) % KTROBO_INPUTMESSAGESTRUCT_SIZE;

}

void InputMessageDispatcher::messageMakeMouseMove(DWORD n_time) {

	// マウスの移動メッセージ
	MYINPUTMESSAGESTRUCT* s = &InputMessageDispatcher::message_structs[now_message_index];
	s->setSENDER(KTROBO_INPUT_MESSAGE_SENDER_INPUTSYSTEM);
	s->setMSGID(KTROBO_INPUT_MESSAGE_ID_MOUSEMOVE);
	s->setTIME(n_time);
	s->setKEYSTATE(Input::keystate);
	s->setMOUSESTATE(&Input::mouse_state);
	s->setGAMEPADSTATE(&Input::gamepad_state);
	s->setISUSE(true);
	Input::mouse_state.mouse_dx = 0;
	Input::mouse_state.mouse_dy = 0;
	Input::b_mousestate.mouse_dx = 0;
	Input::b_mousestate.mouse_dy = 0;
	InputMessageDispatcher::now_message_index = (InputMessageDispatcher::now_message_index +1) % KTROBO_INPUTMESSAGESTRUCT_SIZE;

}


#define INPUTMESSAGE_MAKE_RAWXY_MIN 5

void InputMessageDispatcher::messageMake() {
	// 複数スレッドのロックはこの関数では必要ない
	// MESSAGE_CS でロックする

	

	CS::instance()->enter(CS_MESSAGE_CS, "enter message make");

	DWORD n_time = timeGetTime();
	if (now_time != n_time) {
		dt += (WORD)(n_time- now_time);

		now_time = n_time;
		if (now_time - before_time > KTROBO_INPUT_RENSYA_MAX_MILLISECOND) {
			before_time = now_time;
			int coun=0;
			while (dt >0 && coun < INPUTJYOUTAI_FRAME_MAX) {
				// フレームを進める
				Input::input_jyoutai_index = (Input::input_jyoutai_index+1)% INPUTJYOUTAI_FRAME_MAX;
				// 該当のフラグを0にする	
				Input::input_jyoutai_idou[Input::input_jyoutai_index] = 0;
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] = 0;
				
				dt -= 1000;
				if (dt <0) {
					dt = 0;
				}
				coun++;
				// 何回も回る場合はフレーム落ち？になる
			}


			// フレームが進んだので　コマンド解釈処理に入る
			commandMake(n_time);

		}
	}

	
	bool gamepad_maked = false;
	for (int i = 0; i < KTROBO_GAMEPAD_BUTTON_MAX; i++) {
		if (Input::gamepad_state.button[i]) {

			messageMakeGamePad(i, n_time);
			gamepad_maked = true;
			if (Input::gamepad_state.button[i] & KTROBO_INPUT_BUTTON_DOWN) {

				Input::gamepad_state.button[i] &= ~KTROBO_INPUT_BUTTON_DOWN;
			}
			if (Input::gamepad_state.button[i] & KTROBO_INPUT_BUTTON_UP) {
				Input::gamepad_state.button[i] &= ~KTROBO_INPUT_BUTTON_PRESSED;
				Input::gamepad_state.button[i] &= ~KTROBO_INPUT_BUTTON_UP;
			}
			
			break;
		}
	}

	if (!gamepad_maked) {
		for (int i = 0; i < KTROBO_GAMEPAD_AXISROTSLIDERPOV_MAX; i++) {
			if ((i >= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_START) && (i <= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_END)) {
				// default じゃなかったら　メッセージを作る　default の値が違っていたら・・・　コンフィグの際に困ったことになる
				// コンフィグの際に既に登録されている　キーは重複して登録させないようにすれば大丈夫かもしれない
				// またループで最後のほうで登録するようにすればダイジョブかも
				if (Input::gamepad_state.axisrotsliderpov[i] != KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_DEFAULT) {

					messageMakeGamePad(i, n_time);
					break;
				}

			}
			else {
				if (abs(Input::gamepad_state.axisrotsliderpov[i]) >= KTROBO_GAMEPAD_CONFIG_STATE_AXISROT_OFFSET) {
					messageMakeGamePad(i, n_time);
					break;
				}

			}
		}
	}
	// 現在のinput_jyoutai_indexのフラグを調べる
	for (int i=0;i<256;i++) {
		/*if (Input::keystate[i] & KTROBO_INPUT_BUTTON_PRESSED) {
			// コマンドではなくキー自体はpressedされている場合のみでは何もおきない
		} else */
		if(Input::keystate[i] & KTROBO_INPUT_BUTTON_DOWN) {
			// 押された瞬間はメッセージを飛ばす
			messageMakeButtonDown(i, n_time);
			// 押されたのでながおし判定を始める
			Input::nagaosi_keycode = i;
			Input::nagaosi_start_time = n_time;
			Input::nagaosi_time = 0;
			Input::keystate[i] &=~KTROBO_INPUT_BUTTON_DOWN;
			break;
		} else if(Input::keystate[i] & KTROBO_INPUT_BUTTON_UP) {
			// 離された瞬間もメッセージを飛ばす
			messageMakeButtonUp(i, n_time);
			// keystate をクリアする
			Input::keystate[i] &= ~KTROBO_INPUT_BUTTON_PRESSED;
			Input::keystate[i] &= ~KTROBO_INPUT_BUTTON_UP;

			if (i == Input::nagaosi_keycode) {
				Input::nagaosi_keycode = 0;
				Input::nagaosi_start_time = 0;
				Input::nagaosi_time = 0;
			}
			break;
		}
	}

	// ながおし判定の時間を計算してメッセージを作る周期になったら作る
	if (Input::nagaosi_keycode != 0) {
		DWORD dtime = n_time - Input::nagaosi_start_time;
		if (dtime > KTROBO_INPUT_RENSYA_START_MILLISECOND) {
			if (dtime > KTROBO_INPUT_RENSYA_PER_MILLISECOND + KTROBO_INPUT_RENSYA_START_MILLISECOND) {
				Input::nagaosi_start_time = n_time - KTROBO_INPUT_RENSYA_START_MILLISECOND;
				messageMakeButtonDown(Input::nagaosi_keycode, n_time);
			}
		}
	}

	if (Input::mouse_state.mouse_dx || Input::mouse_state.mouse_dy) {
		messageMakeMouseMove(n_time);
	}

	if (Input::mouse_state.mouse_rawx > INPUTMESSAGE_MAKE_RAWXY_MIN  || Input::mouse_state.mouse_rawy > 
		INPUTMESSAGE_MAKE_RAWXY_MIN  || Input::mouse_state.mouse_button) {
		messageMakeMouseRawStateChanged(n_time);
	}

	for (int i=0; i<INPUTJYOUTAI_KEY_INDEX_MAX;i++) {
		if (Input::keystate[Input::command_key[i]] & KTROBO_INPUT_BUTTON_PRESSED) {
			// pressed のときはdownのフラグを立てる
			switch(i) {
			case	INPUTJYOUTAI_KEY_INDEX_KOKYUU:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KOKYUU_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_LEFT:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_LEFT_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_RIGHT:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_RIGHT_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_FORWARD:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_FORWARD_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_BACK:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_BACK_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KAMAE:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KAMAE_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JUMP:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JUMP_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_SHAGAMI:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_SHAGAMI_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_PICK:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_PICK_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_FRIEND:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_FRIEND_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JYAKU_PUNCH:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JYAKU_PUNCH_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JYAKU_KICK:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JYAKU_KICK_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KYOU_PUNCH:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KYOU_PUNCH_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KYOU_KICK:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KYOU_KICK_DOWN;
				break;
			default:
				break;
			}

		} else if(Input::keystate[Input::command_key[i]] & KTROBO_INPUT_BUTTON_DOWN) {
			// down のときはdownのフラグを立てる
				switch(i) {
			case	INPUTJYOUTAI_KEY_INDEX_KOKYUU:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KOKYUU_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_LEFT:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_LEFT_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_RIGHT:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_RIGHT_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_FORWARD:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_FORWARD_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_BACK:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_BACK_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KAMAE:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KAMAE_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JUMP:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JUMP_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_SHAGAMI:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_SHAGAMI_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_PICK:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_PICK_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_FRIEND:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_FRIEND_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JYAKU_PUNCH:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JYAKU_PUNCH_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JYAKU_KICK:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JYAKU_KICK_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KYOU_PUNCH:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KYOU_PUNCH_DOWN;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KYOU_KICK:
				Input::input_jyoutai_koudou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KYOU_KICK_DOWN;
				break;
			default:
				break;
			}




		} else if(Input::keystate[Input::command_key[i]] & KTROBO_INPUT_BUTTON_UP) {
			// up のときはupのフラグを立てる
			switch(i) {
			case	INPUTJYOUTAI_KEY_INDEX_KOKYUU:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KOKYUU_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_LEFT:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_LEFT_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_RIGHT:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_RIGHT_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_FORWARD:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_FORWARD_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_BACK:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_BACK_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KAMAE:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KAMAE_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JUMP:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JUMP_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_SHAGAMI:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_SHAGAMI_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_PICK:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_PICK_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_FRIEND:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_FRIEND_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JYAKU_PUNCH:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JYAKU_PUNCH_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_JYAKU_KICK:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_JYAKU_KICK_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KYOU_PUNCH:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KYOU_PUNCH_UP;
				break;
			case	INPUTJYOUTAI_KEY_INDEX_KYOU_KICK:
				Input::input_jyoutai_idou[Input::input_jyoutai_index] |= INPUTJYOUTAI_KYOU_KICK_UP;
				break;
			default:
				break;
			}
		}
	}
	// b_keystate にkeystateを設定する（更新）
	for (int i=0;i<256;i++) {
		Input::b_keystate[i] = Input::keystate[i];
		//Input::keystate[i] = 0;
	}
	Input::b_mousestate = Input::mouse_state;
	Input::b_gamepad_state = Input::gamepad_state;

	//Input::mouse_state.mouse_button =0;
	/*
	Input::mouse_state.mouse_dx = 0;
	Input::mouse_state.mouse_dy = 0;
	Input::mouse_state.mouse_l_button_pressed = 0;
	Input::mouse_state.mouse_rawdx = 0;
	Input::mouse_state.mouse_rawdy = 0;
	Input::mouse_state.mouse_rawx = 0;
	Input::mouse_state.mouse_rawy = 0;
	Input::mouse_state.mouse_r_button_pressed = 0;
	Input::mouse_state.mouse_x = 0;
	Input::mouse_state.mouse_y = 0;
	*/
	CS::instance()->leave(CS_MESSAGE_CS, "leave message make");
}


INPUTGETBYMESSAGESTRUCT* InputMessageDispatcher::getGetMessageStruct(INPUTSHORICLASS* cl) {
	for (int i=0;i<KTROBO_INPUTGETMESSAGESTRUCT_SIZE;i++) {
		if (InputMessageDispatcher::message_getter_structs[i].getIsUse()) {					
			if (message_getter_structs[i].impl == cl) {
				return &message_getter_structs[i];
			}
		}
	}
	return NULL;
}
INPUTGETBYMESSAGESTRUCT* InputMessageDispatcher::registerImpl(INPUTSHORICLASS* cl, INPUTSHORICLASS* parent, INPUTSHORICLASS* child) {
	

	CS::instance()->enter(CS_MESSAGE_CS, "enter message make");

	for (int i=0;i<KTROBO_INPUTGETMESSAGESTRUCT_SIZE;i++) {
		if (InputMessageDispatcher::message_getter_structs[i].getIsUse()) {
			if (message_getter_structs[i].impl == cl) throw new GameError(KTROBO::WARNING, "registered inputmessagedispatcher imple two times");
		}
	}
	for (int i=0;i<KTROBO_INPUTGETMESSAGESTRUCT_SIZE;i++) {
		if (!InputMessageDispatcher::message_getter_structs[i].getIsUse()) {
			INPUTGETBYMESSAGESTRUCT* parent_struct=NULL;
			INPUTGETBYMESSAGESTRUCT* child_struct = NULL;
			if (parent) {
				parent_struct = getGetMessageStruct(parent);
				if (parent_struct) {
					parent_struct->setChild(&message_getter_structs[i]);
				}
			}
			if (child) {
				child_struct = getGetMessageStruct(child);
				if (child_struct) {
					child_struct->setParent(&message_getter_structs[i]);
				}
			}
			message_getter_structs[i].setParam(cl,parent_struct, child_struct);
			message_getter_structs[i].setIsUse(true);
			CS::instance()->leave(CS_MESSAGE_CS, "leave message make");
			return &message_getter_structs[i];
		}
	}
	CS::instance()->leave(CS_MESSAGE_CS, "leave message make");
	throw new GameError(KTROBO::FATAL_ERROR, "to many registerimpl");



	
}



void InputMessageDispatcher::unregisterImpl(INPUTSHORICLASS* cl) {

	
	CS::instance()->enter(CS_MESSAGE_CS, "enter message make");
	INPUTGETBYMESSAGESTRUCT* str = getGetMessageStruct(cl);
	if (str) {
		INPUTGETBYMESSAGESTRUCT* p = str->getParent();
		INPUTGETBYMESSAGESTRUCT* c = str->getChild();
		if (p) {
			p->setChild(c);
		}
		if (c) {
			c->setParent(p);
		}
		str->setParam(NULL,NULL,NULL);
		str->setIsUse(false);
	}
	CS::instance()->leave(CS_MESSAGE_CS, "leave message make");


}



volatile unsigned char Input::keystate[256];
MOUSE_STATE Input::mouse_state;
volatile unsigned char Input::b_keystate[256];
MOUSE_STATE Input::b_mousestate;

GAMEPAD_STATE Input::gamepad_state;
GAMEPAD_STATE Input::b_gamepad_state;


volatile unsigned char Input::nagaosi_keycode;// 最後に押されたボタンの仮想キーコード
volatile DWORD Input::nagaosi_time;// 押されてからたった時間 

volatile long Input::input_jyoutai_idou[INPUTJYOUTAI_FRAME_MAX];
volatile long Input::input_jyoutai_koudou[INPUTJYOUTAI_FRAME_MAX];
volatile unsigned int Input::input_jyoutai_index=0;

volatile DWORD InputMessageDispatcher::before_time=0;
volatile WORD InputMessageDispatcher::dt=0;
volatile DWORD Input::nagaosi_start_time=0; // 押され始めた時間

volatile unsigned char Input::command_key[INPUTJYOUTAI_KEY_INDEX_MAX];
MyCommand InputMessageDispatcher::command[KTROBO_INPUTCOMMAND_SIZE];
INPUTGETBYMESSAGESTRUCT* InputMessageDispatcher::rootinputget=0;
INPUTSHORINONE InputMessageDispatcher::getinputdonone;



void InputMessageDispatcher::setCommand(MyCommand* coms, int len) {
	if (len <= KTROBO_INPUTCOMMAND_SIZE) {

		// 全てクリアする
		for (int i=0;i<KTROBO_INPUTCOMMAND_SIZE;i++) {
			command[i].is_use = false;
		}

		for (int i=0;i<len;i++) {
			command[i] = coms[i];
			command[i].is_use = true;
		}

	} else {
		throw new GameError(KTROBO::FATAL_ERROR, "too many commands");
	}

}



void Input::saveGamePadRule() {
	FILE* file;

	string filename = string("userdata/gamepad.myconfig");
	
	CS::instance()->enter(CS_LOG_CS, "saveasm");
		if (0 != fopen_s(&file, filename.c_str(), "w")) {
			CS::instance()->leave(CS_LOG_CS, "saveasm");
			return;
		}

		fclose(file);


		for (int i = 0; i < KTROBO_GAMEPAD_CONFIG_STATE_MAX; i++) {

			int bool_is_button=0;
			int bool_is_minus=0;
			if (gamepad_state.rules[i].is_button) {
				bool_is_button = 1;
			}
			if (gamepad_state.rules[i].is_minus) {
				bool_is_minus = 1;
			}
			if ((bool_is_button) && (gamepad_state.rules[i].index == KTROBO_GAMEPAD_BUTTON_NOUSE)) {
			} else {
				mylog::writelog(filename.c_str(), "{ %d; %d; %d; %d; %d;}\n", bool_is_button, bool_is_minus,
					i, gamepad_state.rules[i].index, gamepad_state.rules[i].pov_value);

			}

		}


	CS::instance()->leave(CS_LOG_CS, "loaditem");
	



}
void Input::loadGamePadRule() {

	// もしゲームパッドがあれば
	if (InputGamePad::getInstance()->getPJOYSTICK()) {

		FILE* fi;
		const char* filename = "userdata/gamepad.myconfig";
		CS::instance()->enter(CS_LOG_CS, "log");
		if (0 != fopen_s(&fi, filename, "r")) {
			KTROBO::mylog::writelog(KTROBO::INFO, "%s の読み込みに失敗", filename);
			CS::instance()->leave(CS_LOG_CS, "log");
			//throw new KTROBO::GameError(KTROBO::FATAL_ERROR, filename);
			return;
		}
		fclose(fi);
		CS::instance()->leave(CS_LOG_CS, "log");
		MyTokenAnalyzer ma;
		if (ma.load(filename)) {
			while (!ma.enddayo()) {
				ma.GetToken("{");
				int bool_is_button = ma.GetIntToken();
				int bool_is_minus = ma.GetIntToken();
				int i = ma.GetIntToken();
				int index = ma.GetIntToken();
				int pov_value = ma.GetIntToken();
				bool is_button = false;
				if (bool_is_button) {
					is_button = true;
				}
				bool is_minus = false;
				if (bool_is_minus) {
					is_minus = true;
				}
				if (ma.enddayo()) break;
				Input::setGamePadRule(is_button, is_minus, index, i, pov_value);
				ma.GetToken("}");
			}




			ma.deletedayo();
		}
	}
}