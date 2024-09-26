#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../parsing/parsing.h"


int is_valid_n_flag(char *arg) {
    int i = 1;
    if (arg[0] != '-')
        return 0;
    while (arg[i]) {
        if (arg[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

void handle_echo(char **args, char **envp) {
    int i = 1;
    int newline = 1;
    char *expanded_arg;

    if (args[i] && is_valid_n_flag(args[i]))
    {
      newline = 0;
        i++;
    }
    while (args[i])
    {
        expanded_arg = expand_env_var(args[i], envp, 0);
        printf("%s", expanded_arg);
        if (args[i + 1])
            printf(" ");
        free(expanded_arg);
        i++;
    }
    if (newline)
        printf("\n");
}
