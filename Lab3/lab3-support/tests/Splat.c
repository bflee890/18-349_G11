#include <stdio.h>

void Splat() {
	int i;
	char glyphArray[] = "|/-\\";
	while (true) {
		for (i = 0; i < 4; i++) {
			putchar(glyphArray[i]);
			sleep(200);
			putchar('\b');
		}
	}
}
			