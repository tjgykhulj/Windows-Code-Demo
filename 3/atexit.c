#include "minicrt.h"

typedef struct _func_node	//atexit的点建在此表中
{
	atexit_func_t func;
	void *arg;
	int is_cxa;
	struct _func_node *next;
} func_node;

static func_node *atexit_list = 0;

int register_atexit(atexit_func_t func, void *arg, int is_cxa)
{
	func_node *node;
	if (!func) return -1;

	if ((node = (func_node*)malloc(sizeof(func_node))) == 0) return -1;

	node->func = func;
	node->arg = arg;
	node->is_cxa = is_cxa;
	node->next = atexit_list;
	atexit_list = node;
	return 0;
}

int atexit(atexit_func_t func)
{
	return register_atexit(func, 0, 0);
}

void mini_crt_call_exit_routine()	//程序退出时调用此函数，把表中函逐个调用
{
	func_node *p = atexit_list;
	for (; p != 0; p = p->next) {
		p->func();
		free(p);
	}
}