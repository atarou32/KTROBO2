#ifndef KTROBO_LUA_EXECTOR_H
#define KTROBO_LUA_EXECTOR_H

#pragma once
using namespace std;
#include <string>
#include "MyDefine.h"
#include "lua.hpp"
#include "tolua_glue/MyLuaGlueMakeCommon.h"
#include <vector>

namespace KTROBO {

interface ILuaExector {

public:
	TO_LUA virtual void setExecDoNow(char* lua_filename) = 0;
	TO_LUA virtual void setExecDoUntilTime(char* lua_filename, int second_delay) = 0;
	TO_LUA virtual void setExecDoUntilKey(char* lua_filename, int key) = 0;
	TO_LUA virtual void setExecCoDoNow(char* lua_filename) = 0;
	TO_LUA virtual void setExecCoDoUntilTime(char* lua_filename, int second_delay) = 0;
	TO_LUA virtual void setExecCoDoUntilKey(char* lua_filename, int key) = 0;
	TO_LUA virtual void doAndCoDoExecByKey(int key) = 0;
	TO_LUA virtual void resetAllLuaTask() = 0;
};
class LuaExec {
public:
	static enum LUAEXEC_STATE {
		NO_USE =0,
		USE = 1,
	};

	static enum LUAEXEC_EXEC_TYPE {
		DONOW = 0,
		DO_UNTIL_TIME = 1,
		DO_UNTIL_KEY = 2,
		DONOW__COROUTINE = 3,
		DO_UNTIL_TIME__COROUTINE = 4,
		DO_UNTIL_KEY__COROUTINE = 5,
	};
	lua_State* co;

	string lua_filename;
	long exec_timestamp;
	int key;
	int second_delay;
	enum LUAEXEC_STATE state;
	enum LUAEXEC_EXEC_TYPE type;
	LuaExec() {
		resetLuaExec();
	};
	void resetLuaExec() {
		exec_timestamp = 0;
		state = LUAEXEC_STATE::NO_USE;
		type = LUAEXEC_EXEC_TYPE::DONOW;
		key = 0;
		second_delay = 0;
		co = 0;
	}
	~LuaExec() {};

};

#define KTROBO_LUA_EXECTOR_TASK_MAX 256
// filename + coromain �ɂ���
#define KTROBO_LUA_COROUTINE_FUNC_NAME_PART "CoroMain"
class LuaExector : public ILuaExector
{
private:
	lua_State* L;
	long now_timestamp;
	LuaExec tasks[KTROBO_LUA_EXECTOR_TASK_MAX]; 
	bool is_donow;
	// 256�����Ȃ��̂Ł@�����s�łȂ��܂��͌J��Ԃ��Ă��{�{�ŌĂ�ł��炤�t�@�C���͂Ȃ�ׂ����Ȃ�����@lua���ł܂Ƃ߂�
	//setexec���Ȃ��Ă���donow�̓��b�N�������Ȃ��H �������������Ă����� donow����������^�X�N�ɐݒ肵�Ă���Ă�
public:
	LuaExector(lua_State* L);
	~LuaExector();

	
private:
	
	void dodayo(LuaExec* task);
	void cododayo(LuaExec* task);
	bool hasEmptyTask();
	int getEmptyTaskIndex();
	LuaExec* setExecTask(LuaExec::LUAEXEC_EXEC_TYPE type, char* filename, int second_delay, int key);
public:
	void setExecDoNow(char* lua_filename); //�ǂ̃Z�b�g�� �ǂ񂾎��_�ł������s����Ȃ��B�@AI�X���b�h�̃��[�v�ő����s�����
	void setExecDoUntilTime(char* lua_filename, int second_delay);
	void setExecDoUntilKey(char* lua_filename, int key);
	void setExecCoDoNow(char* lua_filename);
	void setExecCoDoUntilTime(char* lua_filename, int second_delay);
	// ���߂Ɏ��s�����̂�second_delay��ł��̂��Ƃ�second_delay�ゲ�ƂɌĂ΂��
	void setExecCoDoUntilKey(char* lua_filename, int key);

	void doAndCoDoExecByKey(int key); // codo�ł� �o�^���Ă���^�X�N������s������
	void resetAllLuaTask();
	void doLoop(long timestamp); // ��b���ƂɌĂ΂�� �������s�����^�X�N������ꍇ�͂����Ɏ��s�����
};

class LuaExectors {
private:
	lua_State* L;
	vector<LuaExector*> instdayos;
public:
	LuaExectors(lua_State* L);
	~LuaExectors();
	int makeinst();
	LuaExector* getInstance(int index);
	ILuaExector* getInterface(int index);
	void Del();
};
}
#endif