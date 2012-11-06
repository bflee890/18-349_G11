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
#include <bits/fileno.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../libc/include/bits/fileno.h" 

int main(int argc, char** argv)
<<<<<<< HEAD
{
	unsigned long start, end, total, sec, tenthsec;
	int bytes_read;
	char inputString[50];

	printf("> ");
	start = time();
	bytes_read = read(STDIN_FILENO, inputString, 50);
	write(STDOUT_FILENO, inputString, bytes_read);
	end = time();

	total = end-start;
	sec = total/1000;
	tenthsec = (total % 1000)/100;

	printf("time taken = %lu.%lus\n", sec, tenthsec);
	
	return 0;
=======
{	
	unsigned long start, end, total, sec, tenthsec;
        int bytes_read;
	char inputString[50];
        /*char dur[50];
        int length; */
        while (1) {
		printf("> ");
		start = time();
		bytes_read = read(STDIN_FILENO, inputString, 50);
		end = time();
                
                total = end-start;
                tenthsec = (total % 1000)/100;
                sec = total/1000;

                
                printf("time taken = %lu.%lus\n", sec, tenthsec);
		
	}
	return (-255);   // should never reach here
>>>>>>> f6cb83413f2d2528e8d7baf581da28390840443c
}
