#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "linkedl.h"
//#include "tokenize.h" // NEW

// helper functions
linkedl* cons_token(char* token, linkedl* list);
linkedl* tokenize(const char* cmd);
char* read_str(const char* cmd, long curr_index);
int is_shell_op(int curr_char);

int
main(int _argc, char* _argv[])
{

    char cmd[256];

    while (1) { // while user hasn't hit enter to indicate end of input
     printf("nush$ ");
     fflush(stdout);

     if (feof(stdin)) { // if user types cmd+D to indicate EOF
        exit(0);
     }

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
     print_order(tokens);


     printf("now lets execute a base case:\n");
     //base_case(tokens);

     printf("finally we'll free the tokens:\n");
     free_linkedl(tokens);
    }
    return 0;
}

/* string cmd (string) -> linked list of tokens
   in rev order (last token at head)
*/
linkedl* tokenize(const char* cmd) {
    linkedl* result = 0;
    int len = strlen(cmd);
    long curr_index = 0;

    while (curr_index < len) {
        if (isspace(cmd[curr_index])) {
            ++curr_index;
            continue;
        }

        // if shell operation
        if (is_shell_op(cmd[curr_index])) {
            // check if it's one of the two-char operations
            if ((cmd[curr_index] == '&' || cmd[curr_index] == '|') &&
                (curr_index+1<len && (cmd[curr_index+1] == '&' || cmd[curr_index+1] == '|'))) {
                    char* two_char_op = malloc(3);
                    memcpy(two_char_op, cmd + curr_index, 2);
                    two_char_op[2] = 0;
                    curr_index = curr_index + 2;
                    result = cons_token(two_char_op, result);
                    continue;
            }

            // else single char operation
            char op[4] = "x";
            op[0] = cmd[curr_index];
            result = cons(op, result);
            ++curr_index;
            continue;
        }

        // else command name or command argument
        char* str = read_str(cmd, curr_index);
        curr_index += strlen(str);
        result = cons_token(str,result);
     }
     return result;
}

/* read the string of variable length
*/
char* read_str(const char* input, long curr_index) {
    int len = 0;
    while(!isspace(input[curr_index+len]) && !is_shell_op(input[curr_index+len])) {
        ++len;
    }
    char* str = malloc(len+1);
    memcpy(str, input + curr_index, len);
    str[len] = 0;
    return str;
}

/* string token to be added as head of linked list
*/
linkedl* cons_token(char* token, linkedl* list) {
    linkedl* result = cons(token, list);
    free(token);
    return result;
}

/* character -> isOperation boolean
*/
int is_shell_op(int ch) {
    return ch == '<' || ch == '>' || ch == '|' || ch == '&' || ch == ';';
}
