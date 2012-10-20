//#ifndef 'SWI.H'
//#define 'SWI.H'
#include <exports.h>

#define SDRAM_BEGIN 0xa3000000
#define SDRAM_END   0xa3ffffff

ssize_t read(int,const void*,ssize_t);
ssize_t write(int,const void*, ssize_t);
void extern exit(int);
//#endif
