/** @file typo.c
 *
 * Authors:	Brandon Lee <bfl> 
 * 			Christopher Palmer <ctpalmer>
 * 			Jongyoon Han <jongyoo1>
 *			Lawrence Tsang <ltsang>
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <bits/fileno.h>

int main(int argc, char** argv)
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
}
