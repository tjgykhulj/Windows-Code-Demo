#include "minicrt.h"
#include <Windows.h>

typedef struct _heap_header
{
	enum {
		HEAP_BLOCK_FREE = 0xABABABAB,
		HEAP_BLOCK_USED = 0xCDCDCDCD,
	} type;

	unsigned size;
	struct _heap_header* next;
	struct _heap_header* prev;
} heap_header;

#define ADDR_ADD(a,o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

static heap_header *list_head = NULL;

void free(void *ptr) 
{
	heap_header *header = (heap_header *)ADDR_ADD(ptr, -HEADER_SIZE);
	if (header->type != HEAP_BLOCK_USED)
		return;

	header->type = HEAP_BLOCK_FREE;
	if (header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE) 
	{
		header->prev->size += header->size;
		header->prev->next = header->next;
		if (header->next)
			header->next->prev = header->prev;
		header = header->prev;
	}
	if (header->next != NULL && header->next->type == HEAP_BLOCK_FREE)
	{
		header->size += header->next->size;
		header->next = header->next->next;
	}
}

void *malloc(unsigned size)
{
	heap_header *header;
	if (size == 0) return NULL;

	for (header = list_head; header; header = header->next) 
	{
		if (header->type == HEAP_BLOCK_USED) continue;
		if (header->size > size + HEADER_SIZE * 2) 
		{
			heap_header *next = (heap_header *) ADDR_ADD(header, size + HEADER_SIZE);
			next->prev = header;
			next->next = header->next;
			next->type = HEAP_BLOCK_FREE;
			next->size = header->size - (size + HEADER_SIZE);
			header->next = next;
			header->size = size + HEADER_SIZE;
			header->type = HEAP_BLOCK_USED;
			return ADDR_ADD(header, HEADER_SIZE);
		}
		if (header->size > size + HEADER_SIZE) {
			header->type = HEAP_BLOCK_USED;
			return ADDR_ADD(header, HEADER_SIZE);
		}
	}
	return NULL;
}

int mini_crt_heap_init()
{
	void *base = NULL;
	unsigned heap_size = 1024 * 1024 * 32;

	base = VirtualAlloc(0, heap_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (base == NULL) return 0;

	list_head = (heap_header *)base;
	list_head->size = heap_size;
	list_head->type = HEAP_BLOCK_FREE;
	list_head->next = list_head->prev = NULL;
	return 1;
}