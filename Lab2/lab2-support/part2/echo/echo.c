/** @file echo.c
 *
 * @author  Harry Q Bovik (Change this!)
 * @date    The current date
 */

#include "../kernel/include/bits/fileno.h"
#include "../kernel/include/bits/errno.h"
#include "../kernel/swi_handler.h"
int main(int argc, char** argv) {
    void* buf = (void*) (argv + argc*sizeof(char**));
    size_t buf_size = 100; 
    ssize_t n = read(STDIN_FILENO,buf,buf_size );
    if (n == -EFAULT || n == - ENFILE) {
        exit(n);
        return (n);   
    }
    n = write(STDOUT_FILENO,buf,n);
    if (n == -EFAULT || n == - ENFILE) {
        exit(n);
        return (n);   
    }
    exit(0);
    return 0;
}

/*#include "stdlib.h"
#include "unistd.h"
#include "bits/fileno.h"

int main(int argc, char** argv) {

        char buf[256];
        int bytes_read;

        while(1)
        {
                bytes_read = read(STDIN_FILENO, buf, 100);
                if(bytes_read < 0) //return when error occurs.
                        return 1;
                if(bytes_read == 0 || bytes_read == 1) //exit when there is no input.
                        return 0;

                if(write(STDOUT_FILENO, buf, bytes_read) < 0)
                        return 1; //return when error occurs.
        }

        /* Put your code here */

        return -255;
}*/
