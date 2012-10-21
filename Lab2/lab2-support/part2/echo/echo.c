/** @file echo.c
 *
 * @author  Harry Q Bovik (Change this!)
 * @date    The current date
 */

#include "../kernel/include/bits/fileno.h"
#include "../kernel/include/bits/errno.h"
#include "../kernel/include/swi_handler.h"
int main(int argc, char** argv) {
    void* buf = (void*) (argv + argc*sizeof(char**));
    size_t buf_size; 
    ssize_t n = read(STDIN_FILENO,buf,buf_size )
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
