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
    while (1) {
        char* line;

        if (argc == 2) { // SCRIPT
            //printf("\n\nAT THE START OF SCRIPT\n");

            printf("the script to read from: %s\n", argv[1]);
            FILE* script = fopen(argv[1], "r");

            if (!script) {
                printf("\n\n\nfopen of script failed!\n\n\n");
                exit(0);
            }

            line = fgets(cmd, 256, script);
            if (!line) {
                printf("no lines left\n");
                fclose(script);
                exit(0);
            }
        }

        else { // PROMPT
            printf("/n/nAT THE START OF PROMPT\n");
            printf("nush$ ");
            fflush(stdout);

            if (feof(stdin)) { // if user types cmd+D to indicate EOF
                printf("\n\n\nuser quit with EOF! \n\n\n");
                exit(0);
            }

            // fgets(char * restrict str, int size, FILE * restrict stream);
            // reads at most size - 1 characters from stream and stores them in str

            line = fgets(cmd, 256, stdin);
        }


        // LOGIC TO DO FOR BOTH
        if(!line) {
            printf("\n\nline is null!\n\n");
            exit(0);
        }

        linkedl* tokens_backward = tokenize(cmd);
        linkedl* tokens = reverse_and_free(tokens_backward);
        printf("tokens have been reversed:\n");
        print_order(tokens);                                    // tokens are aleady all constants

        printf("\nnow lets execute a base case:\n");
        base_case(get_head(tokens), "hello");

        free_linkedl(tokens);
    }

    printf("\nmade it to end of main \n");
    return 0;
}



// BEFORE
/*
    else if (argc == 2) { // script was given
        // read from file... do fgets and tokenize
        printf("\nthe script to read from: %s\n", argv[1]);
        FILE* script = fopen(argv[1], "r");
        printf("\ncheck that fopen worked correctly \n");
        assert(script); // ensure fopen worked, script is non null

        while (1) { // while there are more lines
            char* input = fgets(cmd, 256, script);
            if (!input) {
                exit(0);
            }

        }


    }

    else { // prompt
        while (1) { // while user hasn't hit enter to indicate end of input
        printf("nush$ ");
        fflush(stdout);

        if (feof(stdin)) { // if user types cmd+D to indicate EOF
           exit(0);
        }

        // fgets(char * restrict str, int size, FILE * restrict stream);
        // reads at most size - 1 characters from stream and stores them in str
        char* input = fgets(cmd, 256, stdin);
        if (!input) {
            exit(0);
        }

        linkedl* tokens_backward = tokenize(cmd);
        printf("tokens right now head -> tail:\n");
        print_order(tokens_backward);

        // call reverse_and_free to get the correct order and free the OG
        linkedl* tokens = reverse_and_free(tokens_backward);
        printf("now lets reverse them:\n");

        // tokens are aleady all constants
        print_order(tokens);


     printf("now lets execute a base case:\n");
     base_case(get_head(tokens), "hello");

     printf("finally we'll free the tokens:\n");
     free_linkedl(tokens);
    }
    return 0;
}
*/
