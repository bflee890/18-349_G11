/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Brandon Lee <bfl> 
 *          Christopher Palmer <ctpalmer>
 *          Joogyoon Han <jongyoo1>
 *          Lawrence Tsang <ltsang>
 *
 * Date:    Oct. 7, 2012
 * 
 * A basic implementation of Caesar cipher. It reads a single line form STDIN
 * and emits an encrypted output to STDOUT. If the user types return or Ctr-D,
 * it immediately exits with the exit status of 0. If the return value of any 
 * syscall is negative, it immediately exits with the exit status of 1.
 */

<<<<<<< HEAD
#include "stdlib.h"
#include "unistd.h"
=======
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
>>>>>>> 612cb3ae1b172303b192dae381bec8b431465216
#include "../libc/include/bits/fileno.h" 
 
int main(int argc, char *argv[]) {

    char input [256];
    char output [256];
    int bytes_read;
    int i;

    //sleep(1000);
    
    for(i = 0; i < argc; i++)
    {
                printf("%s\n",argv[i]);
    } //check if arguments are correct.


    while(1)
    {
        // Reads an input from STDIN, if '\n' or '' return 0
        bytes_read = read(STDIN_FILENO, input, 100); 
        if(bytes_read == 1 || bytes_read == 0)       
            return 0;
        // If an error ocurs, return 1
        else if(bytes_read < 0)
            return 1;
        /* Do ROT13 on the input string execept last character, \n */
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
        /* Adds newline char and null char to terminate string */
        output[i] = '\n';
        output[i+1] = '\0';  

        /* Write output string to STDOUT or return 1 if error */
        if(write(STDOUT_FILENO, output, bytes_read) < 0) 
        return 1;                               
    }

    //Control never reaches here.
    return -255;
}
