#include "KTRoboLuaExector.h"
#include "KTRoboGameError.h"
#include "KTRoboCS.h"
#include "KTRoboLog.h"
#include "tolua_glue/tolua_glue.h"
#include "KTRoboTask.h"

using namespace KTROBO;

bool LuaExector::hasEmptyTask() {

	for (int i = 0; i < KTROBO_LUA_EXECTOR_TASK_MAX; i++) {
		if (tasks[i].state == tasks->NO_USE) {
			return true;
		}
	}
	return false;
}

int LuaExector::getEmptyTaskIndex() {
	for (int i = 0; i < KTROBO_LUA_EXECTOR_TASK_MAX; i++) {
		if (tasks[i].state == tasks->NO_USE) {
			return i;
		}
	}
	throw new GameError(KTROBO::FATAL_ERROR,"to many lua task");
	return 0;
}

LuaExec* LuaExector::setExecTask(LuaExec::LUAEXEC_EXEC_TYPE type, char* filename, int second_delay, int key) {
	LuaExec* tas = 0;
	CS::instance()->enter(CS_LUAEXE_CS, "test");
	try {
		if (hasEmptyTask()) {
			int index = getEmptyTaskIndex();
			tasks[index].exec_timestamp = now_timestamp + second_delay;
			tasks[index].key = key;
			tasks[index].type = type;
			tasks[index].lua_filename = filename;
			tasks[index].second_delay = second_delay;
			tasks[index].state = LuaExec::LUAEXEC_STATE::USE;
			tas = &tasks[index];
		}
		else {
			throw new GameError(KTROBO::FATAL_ERROR, "to many lua task");
		}

	}
	catch (GameError* err) {
		CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw err;
	}
	catch (...) {
		CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw new GameError(KTROBO::FATAL_ERROR, "unknown fatal in getemptyluatask\n");
	}
	CS::instance()->leave(CS_LUAEXE_CS, "test");
	return tas;
}

LuaExector::LuaExector(lua_State* L)
{
	this->L = L;
	now_timestamp = 0;
	is_donow = false;
	ai_task = 0;
}


LuaExector::~LuaExector()
{
}


void LuaExector::dodayo(LuaExec* task) {
	
	if (task->state == LuaExec::LUAEXEC_STATE::NO_USE) {
		throw new GameError(KTROBO::WARNING, "try to do lua nouse\n");
	}


	const char* lua_filename = task->lua_filename.c_str();// tt->lua_filename;
	
	int tee = lua_gettop(L);
	int error;
	try {
		mylog::writelog(KTROBO::DEBUG, "%sを開きます\n", lua_filename);
		error = luaL_loadfile(L, lua_filename) || lua_pcall(L, 0, 0, 0);

	}
	catch (GameError* err) {

		lua_settop(L, tee);
		mylog::writelog(err->getErrorCode(), err->getMessage());
		//Sleep(500);
		//delete err;

		throw err;
	}
	catch (...) {
		//CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw new GameError(KTROBO::FATAL_ERROR, "unknown fatal in dolua\n");
	}

	if (error) {
		char test[1024];
		memset(test, 0, 1024);
		mystrcpy(test, 1024, 0, lua_tostring(L, -1));
		mylog::writelog(KTROBO::WARNING, "lua_error:%s", test);
		OutputDebugStringA(test);
		lua_settop(L, tee);

	}
	else {
		lua_settop(L, tee);
	}

	if (error) {
		

		mylog::writelog(KTROBO::DEBUG, "%sを開いたときにエラー\n", task->lua_filename.c_str());
	}
	else {
		mylog::writelog(KTROBO::DEBUG, "luaexec 正常終了\n");
		// 一回実行したので終了させる
		task->resetLuaExec();
	}

}

int getLuaNameFirstPos(const char* lua_filename) {
	char test = 0;
	int index = 0;
	int max_index = strlen(lua_filename);
	for (int i = 0; i < max_index; i++) {
		test = lua_filename[i];
		if (test == '/') {
			index = i;
		}
	}
	return index;
}

int getLuaNameLastPos(const char* lua_filename) {
	char test = 0;
	int index = 0;
	int max_index = strlen(lua_filename);
	for (int i = 0; i < max_index; i++) {
		test = lua_filename[i];
		if (test == '.') {
			index = i;
			return index;
		}
	}
	return max_index;

}

static int celd(lua_State* l) {
	string arg = luaL_checkstring(l, -1);
	OutputDebugStringA(arg.c_str());

	mylog::writelog(KTROBO::DEBUG, "w_fromlua:%s\n", arg.c_str());
	return lua_yield(l, 0);
}

