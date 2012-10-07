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

int main(void) {

        char input [256];
        char output [256];
        int bytes_read;
        int i;

        while(1)
        {
                bytes_read = read(STDIN_FILENO, input, 100);     //Read an input string from STDIN 
                if(bytes_read == 1 || bytes_read == 0)           //If the input is '\n' or '', return 0 
                        return 0;
                else if(bytes_read < 0)                          //If an error occurs, return 1
                        return 1;
                for(i = 0; i < bytes_read-1; i++)                //Do ROT13 on the input string except the last character
                {                                                //which is '\n'.
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
                output[i] = '\n';                                //Put a newline character at the end of the output.
                output[i+1] = '\0';                              //Put a null character to terminate the string.

                if(write(STDOUT_FILENO, output, bytes_read) < 0) //Write an output string to STDOUT 
                        return 1;                                //Return 1 if an error occurs.
        }

         //Control never reaches here.
	return -255;
}
