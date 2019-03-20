#include "KTRoboLoadable.h"

using namespace KTROBO;
#pragma once
#include "KTRoboCS.h"

Loadable2::Loadable2()
{
	is_loaded = false;
	is_loaded_only_for_thread = 0;
	thread_id_for_is_loaded = 0;
}


Loadable2::~Loadable2()
{

}

bool Loadable2::getIsLoaded() {
	bool t=false;
	CS::instance()->enter(CS_LOAD_CS, "loadable");
	t = is_loaded;
	CS::instance()->leave(CS_LOAD_CS, "loadable");
	return t;
}
void Loadable2::setLoaded() {
	CS::instance()->enter(CS_LOAD_CS, "loadable");
	is_loaded = true;
	CS::instance()->leave(CS_LOAD_CS, "loadable");
}
bool Loadable2::getIsLoadedForLoopThread() {


	if (!thread_id_for_is_loaded) {
		setLoopThread();
	}

	return is_loaded_only_for_thread;
}

void Loadable2::setLoopThread() {
	thread_id_for_is_loaded = GetCurrentThreadId();
}

void Loadable2::setLoadedForLoopThread() {

	if (thread_id_for_is_loaded == GetCurrentThreadId()) {
		is_loaded_only_for_thread = true;
	}
	else {
		throw new GameError(FATAL_ERROR, "there is error in loadable");
	}
}

bool Loadable2::hasLoaded() {
	if (getIsLoadedForLoopThread()) {

	}
	else {
		if (getIsLoaded()) {
			setLoadedForLoopThread();
		}
		else {
			return false;
		}
	}

	return true;
}