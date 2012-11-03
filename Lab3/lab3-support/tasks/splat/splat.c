/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 */

int main(int argc, char** argv)
{
	int i;
	char glyphArray[] = "|/-\\";
	while (true) {
		for (i = 0; i < 4; i++) {
			putchar(glyphArray[i]);
			sleep(200);
			putchar('\b');
		}
	}
	return 0;
}
