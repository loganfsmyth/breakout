#ifndef INCLUDED_LOG_H
#define INCLUDED_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_OVERWRITE		4
#define LOG_APPEND		8
#define LOG_TIMESTAMP		16

class Log{
	private:
		FILE* file;
		bool timestamp;
	public:
		Log(char* filename, int type);
		void print(char* data);
		void printLine(char* data);
		void printStamp();
		void showStamp(bool stamp);
		~Log();
};

#endif
