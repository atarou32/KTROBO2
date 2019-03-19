#ifndef KTROBOINPUT_H
#define KTROBOINPUT_H

#pragma once
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "KTRoboClock.h"
#include "winuser.h"


namespace KTROBO {


#define KTROBO_INPUT_BUTTON_DOWN 0x01
#define KTROBO_INPUT_BUTTON_PRESSED 0x02
#define KTROBO_INPUT_BUTTON_UP 0x04
#define KTROBO_INPUT_RENSYA_MAX_MILLISECOND 30 // 1�t���[���̃~���Z�R���h
#define KTROBO_INPUT_RENSYA_START_MILLISECOND 500
#define KTROBO_INPUT_RENSYA_PER_MILLISECOND 200 // �Ȃ���������DOWN���b�Z�[�W������������̃~���Z�R���h


class INPUTSHORICLASS {
public:
	virtual bool handleMessage(int msg, void* data, DWORD time)=0;
};

class INPUTSHORINONE : public INPUTSHORICLASS {
public:
	bool handleMessage(int msg, void* data, DWORD time) {return true;}
	INPUTSHORINONE(){};
	~INPUTSHORINONE(){};
};

struct INPUTGETBYMESSAGESTRUCT {
public:
	INPUTGETBYMESSAGESTRUCT* parent;
	INPUTGETBYMESSAGESTRUCT* child;
	bool is_use;
	INPUTSHORICLASS* impl;

	INPUTGETBYMESSAGESTRUCT* getParent() {
		return parent;
	}
	INPUTGETBYMESSAGESTRUCT* getChild() {
		return child;
	}

	void setParent(INPUTGETBYMESSAGESTRUCT* p) {
		parent = p;
	}

	void setChild(INPUTGETBYMESSAGESTRUCT* p) {
		child = p;
	}

	bool handleMessage(int msg, void* data, DWORD time) {
		// ���b�Z�[�W���󂯎���ď������s���A�����Ń`�F�C�����Ƃ߂�Ȃ��true��Ԃ�
		return impl->handleMessage(msg, data, time);
	}

	INPUTGETBYMESSAGESTRUCT() {
		this->impl = 0;
		this->parent = 0;
		this->child = 0;
		this->is_use = false;
	}
	void setIsUse(bool t) {
		is_use = t;
	}

	bool getIsUse() {return is_use;}

	void setParam(INPUTSHORICLASS* impl, INPUTGETBYMESSAGESTRUCT* parent, INPUTGETBYMESSAGESTRUCT* child) {
		this->impl = impl;
		this->parent = parent;
		this->child = child;
		this->is_use = true;
	}

};


#define KTROBO_MOUSESTATE_L_DOWN 0x01
#define KTROBO_MOUSESTATE_L_UP 0x02
#define KTROBO_MOUSESTATE_R_DOWN 0x04
#define KTROBO_MOUSESTATE_R_UP 0x08

struct MOUSE_STATE {
public:
//	unsigned char mouse_r_button;
//	unsigned char mouse_l_button;
//	unsigned char mouse_m_button;

	int mouse_x;
	int mouse_y;
	int mouse_dx;
	int mouse_dy;
	long mouse_rawx;
	long mouse_rawy;
	long mouse_rawdx;
	long mouse_rawdy;
	long mouse_button;
	bool mouse_r_button_pressed;
	bool mouse_l_button_pressed;

	MOUSE_STATE() {
//		mouse_r_button = 0;
//		mouse_l_button = 0;
//		mouse_m_button = 0;
		mouse_x = 0;
		mouse_y = 0;
		mouse_dx = 0;
		mouse_dy = 0;
		mouse_rawx = 0;
		mouse_rawy = 0;
		mouse_button = 0;
		mouse_r_button_pressed = false;
		mouse_l_button_pressed = false;
	}

