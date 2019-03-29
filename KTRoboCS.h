#ifndef KTROBOCS_H
#define KTROBOCS_H

#pragma once
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "stdlib.h"
#include "stdio.h"
#include "KTRoboTask.h"
#include "process.h"

// �������b�N����Ƃ��̏���
// AI(TASK4) LUAEXE LOAD(TASK3) //INPUT(MAIN)input��MESSAGE�����b�N���� // MAINRENDER(TASK2) ANIME(TASK1) BUTUKARI(TASK0) LOAD DEVICE  LOG MESSAGE SOUND RENDERDATA  �̏�

namespace KTROBO {
#define CS_LOG_CS 2
#define CS_TASK_CS 3
#define CS_DEVICECON_CS 4
#define CS_MAINTHREAD_CS 5
#define CS_LOAD_CS 6 // ���[�h�X�g���N�g�̃��[�h�y�єj�������Ɏg����
#define CS_MESSAGE_CS 7 // �X���b�h�Ԃ̃f�[�^�̂����ɂ��g����
#define CS_RENDERDATA_CS 8 //�`��֌W�̃f�[�^�̎Q�ƍX�V�Ɏg���� 
#define CS_CS_CS 9
#define CS_SOUND_CS 10
#define CS_LUAEXE_CS 11
// ��@GUI�{�^���Ń{�^���������ꂽ�Ɣ��肷��̂�handleMessage�ł��̏����̌��ʁA�N���X�̍X�V�L���[




struct CRITICAL_MYSTRUCT {
	CRITICAL_SECTION cs;
	int lock_count;
	unsigned int thread_id;
};

class CS
{
private:
	CRITICAL_MYSTRUCT LOG_CS;
	CRITICAL_MYSTRUCT TASK_CS[TASKTHREAD_NUM];
	CRITICAL_MYSTRUCT DEVICECON_CS;
	CRITICAL_MYSTRUCT MAINTHREAD_CS; // ���C���̃X���b�h���~�܂��Ă��邩�ǂ����Ɏg��
	CRITICAL_MYSTRUCT LOAD_CS;
	CRITICAL_MYSTRUCT MESSAGE_CS;
	CRITICAL_MYSTRUCT RENDERDATA_CS;
	CRITICAL_MYSTRUCT CS_CS;
	CRITICAL_MYSTRUCT SOUND_CS;
	CRITICAL_MYSTRUCT LUAEXE_CS;

	bool is_main_enter;
private:
	CS(void);

	bool is_log;
	char* getCSName(int index);

public:
	static CS* instance() {
		static CS a;
		return &a;
	}
	void setLogMode(bool is_log) {
		this->is_log = is_log;
	}

	void log(int index, char* p, int length);
	
	
	void Init() {



		InitializeCriticalSection(&LOG_CS.cs);
		LOG_CS.lock_count = 0;
		LOG_CS.thread_id =0;
		for (int i = 0 ; i <TASKTHREAD_NUM; i++) {
			InitializeCriticalSection(&TASK_CS[i].cs);
			TASK_CS[i].lock_count = 0;
			TASK_CS[i].thread_id = 0;
		}
		InitializeCriticalSection(&DEVICECON_CS.cs);
		DEVICECON_CS.lock_count = 0;
		DEVICECON_CS.thread_id = 0;
		InitializeCriticalSection(&MAINTHREAD_CS.cs);
		MAINTHREAD_CS.lock_count = 0;
		MAINTHREAD_CS.thread_id = 0;
		InitializeCriticalSection(&LOAD_CS.cs);
		LOAD_CS.lock_count = 0;
		LOAD_CS.thread_id = 0;
		InitializeCriticalSection(&MESSAGE_CS.cs);
		MESSAGE_CS.lock_count = 0;
		MESSAGE_CS.thread_id = 0;
		InitializeCriticalSection(&RENDERDATA_CS.cs);
		RENDERDATA_CS.lock_count = 0;
		RENDERDATA_CS.thread_id = 0;
		InitializeCriticalSection(&CS_CS.cs);
		CS_CS.lock_count = 0;
		CS_CS.thread_id = 0;
		InitializeCriticalSection(&SOUND_CS.cs);
		SOUND_CS.lock_count = 0;
		SOUND_CS.thread_id = 0;
		InitializeCriticalSection(&LUAEXE_CS.cs);
		LUAEXE_CS.lock_count = 0;
		LUAEXE_CS.thread_id = 0;

	}

	void Del() {
		DeleteCriticalSection(&LOG_CS.cs);
		for (int i=0;i<TASKTHREAD_NUM; i++) {
			DeleteCriticalSection(&TASK_CS[i].cs);
		}
		DeleteCriticalSection(&DEVICECON_CS.cs);
		DeleteCriticalSection(&MAINTHREAD_CS.cs);
		DeleteCriticalSection(&LOAD_CS.cs);
		DeleteCriticalSection(&MESSAGE_CS.cs);
		DeleteCriticalSection(&RENDERDATA_CS.cs);
		DeleteCriticalSection(&CS_CS.cs);
		DeleteCriticalSection(&SOUND_CS.cs);
		DeleteCriticalSection(&LUAEXE_CS.cs);
	}

