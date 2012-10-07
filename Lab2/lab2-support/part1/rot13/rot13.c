/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Group Member 1 <email address>
 *          Group Member 2 <email address>
 * Date:    The current time & date
 */

#include <stdlib.h>
#include <unistd.h>

int main(void) {

        char input [256];
        char output [256];
        int bytes_read;
        int i;

        while(1)
        {
                bytes_read = read(STDIN_FILENO, input, 100);
                if(bytes_read == 1 || bytes_read == 0)
                        return 0;
                else if(bytes_read < 0)
                        return 1;
                for(i = 0; i < bytes_read-1; i++)
                {
                        if(input[i] > 64 && input[i] < 78)
                                output[i] = input[i] + 13;
                        else if(input[i] > 77 && input[i] < 91)
                                output[i] = input[i] - 13;
                        else if(input[i] > 96 && input[i] < 110)
                                output[i] = input[i] + 13;
                        else if(input[i] > 109 && input[i] < 123)
                                output[i] = input[i] - 13;
                        else
                                output[i] = input[i];
                }
                output[i] = '\n';
                output[i+1] = '\0';
                write(STDOUT_FILENO, output, bytes_read);
        }

	return -255;
}