	/*MOUSE_STATE& operator=(MOUSE_STATE& value) {
		this->mouse_dx = value.mouse_dx;
		this->mouse_dy = value.mouse_dy;
		this->mouse_l_button = value.mouse_l_button;
		this->mouse_m_button = value.mouse_m_button;
		this->mouse_r_button = value.mouse_r_button;
		this->mouse_x = value.mouse_x;
		this->mouse_y = value.mouse_y;
        return *this;
    }*/

	MOUSE_STATE& operator=(MOUSE_STATE& value) {
		this->mouse_dx = value.mouse_dx;
		this->mouse_dy = value.mouse_dy;
//		this->mouse_l_button = value.mouse_l_button;
//		this->mouse_m_button = value.mouse_m_button;
//		this->mouse_r_button = value.mouse_r_button;
		this->mouse_x = value.mouse_x;
		this->mouse_y = value.mouse_y;
		this->mouse_rawx = value.mouse_rawx;
		this->mouse_rawy = value.mouse_rawy;
		this->mouse_button = value.mouse_button;
		this->mouse_l_button_pressed = value.mouse_l_button_pressed;
		this->mouse_r_button_pressed = value.mouse_r_button_pressed;
        return *this;
    }
	/*
	volatile MOUSE_STATE& operator=(volatile MOUSE_STATE& value) volatile{
		this->mouse_dx = value.mouse_dx;
		this->mouse_dy = value.mouse_dy;
//		this->mouse_l_button = value.mouse_l_button;
//		this->mouse_m_button = value.mouse_m_button;
//		this->mouse_r_button = value.mouse_r_button;
		this->mouse_x = value.mouse_x;
		this->mouse_y = value.mouse_y;
		this->mouse_rawx = value.mouse_rawx;
		this->mouse_rawy = value.mouse_rawy;
		this->mouse_button = value.mouse_button;
		this->mouse_l_button_pressed = value.mouse_l_button_pressed;
		this->mouse_r_button_pressed = value.mouse_r_button_pressed;
        return *this;
    }*/
};

class MYMESSAGESTRUCT;


#define KTROBO_INPUT_MESSAGE_SENDER_INPUTSYSTEM 0

#define KTROBO_INPUT_MESSAGE_ID_NONE 0
#define KTROBO_INPUT_MESSAGE_ID_UNKNOWN 1
#define KTROBO_INPUT_MESSAGE_ID_COMMAND 2
#define KTROBO_INPUT_MESSAGE_ID_KEYUP 3
#define KTROBO_INPUT_MESSAGE_ID_KEYDOWN 4
#define KTROBO_INPUT_MESSAGE_ID_MOUSEMOVE 5
#define KTROBO_INPUT_MESSAGE_ID_MOUSERAWSTATE 6 // �{�^���̏�ԕύX�������ɓ���
class MYMESSAGESTRUCT {
public:
	int msg_id;
	int sender;
	int data_int;// �R�}���h��ID�Ɏg���I
	void* data;
	bool is_use;
	
	DWORD time;
	MYMESSAGESTRUCT() {
		msg_id = 0;
		sender = 0;
		data = 0;
		is_use = false;
		time = 0;
		data_int = 0;
	
	}
	DWORD getTIME() {return time;}
	int getMSGID() {return msg_id;}
	int getSENDER() {return sender;}
	void* getData() {return data;}
	int getDataINT() {return data_int;}
	bool getISUSE() {return is_use;}

	void setTIME(DWORD t) {time =t;}
	void setMSGID(int m) {msg_id=m;}
	void setSENDER(int s) {sender=s;}
	void setData(void* d) {data=d;}
	void setDataINT(int t) {data_int = t;}
	void setISUSE(bool i) {is_use=i;}

};


class MYINPUTMESSAGESTRUCT : public MYMESSAGESTRUCT{
public:
	float X;
	float Y;
	float DX;
	float DY;
	unsigned char keystate[256];
	MOUSE_STATE mousestate;
	MYINPUTMESSAGESTRUCT() : MYMESSAGESTRUCT() {
		X = 0;
		Y = 0;
		DX = 0;
		DY = 0;
		for (int i=0;i<256;i++) {
			keystate[i] = 0;
		}
		mousestate;
	}