void LuaExector::cododayo(LuaExec* task) {
	if (task->state == LuaExec::LUAEXEC_STATE::NO_USE) {
		throw new GameError(KTROBO::WARNING, "try to do lua nouse\n");
	}


	const char* lua_filename = task->lua_filename.c_str();// tt->lua_filename;

/*	int lua_name_first = getLuaNameFirstPos(lua_filename);
	int lua_name_last = getLuaNameLastPos(lua_filename);

	if ((lua_name_first >= lua_name_last) || (lua_name_first >= strlen(lua_filename))) {
		throw new GameError(KTROBO::FATAL_ERROR, "luafilenameis not good resrc/script/naninani.lua\n");
	}
	string lua_name = string(lua_filename);
	lua_name = lua_name.substr(lua_name_first+1, lua_name_last - lua_name_first-1);
	
	string lua_funcname = lua_name + string(KTROBO_LUA_COROUTINE_FUNC_NAME_PART);
	*/
	int tee = lua_gettop(L);
	int error=0;
	try {
		mylog::writelog(KTROBO::DEBUG, "%sを開きます(co)\n", lua_filename);
		if (!task->co) {
			
			
			
			lua_State* co = lua_newthread(L);
			
			int teec = lua_gettop(co);
			lua_register(co, "celd", celd); // lua に関数を登録
			//MyLuaGlueSingleton::getInstance()->registerdayo(co);
			mylog::writelog(KTROBO::DEBUG, "file登録");

			int err = luaL_loadfile(co, lua_filename);
			if (err) {
				mylog::writelog(KTROBO::DEBUG, "file登録失敗");
				char strda[1024];
				memset(strda, 0, 1024);
				mystrcpy(strda, 1024, 0, lua_tostring(co, lua_gettop(co)));
				
				mylog::writelog(KTROBO::WARNING, "%s", strda);
				OutputDebugStringA(strda);
				lua_settop(co, teec);
				// 失敗するのはわかっているけど次のフェーズでまた実行させようとする
				// 失敗したのでタスクを止める
				task->resetLuaExec();
				return;
			}


			/*int kata = lua_getglobal(co, "coro");// lua_funcname.c_str());
			
			if (kata != LUA_TFUNCTION) {
				mylog::writelog(KTROBO::WARNING, "%s", lua_tostring(co, lua_gettop(co)));
				OutputDebugStringA(lua_tostring(co, lua_gettop(co)));
				lua_settop(co, teec);
				// 失敗するのはわかっているけど次のフェーズでまた実行させようとする
				return;
			}
			*/
			//mylog::writelog(KTROBO::DEBUG, "%s %d を登録", lua_funcname.c_str(), kata);
			task->co = co;
		
		}
		//lua_pushnumber(task->co, 0);
		error = lua_resume(task->co, 0, 0);
	
		

	}
	catch (GameError* err) {

		lua_settop(L, tee);
		mylog::writelog(err->getErrorCode(), err->getMessage());
		//Sleep(500);
		//delete err;

		throw err;
	}
	catch (...) {
		//CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw new GameError(KTROBO::FATAL_ERROR, "unknown fatal in codolua\n");
	}


	if ((error != LUA_OK) && (error != LUA_YIELD)) {
		mylog::writelog(KTROBO::DEBUG, "resume 失敗 再登録させます");
		char strda[1024];
		memset(strda, 0, 1024);
		mystrcpy(strda, 1024, 0, lua_tostring(task->co, lua_gettop(task->co)));
		mylog::writelog(KTROBO::WARNING, "%s", strda);
		OutputDebugStringA(strda);
		OutputDebugStringA("\n");
		lua_settop(L, tee);
		task->co = 0;
	}
	else {
		//lua_settop(L, tee);
	}

	if ((error != LUA_OK) && (error != LUA_YIELD)) {
		mylog::writelog(KTROBO::DEBUG, "%sを開いたときにエラー\n", task->lua_filename.c_str());
	}
	else {

		if (error == LUA_OK) {
		mylog::writelog(KTROBO::DEBUG, "luaexec 正常終了\n");
			// 実行終了したので終了させる
			task->resetLuaExec();
		}
		else if (error == LUA_YIELD) {
			// まだ終わっていないのでまた呼ぶ
			mylog::writelog(KTROBO::DEBUG, "luaexec yield 正常終了\n");
			task->exec_timestamp += task->second_delay;

		}
	}

}
void LuaExector::doAndCoDoExecByKeyHonto(int key) {
	CS::instance()->enter(CS_LUAEXE_CS, "test");
	try {
		for (int i = 0; i < KTROBO_LUA_EXECTOR_TASK_MAX; i++) {
			if (tasks[i].state == LuaExec::LUAEXEC_STATE::USE) {
				if (tasks[i].type == LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_KEY) {
					if (tasks[i].key == key) {
						dodayo(&tasks[i]);
					}
				}

				if (tasks[i].type == LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_KEY__COROUTINE) {
					if (tasks[i].key == key) {
						cododayo(&tasks[i]);
					}
				}
			}

		}
	}
	catch (GameError* e) {
		CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw e;
	}
	catch (...) {
		CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw new GameError(KTROBO::FATAL_ERROR, "unknown error in dokeylua\n");
	}
	CS::instance()->leave(CS_LUAEXE_CS, "test");
}

