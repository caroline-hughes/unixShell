#include "linkedl.h"

#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "linkedl.h"

linkedl* tokenize(const char* cmd);
char* read_str(const char* input, long curr_index);
linkedl* cons_token(char* token, linkedl* list);
int is_shell_op(int ch);

#endif
