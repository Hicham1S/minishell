/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:51:39 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/10 10:51:39 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

// Define constants and structures
#define BUILTIN_NOT_FOUND -1

typedef struct s_cmd {
    char **args;        // Array of command arguments
    struct s_cmd *next; // Pointer to the next command (for pipelines)
} t_cmd;

typedef struct s_env {
    char *key;          // Environment variable key
    char *value;        // Environment variable value
    struct s_env *next; // Pointer to the next environment variable
} t_env;

typedef struct s_builtin {
    char *name;
    int (*func)(t_cmd *, t_env **);
} t_builtin;

// Mock builtin functions
int builtin_cd(t_cmd *cmd, t_env **envs) {
    (void)cmd;
    (void)envs;
    printf("Executing cd\n");
    return 0;
}
int builtin_ls(t_cmd *cmd, t_env **envs) {
    (void)cmd;
    (void)envs;
    printf("Executing ls\n");
    return 0;
}
int builtin_echo(t_cmd *cmd, t_env **envs) {
    (void)envs;
    for (int i = 1; cmd->args[i]; i++)
        printf("%s ", cmd->args[i]);
    printf("\n");
    return 0;
}
// Add other mock builtin functions if needed

// Helper functions
int handle_errors(char *path) {
    struct stat sb;

    if (stat(path, &sb) == -1)
        return (fprintf(stderr, "Error: %s: %s\n", path, strerror(errno)), EXIT_FAILURE);
    if (S_ISDIR(sb.st_mode))
        return (fprintf(stderr, "Error: %s: Is a directory\n", path), 126);
    if (access(path, X_OK) != 0)
        return (fprintf(stderr, "Error: %s: Permission denied\n", path), 126);
    return EXIT_SUCCESS;
}

int exec_builtin(t_cmd *cmd, t_env **envs) {
    t_builtin builtin[3] = {
        {.name = "cd", .func = builtin_cd},
        {.name = "echo", .func = builtin_echo},
        {.name = "ls", .func = builtin_ls},
    };

    for (size_t i = 0; i < 2; i++) {
        if (strcmp(builtin[i].name, cmd->args[0]) == 0)
            return builtin[i].func(cmd, envs);
    }
    return BUILTIN_NOT_FOUND;
}

int exec_cmd(t_cmd *cmds, t_env **envs) {
    int backups[2];
    int exit_status;

    backups[0] = dup(STDIN_FILENO);
    backups[1] = dup(STDOUT_FILENO);
    exit_status = exec_builtin(cmds, envs);
    dup2(backups[0], STDIN_FILENO);
    dup2(backups[1], STDOUT_FILENO);
    close(backups[0]);
    close(backups[1]);
    return exit_status;
}

// Main function for testing
int main() {
    t_cmd cmd;
    char *args[] = {"ls", NULL, NULL};
    cmd.args = args;
    cmd.next = NULL;

    t_env *envs = NULL;

    int result = exec_cmd(&cmd, &envs);
    printf("Execution result: %d\n", result);

    return 0;
}
