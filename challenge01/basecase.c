#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include "basecase.h"

// execute single command with variable amt of arguments
int base_case(const char* cmd, const char* arg) {
    printf("in base case, before fork\n");
    int cpid = fork();

    if (cpid > 0) { // parent
        printf("In parent\n");
        int status;
        waitpid(cpid, &status, 0);
        printf("Done waiting\n");
        return 0;
    }
    else if (cpid == 0) { // child
        printf("In child\n");
        // int execlp(const char *file, const char *arg0, ... /*, (char *)0 */);

        //printf("going to run command %s with argument %s\n", cmd, args[0]);
        printf("\ngoing to run command %s with argument %s\n", cmd, arg);
        //execlp("echo", "echo", "hello", NULL);
        execlp(cmd, cmd, arg, NULL);
        
        //printf("Never get here because already execued.\n");
    }

    else {
        perror("error");
        exit(1);
    }
}
