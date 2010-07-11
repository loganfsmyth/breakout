#include "Log.h"

Log::Log(char* filename, int type){
	switch(type){
		case LOG_OVERWRITE:
			file = fopen(filename, "w");
			break;
		case LOG_APPEND:
			file = fopen(filename, "a");
			break;
	}
	if(file == NULL) printf("Log: Failed to Initialize\n");
	else{
		if(type == LOG_APPEND){
			print("\n\n");
		}
		print("Log From ");
		printStamp();	//the time has a \n after it automatically
		print("\n");
		print("-------------------------\n");
	}
}
void Log::print(char* data){
	fputs(data, file);
	fflush(file);
}
void Log::printLine(char* data){
	if(timestamp){
		printStamp();
		print(":  ");
	}
	print(data);
	print("\n");
}
void Log::printStamp(){
	time_t timeStruct = time(NULL);
	char* time = ctime(&timeStruct);
	time[strlen(time)-1] = '\0';	//cut off the last return in the string
	print(time);				//the time has a \n after it automatically
	
	
	//won't this cause a memory leak??!?!
	//where does the memory for that pointer come from
}
void Log::showStamp(bool temp){
	timestamp = temp;
}
Log::~Log(){
	fclose(file);
}
