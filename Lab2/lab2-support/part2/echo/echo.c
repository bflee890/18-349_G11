/*
 * echo.c: Repeats what's written twice
 *
 * Author: Brandon Lee <bfl> 
 *         Christopher Palmer <ctpalmer>
 *         Joogyoon Han <jongyoo1>
 *         Lawrence Tsang <ltsang>
 *
 * Date:   Oct. 21, 2012
 *
 * When this function is called, it repeats whatever is written to STDOUT
 * through calls to the swi function read.  And after reading is completed
 * through just a newline or no bytes read, then it exits oout of the function
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
