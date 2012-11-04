/** @file typo.c
 *
 * Authors:	Brandon Lee <bfl> 
 * 		Christopher Palmer <ctpalmer>
 * 		Jongyoon Han <jongyoo1>
 *		Lawrence Tsang <ltsang>
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../libc/include/bits/fileno.h" 

int main(int argc, char** argv)
{	
	unsigned long start, end;
        int bytes_read;
	char inputString[50];
        /*char dur[50];
        int length; */
        //while (1) {
		printf("> ");
		start = time();
		bytes_read = read(STDIN_FILENO, inputString, 50);
		write(STDOUT_FILENO, inputString, bytes_read);
		end = time();
                
		write(STDOUT_FILENO, inputString, bytes_read);
                printf("time taken = %lu\n", (end-start));
		
	//}
	return (int)(end-start);
}