	float getX() {return X;}
	float getY() {return Y;}
	float getDX() {return DX;}
	float getDY() {return DY;}
	unsigned char* getKEYSTATE() {return keystate;}
	MOUSE_STATE* getMOUSESTATE() {return &mousestate;}

	void setX(float x) {X=x;}
	void setY(float y) {Y=y;}
	void setDX(float dx) {DX=dx;}
	void setDY(float dy) {DY=dy;}
	void setKEYSTATE(volatile unsigned char* y) {
		for (int i=0;i<256;i++) {
			keystate[i]=y[i];
		}
	}
	void setMOUSESTATE(MOUSE_STATE* m) {mousestate=*m;}

};


#define INPUT_MYCOMMAND_FRAME_MAX 30
class MyCommand {
public:
	int command;
	int priority; // 0~15 0 �̂ق����D�悳���
	int frame; // 0~INPUTJYOUTAI_FRAME_MAX
	unsigned long idou[INPUT_MYCOMMAND_FRAME_MAX];
	unsigned long koudou[INPUT_MYCOMMAND_FRAME_MAX];
	char name[32];
	bool is_use;
	bool is_reset; // ���������Ƃ��o�b�t�@���N���A���邩�ǂ���
	MyCommand() {
		command = 0;
		priority = 0;
		frame = 0;
		for (int i=0;i<INPUT_MYCOMMAND_FRAME_MAX;i++) {
			idou[i] = 0;
			koudou[i] = 0;
		}
		for (int i=0;i<32;i++) {
			name[i] = 0;
		}
		is_use = false;
		is_reset = false;
	}


	MyCommand& operator=(MyCommand& value) {
		this->command = value.command;
		this->frame = value.frame;
		for (int i=0;i<INPUT_MYCOMMAND_FRAME_MAX;i++) {
			this->idou[i] = value.idou[i];
			this->koudou[i] = value.koudou[i];
		}
		this->priority = value.priority;
		for (int i=0;i<32;i++) {
			this->name[i] = value.name[i];
		}
		this->is_use = value.is_use;
		this->is_reset = value.is_reset;

        return *this;
    }





};

#define KTROBO_INPUTMESSAGESTRUCT_SIZE 128
#define KTROBO_INPUTGETMESSAGESTRUCT_SIZE 96
#define KTROBO_INPUTCOMMAND_SIZE 48






class InputMessageDispatcher {
public:
	// input���󂯎���ē��삷�镔���Ƃ����̂͂���Ȃɑ����Ȃ��C������
	// ����𗘗p������C���v�b�g�����C���ɂ����Q�[��������悤�ɂȂ邩������Ȃ�
	// �Ƃ肠����96�Őݒ肵�Ă݂�
	// ���͏����Ńo�b�t�@���ǂ̂��炢�ɐݒ肷�邩
	// �܂����͂��ǂ�ǂ񂭂�Ƃ��܂��́@���̃X���b�h���x���Ȃ��Ă���Ƃ���
	// ���̓o�b�t�@�ɂ��܂������͂͂ǂ�����̂�
	// ���͂ɂ��Ă͏�������悤�ɂ���
	// �܂�㏑������
	// ��������Βx���Ȃ��Ă���Ƃ��Ƀ{�^���������Ă��������Ȃ����Ƃ����邪
	// ��x�����Ă��炦�Α��v�Ȃ͂��E�E�E
	// �o�b�t�@�ɂ��񂵂Ă�128�݂��Ă݂�

	// �R�}���h�̎�ނɊւ���
	// ���K�v�Ȃ̂��낤