void doExecByKeyTCB(TCB* thisTCB) {
	((LuaExector*)(thisTCB->data))->doAndCoDoExecByKeyHonto(thisTCB->Work[0]);
	((Task*)(thisTCB->Work[1]))->kill(thisTCB);

}
void LuaExector::doAndCoDoExecByKey(int key) {
	if (ai_task) {
		unsigned long work[TASK_WORK_SIZE];
		memset(work, 0, sizeof(work));
		work[0] = key;
		work[1] = (unsigned long)(ai_task);
		ai_task->make(doExecByKeyTCB, this, work, 0x0000FFFF);
		return;
	}
	else {
		mylog::writelog(KTROBO::FATAL_ERROR, "no ai task in luaexector\n");
	}
	
}
void LuaExector::setExecDoNow(char* lua_filename) {
	LuaExec* le  = setExecTask(LuaExec::LUAEXEC_EXEC_TYPE::DONOW, lua_filename, 0, 0);
	/*
	CS::instance()->enter(CS_LUAEXE_CS, "test");
	try {
		dodayo(le);
	}
	catch (GameError* err) {
		CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw err;

		}
	CS::instance()->leave(CS_LUAEXE_CS, "test");
	*/
	is_donow = true;
}
void LuaExector::setExecDoUntilTime(char* lua_filename, int second_delay) {
	setExecTask(LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_TIME, lua_filename, second_delay, 0);
}
void LuaExector::setExecDoUntilKey(char* lua_filename, int key) {
	setExecTask(LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_KEY, lua_filename, 0, key);
}
void LuaExector::setExecCoDoNow(char* lua_filename) {
	LuaExec* le = setExecTask(LuaExec::LUAEXEC_EXEC_TYPE::DONOW__COROUTINE, lua_filename, 0, 0);
	/*
	CS::instance()->enter(CS_LUAEXE_CS, "test");
	try {
		cododayo(le);
	}
	catch (GameError* err) {
		CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw err;

	}
	CS::instance()->leave(CS_LUAEXE_CS, "test");
	*/
	is_donow = true;
}
void LuaExector::setExecCoDoUntilTime(char* lua_filename, int second_delay) {
	setExecTask(LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_TIME__COROUTINE, lua_filename, second_delay, 0);
}
void LuaExector::setExecCoDoUntilKey(char* lua_filename, int key) {
	setExecTask(LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_KEY__COROUTINE, lua_filename, 0, key);
}
void LuaExector::doLoop(long timestamp) {
	
	if (!is_donow && this->now_timestamp == timestamp) return; // 一秒ごとに呼ぶようにする
	this->now_timestamp = timestamp;
	CS::instance()->enter(CS_LUAEXE_CS, "test");
	try {
		for (int i = 0; i < KTROBO_LUA_EXECTOR_TASK_MAX; i++) {
			if (tasks[i].state == LuaExec::LUAEXEC_STATE::USE) {
				if (tasks[i].type == LuaExec::LUAEXEC_EXEC_TYPE::DONOW) {
					dodayo(&tasks[i]); // dodayo がなげる例外はふぁたるだからそのまま通してしまう

				}

				if (tasks[i].type == LuaExec::LUAEXEC_EXEC_TYPE::DONOW__COROUTINE) {
					cododayo(&tasks[i]);
				}

				if (tasks[i].type == LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_TIME) {
					if (tasks[i].exec_timestamp <= timestamp) {
						dodayo(&tasks[i]);
					}
				}

				if (tasks[i].type == LuaExec::LUAEXEC_EXEC_TYPE::DO_UNTIL_TIME__COROUTINE) {
					if (tasks[i].exec_timestamp <= timestamp) {
						cododayo(&tasks[i]);
					}
				}

				// key関連については実行しない

			}



		}
	}
	catch (GameError* err) {
		CS::instance()->leave(CS_LUAEXE_CS, "test");
		throw err;//fatal
	}


	CS::instance()->leave(CS_LUAEXE_CS, "test");
	is_donow = false;
}

void LuaExector::resetAllLuaTask() {

	CS::instance()->enter(CS_LUAEXE_CS, "test");

	for (int i = 0; i < KTROBO_LUA_EXECTOR_TASK_MAX; i++) {
		tasks[i].resetLuaExec();
	}

	CS::instance()->leave(CS_LUAEXE_CS, "test");
}

LuaExectors::LuaExectors(lua_State* L) {
	this->L = L;
}
LuaExectors::~LuaExectors() {

}

int LuaExectors::makeinst() {

	if (!instdayos.size()) {
		LuaExector* le = new LuaExector(L);
		instdayos.push_back(le);
	}

	return 0;
}
LuaExector* LuaExectors::getInstance(int index) {
	makeinst();
	return instdayos[0];
}
ILuaExector* LuaExectors::getInterface(int index) {
	makeinst();
	return instdayos[0];
}
void LuaExectors::Del() {
	vector<LuaExector*>::iterator it = instdayos.begin();
	while (instdayos.end() != it) {
		if (*it) {
			delete (*it);
		}
		it++;

	}
	instdayos.clear();
}
