#include "minicrt.h"
#include <Windows.h>

extern int main(int argc, char* argv[]);
void exit(int);

//入口函数，初始化参数，并调用初始化堆与IO的函数
void mini_crt_entry(void) 
{
	int ret;
	int flag = 0, argc = 0;
	char *argv[16];
	char *cl = GetCommandLineA();
	
	argv[argc++] = cl;
	//每个位置判断若是空格，且后一个位置非空格，则视为参数
	for (; *cl; cl++) {
		if (*cl == '\"') flag ^= 1;
		else
			if (*cl == ' ' && !flag) {
				if (*(cl + 1) && *(cl + 1) != ' ')
					argv[argc++] = cl + 1;
				*cl = 0;
			}
	}
	if (!mini_crt_heap_init() || !mini_crt_io_init()) exit(1);
	do_global_ctors();

	ret = main(argc, argv);
	exit(ret);
}

void exit(int exitCode) 
{
	mini_crt_call_exit_routine();
	ExitProcess(exitCode);	
}