	// �O�i
	// ��i
	// �E�ړ�
	// ���ړ�
	// �퓬�Ԑ�(�\���̕ύX)
	// ���Ⴊ��
	// �_�b�V��
	// �E�X�e�b�v
	// ���X�e�b�v
	// �o�b�N�X�e�b�v
	// ���W�����v
	// ���W�����v
	// ��W�����v
	// �_�b�V���W�����v
	// �E���E������
	// �F�D�s��
	// ��p���`
	// ���p���`
	// ��L�b�N
	// ���L�b�N
	// �ċz
	// ���Ⴊ�ݎ�p���`
	// ���Ⴊ�݋��p���`
	// ���Ⴊ�ݎ�L�b�N
	// ���Ⴊ�݋��L�b�N
	// �W�����v��p���`
	// �W�����v���p���`
	// �W�����v��L�b�N
	// �W�����v���L�b�N
	// �K�E�Z�P
	// �K�E�Z�Q
	// �K�E�Z�R
	// �K�E�Z�S
	// �K�E�Z�T
	//�@��34

	static INPUTGETBYMESSAGESTRUCT* rootinputget;
	static INPUTSHORINONE getinputdonone;
	static INPUTGETBYMESSAGESTRUCT message_getter_structs[KTROBO_INPUTGETMESSAGESTRUCT_SIZE];
	static volatile DWORD now_time;
	static volatile DWORD before_time;
	static volatile WORD dt;
	static MyCommand command[KTROBO_INPUTCOMMAND_SIZE];

	static MYINPUTMESSAGESTRUCT message_structs[KTROBO_INPUTMESSAGESTRUCT_SIZE];
	static int now_message_index; 
	// ���݂̃o�b�t�@�̃C���f�b�N�X ���̃C���f�b�N�X+1�̃C���f�b�N�X����C���f�b�N�X�̈ʒu�܂ł̃I�u�W�F�N�g��is_use��true�̂���
	// �����������
	static void Init();
	static void messageDispatch();
	static void messageMake();
	static INPUTGETBYMESSAGESTRUCT* getRootInputGetStruct() {return rootinputget;}

	static void messageMakeButtonDown(int i, DWORD ntime);
	static void messageMakeButtonUp(int i, DWORD ntime);
	static void messageMakeMouseMove(DWORD n_time);
	static void messageMakeMouseRawStateChanged(DWORD n_time);
	static void setCommand(MyCommand* coms, int len);

	static void commandMake(DWORD time);
	static bool _commandHantei(MyCommand* com, int k);

