#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#include "linkedl.h"
#include "basecase.h"
#include "tokenize.h"

void helper_main(char cmd[]);

int
main(int argc, char** argv)
{
    if (argc > 2) {
        // return invalid inputs
        printf("\n\ninvalid arguments to ./nush\n");
        printf("usage: pass a script to run or give command line inputs\n");
        exit(1);
    }


    char cmd[256];
            
    char* line;

    if (argc == 2) { // SCRIPT
            FILE* script = fopen(argv[1], "r");

            if (!script) {
                printf("\n\nfopen of script failed!\n\n");
                exit(0);
            }
            
            line = fgets(cmd, 256, script);
            while(line) {
                helper_main(line);
                line = fgets(cmd, 256, script);
           }
            //printf("no lines left\n");
            fclose(script);
        }

    // PROMPT
    else { 
        while (1) {
            printf("nush$ ");
            fflush(stdout);
            
            line = fgets(cmd, 256, stdin);
            if(!line){
                printf("\nuser indicated eof\n");
                exit(0);
            }
            helper_main(line);
        }
    }

    //printf("\nmade it to end of main \n");
    return 0;
}



// execute
void helper_main(char line[]) {

     assert(line);
    
     // print_order(tokenize(cmd);
     linkedl* tokens = reverse_and_free(tokenize(line)); 

     char *args[length(tokens)];
     
     // linkedl -> arr char pointers
     int i = 0;
     for (; tokens; tokens= tokens->rest) {
        args[i] = malloc(strlen(tokens->head));
        strcpy(args[i], tokens->head);
        ++i;
     }
     
     args[i] = NULL; // null terminate
    
     base_case(args);
     
     //for (long j = 0; j < length(tokens); ++j) {
     //    free(args[j]);
     //}
     free_linkedl(tokens);
}
