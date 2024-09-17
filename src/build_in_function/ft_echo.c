#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

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

char *get_env_value(char *var, char **envp) {
    int i = 0;
    int var_len = strlen(var);
    while (envp[i]) {
        if (strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
            return strdup(&envp[i][var_len + 1]);
        i++;
    }
    return NULL;
}

void handle_echo(char **args, char **envp) {
    int i = 1;
    int newline = 1;

    if (args[i] && is_valid_n_flag(args[i])) {
        newline = 0;
        i++;
    }

    while (args[i]) {
        if (args[i][0] == '$')
		{
            char *env_value = get_env_value(&args[i][1], envp);
            if (env_value) {
                printf("%s", env_value);
                free(env_value);
            }
        }
		else
            printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }

    if (newline)
        printf("\n");
}