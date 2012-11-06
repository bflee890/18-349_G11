/** @file hello.c
 *
 * @brief Prints out Hello world using the syscall interface.
 *
 * Links to libc.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-10-29
 */
#include "unistd.h"
#include "stdlib.h"
//#include <stdio.h>
//#include <uboot/include/exports.h>
#include <bits/types.h>
//#include "string.h"
#include <bits/fileno.h>

int main(int argc, char** argv)
{
	//int t = time();
	//printf("%d\n", t);
	/*while(1)
	{
	    t = time();
	    if(t > 20)
		break;
	}*/
	while(1){}
	sleep(1000);
	const char hello[] = "Hello World\r\n";
	write(STDOUT_FILENO, hello, sizeof(hello) - 1);
	//t = time();
	//write(STDOUT_FILENO, &t, 8);
	//sleep(2000);
	//int m = 0;
	//printf("%s\n", hello);
	//unsigned long buf[1];
	//buf[0] = time();
	//write(STDOUT_FILENO, buf, 8);
	//sleep(0x10000);
	return 0;
}
