#ifndef __MINI_CRT_H__
#define __MINI_CRT_H__

#ifdef __cplusplus
extern "C" {
#endif

//Malloc
#ifndef NULL
#define NULL (0)
#endif

void	free(void *ptr);
void*	malloc(unsigned size);
static int brk(void *end_data_segment);
int	mini_crt_init_heap();

//String
char*	itoa(int n, char *str, int radix);
int	strcmp(const char *src, const char *dst);
char*	strcpy(char *dst, const char *src);
unsigned strlen(const char *len);

//File && IO
typedef int FILE;
#define EOF (-1)
#define stdin		((FILE*) GetStdHandle(STD_INPUT_HANDLE))
#define stdout		((FILE*) GetStdHandle(STD_OUTPUT_HANDLE))
#define stderr		((FILE*) GetStdHandle(STD_ERROR_HANDLE))

int	mini_crt_init_io();
int fread(void *buffer, int size, int count, FILE *stream);
int fwritie(const void *buffer, int size, int count, FILE *stream);
int fclose(FILE *fp);
int fseek(FILE *fp, int offset, int set);
int fputc(int c, FILE *stream);
int fputs(const char *str, FILE *stream);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
FILE *fopen(const char *filename, const char *mode);

//internal
void do_global_ctors();
void mini_crt_call_exit_routine();

//atexit
typedef void(*atexit_func_t) (void);
int atexit(atexit_func_t func);

#ifdef __cplusplus
}
#endif

#endif //__MINICRT_H