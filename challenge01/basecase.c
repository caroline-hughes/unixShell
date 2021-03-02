#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

#include "basecase.h"

void check_rv(int rv);

// execute single command with variable amt of arguments
int base_case(char *const args[]) {
    // if cd or exit, don't create new process

    if (strcmp(args[0],"cd") == 0) {
        if (args[1]) {;
            chdir(args[1]);
        }
        else {
            printf("no args provided to cd\n");
            // chdir("~");
        }
        return 0;
    }
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    int cpid = fork();

    if (cpid > 0) {
        //printf("In parent\n");
        int status;
        waitpid(cpid, &status, 0);
        //printf("Done waiting\n");
        return 0;
    }
    else if (cpid == 0) {
        //printf("In child\n");        
        int rv = execvp(args[0], args);
        check_rv(rv);
        printf("Never get here because already execued.\n");
    }

    else {
        perror("error");
        exit(1);
    }
}

void check_rv(int rv) {
    if (rv == -1) {
        //perror("error"); // produce message on stderr
        exit(1);
    }
}
