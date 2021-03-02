#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include "basecase.h"

// execute single command with variable amt of arguments
int base_case(const char* cmd, const char* arg) {
    int opid = getpid();
    int opar = getppid();
    int child_pid;

    printf("IN BASE CASE \n");
    printf("Before fork\n");

    if ((child_pid = fork())) { // parent
        printf("In parent\n");
        int status;
        waitpid(child_pid, &status, 0);
        printf("Done waiting\n");
    }
    else { // child
        printf("In child\n");
        // int execlp(const char *file, const char *arg0, ... /*, (char *)0 */);

        //printf("going to run command %s with argument %s\n", cmd, args[0]);
        printf("\ngoing to run command %s with argument %s\n", cmd, arg);
        //execlp("echo", "echo", "hello", NULL);
        execlp(cmd, cmd, arg, NULL);

        //printf("Never get here because already execued.\n");
    }

    return 0;
}
