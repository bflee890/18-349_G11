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
	char glyphArray[] = "|/-\\";
	while (1) {
		for (i = 0; i < 4; i++) {
			putchar(glyphArray[i]);
			sleep(200);
			putchar('\b');
		}
	}
	return 0;
}
