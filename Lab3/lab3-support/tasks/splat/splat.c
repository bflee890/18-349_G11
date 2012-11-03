#include <stdio.h>

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

int main(int argc, char** argv)
{
  int i;
  char glyphArray[] = "|/-\\\b";
  while (1) {
    for (i = 0; i < 4; i++) {
      write(1, &glyphArray[i], 1);
      sleep(200);
      write(1, &glyphArray[4], 1);
    }
  }
  return 0;
}


