#include <sys/types.h>
#include <unistd.h>

extern int  errno;
extern char _end;  // 使用链接脚本定义的堆起始地址
static char *heap_end = &_end;

void *_sbrk(ptrdiff_t incr)
{
    char *prev_heap_end = heap_end;
    heap_end += incr;
    return (void *)prev_heap_end;
}
