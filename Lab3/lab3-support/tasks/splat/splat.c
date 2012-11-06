/** @file splat.c
 *
 * Authors:	Brandon Lee <bfl> 
 * 			Christopher Palmer <ctpalmer>
 * 			Jongyoon Han <jongyoo1>
 *			Lawrence Tsang <ltsang>
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 */
#include "stdlib.h"
#include "unistd.h"
#include <bits/fileno.h>
#include <bits/types.h>

#include <stdlib.h>
#include <unistd.h>
#include "../libc/include/bits/fileno.h" 

int main(int argc, char** argv)
{
<<<<<<< HEAD
    int i;
    const char glyphArray[] = "|/-\\";
    const char delete[] = "\b \b";
    while (1) {
	for (i = 0; i < 4; i++) {
	    write(STDOUT_FILENO, glyphArray + i, 1);
	    sleep(20);
	    write(STDOUT_FILENO, delete, 3);
	}
    }
	/*for (j = 0; j < 4; j++) {
            write(STDOUT_FILENO, glyphArray + j, 1);
            sleep(20);
            write(STDOUT_FILENO, delete, 3);
        }*/
    return 0;
=======
  int i;
  const char glyphArray[] = "|/-\\";
  const char delete[] = "\b \b";
  while (1) {
    for (i = 0; i < 4; i++) {
      write(STDOUT_FILENO, glyphArray + i, 1);
      sleep(200);
      write(STDOUT_FILENO, delete, 3);
    }
  }
  return 0;
>>>>>>> f6cb83413f2d2528e8d7baf581da28390840443c
}


