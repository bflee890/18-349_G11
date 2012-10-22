/** @file echo.c
 *
 * @author  Harry Q Bovik (Change this!)
 * @date    The current date
 */

#include "stdlib.h"
#include "unistd.h"
#include "bits/fileno.h"

int main(int argc, char** argv) {

        char buf[256];
        int bytes_read;

        while(1)
        {
                bytes_read = read(STDIN_FILENO, buf, 100);
                if(bytes_read < 0) //return when error occurs.
                        return bytes_read;
                if(bytes_read == 0 || bytes_read == 1) //exit when there is no input.
                        return 0;

                if(write(STDOUT_FILENO, buf, bytes_read) < 0)
                        return bytes_read; //return when error occurs.
        }

        /* Put your code here */

        return -255;
}