	~CS(void);
	void enter(int index, char* buf, int offset = 0) {
		if (index == CS_LOG_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (LOG_CS.lock_count != 0) {
				if (GetCurrentThreadId() == LOG_CS.thread_id) {
					LOG_CS.lock_count++;
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			}
			LeaveCriticalSection(&CS_CS.cs);
			EnterCriticalSection(&LOG_CS.cs);
			LOG_CS.lock_count++;
			LOG_CS.thread_id = GetCurrentThreadId();
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_TASK_CS) {

			if (offset > 0 && offset < TASKTHREAD_NUM) {
				EnterCriticalSection(&CS_CS.cs);
				if (TASK_CS[offset].lock_count !=0) {
					if (GetCurrentThreadId() == TASK_CS[offset].thread_id) {
						TASK_CS[offset].lock_count++;
						LeaveCriticalSection(&CS_CS.cs);
						return;
					}
				}
				LeaveCriticalSection(&CS_CS.cs);
				EnterCriticalSection(&TASK_CS[offset].cs);
				TASK_CS[offset].lock_count++;
				TASK_CS[offset].thread_id = GetCurrentThreadId();
			}
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_DEVICECON_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (DEVICECON_CS.lock_count != 0) {
				if (GetCurrentThreadId() == DEVICECON_CS.thread_id) {
					DEVICECON_CS.lock_count++;
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			}
			LeaveCriticalSection(&CS_CS.cs);
			EnterCriticalSection(&DEVICECON_CS.cs);
			DEVICECON_CS.lock_count++;
			DEVICECON_CS.thread_id = GetCurrentThreadId();
			// ����Ȃ��Ȃ����킯�ł͂Ȃ��݂�����
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_MAINTHREAD_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (MAINTHREAD_CS.lock_count != 0) {
				if (GetCurrentThreadId() == MAINTHREAD_CS.thread_id) {
					MAINTHREAD_CS.lock_count++;
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			}
			LeaveCriticalSection(&CS_CS.cs);
			EnterCriticalSection(&MAINTHREAD_CS.cs);
			MAINTHREAD_CS.lock_count++;
			MAINTHREAD_CS.thread_id = GetCurrentThreadId();
			is_main_enter = true;
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_LOAD_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (LOAD_CS.lock_count != 0) {
				if (GetCurrentThreadId() == LOAD_CS.thread_id) {
					LOAD_CS.lock_count++;
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			}
			LeaveCriticalSection(&CS_CS.cs);
			EnterCriticalSection(&LOAD_CS.cs);
			LOAD_CS.lock_count++;
			LOAD_CS.thread_id = GetCurrentThreadId();
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_MESSAGE_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (MESSAGE_CS.lock_count != 0) {
				if (GetCurrentThreadId() == MESSAGE_CS.thread_id) {
					MESSAGE_CS.lock_count++;
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			}
			LeaveCriticalSection(&CS_CS.cs);
			EnterCriticalSection(&MESSAGE_CS.cs);
			MESSAGE_CS.lock_count++;
			MESSAGE_CS.thread_id = GetCurrentThreadId();
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_RENDERDATA_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (RENDERDATA_CS.lock_count != 0) {
				if (GetCurrentThreadId() == RENDERDATA_CS.thread_id) {
					RENDERDATA_CS.lock_count++;
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			}
			LeaveCriticalSection(&CS_CS.cs);
			EnterCriticalSection(&RENDERDATA_CS.cs);
			RENDERDATA_CS.lock_count++;
			RENDERDATA_CS.thread_id = GetCurrentThreadId();
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_SOUND_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (SOUND_CS.lock_count != 0) {
				if (GetCurrentThreadId() == SOUND_CS.thread_id) {
					SOUND_CS.lock_count++;
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			}
			LeaveCriticalSection(&CS_CS.cs);
			EnterCriticalSection(&SOUND_CS.cs);
			SOUND_CS.lock_count++;
			SOUND_CS.thread_id = GetCurrentThreadId();
			int length = strlen(buf);
			log(index, buf, length);
		}
		else if (index == CS_LUAEXE_CS) {
		EnterCriticalSection(&CS_CS.cs);
		if (LUAEXE_CS.lock_count != 0) {
			if (GetCurrentThreadId() == LUAEXE_CS.thread_id) {
				LUAEXE_CS.lock_count++;
				LeaveCriticalSection(&CS_CS.cs);
				return;
			}
		}
		LeaveCriticalSection(&CS_CS.cs);
		EnterCriticalSection(&LUAEXE_CS.cs);
		LUAEXE_CS.lock_count++;
		LUAEXE_CS.thread_id = GetCurrentThreadId();
		int length = strlen(buf);
		log(index, buf, length);
		}
	}

	void leave(int index, char* buf, int offset = 0) {
		if (index == CS_LOG_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (LOG_CS.lock_count) {
				LOG_CS.lock_count--;
			}
			if (LOG_CS.lock_count) {
				LeaveCriticalSection(&CS_CS.cs);
				return;
			}
				
			LOG_CS.thread_id = 0;
			LeaveCriticalSection(&CS_CS.cs);
			LeaveCriticalSection(&LOG_CS.cs);
		} else if(index == CS_TASK_CS) {
			if (offset >0 && offset < TASKTHREAD_NUM) {
				EnterCriticalSection(&CS_CS.cs);
				if (TASK_CS[offset].lock_count) {
					TASK_CS[offset].lock_count--;
				}
				if (TASK_CS[offset].lock_count) {
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
				TASK_CS[offset].thread_id = 0;
				LeaveCriticalSection(&CS_CS.cs);
				LeaveCriticalSection(&TASK_CS[offset].cs);
				
			}
		} else if(index == CS_DEVICECON_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (DEVICECON_CS.lock_count) {
				DEVICECON_CS.lock_count--;
			}
			if (DEVICECON_CS.lock_count) {
				LeaveCriticalSection(&CS_CS.cs);
				return;
			}
			DEVICECON_CS.thread_id = 0;
			LeaveCriticalSection(&CS_CS.cs);

			LeaveCriticalSection(&DEVICECON_CS.cs);
			
			// ����Ȃ��Ȃ����킯�ł͂Ȃ��݂�����
		} else if(index == CS_MAINTHREAD_CS) {
			if (is_main_enter) {

				EnterCriticalSection(&CS_CS.cs);
				if (MAINTHREAD_CS.lock_count) {
					MAINTHREAD_CS.lock_count--;
				}
				if (MAINTHREAD_CS.lock_count) {
					LeaveCriticalSection(&CS_CS.cs);
					return;
				}
			is_main_enter = false;
			MAINTHREAD_CS.thread_id = 0;
			LeaveCriticalSection(&CS_CS.cs);
			LeaveCriticalSection(&MAINTHREAD_CS.cs);
		
			int length = strlen(buf);
			log(index, buf, length);
			}
		} else if(index == CS_LOAD_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (LOAD_CS.lock_count) {
				LOAD_CS.lock_count--;
			}
			if (LOAD_CS.lock_count) {
				LeaveCriticalSection(&CS_CS.cs);
				return;
			}
			LOAD_CS.thread_id = 0;
			LeaveCriticalSection(&CS_CS.cs);
			LeaveCriticalSection(&LOAD_CS.cs);
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_MESSAGE_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (MESSAGE_CS.lock_count) {
				MESSAGE_CS.lock_count--;
			}
			if (MESSAGE_CS.lock_count) {
				LeaveCriticalSection(&CS_CS.cs);
				return;
			}
				MESSAGE_CS.thread_id = 0;
				LeaveCriticalSection(&CS_CS.cs);
			LeaveCriticalSection(&MESSAGE_CS.cs);
		
			int length = strlen(buf);
			log(index, buf, length);
		} else if(index == CS_RENDERDATA_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (RENDERDATA_CS.lock_count) {
				RENDERDATA_CS.lock_count--;
			}
			if (RENDERDATA_CS.lock_count) {
				LeaveCriticalSection(&CS_CS.cs);
				return;
			}
			RENDERDATA_CS.thread_id = 0;
			LeaveCriticalSection(&CS_CS.cs);
			LeaveCriticalSection(&RENDERDATA_CS.cs);	
			int length = strlen(buf);
			log(index, buf, length);
		}else if(index == CS_SOUND_CS) {
			EnterCriticalSection(&CS_CS.cs);
			if (SOUND_CS.lock_count) {
				SOUND_CS.lock_count--;
			}
			if (SOUND_CS.lock_count) {
				LeaveCriticalSection(&CS_CS.cs);
				return;
			}
			SOUND_CS.thread_id = 0;
			LeaveCriticalSection(&CS_CS.cs);
			LeaveCriticalSection(&SOUND_CS.cs);	
			int length = strlen(buf);
			log(index, buf, length);
		}

		else if (index == CS_LUAEXE_CS) {
		EnterCriticalSection(&CS_CS.cs);
		if (LUAEXE_CS.lock_count) {
			LUAEXE_CS.lock_count--;
		}
		if (LUAEXE_CS.lock_count) {
			LeaveCriticalSection(&CS_CS.cs);
			return;
		}
		LUAEXE_CS.thread_id = 0;
		LeaveCriticalSection(&CS_CS.cs);
		LeaveCriticalSection(&LUAEXE_CS.cs);
		int length = strlen(buf);
		log(index, buf, length);
		}
	}
};

}

#endif
