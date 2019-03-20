#ifndef KTROBOSCENE_H
#define KTROBOSCENE_H

#pragma once
#include "KTRoboGraphics.h"
//#include "KTRoboGame.h"
#include "lua.hpp"
#include "MyDefine.h"
#include "KTRoboGameError.h"
#include "KTRoboTask.h"
#include "MyTokenAnalyzer.h"
#include "KTRoboInput.h"
#include "string.h"
#include "mmsystem.h"
#include "MyButukari.h"


using namespace std;
namespace KTROBO {

class Game;

// �V�[�����m�̃X�g���N�g�󂯓n���Ȃǂ͂ǂ�����̂�
// tolua�̃V���O���g���ɑS�Ď�������
// tolua�Ƃ͕ʂɃV���O���g�������Ƃ�����������Ȃ�



class Scene
{
private:
	char scene_name[32];
public:
	static Graphics* gs[TASKTHREAD_NUM];

	static Game* game;

protected:
	TCB* looptcbs[TASKTHREAD_NUM];
	bool send_remove_message;

public:	
	virtual void mainrenderIMPL(bool is_focused, Graphics* g, Game* game)=0;
	virtual void renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game)=0;
	virtual void aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game)=0;
	virtual void posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game)=0;
	virtual void loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game)=0;

public:

	virtual void enter(); // �V�[���ɓ���Ƃ��ɌĂ΂�� enter leave ���Ă΂��̂�AI�X���b�h����
	//�i��ԏ�ʂ̃X���b�h�j�ő��̃X���b�h�i�C���v�b�g�ȊO�H�j�����b�N���čs��
	virtual void leave(); // �V�[�����甲����Ƃ��ɌĂ΂��

	static void Init(Graphics** mgs,  Game* mgame) {
		for (int i=0;i<TASKTHREAD_NUM;i++) {
			gs[i] = mgs[i];
		

		}
		Scene::game = mgame; // gs ls game �̓o�^�Ɏg��
	}

	static void Del() {
		for (int i=0;i<TASKTHREAD_NUM;i++) {
			gs[i] = 0;
		}
	
	
	};

	Scene(char* n, int len) {
		if (len >= 31) {
			memcpy(scene_name,n,31);
			scene_name[31] = 0;
		} else {
			memcpy(scene_name,n, len);
			scene_name[len] = 0;
		}
		for (int i=0;i<TASKTHREAD_NUM;i++) {
			looptcbs[i] = 0;
		}
		send_remove_message = false;
		
	}
	virtual ~Scene(void);

	void mainrender(bool is_focused){
		mainrenderIMPL(is_focused, gs[TASKTHREADS_UPDATEMAINRENDER], game);
	};
	void renderhojyo(Task* task, TCB* thisTCB){
		renderhojyoIMPL(task, thisTCB, gs[TASKTHREADS_UPDATEANIMEFRAMENADO], game);
	
	};
	void ai(Task* task, TCB* thisTCB){
		aiIMPL(task, thisTCB, gs[TASKTHREADS_AIDECISION], game);
	
	};
	void posbutukari(Task* task,TCB* thisTCB){
		posbutukariIMPL(task,thisTCB, gs[TASKTHREADS_UPDATEPOSBUTUKARI], game);
	
	};
	void loaddestruct(Task* task, TCB* thisTCB){
		loaddestructIMPL(task,thisTCB,gs[TASKTHREADS_LOADDESTRUCT], game);
	};
	
};

class ONEMESSAGE : public Scene, public INPUTSHORICLASS {
	int message;
	string message_str;
public:
	void mainrenderIMPL(bool is_focused, Graphics* g, Game* game) {};
	void renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game){};
	void aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game){};
	void posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game){};
	void loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game){};

	void enter();
	void leave();

	void changeText(char* message);
	ONEMESSAGE();
	bool handleMessage(int msg, void* data, DWORD time);

};

// yes_luastr
// no_luastr�ɂ̓V�[���̃����[�u����R�}���h�������Ă��邱��

class LOADTYUU : public Scene, public INPUTSHORICLASS {
private:
	int string_id;
	DWORD time;
	int dtime;
public:
	void mainrenderIMPL(bool is_focused, Graphics* g, Game* game) {};
	void renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game){};
	void posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game){};
	void loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game){};

	void enter();
	void leave();
	bool handleMessage(int msg, void* data, DWORD time);
	LOADTYUU();
};


class TWOTAKU : public Scene, public INPUTSHORICLASS {// ���̃V�[���ɃC���v�b�g���b�Z�[�W�𑗂点�Ȃ����߂�INPUTSHORICLASS���p��������
private:
	string yes_str;
	string no_str;
	string srender_text;

	int render_text;
	int yes_button;
	int no_button;
	int window_id;
public:
	void mainrenderIMPL(bool is_focused, Graphics* g, Game* game) {};
	void renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {};
	void aiIMPL(Task* task, TCB* thisTCB, Graphics* g,  Game* game){};
	void posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g,  Game* game){};
	void loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g,  Game* game){};

	void enter();
	void leave();
	bool handleMessage(int msg, void* data, DWORD time);

	void setYesStr(char* y);
	void setNoStr(char* n);
	void setRenderText(char* t);

	TWOTAKU ( char* yes_str, char* no_str, char* text);

};
}
#endif