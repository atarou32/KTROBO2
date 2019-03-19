#ifndef KTROBOTASK_H
#define KTROBOTASK_H

#pragma once
#include "stdio.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "KTRoboGameError.h"

namespace KTROBO {
#define TASK_WORK_SIZE 32
#define MAX_TASK_COUNT 64
#define TASK_USE 0x0001
#define TASK_DONTUSE_PRIO 0x0000
#define TASK_HEAD_PRIO 0x0000

#define TASKTHREAD_NUM 5 // DONT CHANGE IT
#define TASK_ERR_COUNT_MAX 3
struct TCB {
	void (*Exec)(TCB*);
	TCB* prev;
	TCB* next;
	unsigned int flag;
	unsigned int prio;
	void *data;
	unsigned long Work[TASK_WORK_SIZE];
};



class Task {
private:
	HWND hWnd;
	HANDLE hd;
	int err_count;
	TCB Tasks[MAX_TASK_COUNT];
	bool is_exec_task;
	int index;
	static int NOW_TASK_THREAD_NUM;
private:
	Task(HWND hWnd, int index) { 
		this->hWnd = hWnd;
		this->index = index;
		err_count = 0;
		memset(Tasks, 0, sizeof(TCB) * MAX_TASK_COUNT);
		is_exec_task = false;
		hd = 0;
	};
	Task(Task& t) {};
	Task& operator =(Task& t) {};
	void init();
	

	
public:
	~Task() {};
	void exec();// �O������͌Ă΂Ȃ�����
	// ����Ŏ擾����Task�͊O����deleteTask��delete����΂��K�v������
	static Task* factory(HWND hwnd) {
		if (NOW_TASK_THREAD_NUM < TASKTHREAD_NUM) {
			Task* t = new Task(hwnd, NOW_TASK_THREAD_NUM);
			t->init();
			NOW_TASK_THREAD_NUM++;
			return t;
		}
		throw new GameError(KTROBO::FATAL_ERROR, "too many task");
	}
	bool getIsExecTask() {return is_exec_task;}
	TCB* make(void(*exec)(TCB*), void* data,  unsigned long* work,unsigned int prio);// work ��TASK_WORK_SIZE�̑傫�����m�ۂ��邱��
	void donow(void(*exec)(TCB*), void* data,  unsigned long* work,unsigned int prio);
	void kill(TCB* killTCB);
	void change(TCB* thisTCB, void(*exec)(TCB*), void* data);
	void deleteTask();
	void deleteTaskWithoutLock();
	void waitForTaskEnd();
};






}

#endif