typedef void(*init_func) (void);

#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)

__declspec(allocate(".CRT$XCA")) init_func ctors_begin[] = { 0 };
__declspec(allocate(".CRT$XCZ")) init_func ctors_end[] = { 0 };

extern "C" void do_global_ctors()
{
	init_func* p = ctors_begin;
	while (p < ctors_end){
		if (*p) 
			(**p)();
		++p;
	}
}