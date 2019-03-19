#ifndef KTROBOLOG_H
#define KTROBOLOG_H

#pragma once
#include "stdio.h"
#include "stdarg.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "KTRoboGameError.h"

namespace KTROBO {
class mylog
{
private:
	static char* getLogFileName(int error_num) {
		if (error_num == KTROBO::FATAL_ERROR) {
			return "log/errtxt.txt";
		} else if(error_num == KTROBO::INFO) {
			return "log/infotxt.txt";
		} else if(error_num == KTROBO::NOTICE) {
			return "log/noticetxt.txt";
		} else if (error_num == KTROBO::WARNING) {
			return "log/warningtxt.txt";
		}
		else if (error_num == KTROBO::DEBUG) {
			return "log/debugtxt.txt";
		}

		return "log/unknowntxt.txt";
	}
public:
	mylog(void);
	~mylog(void);

	static char* writelog(const char* filename, const char* buffer, ...);
	static char* writelog(int error_num, const char* buffer, ...);

};
}

#endif