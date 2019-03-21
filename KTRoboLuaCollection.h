#ifndef KTROBOLUACOLLECTION_H
#define KTROBOLUACOLLECTION_H

#pragma once
#include "KTRoboCS.h"
#include "KTRoboGameError.h"
#include "KTRoboTask.h"
#include "lua.hpp"

namespace KTROBO {

class LuaTCBStruct {
public:
	char lua_filename[256];
	bool is_lock_sita;
	int task_index;
	bool is_use;
	bool is_send;
};

#define KTROBO_LUAEXEC_STRUCT_SIZE 32
class LuaTCBMaker {
private:
	static LuaTCBStruct structs[KTROBO_LUAEXEC_STRUCT_SIZE];	
	static lua_State* ls;
	static Task* ts[TASKTHREAD_NUM];
public:
	static void Init(Task** t, lua_State* l);
	static void doTCBnow(int task_index, bool is_lock_sita, char* lua_filename); // ���ׂ�AI�X���b�h�œ��� ���̊֐��͎g������_��
	static void makeTCB(int task_index, bool is_lock_sita, char* lua_filename);
	static void makeTCBExec();
	
};



// ���[�h���������N���X�ő��̃X���b�h�Ƃ̋����������������ȃN���X�Ɏg��
// ���̃N���X���̃R���N�g�����N���X�̃R���X�g���N�^�܂��̓f�X�g���N�^��execConstructOrDestruct() ���ĂԂ悤�ɂ���
// is_load��false�ɂ���̂͐��������j�������X���b�h�̂�
// is_load��true�ɂ���̂͑��̃X���b�h�̂ǂꂩ�ЂƂ̂�
// is_load ��p�ɂɕς����邱�Ƃ͍l�����Ă��Ȃ�

class Loadable
{
protected:
	volatile bool is_load; // collect�����N���X�𐶐������ǂ���

public:
//	virtual int getInstance(int index)=0;
//	virtual int getInterface(int index)=0;
//  construct
//  destruct

	Loadable() {
		is_load = true;
	}

	void setIsLoad(bool t) {
		
			CS::instance()->enter(CS_LOAD_CS, "set isload");
			is_load = t;
			CS::instance()->leave(CS_LOAD_CS, "set isload");
	}

	void execConstructOrDestruct() { 
		// ���̃��\�b�h��is_load��false�ɂ���̂������j�������X���b�h�����������Ȃ����Ƃ�O��Ƃ��Ă���
		// �������A���݂̂Ƃ��둼�̃X���b�h�ł�is_load��false�ɂł��邱��ɂ͒��ӂ��Ȃ���΂Ȃ�Ȃ�
		CS::instance()->enter(CS_LOAD_CS, "set isload");
		if (is_load) {
			// ���v
		} else {

			
			if (is_load) {
				// ���v
			} else {
				// ��O�𓊂���
				CS::instance()->leave(CS_LOAD_CS, "set isload");
				throw new GameError(KTROBO::WARNING, "exception in execConstructOrDestruct");
			}
			
		}
		CS::instance()->leave(CS_LOAD_CS, "set isload");
	}


	bool getIsLoad() {

		CS::instance()->enter(CS_LOAD_CS, "get isload");
		bool t;
		t = is_load;
		CS::instance()->leave(CS_LOAD_CS, "get isload");
		return t;
	}
};


}

#endif