	static void _messageDispatch(MYINPUTMESSAGESTRUCT* message, INPUTGETBYMESSAGESTRUCT* get_input, DWORD time);
	static INPUTGETBYMESSAGESTRUCT* registerImpl(INPUTSHORICLASS* cl, INPUTSHORICLASS* parent, INPUTSHORICLASS* child);
	static void unregisterImpl(INPUTSHORICLASS* cl);
	static INPUTGETBYMESSAGESTRUCT* getGetMessageStruct(INPUTSHORICLASS* cl);
};


// ���������̎����Ƃ��ǂ�����΂����̂�
// �����������R�}���h�Ǝ�������
// ����̃t���[�����ɊY���̃{�^��������邢�͎O�o�ꂵ�Ă���Δ���OK�Ƃ���
// �R�}���h�̎����Ƃ��ǂ�����΂����̂�
// �t���[�����ƂɃC���v�b�g�̏�Ԃ�ۑ����Ă���
// �t���[�����ƂɃR�}���h�̔�����s���@�����厖�@�X���b�h�̃��[�v�i�P�������炢�j�ł͂Ȃ��@�t���[���̎��ԒP�ʂŁi30ms���炢�H)�@
// �R�}���h�ɂ���āA
// ���̃R�}���h�ɂȂ���悤�ȃR�}���h�̏ꍇ�̓R�}���h�������Ȃ�
// ��{�ړ���s���̃R�}���h�̓R�}���h�������Ȃ� �W�����v���Ⴊ�݁A�O�ړ����ړ����ړ��ȂǃK�[�h
// �R�}���h�͓����R�}���h��������o��̂�h�����߂ɃR�}���h��S�N���A����

// ���߃p���`�̎����ɂ���
// �{�^���𒷂������Ă��邩�ǂ����̔���͂ǂ������炢���̂�
// ����̃t���[���̊ԉ�����Ă��邩�ǂ������R�}���h�Ƃ��ēo�^����΂悢
// �{�^���������ꂽ�Ƃ��ɔ������邩�A����̎��Ԃ����ꂽ�Ƃ��ɔ������邩�́@�R�}���h�ɂ��
// ���ߏ�ԂɂȂ邩�ǂ����̔���ɃR�}���h���g���āA�j���[�g���������ߏ�ԉ����Ɏg��
// ���ߏ�Ԏ��Ƀ{�^�������R�}���h�����m������Z�𔭓�������
// �R�}���h�̔���ő�t���[�����ɂ���
// 50�t���[���Ƃ��Ă݂悤 (50*30 = 1500 �P�D�T�b�j


// �A�ł̎����ɂ���
// �{�^���A�łɂ���
// �{�^���A�ł̏ꍇ�̓R�}���h�������Ȃ��H �������
// ���Ԃ�j���[�g�����̏�Ԃ̃R�}���h���{�^���A�ł���߂��Ƃ��ɗ���āA
// ���̂Ƃ��ɃL�����N�^�[�̋Z������Ԃ����������悤�ɂȂ��Ă���͂�
// �܂�L�����N�^�[�̏�ԑJ�ڂ̖��ɂȂ�

// �R�}���h�����߂�������͂��ɂ����炢���̂��낤
// �P�t���[�����Ƃɍs��



#define INPUTJYOUTAI_KEY_DEFAULT_KOKYUU VK_LCONTROL
#define INPUTJYOUTAI_KEY_DEFAULT_LEFT 'A'
#define INPUTJYOUTAI_KEY_DEFAULT_RIGHT 'D'
#define INPUTJYOUTAI_KEY_DEFAULT_FORWARD 'W'
#define INPUTJYOUTAI_KEY_DEFAULT_BACK 'S'
#define INPUTJYOUTAI_KEY_DEFAULT_KAMAE 'Q'
#define INPUTJYOUTAI_KEY_DEFAULT_JUMP VK_SPACE
#define INPUTJYOUTAI_KEY_DEFAULT_SHAGAMI VK_LSHIFT

#define INPUTJYOUTAI_KEY_DEFAULT_PICK 'E'
#define INPUTJYOUTAI_KEY_DEFAULT_FRIEND 'C'
#define INPUTJYOUTAI_KEY_DEFAULT_JYAKU_PUNCH 'R'
#define INPUTJYOUTAI_KEY_DEFAULT_JYAKU_KICK 'F'
#define INPUTJYOUTAI_KEY_DEFAULT_KYOU_PUNCH 'T'
#define INPUTJYOUTAI_KEY_DEFAULT_KYOU_KICK 'G'

#define INPUTJYOUTAI_KEY_INDEX_KOKYUU 0
#define INPUTJYOUTAI_KEY_INDEX_LEFT 1
#define INPUTJYOUTAI_KEY_INDEX_RIGHT 2
#define INPUTJYOUTAI_KEY_INDEX_FORWARD 3
#define INPUTJYOUTAI_KEY_INDEX_BACK 4
#define INPUTJYOUTAI_KEY_INDEX_KAMAE 5
#define INPUTJYOUTAI_KEY_INDEX_JUMP 6
#define INPUTJYOUTAI_KEY_INDEX_SHAGAMI 7
#define INPUTJYOUTAI_KEY_INDEX_PICK 8
#define INPUTJYOUTAI_KEY_INDEX_FRIEND 9
#define INPUTJYOUTAI_KEY_INDEX_JYAKU_PUNCH 10
#define INPUTJYOUTAI_KEY_INDEX_JYAKU_KICK 11
#define INPUTJYOUTAI_KEY_INDEX_KYOU_PUNCH 12
#define INPUTJYOUTAI_KEY_INDEX_KYOU_KICK 13
#define INPUTJYOUTAI_KEY_INDEX_MAX 14

// �ړ��\����
#define INPUTJYOUTAI_FRAME_MAX 50
#define INPUTJYOUTAI_KOKYUU_UP 0x01
#define INPUTJYOUTAI_KOKYUU_DOWN 0x02
#define INPUTJYOUTAI_LEFT_UP 0x04
#define INPUTJYOUTAI_LEFT_DOWN 0x08
#define INPUTJYOUTAI_RIGHT_UP 0x010
#define INPUTJYOUTAI_RIGHT_DOWN 0x020
#define INPUTJYOUTAI_FORWARD_UP 0x040
#define INPUTJYOUTAI_FORWARD_DOWN 0x080
#define INPUTJYOUTAI_BACK_UP 0x0100
#define INPUTJYOUTAI_BACK_DOWN 0x0200
#define INPUTJYOUTAI_KAMAE_UP 0x0400
#define INPUTJYOUTAI_KAMAE_DOWN 0x0800
#define INPUTJYOUTAI_JUMP_UP 0x1000
#define INPUTJYOUTAI_JUMP_DOWN 0x2000
#define INPUTJYOUTAI_SHAGAMI_UP 0x4000
#define INPUTJYOUTAI_SHAGAMI_DOWN 0x8000

// �s���\����
#define INPUTJYOUTAI_MOUSEBUTTON_R_UP 0x0001
#define INPUTJYOUTAI_MOUSEBUTTON_R_DOWN 0x0002
#define INPUTJYOUTAI_MOUSEBUTTON_L_UP 0x0004
#define INPUTJYOUTAI_MOUSEBUTTON_L_DOWN 0x0008
#define INPUTJYOUTAI_PICK_UP 0x0010
#define INPUTJYOUTAI_PICK_DOWN 0x0020
#define INPUTJYOUTAI_FRIEND_UP 0x0040
#define INPUTJYOUTAI_FRIEND_DOWN 0x0080
#define INPUTJYOUTAI_JYAKU_PUNCH_UP 0x0100
#define INPUTJYOUTAI_JYAKU_PUNCH_DOWN 0x0200
#define INPUTJYOUTAI_KYOU_PUNCH_UP 0x0400
#define INPUTJYOUTAI_KYOU_PUNCH_DOWN 0x0800
#define INPUTJYOUTAI_JYAKU_KICK_UP 0x1000
#define INPUTJYOUTAI_JYAKU_KICK_DOWN 0x2000
#define INPUTJYOUTAI_KYOU_KICK_UP 0x4000
#define INPUTJYOUTAI_KYOU_KICK_DOWN 0x8000




class Input
{
private:
	static DWORD now_time;
	static DWORD last_time;
	static Clock clock;
	

public:
	static volatile unsigned char keystate[256];
	static MOUSE_STATE mouse_state;
	static volatile unsigned char b_keystate[256];
	static MOUSE_STATE b_mousestate;
	static volatile unsigned char nagaosi_keycode;// �Ō�ɉ����ꂽ�{�^���̉��z�L�[�R�[�h // inputtext�p
	static volatile DWORD nagaosi_start_time; // ������n�߂�����
	static volatile DWORD nagaosi_time;// ������Ă��炽�������� // inputtext�p
	static volatile long input_jyoutai_idou[INPUTJYOUTAI_FRAME_MAX];
	static volatile long input_jyoutai_koudou[INPUTJYOUTAI_FRAME_MAX];
	static volatile unsigned int input_jyoutai_index;

	static volatile unsigned char command_key[INPUTJYOUTAI_KEY_INDEX_MAX];

public:
	Input(void);
	~Input(void);

	static void Init(HWND hwnd);
	static void setCommandKey(unsigned char* c) {
		for (int i=0;i<INPUTJYOUTAI_KEY_INDEX_MAX;i++) {
			command_key[i] = c[i];
		}
	}

	static LRESULT CALLBACK myWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
};

}

#endif