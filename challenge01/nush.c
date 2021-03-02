#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "linkedl.h"
#include "basecase.h"
#include "tokenize.h"

// helper functions
// linkedl* cons_token(char* token, linkedl* list);
// linkedl* tokenize(const char* cmd);
// char* read_str(const char* cmd, long curr_index);
// int is_shell_op(int curr_char);

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
void helper_main(char cmd[]) {

    /*if(!line) {
         printf("\n\nline is null!\n\n");
         exit(0);
     }
    */
     linkedl* tokens_backward = tokenize(cmd);
     linkedl* tokens = reverse_and_free(tokens_backward);
     //print_order(tokens);                               
     

     const char* head = get_head(tokens); // the command to be executed
     //linkedl* args = tokens->rest;                      // with the commands
     
     char *args[length(tokens)];
     
     // copy the strings from tokens to the array of char pointers
     int i = 0;
     for (; tokens; tokens= tokens->rest) {
        args[i] = malloc(strlen(tokens->head));
        strcpy(args[i], tokens->head);
        ++i;
     }
     
     args[i] = NULL;

     //char *const args[] = {"echo", "one", "two", NULL};

     base_case(head, args);
     
     //for (long j = 0; j < length(tokens); ++j) {
     //    free(args[j]);
     //}
     free_linkedl(tokens);
}
