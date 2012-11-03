#include <stdio.h>
#include <arm/timer.h>

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

int main(int argc, char** argv)
{	
	float start, end;
	char inputString[50];
	while (1) {
		printf("> ");
		start = (float) (MILLIS_FROM_TICKS(time()) / 1000);
		fgets(inputString, 50, stdin);
		end = (float) (MILLIS_FROM_TICKS(time()) / 1000);
		printf("%s", inputString);
		printf("%0.1f\n", start-end);
	}
	return 0;
}
